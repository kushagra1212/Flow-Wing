# Flow-Wing Documentation Overhaul — Design Spec

**Date:** 2026-04-27
**Scope:** All docs + cross-reference against all test fixtures
**Tone:** Warm professional (clean, crisp, light humor via subtle asides)
**Approach:** Full refresh — fix bugs, restructure, add missing pages, validate against tests

---

## Goals

1. Fix all semantic errors (contradictions, dead code, wrong values)
2. Fix all grammar, typos, naming errors
3. Align every code example with actual Flow-Wing behavior (verified via test fixtures)
4. Restructure where files are too small, misnamed, or misorganized
5. Apply consistent warm-professional tone throughout
6. Add missing content where docs are stubs (Syntax Overview, Game page, multiple constructors)
7. Zero broken links; Docusaurus redirects for all renamed URLs

---

## Structural Changes

### Directory renames

| Before | After | Reason |
|--------|-------|--------|
| `Advance/` | `Advanced/` | Grammar fix |
| `Creating an Server/` | `Creating a Server/` | Grammar fix |
| `BuiltIn Libraries/` | `Built-in Libraries/` | Standard hyphenation |
| `Custom Type and Objects/` | `Custom Types and Objects/` | Plural consistency |

### Merge stubs

- `Single Line Comment.md` + `Multi Line Comment.md` → `Comments.md`
- `Objects.md` + `Custom Types.md` → `Custom Types and Objects.md`

### New pages

- `Functions/Function Types.md` — document `[(params) -> ret]` syntax
- `Containers/2D Containers.md` — 2D arrays before 4D
- `Writing Good Code.md` — conventions, patterns, debugging tips

### Redirects

All renamed paths get `@docusaurus/plugin-client-redirects` entries.

---

## Per-File Fix Plan

### Language Fundamentals (14 files)

**Syntax Overview.md**
- Current: 19-line stub
- Fix: Add hello-world snippet, statement terminators, block delimiters, basic structure diagram

**Data Types.md**
- Fix: Move file-reading/Err example out of `null` section
- Fix: Add string indexing semantics (0-based, returns char)
- Fix: Clarify `deci` vs `deci32` tradeoffs (64-bit vs 32-bit float)
- Fix: `dyn` section — show actual dynamic operation beyond assignment
- Add: Type inference rules

**Variables and Constants.md**
- Fix: Rename "Dynamically Allocated Variables" heading (misleading)
- Fix: Grammar "but its current value" → "but its current value is"
- Add: Scope section, const vs var rationale, naming conventions

**Assignment Expressions.md**
- Fix: Align `=` vs `<-` with Operator page — tests confirm they ARE identical; remove "Full Reassignment" label in Operators.md
- Add: Compound assignment (`+=`, `-=`, etc.) docs

**Operators.md**
- Fix: Remove `^` and `~` from Arithmetic table (bitwise only)
- Fix: Delete `<-` "Full Reassignment" label (contradiction with Assignment page)
- Fix: `;` description — statement terminator, not "Return Statement terminator"
- Fix: `println(1.0 * 1.0)` output typo "1" → "1.0"
- Add: Operator precedence table
- Add: Examples for comparison, logical, bitwise operators

**Keywords.md**
- Add: Grouping by category (types, control flow, declarations)
- Add: Link each keyword to its doc page

**Flow-Wing CLI.md**
- Minor: Add `-S` flag clarification cross-ref
- Good as-is

**Classes and Objects/Class.md**
- Fix: "two methods" → "three methods" (count is wrong)
- Fix: Fill multiple constructors example (add actual second `init`) or drop heading
- Add: Access modifiers section, `self` semantics deep-dive, static methods docs

**Conditionals/Or if else Statement.md**
- Fix: Dead code example — conditions always true, `or if` never fires
- Add: Comparison to `else if`, evaluation order, short-circuit behavior

**Conditionals/Switch Statement.md**
- Fix: Title typo "Statment" → "Statement"
- Fix: Warn explicitly about duplicate cases in first example
- Add: Fallthrough behavior docs (does switch need `break`?)
- Add: `break` explanation inside switch

**Conditionals/Ternary Expression.md**
- Fix: Wrong value references in explanation text (line 56 says 10/20, should be a/b)
- Fix: Show counter-example for parenthesis warning
- Fix: Operator precedence for `+ "\n"` ambiguity
- Fix: Remove redundant second Toast warning

**Containers/1D Container.md**
- Fix: Unify for-loop style (with/without type annotation)
- Add: Default initialization explanation (why `[0, 0, 0, 0, 0]`)
- Add: Bounds-checking note

**Containers/Multi Dimensional Container.md**
- Add: 2D example before 4D
- Add: Output for example
- Fix: Unify loop variable style

