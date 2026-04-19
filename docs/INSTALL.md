# Flow-Wing Installation Guide

Complete reference for installing Flow-Wing across all supported platforms using every available method.

---

## Table of Contents

1. [Supported Platforms](#supported-platforms)
2. [Quick Start](#quick-start)
3. [Method 1: Pre-built Installers (Recommended)](#method-1-pre-built-installers-recommended)
4. [Method 2: Package Managers](#method-2-package-managers)
5. [Method 3: Build from Source](#method-3-build-from-source)
6. [Post-Installation Verification](#post-installation-verification)
7. [Troubleshooting](#troubleshooting)

---

## Supported Platforms

| Platform | Architecture | Pre-built Installer | Package Manager | Build from Source |
|----------|-------------|---------------------|-----------------|-------------------|
| macOS    | Apple Silicon (arm64)   | `.dmg`              | Homebrew        | Yes               |
| macOS    | Intel (x86_64)          | N/A                 | Homebrew*       | Yes               |
| Windows  | x86_64                  | `.exe` (NSIS)       | Chocolatey      | Yes               |
| Linux    | x86_64 (amd64)          | `.deb`              | APT             | Yes               |

> *Homebrew formula supports macOS ARM64 and Linux. Intel Mac support depends on release availability.

---

## Quick Start

The fastest way to get started:

```bash
# Clone the repository
git clone https://github.com/kushagra1212/Flow-Wing.git
cd Flow-Wing

# Build dependencies (first time only)
make deps-install-debug

# Build AOT compiler and run a .fg file
make run-aot-debug FILE=examples/hello.fg
```

---

## Method 1: Pre-built Installers (Recommended)

Download pre-built binaries from the [Flow-Wing releases page](https://flowwing.is-a.dev/).

### macOS (Apple Silicon arm64)

1. Download `FlowWing-<version>-macos-arm64.dmg`
2. Open the DMG and drag `FlowWing.app` to Applications
3. Add Flow-Wing to your PATH:

```bash
export PATH="/Applications/FlowWing.app/Contents/Resources/FlowWingSDK/bin:$PATH"
flowwing --version
```

Or call directly:

```bash
"/Applications/FlowWing.app/Contents/Resources/FlowWingSDK/bin/FlowWing" --version
```

### Windows (x86_64)

1. Download `FlowWing-<version>-windows-x86_64.exe`
2. Run the installer — it installs to `C:\Program Files\FlowWing\<version>\`
3. The installer automatically adds Flow-Wing's `bin/` directory to your system PATH via PowerShell
4. Open a new terminal and verify:

```powershell
flowwing --version
```

### Linux (x86_64 / amd64)

1. Download `FlowWing-<version>-linux-x86_64.deb`
2. Install with dpkg:

```bash
sudo dpkg -i FlowWing-<version>-linux-x86_64.deb
flowwing --version
```

### SDK Archives (All Platforms)

Each release also includes a `.zip` archive containing the full SDK tree (`bin/`, `lib/modules/`). Extract and add to PATH:

```bash
# macOS / Linux example
unzip FlowWing-<version>-macos-arm64.zip -d /opt/flowwing
export PATH="/opt/flowwing/bin:$PATH"
```

---

## Method 2: Package Managers

### Homebrew (macOS, limited)

Flow-Wing is distributed via a community tap. Add the tap and install:

```bash
# macOS only — Apple Silicon recommended
brew tap kushagra1212/flow-wing
brew install flowwing
flowwing --version
```

> **Note:** The tap ships an Apple Silicon (arm64) macOS SDK zip. On Intel Macs, `brew install` will stop with a clear message; use Linux/Windows binaries or build from source. Linux is supported via the `.deb` asset in the formula.

### Chocolatey (Windows)

The package downloads the release **zip** into the Chocolatey package `tools` folder (full `bin/` + `lib/` tree) and adds `tools/bin` to the **machine** PATH (requires an elevated/admin Chocolatey install).

```powershell
choco install flowwing
flowwing --version
```

If Chocolatey is not installed, first run:

```powershell
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadScript('https://community.chocolatey.org/install.ps1'))
```

### APT (Linux)

Flow-Wing is published to a custom APT repository. After adding the repo:

```bash
echo "deb [trusted=yes] https://repo.flowwing.dev/apt stable main" | sudo tee /etc/apt/sources.list.d/flow-wing.list
sudo apt update && sudo apt install flowwing
flowwing --version
```

> **Note:** The APT repository URL is a placeholder — check the official release workflow for the actual repo configuration.

---

## Method 3: Build from Source

Building from source gives you full control over build modes (Debug/Release), compiler type (AOT/JIT), and test suites. This method works on all three platforms.

### Prerequisites by Platform

#### macOS

```bash
# Core build tools
brew install ninja ccache automake autoconf libtool llvm@17

# Xcode command line tools (required for SDK path resolution)
xcode-select --install

# For LSP development
corepack enable   # enables yarn via Node.js
npm install -g yarn  # or use npx directly
```

#### Linux (Ubuntu/Debian)

```bash
sudo apt-get update && sudo apt-get install -y \
    clang-17 lld ninja-build ccache automake autoconf libtool wget \
    libx11-dev libxcursor-dev libxinerama-dev libxrandr-dev \
    libxi-dev libgl1-mesa-dev libglu1-mesa-dev mesa-common-dev
```

#### Windows (Git Bash / MSYS2)

```powershell
# In PowerShell (run as Administrator for Chocolatey)
choco install -y 7zip make ninja llvm nodejs yarn

# Enable long paths (required by CMake external projects)
git config --system core.longpaths true

# Set up MSVC toolchain
& "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\vsdevcmd.bat" -arch=x64
```

### Build Steps (All Platforms)

#### Step 1: Clone and Configure Dependencies

```bash
git clone https://github.com/kushagra1212/Flow-Wing.git
cd Flow-Wing

# Download and build LLVM, GTest, bdwgc, raylib etc.
make deps-install-debug    # Debug dependencies (~hundreds of MB)
# or for release builds:
# make deps-install-release
```

This downloads and compiles the following from source via CMake ExternalProject:
- **LLVM 17** (llvmorg-17.0.6 tag) — with Clang, LLD projects
- **Google Test** v1.17.0 — for unit testing
- **bdwgc** v8.2.4 — Boehm garbage collector
- **libatomic_ops** v7.8.0 — atomic operations library
- **raylib** 5.5 — game/media library (static build)

#### Step 2: Set Environment Variables (Unix/macOS only)

```bash
# Point to the locally-built clang from deps
export CC="$(brew --prefix llvm@17)/bin/clang"      # macOS
export CC="/usr/bin/clang-17"                        # Linux
export CXX="${CC//clang/clang++}"
export LDFLAGS="-fuse-ld=lld"

# macOS only — required for SDK path resolution during dependency builds
export SDKROOT="$(xcrun --show-sdk-path)"
```

#### Step 3: Build the Compiler

Choose one or more build modes. Each mode produces a compiler binary staged at `build/sdk/bin/FlowWing`.

| Target | What it does | Output |
|--------|-------------|--------|
| `make build-aot-debug` | AOT compiler, debug symbols + assertions | Debug build for development |
| `make build-aot-release` | AOT compiler, optimized | Production-ready binary |
| `make build-jit-debug` | JIT interpreter, debug mode | For interactive REPL use |
| `make build-jit-release` | JIT interpreter, optimized | Fastest runtime interpretation |

#### Step 4: Run a Flow-Wing Program

```bash
# AOT: compile .fg → executable, then run it
make run-aot-debug FILE=examples/hello.fg

# JIT: interpret and run directly (no separate compilation step)
make run-jit-release FILE=examples/hello.fg ARGS="--some-flag"
```

#### Step 5: Run Tests

```bash
# AOT integration tests (.fg fixtures vs .expect files)
make test-aot                          # all tests
make test-aot FILTER=Parser*           # only Parser fixtures
make test-aot ARGS='--keep-going'      # continue after failures

# JIT integration tests
make test-jit

# IR artifacts from failures are written to build/bin/test_artifacts/ir_on_failure/*.ll
```

#### Step 6: LSP Development (Optional)

The Language Server Protocol extension provides IntelliSense for VS Code / Cursor.

```bash
# Compile TypeScript sources
make lsp-compile

# Launch a new editor window with the extension loaded
make run-lsp

# Run LSP unit tests (completion, hover, definitions, signature help)
make lsp-test
```

Requires: Node.js 20+, Yarn (`corepack enable`).

### Build System Details

The build uses CMake presets referenced through `makefile` wrappers. **Never run cmake directly** — always use the make targets which handle dependency ordering and SDK staging.

Key files:
- `CMakePresets.json` — configure/build/test preset definitions (Ninja generator)
- `cmake/deps_builder/` — external project dependencies (LLVM, GTest, etc.)
- `makefile` — cross-platform wrapper handling Windows cmd.exe vs POSIX shell differences

Cache variables for advanced configuration:
| Variable | Default | Description |
|----------|---------|-------------|
| `BUILD_AOT` | OFF | Enable AOT compilation mode |
| `TESTS_ENABLED` | OFF | Build with test suites |
| `ENABLE_LOGGING` | ON (debug) | Enable compiler internal logging |
| `FLOWWING_INSTALL_PREFIX` | "" | Install prefix for release packaging |

### Release Packaging (For Maintainers)

To build a distributable SDK tree:

```bash
make release-aot-configure RELEASE_INSTALL_PREFIX="/path/to/install"
make release-aot-build
make release-aot-install RELEASE_INSTALL_PREFIX="/path/to/install"
```

This produces an installable directory with `bin/`, `lib/modules/` and version metadata.

---

## Post-Installation Verification

After installation, verify the compiler works:

```bash
flowwing --version
# Expected output: FlowWing <version> (AOT/JIT) using LLVM 17.x

# Quick smoke test — create a minimal program
echo 'fun main_func() -> nthg { print("Hello from Flow-Wing!") }' > /tmp/test.fg
flowwing /tmp/test.fg -o /tmp/test && /tmp/test
```

---

## Troubleshooting

### Common Issues

| Symptom | Cause | Fix |
|---------|-------|-----|
| `clang: command not found` during deps build | LLVM 17 not in PATH or Xcode CLT missing | Install llvm@17 via Homebrew (macOS) or clang-17 package (Linux); set `CC=clang-17` env var |
| `Could not determine macOS SDK path using 'xcrun'` | Xcode command line tools not installed | Run `xcode-select --install`; verify with `xcrun --show-sdk-path` |
| `LLVM 17 required but not found` after deps build | Dependencies not built or wrong prefix | Ensure `.fw_dependencies_debug/install/` exists; re-run `make deps-install-debug` |
| LSP tests fail: compiler path error | Compiler binary at non-default location | Set `FLOWWING_COMPILER_PATH=/absolute/path/to/build/sdk/bin/FlowWing` env var, or configure `FlowWing.compilerPath` in VS Code settings |
| Windows: long path errors during git clone | Git max path limit on Windows | Run `git config --system core.longpaths true` before cloning |
| Slow dependency builds (LLVM takes 30+ min) | Single-threaded build by default | Set `JOBS=-j<N>` to use more cores, e.g. `make deps-install-debug JOBS=-j8` |

### Cleaning Builds

```bash
# Remove only build artifacts (safe)
make clean          # deletes build/ and bin/ directories

# Remove everything including dependencies (destructive!)
make clean-all FORCE=1   # requires FORCE=1 on non-interactive shells
```

### Disk Space Requirements

| Component | Approximate Size |
|-----------|-----------------|
| `.fw_dependencies_debug/install` (LLVM + deps) | ~2–3 GB |
| `build/` directory tree | ~500 MB – 1.5 GB |
| Full workspace after first build | ~4–6 GB total |

### Platform-Specific Notes

**macOS:** Minimum deployment target is macOS 12.0 (Monterey). The pre-built `.dmg` installer targets Apple Silicon (arm64) only — Intel Macs cannot run arm64 binaries natively.

**Windows:** Uses MSVC toolchain for dependency builds and the locally-built Clang as the AOT linker driver. Git Bash is used for makefile execution; native cmd.exe works with `SHELL := cmd.exe` detection in the makefile.

**Linux:** Requires LLVM 17 (system package) to build dependencies, then uses the locally-compiled Clang from `.fw_dependencies_debug/install/bin/clang`. The AOT compiler links user code via this local clang++. LLD is used as the system linker (`-fuse-ld=lld`).
