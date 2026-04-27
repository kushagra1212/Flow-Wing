# Flow-Wing Documentation Overhaul — Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Fix all semantic errors, grammar, structure, and missing content across 39 doc files; align all code examples with actual Flow-Wing behavior verified against test fixtures; apply consistent warm-professional tone.

**Architecture:** Sequential 5-phase plan. Each phase builds on prior. Phase 1 fixes critical semantic bugs that block correctness. Phase 2 fixes grammar/typos/naming. Phase 3 restructures directories and merges stubs. Phase 4 adds missing content and new pages. Phase 5 polishes tone and cross-references against tests.

**Tech Stack:** Docusaurus 3.x, MDX/Markdown, React CodeBlock components, yarn, TypeScript

---

### Task 1: Fix `=` vs `<-` contradiction

**Files:**
- Modify: `FlowWing-Docs/docs/Language Fundamentals/Operators.md`
- Modify: `FlowWing-Docs/docs/Language Fundamentals/Assignment Expressions.md`

- [ ] **Step 1: Read both files to understand current state**

Run: `cd FlowWing-Docs && grep -n '<-\|Full Reassignment\|identical' "docs/Language Fundamentals/Operators.md" "docs/Language Fundamentals/Assignment Expressions.md"`

- [ ] **Step 2: Fix Operators.md — remove `<-` "Full Reassignment" label**

In `Operators.md`, find the table row containing `<-` labeled as "Full Reassignment". Change it to match Assignment Expressions.md truth: `=` and `<-` are identical. Remove "Full Reassignment" label, replace with "Assignment (same as `=`)".

- [ ] **Step 3: Fix Operators.md — remove `^` and `~` from Arithmetic table**

`^` and `~` appear in both Arithmetic and Bitwise tables. Remove them from Arithmetic table (lines ~18-19). They stay only in Bitwise table (lines ~54).

- [ ] **Step 4: Fix Operators.md — `;` description**

Change `;` description from "Return Statement terminator" to "Statement terminator".

- [ ] **Step 5: Fix Operators.md — `println` output typo**

In the arithmetic example code block, change `/; Output: 1` to `/; Output: 1.0` (to match `println(1.0 * 1.0)`).

- [ ] **Step 6: Add operator precedence table to Operators.md**

Insert after the Miscellaneous section:

```markdown
## Operator Precedence

Operators evaluate in this order, highest to lowest:

| Precedence | Operators |
|------------|-----------|
| 1 (highest) | `()`, `[]`, `.`, `::` |
| 2 | `-` (unary), `!`, `~`, `+` (unary) |
| 3 | `*`, `/`, `//`, `%` |
| 4 | `+`, `-` (binary) |
| 5 | `<`, `<=`, `>`, `>=` |
| 6 | `==`, `!=` |
| 7 | `&&` |
| 8 | `\|\|` |
| 9 (lowest) | `=`, `<-`, `+=`, `-=`, `*=`, `/=` |
```

- [ ] **Step 7: Verify — run doc build**

Run: `cd FlowWing-Docs && yarn build`

Expected: Build succeeds, no broken links.

- [ ] **Step 8: Commit**

```bash
git add FlowWing-Docs/docs/Language\ Fundamentals/Operators.md
git commit -m "docs: fix operator table contradictions (= vs <-, ^ in two tables, ; label, precedence)"
```

---

### Task 2: Fix `or if` dead code example

**Files:**
- Modify: `FlowWing-Docs/docs/Language Fundamentals/Conditionals/Or if else Statement.md`

- [ ] **Step 1: Read the file**

- [ ] **Step 2: Verify against test fixtures**

Run: `make test-aot FILTER="OrIf\|or_if"`

Check how `or if` actually works in passing tests. The existing example has `x=10` and `y=20` with condition `x == 10 || y == 20` — always true, so `or if` branch never fires. Fix by changing values so both branches can be taken.

- [ ] **Step 3: Rewrite example with real branching**

Replace the example code block with:

```flowwing
var x: int = 10
var y: int = 10

if (x == 10) {
    print("x is 10")
} or if (y == 20) {
    print("y is 20")
} else {
    print("neither condition matched")
}
```

Output: `x is 10`

- [ ] **Step 4: Add second example showing `or if` branch taken**

```flowwing
var a: int = 5

if (a > 10) {
    print("greater than 10")
} or if (a > 3) {
    print("a is between 4 and 10")
} else {
    print("a is 3 or less")
}
```

Output: `a is between 4 and 10`

- [ ] **Step 5: Add comparison to `else if`**

Add a note: `or if` is Flow-Wing's equivalent of `else if` in other languages. Conditions evaluate top-to-bottom; first matching branch runs.

- [ ] **Step 6: Verify**

Run: `cd FlowWing-Docs && yarn build`
Run: `make test-aot FILTER="OrIf\|or_if"`

- [ ] **Step 7: Commit**

```bash
git add FlowWing-Docs/docs/Language\ Fundamentals/Conditionals/Or\ if\ else\ Statement.md
git commit -m "docs: fix or-if dead code example, add second example, add else-if comparison"
```

---

### Task 3: Fix wrong ternary explanation text

**Files:**
- Modify: `FlowWing-Docs/docs/Language Fundamentals/Conditionals/Ternary Expression.md`

- [ ] **Step 1: Read the file to find the bug**

The text around what is now line 56 says "if first condition is true, `10` is returned. If first condition is false, `20` is returned." But the adjacent example calls `max(a, b)` with ternary `a > b ? a : b`. Fix text to refer to the correct variables.

- [ ] **Step 2: Fix explanation text**

Change to: "If `a > b` is true, `a` is returned. Otherwise, `b` is returned."

- [ ] **Step 3: Fix `+ "\n"` operator precedence ambiguity**

In the first example: `print(false ? "Hello" : "World" + "\n")`. Add parentheses or separate line to clarify intent:

```flowwing
print(false ? "Hello" : ("World" + "\n"))
```

And add a note: the `+` operator binds tighter than `?:`, so use parentheses for clarity.

- [ ] **Step 4: Add counter-example for parenthesis warning**

After the Toast warning about parentheses, add:

```flowwing
// Without parentheses — may not evaluate as you expect
var r = a > b ? a + 1 : b + 1

