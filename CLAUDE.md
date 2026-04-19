# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Flow-Wing is a programming language experiment combining static and dynamic typing with object-oriented programming, memory management, garbage collection, and modularity. It supports both AOT (Ahead-of-Time) and JIT (Just-In-Time) compilers, a REPL, LSP integration for VS Code, and capabilities for building servers and games.

## Compilation Pipeline

The compiler operates as a series of discrete passes managed by a `CompilationPipeline`. The typical flow is:

1.  **Source Loading**: `SourceLoaderPass` loads the `.fg` source files.
2.  **Lexical Analysis**: `LexerPass` tokenizes the source code.
3.  **Parsing**: `ParsingPass` constructs the initial syntax tree.
4.  **Semantic Analysis**: `SemanticAnalysisPass` performs type checking and binds symbols.
5.  **IR Generation**: `IRGenerationPass` transforms the semantic tree into LLVM Intermediate Representation (IR).
6.  **Object Emission**: `ObjectEmissionPass` generates object files (for AOT mode).
7.  **Linking**: `LinkerPass` combines object files into a final executable.
8.  **JIT Compilation**: `JITCompilerPass` (for JIT mode) handles runtime execution.

## Build System

The build system uses CMake with a cross-platform Makefile wrapper.

### Dependencies

```bash
make deps-install-debug    # Build dependencies in Debug mode
make deps-install-release  # Build dependencies in Release mode
```

### Compilers

```bash
# JIT Compiler (interprets and runs code)
make build-jit-debug       # Debug JIT build
make build-jit-release     # Release JIT build

# AOT Compiler (compiles to native executable)
make build-aot-debug       # Debug AOT build
make build-aot-release     # Release AOT build
```

### Running Code

```bash
# Run a Flow-Wing (.fg) file
make run-jit-debug FILE=tests/fixtures/some.fg
make run-aot-debug FILE=tests/fixtures/some.fg

# With additional arguments
make run-jit-debug FILE=tests/fixtures/some.fg ARGS='--some-flag'
```

### Testing

Tests are managed by a Python test runner (`tests/runner.py`) that supports both JIT and AOT modes.

```bash
# Run all tests
make test-jit              # Run JIT integration tests
make test-aot              # Run AOT integration tests

# Filter specific tests
make test-jit FILTER=Parser*
make test-aot FILTER=MyTestSuite.MySpecificTest

# Update expected outputs (creates/updates .expect files)
make test-jit --update
make test-aot --update
```

### Cleaning

```bash
make clean                 # Remove build artifacts
make clean-all             # Remove all artifacts and dependencies (requires FORCE=1)
```

### Visualization

```bash
# Generate visualization data (tokens, AST, semantic tree)
make viz FILE=path/to/file.fg
```

### LSP (Language Server Protocol)

The LSP is a TypeScript-based extension for VS Code.

```bash
make lsp-compile           # Compile the LSP extension
make lsp-test              # Run LSP unit tests
make run-lsp               # Launch VS Code with LSP in development mode

# LSP Linting
cd src/lsp && npm run lint
```

## Project Structure

```
Flow-Wing/
├── src/                    # Main source code
│   ├── compiler/           # Compiler implementation (Pipeline, Passes, Diagnostics)
│   ├── ASTBuilder/         # AST construction and parsing
│   ├── SemanticAnalyzer/   # Semantic analysis and type checking
│   ├── syntax/             # Syntax tree nodes
│   ├── SourceTokenizer/    # Lexical analysis/tokenization
│   ├── REPL/               # REPL implementation
│   ├── fw-modules/         # Built-in modules
│   └── ...
├── tests/
│   ├── fixtures/           # Test fixtures (.fg files)
│   └── runner.py           # Python test runner
├── src/lsp/                # Language Server Protocol (TypeScript)
└── flow-wing-viz/          # Visualization tool (Bun-based)
```

## CMake Presets

- `jit-debug` / `jit-release` - JIT compiler configurations
- `aot-debug` / `aot-release` - AOT compiler configurations
- `test-jit` / `test-aot` - Test configurations

## Language Syntax

### Type System

- Primitive types: `int`, `deci`, `bool`, `str`, `nthg` (nothing)
- Container types: `int[5]`, `str[3][4]` (arrays)
- Object types: `type Name = { field:type, ... }`
- Function types: `(param:type) -> returnType`

### Key Language Features

```flow-wing
var x = 10              # Type inference
var y: int = 20         # Explicit type
const pi = 3.14159      # Constants

class Vehicle {
  var make: str
  init(make: str) -> nthg {
    self.make = make
  }
}

class Car extends Vehicle {
  var doors: int
}

fun greet(name: str) -> str {
  return "Hello, " + name
}

for (var i = 0 to 10 : 2) {
  // loop with step
}

var arr: int[5] = [3 fill 10]  # [10, 10, 10, 10, 10]
```

## Development Workflow

### Adding a New Test

1. Create a `.fg` file in `tests/fixtures/LatestTests/<category>/`
2. Run `make test-jit` to see current output
3. If output is correct, run with `--update` to create `.expect` file
4. Commit both files

### Debugging

- Enable logging: `make build-jit-debug`
- Use `--emit=ir` flag to dump LLVM IR on failure
- IR artifacts are saved in `build/bin/test_artifacts/ir_on_failure/`

## Cursor Rules

The `flow-wing-viz` project uses Bun instead of Node.js:

- Use `bun <file>` instead of `node <file>`
- Use `bun test` for testing
- Use `Bun.serve()` for HTTP servers
- Use `Bun.sql` for PostgreSQL, `Bun.redis` for Redis
- Use `bun:sqlite` for SQLite

## License

Flow-Wing is licensed under GNU General Public License v2 (GPLv2).
