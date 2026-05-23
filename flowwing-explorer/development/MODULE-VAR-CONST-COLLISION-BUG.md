# Module-level `var` / `const` collide across modules (open bug)

## Summary

Two modules each declaring a top-level `var` (or `const`) with the same identifier silently collide at link time. Reads of either module's variable resolve to whichever module's `.o` is loaded first by the linker — the second module's storage is unreachable from user code.

Discovered 2026-05-24 while fixing the cross-module **class** collision (which is now patched — see `tests/fixtures/LatestTests/BringTests/01_ok/module_class_collision.fg` and `module_class_same_init_signature.fg`). The class fix uses module-qualified mangling on `__vt_<module>.<Class>` and `<module>.<Class>.<method>.<params>` symbols; the same approach for module-level `var`/`const` is needed but isn't shipped here.

## Minimal repro

`/tmp/probe/mod_a.fg`:
```
module [probe_a]
var shared_var: int = 111
const SHARED_CONST: int = 1111
fun shared_fn(x: int) -> int { return x + 1 }
```

`/tmp/probe/mod_b.fg` (parallel, different values):
```
module [probe_b]
var shared_var: int = 222
const SHARED_CONST: int = 2221
fun shared_fn(x: int) -> int { return x + 2 }
```

`/tmp/probe/main.fg`:
```
bring "mod_a.fg"
bring "mod_b.fg"
bring io

fun fg_main() -> nthg {
    io::printLogln("var_a = " + probe_a::shared_var, "cyan")
    io::printLogln("var_b = " + probe_b::shared_var, "cyan")
    io::printLogln("const_a = " + probe_a::SHARED_CONST, "cyan")
    io::printLogln("const_b = " + probe_b::SHARED_CONST, "cyan")
    var n: int = 10
    io::printLogln("fn_a(10) = " + probe_a::shared_fn(n), "cyan")
    io::printLogln("fn_b(10) = " + probe_b::shared_fn(n), "cyan")
}
fg_main()
```

Compile + run with the post-fix Flow-Wing 1.0.5 (the class-collision build):
```
$ flowwing main.fg -o probe && ./probe
var_a = 222
var_b = 222          ← BUG: should be 222 only on b
const_a = 2221
const_b = 2221       ← BUG: should be 2221 only on b
fn_a(10) = 11        ← OK (functions already module-prefixed)
fn_b(10) = 12        ← OK
```

(Which value "wins" — 111 vs 222 — depends on link order. Either way the OTHER module's storage is shadowed.)

## Status of related symbols

| Item | Status | Why |
|------|--------|-----|
| Class methods / `init` | ✓ FIXED | Mangle = `<module>.<Class>.<method>.<params>` |
| Class vtable (`__vt_`) | ✓ FIXED | `__vt_<module>.<Class>` |
| Class field/member variables | ✓ Always OK | Struct-index access, no link symbol |
| Module free functions | ✓ Always OK | Already `<module>_fw_<name>` pre-fix (`FunctionDeclarationAnalyzer.cpp:159`) |
| **Module `var`** | ❌ COLLIDES | Emits `_init_global_var_<name>` (no module prefix); WeakODRLinkage de-dups silently |
| **Module `const`** | ❌ COLLIDES | Same path as `var` |

## Root cause

`src/IRGen/GlobalDeclarationsInitializer/GlobalDeclarationsInitializer.cpp::emitGlobalVariableForSymbol` builds the LLVM global as:

```cpp
auto *globalVar = new llvm::GlobalVariable(
    *module, llvm_type, is_llvm_constant,
    llvm::GlobalValue::ExternalLinkage,
    imported ? nullptr : default_value,
    "_init_global_var_" + variable_symbol->getName());
```

`variable_symbol->getName()` is the unqualified identifier (`"shared_var"`). Two modules both produce `_init_global_var_shared_var`. WeakODRLinkage tells the linker to pick one and discard the rest — silent.

Even if the LLVM global is renamed (e.g. `_init_global_var_<module>.<name>`), the read side also fails: in the same file `declareGlobalVariablesFromSymbolTable`'s dedup check at the top:

```cpp
if (m_ir_gen_context.getSymbol(name)) {
    return;  // already emitted in this TU, skip
}
```

uses `name` (the symbol's unqualified name) as the IRGen context's symbol-map key. When iterating probe_b's module table after probe_a's, `getSymbol("shared_var")` returns probe_a's already-emitted global and probe_b's extern is never declared in the user TU — so user code loading `probe_b::shared_var` ends up pointing at probe_a's storage.

Per-TU IR observation (this was the giveaway):
```llvm
@_init_global_var_shared_var = external global i32      ; only ONE extern declared
%global_load  = load i32, ptr @_init_global_var_shared_var   ; probe_a::shared_var
%global_load3 = load i32, ptr @_init_global_var_shared_var   ; probe_b::shared_var (wrong!)
```

## Sketch of a complete fix (NOT applied)

Touching only the LLVM symbol name is not enough — the IRGen symbol-table key and all `getSymbol` / `setSymbol` call sites that use `variable_symbol->getName()` also need to switch to a qualified key. Specifically:

1. **`VariableSymbol.hpp`** — add `m_module_name` + `setModuleName()` + `getQualifiedName()` returning `<module>.<name>` (mirrors what's already on `ClassType`).
2. **`VariableDeclarationBinder.cpp:71`** — after constructing the `VariableSymbol`, call `variable_symbol->setModuleName(*m_context->peekModuleName())` when inside a module.
3. **`GlobalDeclarationsInitializer.cpp::emitGlobalVariableForSymbol`** — use `getQualifiedName()` for both the LLVM global name and the `setSymbol` key.
4. **`GlobalDeclarationsInitializer.cpp::declareGlobalVariablesFromSymbolTable`** — key the `getSymbol(name)` / `llvm_module->getGlobalVariable(name, true)` dedup checks by `getQualifiedName()` so probe_b doesn't suppress its own extern when probe_a already emitted one with the same unqualified name.
5. **`VariableDeclarationIrGen.cpp:83,93,121,131`** — `getSymbol`/`setSymbol` calls also use `getQualifiedName()`.

All five edits were prototyped during the class-fix session. Edits 1-3 worked in isolation (distinct LLVM symbols verified via `nm`) but the read side still resolved to the first module's global — edit 4 plus a likely-missed sixth site for ModuleAccess resolution is needed to fully close the loop. Suspect there's an identifier-resolution path in `IdentifierExpressionIrGen.cpp:33` (`getSymbol(symbol->getName())`) that also needs the qualified key when the symbol came in via a module-access.

## Workarounds

Until fixed:

- Don't share module-level identifier names for `var`/`const` across modules in the same program. Prefer per-module unique names (e.g. `probe_a_shared_var`).
- Wrap state in a `class` and access via methods — class methods + vtable are module-prefixed correctly.
- Or expose state via `fun getX() -> int { return X }` — module-level free functions are already module-prefixed.

## Impact on current work

The portfolio's `server.fg` (`/Users/apple/code/per/me/server.fg`) and the upstream `fw-modules/mongo_module/mongo-module.fg` do not declare any module-level `var`/`const` that would collide with another module — both keep state inside classes (`mongo::Client`, etc.) and call libmongoc through extern declarations. The mongo binding work is **not blocked** by this bug.