// With parentheses — explicit grouping
var r = (a > b) ? (a + 1) : (b + 1)
```

- [ ] **Step 5: Remove redundant second Toast warning**

Delete the duplicate `<Toast>` block that appears a second time in the file.

- [ ] **Step 6: Verify**

Run: `cd FlowWing-Docs && yarn build`

- [ ] **Step 7: Commit**

```bash
git add FlowWing-Docs/docs/Language\ Fundamentals/Conditionals/Ternary\ Expression.md
git commit -m "docs: fix ternary explanation (wrong variable refs), operator precedence, add counter-example"
```

---

### Task 4: Fix "Hehe" vs "Hello" contradiction in Passing Functions

**Files:**
- Modify: `FlowWing-Docs/docs/Advance/Passing Functions as Arguments.md`

- [ ] **Step 1: Read the file, locate the bug**

The explanation text says the callback is called with `"Hehe"` but the code calls `callback("Hello")`.

- [ ] **Step 2: Fix text to match code**

Change `"Hehe"` → `"Hello"` in the explanation paragraph.

- [ ] **Step 3: Add function type syntax introduction section**

Insert before the complex example:

```markdown
## Function Type Syntax

Flow-Wing represents function signatures with bracket notation:

```
[(param_types) -> return_type]
```

Examples:
- `[(str) -> nthg]` — function taking a string, returning nothing
- `[(int, int) -> int]` — function taking two ints, returning int
- `[(int) -> bool]` — predicate function
```

- [ ] **Step 4: Add simple one-param example before the complex one**

Insert before the `mainFunction` example:

```flowwing
fun greet(name: str) -> nthg {
    print("Hello, " + name)
}

fun runCallback(callback: [(str) -> nthg]) {
    callback("World")
}

runCallback(greet)
```

Output: `Hello, World`

- [ ] **Step 5: Verify**

Run: `cd FlowWing-Docs && yarn build`

- [ ] **Step 6: Commit**

```bash
git add FlowWing-Docs/docs/Advance/Passing\ Functions\ as\ Arguments.md
git commit -m "docs: fix Hehe/Hello mismatch, add function type syntax intro, add simple callback example"
```

---

### Task 5: Document `return :` syntax (used in 3+ files, never explained)

**Files:**
- Modify: `FlowWing-Docs/docs/Language Fundamentals/Functions/Declare and Define Functions.md`

- [ ] **Step 1: Add `return :` section**

Insert after the existing return value examples:

```markdown
### Early Return from Void Functions

For functions returning `nthg` (nothing), use `return :` to exit early:

```flowwing
fun maybePrint(shouldPrint: bool) -> nthg {
    if (!shouldPrint) {
        return :
    }
    print("Hello")
}
```

The `:` after `return` represents the absence of a value — it matches the `nthg` return type.
```

- [ ] **Step 2: Also explain `decl` keyword**

Add section:

```markdown
### Forward Declarations

Use `decl` to declare a function without defining its body. Useful for FFI or separating interface from implementation:

```flowwing
fun external_lib_func(x: int) -> int decl
fun add(x: int, y: int) -> int decl
```

The body is provided elsewhere — via a linked native library (`-l` flag) or in another file brought with `bring`.
```

- [ ] **Step 3: Fix grammar "is declared. but not defined."**

Change: "Here, the function `add` is declared. but not defined." → "Here, the function `add` is declared but not defined yet."

- [ ] **Step 4: Verify**

Run: `cd FlowWing-Docs && yarn build`

- [ ] **Step 5: Commit**

```bash
git add FlowWing-Docs/docs/Language\ Fundamentals/Functions/Declare\ and\ Define\ Functions.md
git commit -m "docs: document return : and decl keywords, fix grammar"
```

---

### Task 6: Fix Switch Statement typos and duplicate case

**Files:**
- Modify: `FlowWing-Docs/docs/Language Fundamentals/Conditionals/Switch Statement.md`

- [ ] **Step 1: Fix title typo**

Change "Switch Statment" → "Switch Statement" in heading (line ~7).

- [ ] **Step 2: Add explicit warning about duplicate cases**

Right after the first example's code block, add:

```markdown
:::warning
Duplicate `case` values are not errors, but only the first matching case executes. The second `case 1:` above is dead code.
:::
```

- [ ] **Step 3: Add `break` behavior explanation**

Add section:

```markdown
### Break in Switch

Unlike some languages, Flow-Wing switch cases **do not fall through**. Each case block is self-contained — no `break` needed between cases:

```flowwing
switch x {
    case 1: {
        print("one")
    }
    case 2: {
        print("two")
    }
}
```

Both cases are independent. The `break` keyword exits the entire switch early, useful inside nested loops:

