# Design: `sys` Module for Flow-Wing

## Overview
The `sys` module provides access to system-level information and controls, such as command-line arguments, process termination, and platform identification.

## API Definition

### `sys::arg(index: int) -> str`
Returns the command-line argument at the specified index.
- `index 0` is typically the executable/script name.
- If the index is out of bounds, it should return an empty string `""` or handle it gracefully according to language conventions.

### `sys::exit(code: int) -> nthg`
Terminates the Flow-Wing runtime immediately with the provided exit code.

### `sys::platform() -> str`
Returns a string representing the operating system (e.g., `"darwin"`, `"linux"`, `"windows"`).

## Implementation Strategy

### 1. JIT Runtime (LLVM ORC)
- **Modification**: In `src/compiler/pipeline/passes/JITCompilerPass/JITCompilerPass.cpp`, replace the hardcoded "fake" arguments in `MainFn` call with the actual `argc` and `argv` passed to the compiler's `main`.
- **Data Flow**: The `argv` from the compiler's `main` will be passed into the JIT-compiled function.

### 2. AOT Runtime
- **Search**: Identify the runtime entry point in the AOT-generated binary.
- **Modification**: Ensure the runtime's `main` function captures `argc` and `argv` from the OS and stores them in a globally accessible location (or passes them through the `CompilationContext`/Runtime state) so the `sys` module can access them.

### 3. Module Implementation
- **Location**: `fw-modules/sys_module/`
- **Files**:
    - `sys-module.fg`: The Flow-Wing module definition.
    - `libflowwing_sys.cpp`: The C++ implementation that interfaces with the runtime and provides the logic for `arg`, `exit`, and `platform`.
- **Integration**: Add the new module to the build system (`CMakeLists.txt`).

## Testing
A new test suite will be created in `tests/fixtures/LatestTests/sysTests/`.
- `arg_test.fg`: Verifies `sys::arg` returns correct values.
- `exit_test.fg`: Verifies `sys::exit` terminates the process.
- `platform_test.fg`: Verifies `sys::platform` returns expected strings.

Tests will be run in both JIT and AOT modes using `tests/runner.py`.

## Success Criteria
- `sys::arg(index)` correctly retrieves arguments in both JIT and AOT.
- `sys::exit` terminates the process with the correct code.
- `sys::platform` returns the correct OS string.
- All new tests pass in both modes.