**Containers/Fill Expression.md**
- Fix: Explain partial overwrite behavior (2-fill on 3-element array leaves 3rd element)
- Clarify: `[count fill value]` syntax order

**Loops/For Loop.md**
- Fix: "steper" typo → "step" (all occurrences)
- Add: Descending loop example (`10 to 0 : -1`)
- Add: `break`/`continue` in for-loop context

**Loops/While Loop.md**
- Add: `while true` / infinite loop pattern
- Add: Nested loop example

**Functions/Declare and Define Functions.md**
- Fix: Explain `return :` syntax (early return with void value)
- Fix: Explain `decl` keyword (forward declaration / FFI)
- Fix: Punctuation "is declared. but not defined."
- Add: Rationale for `inout` recommendation (performance, mutation semantics)
- Add: Function overloading info (is it supported?)
- Add: Lambda/anonymous function reference → new Function Types page

**Functions/Builtin Functions.md**
- Move: `super` section → Inheritance page
- Add: `Int8()`, `Int64()`, `Char()` conversion examples
- Fix: Clarify `input()` note — mention `io::readLine()`
- Add: `println` documentation (used in many examples, never explained)
- Add: `print` documentation (used everywhere, never formally introduced)

### Advanced (5 files)

**Bring Import Exports.md**
- Add: Show choosy_lib.fg content inline in doc
- Add: Clarify path resolution rules
- Add: Circular import warning

**Choosy Imports.md**
- Fix: "fictive" → "fictitious"
- Consolidate: Reduce overlap with Bring page
- Add: `expose` rules for same-named functions across files

**Creating and Using Modules.md**
- Fix: Clarify `local::` qualification — when needed vs optional
- Add: Module initialization order
- Add: Module re-export pattern

**Inheritance.md**
- Fix: Misspelled car names (Toyota→Toyota, Camry→Camry)
- Fix: `fg_main` vs top-level code relationship
- Add: `super` in overridden methods
- Deduplicate: Merge repeated Vehicle/Car code blocks

**Passing Functions as Arguments.md**
- Fix: "Hehe" vs "Hello" contradiction in explanation vs code
- Add: Function type syntax formal section before complex example
- Add: Simple first example (single-param callback) before the 5-param one

### Getting Started & Introduction (4 files)

**Overview.md**
- Add: Hello-world code snippet showing what Flow-Wing looks like
- Add: Brief syntax teaser

**Key Features.md**
- Add: Code example per feature listed
- Fix: Reduce excessive bold formatting

**Installation.md**
- Fix: "can update slower" → "may be slower to update"
- Fix: Explain Python 3 role in build process

**Hello World Example.md**
- Fix: Use proper code block language label
- Add: `fg_main` example with command-line args
- Fix: "unstable" → "temporary" for auto-generated hash names

### Example Projects (2 files)

**Creating a Game.md**
- Critical: Add actual Flow-Wing raylib code — currently zero `.fg` examples
- Fix: Broken iframe video embed
- Fix: Clarify platform-specific library names

**Creating a Server.md**
- Fix: Explain `return :` syntax
- Fix: Directory name grammar (already handled by rename)
- Add: Error handling example for `accept()`

### Built-in Libraries (8 files)

**Vec Module.md**
- Fix: Merge redundant examples into one consolidated example
- Add: Output for all examples
- Fix: "Dynamically typed at the value level" → "Vec holds values of any type"
- Add: Performance table (O(1) push, O(n) insert, etc.)
- Add: Note about iteration support (for-loop compatibility)

**Text Module.md**
- Fix: Remove misleading internal note about filename ("str Module.md" vs "Text Module.md")
- Add: Complete function list with descriptions
- Add: Substring, split, join examples
- Fix: Remove release-hedging language ("names not guaranteed every release")

**Map Module.md**
- Add: Examples for `getOr`, `has`, `remove`, `clear`
- Fix: Clarify "convenience over map::..."
- Add: Iteration example over keys/values

**File Handling Module.md**
- Add: Stateful `file::File` example (open/readLine/close)
- Fix: Unused `ok` variable in example

**Err Module.md**
- Fix: Replace pseudocode in pattern section with real Flow-Wing code
- Add: Complete error code list
- Fix: Clarify `withMessage`/`withDetails` return semantics (modify in place or return new?)

**Sys Module.md**
- Fix: Probable off-by-one in for-loop example (count vs index)
- Fix: `//` comment → `/;` (Flow-Wing syntax, not C syntax)
- Add: Environment variable and working directory docs (if implemented)