```flowwing
while (true) {
    switch getInput() {
        case "quit": {
            break  // exits the switch, not the while
        }
    }
}
```
```

- [ ] **Step 4: Add `switch true` use case explanation**

After the `switch true` example, add: "This pattern replaces long `if/else if` chains when each case tests a different expression. It reads cleaner than nested ternaries."

- [ ] **Step 5: Verify**

Run: `cd FlowWing-Docs && yarn build`

- [ ] **Step 6: Commit**

```bash
git add FlowWing-Docs/docs/Language\ Fundamentals/Conditionals/Switch\ Statement.md
git commit -m "docs: fix Switch Statement typo, add duplicate case warning, add break behavior docs"
```

---

### Task 7: Fix For Loop "steper" typos

**Files:**
- Modify: `FlowWing-Docs/docs/Language Fundamentals/Loops/For Loop.md`

- [ ] **Step 1: Replace all "steper" → "step"**

Run: `grep -n "steper\|Steper" "FlowWing-Docs/docs/Language Fundamentals/Loops/For Loop.md"`

Replace every occurrence of "steper" with "step" and "Steper" with "Step".

- [ ] **Step 2: Add descending loop example**

Insert after the basic examples:

```flowwing
// Count down from 10 to 0
for (var i: int = 10 to 0 : -1) {
    print(i)
}
```

Output: `10 9 8 7 6 5 4 3 2 1 0`

- [ ] **Step 3: Add break/continue in for-loop**

```flowwing
// Skip even numbers
for (var i: int = 0 to 10 : 1) {
    if (i % 2 == 0) {
        continue
    }
    print(i)
}
```

Output: `1 3 5 7 9`

- [ ] **Step 4: Add `: 1` is default note**

The step `: 1` is the default. Writing `for (var i = 0 to 10)` without `: 1` is equivalent.

- [ ] **Step 5: Verify**

Run: `cd FlowWing-Docs && yarn build`

- [ ] **Step 6: Commit**

```bash
git add FlowWing-Docs/docs/Language\ Fundamentals/Loops/For\ Loop.md
git commit -m "docs: fix steper→step typos, add descending loop, break/continue in for"
```

---

### Task 8: Fix Class.md — method count, multiple constructors stub

**Files:**
- Modify: `FlowWing-Docs/docs/Language Fundamentals/Classes and Objects/Class.md`

- [ ] **Step 1: Fix method count**

Change "two methods `print` and `getAge`" → "three methods `print`, `getAge`, and `setAge`".

- [ ] **Step 2: Fill multiple constructors example or drop heading**

Check: can Flow-Wing classes have multiple `init` definitions? (Test: check `ClassTests/` for patterns with multiple init).

If yes: add a second `init` to the Person class example:

```flowwing
// Second constructor — only name, default age
fun init(name: str) -> nthg {
    self.name = name
    self.age = 0
}
```

If no: change heading from "Multiple Constructors Example" to "Constructor Example" and add note that Flow-Wing supports a single `init` per class.

- [ ] **Step 3: Add access modifiers section**

If Flow-Wing supports visibility, add docs. If not, add note: "All class members are publicly accessible in Flow-Wing."

- [ ] **Step 4: Add self semantics explanation**

Add a short section explaining `self`:
- `self` is the current instance, automatically available in all methods
- `self` is never passed explicitly — it's implicit
- Use `self.field` to access members, `self.method()` to call other methods

- [ ] **Step 5: Verify**

Run: `cd FlowWing-Docs && yarn build`

- [ ] **Step 6: Commit**

```bash
git add FlowWing-Docs/docs/Language\ Fundamentals/Classes\ and\ Objects/Class.md
git commit -m "docs: fix method count, fill multiple constructors, add self semantics"
```

---

### Task 9: Fix Data Types — move Err example, add string indexing

**Files:**
- Modify: `FlowWing-Docs/docs/Language Fundamentals/Data Types.md`

- [ ] **Step 1: Move file-reading/Err example out of `null` section**

Cut the `Err::Result` and file-reading code from the `null` section (lines ~140-155). Add a brief cross-reference: "See the [File Handling Module](../BuiltIn%20Libraries/File%20Handling%20Module) for real-world `null` and `Err` patterns."

- [ ] **Step 2: Add string indexing semantics**

After the string example, add:

```markdown
### String Indexing

Strings are 0-indexed. `name[i]` returns a `char` at position `i`:

```flowwing
var name: str = "Flow"
print(name[0])  // 'F'
print(name[3])  // 'w'
```
```

- [ ] **Step 3: Clarify `deci` vs `deci32`**

Add a note: `deci` is 64-bit (double precision), `deci32` is 32-bit (single precision). Use `deci` unless memory is tight.

- [ ] **Step 4: Improve `dyn` section**

Replace the assignment-only example with one showing dynamic operations:

```flowwing
var x = 42       // x is dyn, currently holds int
print(x + 1)     // 43 — works, x acts as int
x = "hello"      // x now holds str
print(x + "world")  // helloworld — works, x acts as str
```

- [ ] **Step 5: Verify**

Run: `cd FlowWing-Docs && yarn build`

- [ ] **Step 6: Commit**

```bash
git add FlowWing-Docs/docs/Language\ Fundamentals/Data\ Types.md
git commit -m "docs: move Err example from null section, add string indexing, clarify deci vs deci32"
```

---

### Task 10: Fix Variables and Constants — misleading heading, add scope

**Files:**
- Modify: `FlowWing-Docs/docs/Language Fundamentals/Variables and Constants.md`

- [ ] **Step 1: Fix "Dynamically Allocated Variables" heading**

Change "Dynamically Allocated Variables" → "Variable Declarations with Types" or just "Typed Variables". The section shows standard `var` declarations, not heap allocation.

- [ ] **Step 2: Fix grammar**

Change "but its current value." → "but its current value is used."

- [ ] **Step 3: Add scope section**

```markdown
### Variable Scope

Variables are scoped to the block `{ }` where they're declared:

```flowwing
{
    var x: int = 10
    print(x)  // 10
}
// x is not accessible here — out of scope
```

