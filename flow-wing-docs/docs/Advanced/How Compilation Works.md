---
sidebar_position: 8
---
import CodeBlock from "../../src/components/common/CodeBlock";

# How Compilation Works

The compiler turns a `.fg` file into a program in stages. Each stage reads
what the one before it made, and each can stop and report a problem. You can
print the result of every stage with `--emit`, and the
[playground](/playground) shows them all as you type.

```
square.fg
    │
    │  1  Lexer               --emit=tokens    tokens.json
    ▼
 tokens
    │
    │  2  Parser              --emit=ast       ast.json
    ▼
 syntax tree
    │
    │  3  Semantic analysis   --emit=sem       semantic_tree.json
    ▼
 semantic tree        names resolved, types checked
    │
    │  4  IR generation       --emit=ir        llvm_ir.ll
    ▼
 LLVM IR
    │
    │  5  Optimisation        -O0 … -O3
    ▼
    ├── native    6  machine code   --emit=obj     7  link   --emit=exe   a program for this machine
    ├── wasm32    6  wasm code                     7  link   --emit=exe   main.js + main.wasm
    └── JIT          run straight from memory      FlowWing-jit
```

Stages 1 to 3 are the **front end**: they read and check the program. Stages
4 to 7 are the **back end**: they make it runnable. The back end is built on
[LLVM](https://llvm.org).

This page follows one small program through every stage:

<CodeBlock code={
`fun square(n: int) -> int {
  return n * n
}

println(square(7))
`} language="fg"/>

## 1. Lexer: text to tokens

The lexer reads the text character by character and groups it into
**tokens**: keywords, names, numbers, strings and symbols. Spaces and
comments are dropped.

```bash
flowwing square.fg --emit=tokens --output-dir=out    # writes out/tokens.json
```

```
FunctionKeyword        "fun"
IdentifierToken        "square"
OpenParenthesisToken   "("
IdentifierToken        "n"
ColonToken             ":"
Int32Keyword           "int"
CloseParenthesisToken  ")"
RightArrowToken        "->"
Int32Keyword           "int"
OpenBraceToken         "{"
ReturnKeyword          "return"
IdentifierToken        "n"
...
```

Each token also records where it is in the file. **The lexer finds**
characters that cannot start any token (a name like `café`: names are ASCII)
and strings with no closing quote.

## 2. Parser: tokens to a syntax tree

The parser checks that the tokens follow the grammar, and builds a **syntax
tree**: the program's structure, with each part inside the part it belongs
to. `n * n` becomes a `BinaryExpression` with the operator `*` and two
`IdentifierExpression` children.

```bash
flowwing square.fg --emit=ast --output-dir=out       # writes out/ast.json
```

```
CompilationUnit
├── FunctionStatement  square
│   ├── parameters: ParameterExpression  n : Int32TypeExpression
│   ├── returnType: Int32TypeExpression
│   └── body: BlockStatement
│       └── ReturnStatement
│           └── BinaryExpression  *
│               ├── left:  IdentifierExpression  n
│               └── right: IdentifierExpression  n
└── ExpressionStatement
    └── CallExpression  println
        └── CallExpression  square
            └── NumberLiteralExpression  7
```

The parser knows nothing about meaning yet: `n * n` would parse the same if
`n` did not exist. **The parser finds** missing brackets, a statement where
an expression must be, and other mistakes in the shape of the code.

## 3. Semantic analysis: meaning and types

Semantic analysis walks the syntax tree and works out what every name means
and what type every expression has. Each name is resolved to a **symbol**
(the declaration it refers to), and every expression gets a **type**.

```bash
flowwing square.fg --emit=sem --output-dir=out       # writes out/semantic_tree.json
```

The semantic tree has the same shape as the syntax tree, plus two tables it
points into: `symbols` and `types`. For `n * n`:

```
BinaryExpression  *            int * int -> int
├── IdentifierExpression  n    symbol: parameter n, type int
└── IdentifierExpression  n    symbol: parameter n, type int
```

**Semantic analysis finds** most errors: a name that does not exist, a value
of the wrong type (`var count: int = "three"`), a call with the wrong number
of arguments, an assignment to a constant. A program that passes this stage
compiles.

## 4. IR generation: LLVM IR

IR generation turns the semantic tree into **LLVM IR**, a low-level language
that looks like assembly for an imaginary machine with unlimited registers.
From here on, LLVM does the work that every compiler built on it shares.

```bash
flowwing square.fg --emit=ir --output-dir=ir        # writes ir/llvm_ir.ll
```

```llvm
define weak_odr void @square(ptr %0, ptr %1) {
entry:
  %n_local = alloca i32, align 4
  call void @llvm.memcpy.p0.p0.i64(ptr align 4 %n_local, ptr align 4 %1, i64 4, i1 false)
  %load_var = load i32, ptr %n_local, align 4
  %load_var1 = load i32, ptr %n_local, align 4
  %multiplication_result = mul i32 %load_var, %load_var1
  store i32 %multiplication_result, ptr %0, align 4
  ret void
}
```

`int` is `i32`, a 32-bit integer. The function takes its argument and
returns its result through pointers, which is how Flow-Wing passes values of
every type the same way. `--emit=ir` shows the IR as IR generation made it,
before optimisation.

The IR depends on the **target**. With `--target=wasm32` pointers are 4 bytes
instead of 8, and the file starts with
`target triple = "wasm32-unknown-emscripten"`.

## 5. Optimisation

The optimiser rewrites the IR to do the same work faster: it keeps values in
registers instead of memory, removes code that never runs, and replaces
calls with the function's body where that is cheaper. `-O0` (the default)
skips it; `-O1`, `-O2` and `-O3` do more each.

```bash
flowwing square.fg -O2 -o square
```

## 6 and 7. Code generation and linking

LLVM turns the optimised IR into machine code for the target, one object
file per module (`--emit=obj`). The **linker** then joins your objects with
the Flow-Wing runtime (the garbage collector, the task scheduler, the
built-in modules) into one program (`--emit=exe`, the default).

| Target | Linked by | Result |
|---|---|---|
| native (default) | the system linker, through `clang++` or `lld-link` | an executable for this machine |
| `wasm32` | Emscripten | `main.js` and `main.wasm`, for Node or a browser. See [Compiling to WebAssembly](./Compiling%20to%20WebAssembly.md) |

The JIT (`FlowWing-jit`) stops before this step: it turns the IR into
machine code in memory and runs it at once, with no files.

## Where each stage runs in the playground

| Tab | Stage | Runs |
|---|---|---|
| Tokens, Syntax tree, Semantic tree, Problems | 1 to 3 | **In your browser**, on every edit. It is the compiler's own front end, built to WebAssembly (about 1.4 MB). |
| LLVM IR, WebAssembly | 4 to 7 | **On the Flow-Wing server**, in a sandbox, when you run the program or open the tab. |
| Output | the program itself | **In your browser** as WebAssembly, or **on the server**, turned into machine code by the JIT: you choose. |
| Logs | | Every step above, with how long it took. |

The whole compiler does not run in the browser because its back end is
large: with LLVM inside, the compiler is about 55 MB, and the link to WebAssembly needs
Emscripten, which runs on Python and Node. The front end needs none of that,
so it runs in the page, and errors appear as you type.