**Io Module.md**
- Fix: Note about Err module capitalization inconsistency (`bring Err` vs `bring io`)
- Add: Logging output examples
- Add: Clarify `print` vs `printLog` difference (stderr vs stdout?)

**Json Module.md**
- Good as-is generally
- Add: Note about single quotes in string literals for JSON
- Add: `boolVal` property docs
- Add: Pretty-print option if exists

---

## Tone Guidelines

- **Warm professional** voice throughout
- No forced jokes or cringe
- Subtle humor through analogy and phrasing, not through variable names or Easter eggs
- Active voice, direct address ("you write...", not "one writes...")
- Short paragraphs, clear headings, generous code examples
- Every concept introduced with a code snippet
- "Here's how it works:" → code → explanation pattern

---

## Cross-Reference Methodology

1. For each code example in docs, find matching test fixture in `tests/fixtures/LatestTests/`
2. Run `make test-aot FILTER=<FeaturePattern>` to confirm expected behavior
3. Doc example output must match `.expect` file output
4. Doc syntax must match syntax found in passing test fixtures (ground truth)
5. If doc claims behavior X but tests show behavior Y → fix doc to match tests
6. Document feature as "not supported" if tests show error/absent feature

### Key test directories per doc category

| Doc category | Test directory |
|-------------|---------------|
| Data types, variables | `VariableDeclarationTests/`, `ConstVariableDeclarationTests/`, `DynamicVariableTests/` |
| Operators | `BinaryOperationLiteralTests/`, `UnaryOperationLiteralTests/` |
| Functions | `FunctionTests/` (445 files — largest) |
| Classes/OOP | `ClassTests/` (176 files) |
| Objects/Types | `ObjectTests/` (173 files) |
| Conditionals | `IfStatementTests/`, `TernaryTests/`, `SwitchTests/` |
| Loops | `ForTests/`, `WhileTests/` |
| Arrays | `ArrayTests/`, `ContainerTests/` |
| Modules/Import | `BringTests/`, `ModuleTests/` |
| Built-in libraries | `ErrModuleTests/`, `FileModuleTests/`, `IoModuleTests/`, `JsonModuleTests/`, `MapModuleTests/`, `VecModuleTests/`, `SysModuleTests/`, `StrModuleTests/` |
| Type conversion | `TypeConversionFunctionTests/` |

---

## Verification Steps

1. `cd FlowWing-Docs && yarn install && yarn start` — dev server starts, no errors
2. `yarn build` — production build succeeds, zero broken links
3. `make test-aot` — all tests pass (docs changes don't break compiler)
4. Spot-check: 20 random doc code examples verified against test fixture outputs
5. All renamed URLs resolve with 301 redirects
6. Sidebar navigation intact after merge/structure changes

---

## Implementation Phases

Executing all changes in one pass is impractical. Ordered by impact:

**Phase 1: Critical semantic fixes** (highest impact)
- `=` vs `<-` contradiction (Operators.md + Assignment Expressions.md)
- `^` in two tables (Operators.md)
- Dead `or if` example
- "Hehe" vs "Hello" mismatch (Passing Functions as Arguments.md)
- Wrong ternary explanation text
- `return :` syntax documentation (Functions + Server pages)

**Phase 2: Grammar, typos, naming**
- Directory renames: `Advance/`→`Advanced/`, `Creating an Server/`→`Creating a Server/`, `BuiltIn Libraries/`→`Built-in Libraries/`
- All typos: "Statment", "steper", "fictive", car name misspellings
- File name fixes, heading fixes, grammar fixes

**Phase 3: Structure (merge stubs, add pages, redirects)**
- Merge Comment stubs → `Comments.md`
- Merge Objects + Custom Types → single page
- Add new pages: Function Types, 2D Containers, Writing Good Code
- Set up redirect plugin

**Phase 4: Complete missing content**
- Syntax Overview stub → real overview with code
- Game page → actual raylib `.fg` code example
- Multiple constructors example → real second `init`
- `println`/`print` formal documentation
- All missing conversion function examples
- Module docs with complete function lists

**Phase 5: Tone polish + cross-reference**
- Apply warm-professional tone consistently across all files
- Verify 20+ code examples against passing test fixtures
- Run full `make test-aot` to confirm nothing broke
- Final `yarn build` with zero broken links

---

## Risks & Mitigations

| Risk | Mitigation |
|------|-----------|
| Renamed URLs break external links | Docusaurus `@docusaurus/plugin-client-redirects` handles all renames |
| Cross-referencing 2,662 tests is time-consuming | Focus on representative samples per feature; use test runner's `--filter` to batch-verify |
| `yarn build` fails due to broken internal links | Fix links as part of per-file pass; run build after each major section |
| Tone inconsistency across files | Write a short tone guide and apply as final pass |