Variables in outer scopes are accessible in inner scopes, but inner scopes can shadow them with new declarations.
```

- [ ] **Step 4: Add `const` vs `var` rationale**

Expand the constants section: "Use `const` for values that never change — it helps the compiler optimize and prevents accidental reassignment. `var` is for mutable state."

- [ ] **Step 5: Verify**

Run: `cd FlowWing-Docs && yarn build`

- [ ] **Step 6: Commit**

```bash
git add FlowWing-Docs/docs/Language\ Fundamentals/Variables\ and\ Constants.md
git commit -m "docs: fix misleading heading, add scope section, add const vs var rationale"
```

---

### Task 11: Directory renames + redirects

**Files:**
- Rename: `FlowWing-Docs/docs/Advance/` → `FlowWing-Docs/docs/Advanced/`
- Rename: `FlowWing-Docs/docs/Creating an Server/` → `FlowWing-Docs/docs/Creating a Server/`
- Rename: `FlowWing-Docs/docs/BuiltIn Libraries/` → `FlowWing-Docs/docs/Built-in Libraries/`
- Rename: `FlowWing-Docs/docs/Language Fundamentals/Custom Type and Objects/` → `FlowWing-Docs/docs/Language Fundamentals/Custom Types and Objects/`
- Modify: `FlowWing-Docs/docusaurus.config.ts` — add redirect plugin
- Modify: `FlowWing-Docs/sidebars.ts` — if autogenerated, it auto-updates

- [ ] **Step 1: Install redirect plugin**

Run: `cd FlowWing-Docs && yarn add @docusaurus/plugin-client-redirects`

- [ ] **Step 2: Add plugin config to docusaurus.config.ts**

Add to the `plugins` array:

```typescript
[
  '@docusaurus/plugin-client-redirects',
  {
    redirects: [
      { from: '/docs/Advance', to: '/docs/Advanced' },
      { from: '/docs/Advance/Bring%20Import%20Exports', to: '/docs/Advanced/Bring%20Import%20Exports' },
      { from: '/docs/Advance/Choosy%20Imports', to: '/docs/Advanced/Choosy%20Imports' },
      { from: '/docs/Advance/Creating%20and%20Using%20Modules', to: '/docs/Advanced/Creating%20and%20Using%20Modules' },
      { from: '/docs/Advance/Inheritance', to: '/docs/Advanced/Inheritance' },
      { from: '/docs/Advance/Passing%20Functions%20as%20Arguments', to: '/docs/Advanced/Passing%20Functions%20as%20Arguments' },
      { from: '/docs/Creating%20an%20Server', to: '/docs/Creating%20a%20Server' },
      { from: '/docs/Creating%20an%20Server/Creating%20an%20Server', to: '/docs/Creating%20a%20Server/Creating%20a%20Server' },
      { from: '/docs/BuiltIn%20Libraries', to: '/docs/Built-in%20Libraries' },
      { from: '/docs/BuiltIn%20Libraries/Vec%20Module', to: '/docs/Built-in%20Libraries/Vec%20Module' },
      { from: '/docs/BuiltIn%20Libraries/Text%20Module', to: '/docs/Built-in%20Libraries/Text%20Module' },
      { from: '/docs/BuiltIn%20Libraries/Map%20Module', to: '/docs/Built-in%20Libraries/Map%20Module' },
      { from: '/docs/BuiltIn%20Libraries/File%20Handling%20Module', to: '/docs/Built-in%20Libraries/File%20Handling%20Module' },
      { from: '/docs/BuiltIn%20Libraries/Err%20Module', to: '/docs/Built-in%20Libraries/Err%20Module' },
      { from: '/docs/BuiltIn%20Libraries/Sys%20Module', to: '/docs/Built-in%20Libraries/Sys%20Module' },
      { from: '/docs/BuiltIn%20Libraries/Io%20Module', to: '/docs/Built-in%20Libraries/Io%20Module' },
      { from: '/docs/BuiltIn%20Libraries/Json%20Module', to: '/docs/Built-in%20Libraries/Json%20Module' },
      { from: '/docs/Language%20Fundamentals/Custom%20Type%20and%20Objects', to: '/docs/Language%20Fundamentals/Custom%20Types%20and%20Objects' },
      { from: '/docs/Language%20Fundamentals/Custom%20Type%20and%20Objects/Custom%20Types', to: '/docs/Language%20Fundamentals/Custom%20Types%20and%20Objects/Custom%20Types' },
      { from: '/docs/Language%20Fundamentals/Custom%20Type%20and%20Objects/Objects', to: '/docs/Language%20Fundamentals/Custom%20Types%20and%20Objects/Objects' },
    ],
  },
],
```

- [ ] **Step 3: Physically rename directories**

```bash
cd FlowWing-Docs/docs
mv "Advance" "Advanced"
mv "Creating an Server" "Creating a Server"
mv "BuiltIn Libraries" "Built-in Libraries"
mv "Language Fundamentals/Custom Type and Objects" "Language Fundamentals/Custom Types and Objects"
```

- [ ] **Step 4: Rename inner file**

```bash
cd FlowWing-Docs/docs
mv "Creating a Server/Creating an Server.md" "Creating a Server/Creating a Server.md"
```

- [ ] **Step 5: Update internal cross-reference links**

Search all `.md` files for `Advance/`, `Creating an Server/`, `BuiltIn Libraries/`, `Custom Type and Objects/` and update to new paths.

Run: `cd FlowWing-Docs && grep -r "Advance/\|Creating an Server/\|BuiltIn Libraries/\|Custom Type and Objects/" docs/`

Fix each occurrence.

- [ ] **Step 6: Verify**

Run: `cd FlowWing-Docs && yarn build`

Expected: Build succeeds with zero broken links. Redirects active.

- [ ] **Step 7: Commit**

```bash
git add FlowWing-Docs/
git commit -m "docs: rename Advance→Advanced, fix grammar in dir names, add redirects"
```

---

### Task 12: Merge comment stubs + merge Objects/CustomTypes

**Files:**
- Create: `FlowWing-Docs/docs/Language Fundamentals/Comments/Comments.md`
- Delete: `FlowWing-Docs/docs/Language Fundamentals/Comments/Single Line Comment.md`
- Delete: `FlowWing-Docs/docs/Language Fundamentals/Comments/Multi Line Comment.md`
- Modify: existing file → merge `Objects.md` and `Custom Types.md` into one
- Modify: `FlowWing-Docs/docusaurus.config.ts` — add redirects for old comment pages

- [ ] **Step 1: Create merged Comments.md**

Combine both comment files into one. Add intro explaining both types:

```markdown
---
sidebar_position: 1
title: Comments
sidebar_label: Comments
---

