
# Building the FlowWing Compiler

Welcome, contributor! This guide provides a comprehensive set of instructions for setting up your development environment and building the FlowWing compiler on Windows, macOS, and Linux.

Build system is orchestrated by a cross-platform `Makefile` which acts as a user-friendly interface to CMake.

## Table of Contents
1.  [Prerequisites](#part-1-prerequisites)
    -   [Windows](#windows)
    -   [macOS](#macos)
    -   [Linux (Debian/Ubuntu)](#linux-debianubuntu)
2.  [Getting the Code](#part-2-getting-the-code)
3.  [Core Build Workflow](#part-3-core-build-workflow)
    -   [Step 1: Build Dependencies](#step-1-build-dependencies)
    -   [Step 2: Build the Compiler](#step-2-build-the-compiler)
4.  [Common Development Tasks](#part-4-common-development-tasks)
    -   [Running Tests](#running-tests)
    -   [Running a Local File](#running-a-local-file)
    -   [Debugging](#debugging)
    -   [Cleaning the Workspace](#cleaning-the-workspace)
5.  [Makefile Commands Quick Reference](#makefile-commands-quick-reference)

---

## Part 1: Prerequisites

Before you begin, please ensure you have the necessary toolchain installed for your operating system.

### Windows

The recommended setup uses the Microsoft Visual C++ (MSVC) toolchain.

1.  **Windows Terminal (Recommended):** Install from the **Microsoft Store**.
2.  **Chocolatey (Package Manager):** Open **PowerShell as an Administrator** and run:
    ```powershell
    Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
    ```
3.  **Visual Studio 2022:** Download the free **Community Edition**. During installation, select the **"Desktop development with C++"** workload and ensure **"C++ CMake tools for Windows"** is checked in the installation details.
4.  **Git & Make:** Open a new Windows Terminal and run:
    ```powershell
    choco install -y git make python3
    ```

### macOS

The recommended setup uses Homebrew and the LLVM toolchain.

1.  **Homebrew:** If you don't have it, follow the instructions at [brew.sh](https://brew.sh/).
2.  **Xcode Command Line Tools:** Open a terminal and run:
    ```bash
    xcode-select --install
    ```
3.  **Build Tools:** Install all required packages using Homebrew:
    ```bash
    brew install git ninja ccache automake autoconf libtool python llvm@17
    ```

### Linux (Debian/Ubuntu)

The recommended setup uses the system package manager (`apt`) and the Clang toolchain.

1.  **Build Essentials:** Open a terminal and install the core build tools:
    ```bash
    sudo apt-get update
    sudo apt-get install -y build-essential git
    ```
2.  **Project-Specific Tools:** Install the remaining required packages:
    ```bash
    sudo apt-get install -y clang-17 ninja-build ccache automake autoconf libtool python3 wget
    ```

---

## Part 2: Getting the Code

Clone the repository using Git.

```bash
git clone https://github.com/kushagra1212/Flow-Wing.git
cd Flow-Wing
```

---

## Part 3: Core Build Workflow

The following steps are performed from a terminal inside the project's root directory.

> **Important for Windows Users:** You **must** use the **"x64 Native Tools Command Prompt for VS 2022"** terminal for all `make` commands. You can find it in your Start Menu.

### Step 1: Build Dependencies

The first time you build, and anytime the third-party dependencies change, you must build them. We recommend using the `release` configuration as it's used for testing.

```bash
# This will download and build LLVM and other libraries.
# It will take a significant amount of time.
make deps-install-release
```
For a debug build of the dependencies, use `make deps-install-debug`.

### Step 2: Build the Compiler

Once dependencies are installed, you can build the FlowWing compiler itself. You can choose between the JIT or AOT compiler in either Debug or Release mode.

```bash
# Build the JIT compiler in Debug mode (most common for development)
make build-jit-debug

# Or, build the AOT compiler in Release mode
make build-aot-release
```
The build artifacts will be placed in the `build/` directory, and the final SDK (including the `FlowWing` executable) will be staged in `build/sdk/`.

---

## Part 4: Common Development Tasks

### Running Tests

Our test suite uses GoogleTest and can be run easily via the Makefile.

```bash
# Build and run all JIT tests
make test-jit

# Build and run all AOT tests
make test-aot
```

**Filtering Tests:** To run a specific subset of tests, use the `FILTER` option. It accepts a GoogleTest filter pattern.

```bash
# Run only tests in the "Parser" suite
make test-jit FILTER=Parser*

# Run a single specific test
make test-aot FILTER=MyTestSuite.MySpecificTest
```

### Running a Local File

You can quickly compile and run a local `.fg` file to test your changes.

#### Running with the JIT Compiler

The JIT compiler interprets and executes the code directly.

```bash
make run-jit-debug FILE=tests/local/dyn.fg
```

#### Running with the AOT Compiler

The AOT compiler first compiles your `.fg` file to a native executable in the `build/bin/` directory and then runs it.

```bash
make run-aot-release FILE=tests/local/dyn.fg
```

### Cleaning the Workspace

The Makefile provides targets to clean up build artifacts.

```bash
# Remove all build artifacts (but keep downloaded dependencies)
make clean

# Remove EVERYTHING, including the .fw_dependencies folder.
# You will need to run 'make deps-install-*' again after this.
make clean-all
```

---

## Makefile Commands Quick Reference

| Command | Description |
| :--- | :--- |
| `make deps-install-release` | **(Run First)** Builds and installs all third-party dependencies. |
| `make build-jit-debug` | Builds the JIT compiler in Debug mode. |
| `make build-aot-release` | Builds the AOT compiler in Release mode. |
| `make test-jit` | Builds and runs the full JIT test suite. |
| `make test-aot` | Builds and runs the full AOT test suite. |
| `make run-jit-debug FILE=<path>` | Runs a local `.fg` file with the JIT compiler. |
| `make run-aot-release FILE=<path>` | Compiles and runs a local `.fg` file with the AOT compiler. |
| `make clean` | Deletes build artifacts. |
| `make clean-all` | Deletes all build artifacts and all dependencies. |
