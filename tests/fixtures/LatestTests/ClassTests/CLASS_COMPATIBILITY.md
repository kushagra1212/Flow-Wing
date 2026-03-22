# Class compatibility / legacy parity

## Implemented (current compiler)

| Feature | Notes |
|--------|--------|
| Methods without `fun` | Class body: `name(` … parsed like `fun name(` … |
| Multiple `init` overloads | `ClassType::resolveMethod*` + mangled names |
| Default parameters on `init` | Semantic + **IR** `visit(BoundNewExpression)` fills missing visible args from `ParameterSymbol` defaults |
| Implicit `self` (`x` → `self.x`) | When `self` is in scope and name is an instance field symbol |
| `super(args)` | Keyword `super`; **only** inside `init`; resolves **immediate** base class `init` and passes `self` last (`CallExpressionBinder::bindSuperInitCall`) |
| `extends` / field layout | Root class has hidden **vptr** (`i8*`) at LLVM struct index 0; derived layouts prefix-copy base; `getMemberFieldIndex` / `getLLVMFieldCount` |
| **Subtyping** | `ClassType::operator<=`: a derived class type is compatible where a base class type is expected (variables, parameters, `new Derived()` assigned to `Base`) |
| **Dynamic / virtual dispatch** | Per-class vtable globals (`__vt_<ClassName>`), vptr stored on `new`; **member calls** use indirect call when the receiver is **not** a bare `self` identifier and the method has a vtable slot (skips `init`). See `UserDefinedOrExternalFunctionCall.cpp`, `GlobalDeclarationsInitializer`, `ClassType::getVtableEntries`. |

## Not implemented (optional / dialect-specific)

| Item | Notes |
|------|--------|
| `super.method()` / base **method** calls | Only `super(...)` for **base `init`** is supported, not qualified base method dispatch. |
| “Large” graphs as a language feature | N/A — use **stress** fixtures (`13_stress/`) for scale; compiler has no extra API. |

## Error tests

`tests/fixtures/ErrorTest` includes `SuperCallOutsideConstructor.fg` and other class rules — run with the **diagnostic** harness, not as success tests in `LatestTests/ClassTests`.

## Implementation pointers (code)

- Vtable layout / slots: `src/common/types/ClassType/ClassType.{hpp,cpp}`
- LLVM struct + vptr: `src/IRGen/LLVMTypeBuilder/LLVMTypeBuilder.cpp` (`convertClass`)
- Vtable globals: `src/IRGen/GlobalDeclarationsInitializer/GlobalDeclarationsInitializer.cpp`
- `new` stores vptr: `src/IRGen/IRGenerator/IRGenerator.cpp` (`visit(BoundNewExpression)`)
- Virtual vs static member calls: `src/SemanticAnalyzer/SyntaxBinder/.../CallExpressionBinder.cpp` (`bindMemberFunctionCall`)
- Indirect call: `src/IRGen/IRGenerator/IRGenHelper/UserDefinedOrExternalFunctionCall.cpp`