# Comments

Flow-Wing supports two comment styles.

## Single-Line Comments

Use `/;` to comment out the rest of a line:

```flowwing
/; This is a comment
print("Hello")  /; This part is also a comment
```

## Multi-Line Comments

Use `/#` to start and `#/` to end:

```flowwing
/#
This entire
block is a comment
#/
print("Hello")
```

Multi-line comments cannot nest.
```

- [ ] **Step 2: Add redirects for deleted comment pages**

Add to the redirects plugin config:

```typescript
{ from: '/docs/Language%20Fundamentals/Comments/Single%20Line%20Comment', to: '/docs/Language%20Fundamentals/Comments/Comments' },
{ from: '/docs/Language%20Fundamentals/Comments/Multi%20Line%20Comment', to: '/docs/Language%20Fundamentals/Comments/Comments' },
```

- [ ] **Step 3: Merge Objects.md into Custom Types.md**

Read both files. Expand `Custom Types.md` to include object creation section from `Objects.md`. Rename file to `Custom Types and Objects.md` and update title. Delete `Objects.md`.

Add redirect:

```typescript
{ from: '/docs/Language%20Fundamentals/Custom%20Types%20and%20Objects/Objects', to: '/docs/Language%20Fundamentals/Custom%20Types%20and%20Objects/Custom%20Types%20and%20Objects' },
```

- [ ] **Step 4: Verify**

Run: `cd FlowWing-Docs && yarn build`

- [ ] **Step 5: Commit**

```bash
git add FlowWing-Docs/
git commit -m "docs: merge comment stubs into Comments.md, merge Objects into Custom Types"
```

---

### Task 13: Add new pages (Function Types, 2D Containers, Writing Good Code)

**Files:**
- Create: `FlowWing-Docs/docs/Language Fundamentals/Functions/Function Types.md`
- Create: `FlowWing-Docs/docs/Language Fundamentals/Containers/2D Containers.md`
- Create: `FlowWing-Docs/docs/Writing Good Code.md`

- [ ] **Step 1: Create Function Types page**

```markdown
---
sidebar_position: 3
title: Function Types
sidebar_label: Function Types
---

# Function Types

Flow-Wing lets you pass functions as arguments using function type syntax.

## Syntax

```
[(param_types) -> return_type]
```

## Basic Callback

```flowwing
fun greet(name: str) -> nthg {
    print("Hello, " + name)
}

fun runCallback(cb: [(str) -> nthg]) {
    cb("World")
}

runCallback(greet)
```

Output: `Hello, World`

## Multi-Parameter Callbacks

```flowwing
fun add(x: int, y: int) -> int {
    return x + y
}

fun apply(op: [(int, int) -> int], a: int, b: int) -> int {
    return op(a, b)
}

var result: int = apply(add, 3, 4)
print(result)
```

Output: `7`

## Returning Functions

Use function types as return types:

```flowwing
fun getGreeter() -> [(str) -> nthg] {
    return greet
}
```

## Limitations

Flow-Wing does not currently support anonymous functions (lambdas/closures). Functions must be declared with `fun` before being passed as callbacks.
```

- [ ] **Step 2: Create 2D Containers page**

```markdown
---
sidebar_position: 1
title: 2D Containers
sidebar_label: 2D Containers
---

# Two-Dimensional Containers

Flow-Wing supports multi-dimensional arrays. Start with 2D.

## Declaration

```flowwing
var grid: int[2][3] = [[1, 2, 3], [4, 5, 6]]
```

This creates a 2×3 grid of integers.

## Access

```flowwing
print(grid[0][1])  // 2 — first row, second column
grid[1][0] = 10    // modify an element
```

## Iteration

```flowwing
for (var i: int = 0 to 1 : 1) {
    for (var j: int = 0 to 2 : 1) {
        print(grid[i][j])
    }
}
```

Output: `1 2 3 4 5 6`

## More Dimensions

See [Multi Dimensional Container](Multi%20Dimensional%20Container) for 3D, 4D, and beyond.
```

- [ ] **Step 3: Create Writing Good Code page**

```markdown
---
sidebar_position: 1
title: Writing Good Code
sidebar_label: Writing Good Code
---

# Writing Good Code in Flow-Wing

## Style Conventions

- File extension: `.fg`
- Indentation: 4 spaces (not tabs)
- Variable names: `camelCase`
- Type names: `PascalCase`
- Function names: `camelCase`

## Naming

```flowwing
/; Good
var userName: str = "Alice"
type Point = { x: int; y: int }
class HttpClient { ... }

/; Avoid
var un: str = "Alice"
type point = { X: int; Y: int }
```

## Organization

- One module per file
- `bring` imports at top
- Types and classes before functions
- `fg_main()` at bottom (or omit for scripts)

## Error Handling

Always check `Err::Result` return values:

```flowwing
var ok: bool, werr: Err::Result = file::readText("data.txt")
if (werr.isErr()) {
    printErrorLog("Failed: " + werr.message)
    return :
}
/; use ok ...
```

## Debugging

