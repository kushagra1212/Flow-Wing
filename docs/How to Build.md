# How to Build FlowWing Compiler Project

## Prerequisites

- CMake version 2.39
- C++ Compiler (clang-17)
- Docker (Optional)

# Building FlowWing

This guide provides instructions for building the FlowWing compiler from source on macOS and Linux.

The build system is managed by CMake, with a convenient `Makefile` providing shortcuts for all common operations.

## 1. Prerequisites

Before you begin, you need to install the necessary build tools for your platform.

### macOS

You will need Homebrew to install the dependencies.

```bash
# Install Homebrew (if you don't have it)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install build tools
brew install cmake ninja automake autoconf libtool
```

### Linux (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install build-essential cmake ninja-build automake autoconf libtool
```

## 2. First-Time Setup: Installing Dependencies

The FlowWing compiler depends on several third-party libraries, including LLVM, Clang, and the Boehm GC. These are managed automatically.

You only need to run this command once for each build type (Debug and Release).

```bash
# To install dependencies for DEBUG builds (most common for development)
make deps-install-debug

# To install dependencies for RELEASE builds
make deps-install-release
```

This process will download and compile all necessary libraries into the `.fw_dependencies` directory in the project root. This can take a significant amount of time.

## 3. Daily Development Workflow

These are the commands you will use most often for writing and testing code.

### Building the Compiler

You can build the compiler in two modes: AOT (Ahead-of-Time) and JIT (Just-in-Time), each in either Debug or Release configuration.

```bash
# Build the AOT compiler in Debug mode (recommended for development)
make build-aot-debug

# Build the JIT compiler in Debug mode
make build-jit-debug

# Build in Release mode for performance testing
make build-aot-release
make build-jit-release
```

### Running a `.fg` File

The `run-*` targets automatically build the compiler, stage a clean SDK, and then execute your file.

**This is the primary command for testing your code changes.**

```bash
# Run a file using the AOT Debug compiler
make run-aot-debug FILE=path/to/your/program.fg

# Run a file using the JIT Debug compiler
make run-jit-debug FILE=path/to/your/program.fg
```

To see a clean output showing only your program's results (and not the build messages), add the `SILENT=1` option:

```bash
make run-aot-debug FILE=path/to/your/program.fg SILENT=1
```

### Running Tests

The project uses Google Test for its test suites. The `test-*` targets will automatically build the test runner and execute all tests.

```bash
# Run the entire AOT test suite
make test-aot

# Run the entire JIT test suite
make test-jit
```

To run only a specific subset of tests, use the `FILTER` option with a `gtest_filter` pattern:

```bash
# Run only tests related to the Parser
make test-aot FILTER=Parser*

# Run a single specific test
make test-jit FILTER=MyTestSuite.MySpecificTest
```

## 4. Cleaning

To clean up build artifacts:

```bash
# Remove all build output (but keep dependencies)
make clean

# Remove all build output AND all downloaded dependencies
# This will require you to run 'make deps-install-*' again.
make clean-all
```
