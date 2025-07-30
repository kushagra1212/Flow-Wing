# How to Build FlowWing Compiler Project

## Prerequisites

- CMake version 2.39
- C++ Compiler (clang-17)
- Docker (Optional)

## Commands to Build, Run, Test, Package FlowWing Compiler Project

### Build

```bash
make build
```

### Run FlowWing Compiler Project

```bash
make run
```

### Test FlowWing Compiler Project

```bash
make test
```

### Package FlowWing Compiler Project

```bash
make package
```

## Usage: `make <target>` [FILE=<path/to/your.fg>]

### Primary Development Targets:

- `help` Show all available targets.
- `build` Builds the AOT debug version (default).
- `build-aot` Builds the AOT debug version.
- `build-aot-release` Builds the AOT release version.
- `build-jit` Builds the JIT debug version.
- `run` Compile & run `myProgram.fg` file with the AOT Debug compiler.
- `run-aot` Same as 'run'.
- `run-aot-release` Compile & run `myProgram.fg` file with the AOT Release compiler.
- `run-jit` Run `myProgram.fg` file with the JIT Debug.
- `run-jit-release` Run `myProgram.fg` file with the JIT Release.

### Local Running Targets (for scratch files):

- `run` Compile & run `myProgram.fg` file with the AOT Debug compiler.
- `run-aot` Same as 'run'.
- `run-aot-release` Compile & run `myProgram.fg` file with the AOT Release compiler.
- `run-jit` Run `myProgram.fg` file with the JIT Debug.
- `run-jit-release` Run `myProgram.fg` file with the JIT Release.

### Testing Targets:

- `test` Run all AOT tests. (default)
- `test-aot` Configure, build, and run the AOT tests.
  Example: `make test-aot FILTER=SomeTestSuite.\*`
- `test-jit` Configure, build, and run the JIT tests.

### Packaging Targets (for distribution):

- `package` Create the final AOT release package.
- `package-aot` Create the final AOT release package.
- `package-jit` Create the final JIT release package.

### Utility Targets:

- `clean` Deletes the entire 'build' and 'run_output' directories. (default)
- `clean-all` Deletes everything, INCLUDING downloaded dependencies.
  Example: `make clean-all`

### Dependency Management:

- `deps-build` Manually build external dependencies (LLVM, GTest).
  Example: `make deps-build`

### Options:

- `FILE=<path>` Sets the .fg file for 'run' targets. (default)
- `FILTER=<pattern>` Sets the GTest filter for 'test' targets. (default)
- `SILENT=1` Suppresses build status messages for a cleaner log. (default)
- `JOBS=-j<N>` Sets the number of parallel build jobs (default: all cores). (default)

### Example:

```bash
make run FILE=my_tests/feature.fg
```