- Use `print()` for quick inspection
- Use `io::printLog()` for structured logging
- Compile with `--emit=ir` to inspect generated LLVM IR
- Run with `make run-aot-debug FILE=your.fg` for debug mode
```

- [ ] **Step 4: Verify**

Run: `cd FlowWing-Docs && yarn build`

- [ ] **Step 5: Commit**

```bash
git add FlowWing-Docs/docs/Language\ Fundamentals/Functions/Function\ Types.md
git add FlowWing-Docs/docs/Language\ Fundamentals/Containers/2D\ Containers.md
git add FlowWing-Docs/docs/Writing\ Good\ Code.md
git commit -m "docs: add Function Types, 2D Containers, and Writing Good Code pages"
```

---

### Task 14: Fix Built-in Libraries — all 8 files

**Files:**
- Modify: `FlowWing-Docs/docs/Built-in Libraries/Vec Module.md`
- Modify: `FlowWing-Docs/docs/Built-in Libraries/Text Module.md`
- Modify: `FlowWing-Docs/docs/Built-in Libraries/Map Module.md`
- Modify: `FlowWing-Docs/docs/Built-in Libraries/File Handling Module.md`
- Modify: `FlowWing-Docs/docs/Built-in Libraries/Err Module.md`
- Modify: `FlowWing-Docs/docs/Built-in Libraries/Sys Module.md`
- Modify: `FlowWing-Docs/docs/Built-in Libraries/Io Module.md`
- Modify: `FlowWing-Docs/docs/Built-in Libraries/Json Module.md`
- Reference: `fw-modules/vec_module/`, `fw-modules/text_module/`, etc. (for accurate API docs)
- Reference: `tests/fixtures/LatestTests/VecModuleTests/`, etc. (for behavior validation)

- [ ] **Step 1: Fix Vec Module.md**

Consolidate two near-identical examples into one. Add output. Fix "Dynamically typed at the value level" → "Vec holds values of any type." Add:

```markdown
## Performance

| Operation | Complexity |
|-----------|------------|
| `push()` | O(1) amortized |
| `pop()` | O(1) |
| `get()` | O(1) |
| `set()` | O(1) |
| `insert()` | O(n) |
| `removeAt()` | O(n) |
| `indexOf()` | O(n) |
| `size()` | O(1) |

## Iteration

Use a standard `for` loop with `size()`:

```flowwing
for (var i: int = 0 to v.size() - 1 : 1) {
    print(v.get(i))
}
```
```

- [ ] **Step 2: Fix Text Module.md**

Remove the misleading note about "str Module.md" vs "Text Module.md". Add complete function table:

```markdown
## Available Functions

| Function | Description |
|----------|-------------|
| `getLength(s)` | String length |
| `toUpper(s)` | Uppercase |
| `toLower(s)` | Lowercase |
| `reverse(s)` | Reverse string |
| `trim(s)` | Remove whitespace |
| `replace(s, old, new)` | Replace substrings |
| `concat(a, b)` | Concatenate |
| `charAt(s, i)` | Character at index |
| `substring(s, start, len)` | Extract substring |
| `indexOf(s, sub)` | Find substring position |
| `isEmpty(s)` | Check if empty |
```

Add substring and split examples.

- [ ] **Step 3: Fix Map Module.md**

Add examples for all operations:

```flowwing
var m = map::newMap()
m.set("name", "Alice")
m.set("age", 30)

var hasName: bool = m.has("name")  // true
var name = m.get("name")           // "Alice"
m.remove("age")
m.clear()
```

Add iteration example. Clarify "convenience over map::...".

- [ ] **Step 4: Fix File Handling Module.md**

Add stateful File example:

```flowwing
var f = file::open("data.txt")
while (!f.isEOF()) {
    var line = f.readLine()
    print(line)
}
f.close()
```

Fix unused `ok` variable in existing example — actually use it in the happy path.

- [ ] **Step 5: Fix Err Module.md**

Replace pseudocode with real code. Add complete error code list from `fw-modules/error_module/`. Clarify `withMessage` returns a new `Result`, doesn't modify in place.

- [ ] **Step 6: Fix Sys Module.md**

Fix probable off-by-one: `for (var i = 0 to sys::getArgCount() - 1)` not `count` (inclusive range needs `count - 1`). Fix `//` comment → `/;`. Add environment variable docs if `sys` module has them.

- [ ] **Step 7: Fix Io Module.md**

Add logging output examples. Clarify `print` (stdout, no prefix) vs `printLog` (stdout, with formatting). Note about Err capitalization.

- [ ] **Step 8: Fix Json Module.md**

Add `boolVal` property docs. Add single-quote note. If pretty-print exists in module, document it.

- [ ] **Step 9: Verify**

Run: `cd FlowWing-Docs && yarn build`
Run: `make test-aot FILTER="VecModule\|StrModule\|MapModule\|FileModule\|ErrModule\|SysModule\|IoModule\|JsonModule"`

- [ ] **Step 10: Commit**

```bash
git add FlowWing-Docs/docs/Built-in\ Libraries/
git commit -m "docs: fix all 8 Built-in Libraries pages — examples, output, API completeness"
```

---

### Task 15: Fix remaining Language Fundamentals files

**Files:**
- Modify: `FlowWing-Docs/docs/Language Fundamentals/Syntax Overview.md`
- Modify: `FlowWing-Docs/docs/Language Fundamentals/Keywords.md`
- Modify: `FlowWing-Docs/docs/Language Fundamentals/Flow-Wing CLI.md`
- Modify: `FlowWing-Docs/docs/Language Fundamentals/Containers/1D Container.md`
- Modify: `FlowWing-Docs/docs/Language Fundamentals/Containers/Fill Expression.md`
- Modify: `FlowWing-Docs/docs/Language Fundamentals/Functions/Builtin Functions.md`
- Modify: `FlowWing-Docs/docs/Advanced/Inheritance.md` (move `super` section here from Builtin Functions)
- Modify: `FlowWing-Docs/docs/Language Fundamentals/Loops/While Loop.md`

- [ ] **Step 1: Rewrite Syntax Overview.md from stub**

Replace 19-line stub with:

```markdown
---
sidebar_position: 1
title: Syntax Overview
sidebar_label: Syntax Overview
---

# Syntax Overview

Here's what Flow-Wing looks like:

```flowwing
var name: str = "World"
print("Hello, " + name)
```

Flow-Wing is **statically typed**, **case-sensitive**, and **whitespace-insensitive**. Think of it as a modern C with garbage collection.

## Basic Structure

```flowwing
/; Imports
bring someModule

/; Types
type Point = { x: int; y: int }

/; Functions
fun greet(name: str) -> nthg {
    print("Hello")
}

/; Entry Point
fun fg_main() -> int {
    greet("World")
    return 0
}
```

## Quick Reference

| Element | Syntax |
|---------|--------|
| Variable | `var x: int = 42` |
| Constant | `const x: int = 100` |
| Function | `fun name(p: Type) -> RetType { }` |
| Type | `type Name = { field: Type }` |
| Class | `class Name { }` |
| If | `if (cond) { } or if (cond) { } else { }` |
| While | `while (cond) { }` |
| For | `for (var i = 0 to 10 : 1) { }` |
| Switch | `switch val { case v: { } default: { } }` |
| Comment (line) | `/; comment` |
| Comment (block) | `/# comment #/` |
| Import | `bring "file.fg"` or `bring {a, b} from mod` |
```

- [ ] **Step 2: Fix Keywords.md — add grouping and links**

Group keywords by category with a table per category. Link each to its doc page.

- [ ] **Step 3: Fix Flow-Wing CLI.md — add -S clarification**

Minor: cross-reference to Server page for `-S` flag behavior.

- [ ] **Step 4: Fix 1D Container.md — unify for-loop style**

Make all for-loops use the same style (with type annotation). Add note: the `: 1` step is default and can be omitted.

- [ ] **Step 5: Fix Fill Expression.md — explain partial overwrite**

Add explicit explanation: "If `fill` count is less than array size, remaining elements keep their old values. If count exceeds, it's an error."

- [ ] **Step 6: Fix Builtin Functions.md — add println, print docs**

Move `super` section to Inheritance page. Add:

```markdown
## `print()` and `println()`

Both accept any number of arguments. `print()` outputs without a newline; `println()` appends one.

```flowwing
print("Hello ")    /; No newline
println("World!")  /; With newline
print(42)          /; Works with any type
```
```

Add `Int8()`, `Int64()`, `Char()` conversion examples.

- [ ] **Step 7: Fix While Loop.md — add while true and nested**

Add `while true` pattern with `break`. Add nested while example.

- [ ] **Step 8: Verify**

Run: `cd FlowWing-Docs && yarn build`

- [ ] **Step 9: Commit**

```bash
git add FlowWing-Docs/docs/Language\ Fundamentals/
git commit -m "docs: rewrite Syntax Overview, fix Keywords, Builtin Functions, While Loop, Fill Expression"
```

---

### Task 16: Fix Getting Started & Introduction files

**Files:**
- Modify: `FlowWing-Docs/docs/Introduction/Overview.md`
- Modify: `FlowWing-Docs/docs/Introduction/Key Features.md`
- Modify: `FlowWing-Docs/docs/Getting Started/Installation.md`
- Modify: `FlowWing-Docs/docs/Getting Started/Hello World Example.md`

- [ ] **Step 1: Add code to Overview.md**

Add hello-world snippet at the top:

```flowwing
print("Hello, World!")
```

- [ ] **Step 2: Fix Key Features.md — add examples, reduce bold**

Add a code snippet per feature. Reduce bold formatting (only bold feature names, not entire paragraphs).

- [ ] **Step 3: Fix Installation.md grammar**

Change "can update slower" → "may be slower to update". Add note: "Python 3 is required for running the test suite (`tests/runner.py`) and formatter tests."

- [ ] **Step 4: Fix Hello World Example.md**

Fix code block language label. Add `fg_main` example:

```flowwing
fun fg_main() -> int {
    print("Hello, World!")
    return 0
}
```

Add command-line args example using `sys::getArg()`.

- [ ] **Step 5: Fix "unstable" → "temporary"**

Change "unstable name" → "temporary filename" for hash-named executables.

- [ ] **Step 6: Verify**

Run: `cd FlowWing-Docs && yarn build`

- [ ] **Step 7: Commit**

```bash
git add FlowWing-Docs/docs/Introduction/ FlowWing-Docs/docs/Getting\ Started/
git commit -m "docs: fix Intro and Getting Started — add code, fix grammar, add fg_main"
```

---

### Task 17: Fix Advanced pages (remaining)

**Files:**
- Modify: `FlowWing-Docs/docs/Advanced/Bring Import Exports.md`
- Modify: `FlowWing-Docs/docs/Advanced/Choosy Imports.md`
- Modify: `FlowWing-Docs/docs/Advanced/Creating and Using Modules.md`
- Modify: `FlowWing-Docs/docs/Advanced/Inheritance.md`

- [ ] **Step 1: Fix Bring Import Exports.md**

Inline choosy_lib.fg content. Add path resolution rules. Add circular import warning.

- [ ] **Step 2: Fix Choosy Imports.md**

Fix "fictive" → "fictitious". Reduce overlap with Bring page. Add expose rules for same-named functions.

- [ ] **Step 3: Fix Creating and Using Modules.md**

Clarify `local::` inside module. Add init order note. Add re-export pattern.

- [ ] **Step 4: Fix Inheritance.md**

Fix car name misspellings. Deduplicate repeated Vehicle/Car code blocks. Add `super` in overridden methods note.

- [ ] **Step 5: Verify**

Run: `cd FlowWing-Docs && yarn build`

- [ ] **Step 6: Commit**

```bash
git add FlowWing-Docs/docs/Advanced/
git commit -m "docs: fix Advanced pages — Bring, Choosy, Modules, Inheritance"
```

---

### Task 18: Fix Example Project pages

**Files:**
- Modify: `FlowWing-Docs/docs/Creating a Game/Creating a Game.md`
- Modify: `FlowWing-Docs/docs/Creating a Server/Creating a Server.md`

- [ ] **Step 1: Add raylib Flow-Wing code to Game page**

Add minimal working example:

```flowwing
bring raylib

var window = raylib::initWindow(800, 600, "My Game")

while (!raylib::windowShouldClose(window)) {
    raylib::beginDrawing()
    raylib::clearBackground(raylib::RAYWHITE)
    raylib::drawText("Hello from Flow-Wing!", 190, 200, 20, raylib::LIGHTGRAY)
    raylib::endDrawing()
}

raylib::closeWindow(window)
```

- [ ] **Step 2: Fix Game page — fix broken iframe, clarify library names**

Remove the broken GitHub attachment iframe. Add OS-specific library names: `raylib.lib` (Windows), `libraylib.so` (Linux), `libraylib.dylib` (macOS).

- [ ] **Step 3: Fix Server page — explain return :, add error handling**

Add `return :` explanation. Add `accept()` error handling example:

```flowwing
var conn = server.accept()
if (conn == null) {
    printErrorLog("Accept failed")
    return :
}
```

- [ ] **Step 4: Verify**

Run: `cd FlowWing-Docs && yarn build`

- [ ] **Step 5: Commit**

```bash
git add FlowWing-Docs/docs/Creating\ a\ Game/ FlowWing-Docs/docs/Creating\ a\ Server/
git commit -m "docs: add raylib code to Game page, fix Server page error handling"
```

---

### Task 19: Tone polish pass

**Files:** All `.md` files in `FlowWing-Docs/docs/`

- [ ] **Step 1: Read each file and check for:**
  - Passive voice → change to active
  - "One writes..." → "You write..."
  - Excessive bold formatting → reduce
  - Hedging language ("may be", "could be", "not guaranteed") → remove
  - Run-on sentences → break into short paragraphs
  - Missing code examples for concepts described in prose

- [ ] **Step 2: Ensure every page follows the pattern:**
  1. Brief what-it-is sentence
  2. Code example
  3. Explanation of code
  4. Variations / edge cases
  5. Link to related pages

- [ ] **Step 3: Verify**

Run: `cd FlowWing-Docs && yarn build`

- [ ] **Step 4: Commit**

```bash
git add FlowWing-Docs/docs/
git commit -m "docs: tone polish — active voice, short paragraphs, consistent pattern"
```

---

### Task 20: Cross-reference code examples against test fixtures

**Files:** All 39 doc files (verify, not modify unless discrepancies found)
**Reference:** `tests/fixtures/LatestTests/`

- [ ] **Step 1: For each doc page, find matching test directory**

| Doc page | Test directory | Filter |
|----------|---------------|--------|
| Variables and Constants | `VariableDeclarationTests/` | `FILTER=VariableDeclaration` |
| Data Types | `*/01_int/`, `*/01_deci/`, `*/01_bool/`, `*/01_string/`, `*/01_char/` | various |
| Operators | `BinaryOperationLiteralTests/`, `UnaryOperationLiteralTests/` | `FILTER=BinaryOperation` |
| Conditionals | `IfStatementTests/`, `TernaryTests/`, `SwitchTests/` | `FILTER=If\|Ternary\|Switch` |
| Loops | `ForTests/`, `WhileTests/` | `FILTER=For\|While` |
| Functions | `FunctionTests/` | `FILTER=Function` |
| Classes | `ClassTests/` | `FILTER=Class` |
| Objects/Types | `ObjectTests/` | `FILTER=Object` |
| Arrays | `ArrayTests/`, `ContainerTests/` | `FILTER=Array\|Container` |
| Modules | `BringTests/`, `ModuleTests/` | `FILTER=Bring\|Module` |
| Type Conversion | `TypeConversionFunctionTests/` | `FILTER=TypeConversion` |
| Dynamic Variables | `DynamicVariableTests/` | `FILTER=Dynamic` |
| Fill Expression | `ContainerTests/` | `FILTER=Container` |

- [ ] **Step 2: Run each test suite**

For each test directory, run: `make test-aot FILTER=<pattern>`
Expected: All tests pass. If any fail, investigate whether doc is wrong or test is stale.

- [ ] **Step 3: Spot-check 20 specific doc code examples**

Pick 20 code examples from across doc files. Find equivalent test fixtures. Verify the doc's claimed output matches the `.expect` file's output.

- [ ] **Step 4: Fix any discrepancies found**

If doc says behavior X but tests show Y → fix doc to match tests. Tests are ground truth for language behavior.

- [ ] **Step 5: Run full test suite**

```bash
make test-aot
```

Expected: All 2,662 tests pass.

- [ ] **Step 6: Commit any fixes**

```bash
git add FlowWing-Docs/docs/ tests/
git commit -m "docs: cross-reference fixes — align code examples with test fixture behavior"
```

---

### Task 21: Final verification

**Files:** All

- [ ] **Step 1: Clean build**

```bash
cd FlowWing-Docs && yarn clear && yarn build
```

Expected: Zero errors, zero warnings about broken links.

- [ ] **Step 2: Dev server smoke test**

```bash
cd FlowWing-Docs && yarn start
```

Open `http://localhost:3000/docs/Language%20Fundamentals/Syntax%20Overview`. Verify:
- Page renders correctly
- Code blocks have syntax highlighting
- Sidebar navigation works
- All renamed URLs redirect properly

- [ ] **Step 3: Check all renamed URLs redirect**

Visit each old URL and confirm 301 redirect to new URL:
- `/docs/Advance/Inheritance` → `/docs/Advanced/Inheritance`
- `/docs/Creating%20an%20Server/Creating%20an%20Server` → `/docs/Creating%20a%20Server/Creating%20a%20Server`
- `/docs/BuiltIn%20Libraries/Vec%20Module` → `/docs/Built-in%20Libraries/Vec%20Module`

- [ ] **Step 4: Final commit**

```bash
git add -A && git status
```

If clean: no further commit needed.
If any remaining changes:

```bash
git commit -m "docs: final verification — clean build, all redirects working"
```
