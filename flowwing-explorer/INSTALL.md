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
| macOS    | Apple Silicon (arm64)   | `.dmg` or `.pkg`    | Homebrew        | Yes               |
| macOS    | Intel (x86_64)          | N/A                 | Homebrew*       | Yes               |
| Windows  | x86_64                  | `.exe` (NSIS)       | Chocolatey      | Yes               |
| Linux    | x86_64 (amd64)          | `.deb`              | APT             | Yes               |

> *Homebrew formula supports macOS ARM64 and Linux. Intel Mac support depends on release availability.

### What's in the box

Every release ships two compiler binaries — use whichever fits your workflow:

| Binary | Mode | When to use |
|--------|------|-------------|
| `FlowWing` (`flowwing`) | AOT — compiles `.fg` → native executable | Shipping standalone executables, benchmarking, production |
| `FlowWing-jit` (`flowwing-jit`) | JIT — interprets `.fg` directly, no separate artifact | Quick iteration, scripting, REPL-style runs |

Both share the same SDK layout (`lib/modules/` for `.fg` standard library modules, `lib/<platform>/` for the runtime libraries), and both ship inside the installer / zip / package-manager artifact — no second download needed.

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

> **Heads-up — first-launch OS warnings.** The release installers are **not code-signed** yet, so every platform's first-launch gatekeeping prompt will fire. These are expected and do not indicate a broken build:
>
> - **macOS (`.pkg` / `.dmg`)**: "Apple could not verify 'FlowWing…' is free of malware." → open **System Settings → Privacy & Security → Open Anyway**, or `Ctrl`-click the installer and pick **Open**. On arm64 you may also need `sudo xattr -dr com.apple.quarantine /path/to/FlowWing.pkg` before the first run.
> - **Windows (`.exe` NSIS)**: "Windows protected your PC" / Defender SmartScreen. → click **More info → Run anyway**.
> - **Linux `.deb`**: no warning — `dpkg -i` just works.
>
> Everything below assumes you've cleared the prompt once; it will not recur for that artifact.
>
> **Glibc compatibility (Linux).** The pre-built `.deb` is produced on `ubuntu-latest` (currently Ubuntu 24.04, glibc ≥ 2.39). Users on Ubuntu 20.04 (glibc 2.31) / Debian 11 (glibc 2.31) will see `GLIBC_2.34 not found`. Workaround: upgrade your base OS, use Ubuntu 22.04+ / Debian 12+, or build from source (see [Method 3](#method-3-build-from-source-all-platforms)).

### macOS (Apple Silicon arm64)

Every macOS release ships **two** installers — pick one:

#### Option A: `.pkg` (recommended — auto-PATH)

1. Download `FlowWing-<version>-macos-arm64.pkg`
2. Double-click to launch Installer.app and confirm the admin prompt
3. The package installs the SDK to `/usr/local/flow-wing/<version>/` and its postinstall script drops symlinks in `/usr/local/bin/` (already on Terminal.app's default PATH):

```bash
FlowWing --version        # /usr/local/bin/FlowWing     -> …/<version>/bin/FlowWing
flowwing --version        # lowercase alias
FlowWing-jit --version    # /usr/local/bin/FlowWing-jit -> …/<version>/bin/FlowWing-jit
flowwing-jit --version
```

A stable `/usr/local/flow-wing/current` symlink is maintained too, so upgrades flip the pointer without rewriting `/usr/local/bin`.

#### Option B: `.dmg` (drag-to-Applications)

1. Download `FlowWing-<version>-macos-arm64.dmg`
2. Open the DMG and drag `FlowWing.app` to Applications
3. The DMG **does not** modify your shell PATH automatically (macOS drag-and-drop installs can't run scripts). Export the SDK `bin/` dir once:

```bash
export PATH="/Applications/FlowWing.app/Contents/Resources/FlowWingSDK/bin:$PATH"
FlowWing --version
FlowWing-jit --version
```

Add the `export` line to `~/.zshrc` (or `~/.bash_profile`) to make it permanent. If you prefer an install method that wires up PATH automatically, use the `.pkg` above or [Homebrew](#homebrew-macos).

Or call directly, without editing PATH:

```bash
"/Applications/FlowWing.app/Contents/Resources/FlowWingSDK/bin/FlowWing" --version
"/Applications/FlowWing.app/Contents/Resources/FlowWingSDK/bin/FlowWing-jit" --version
```

### Windows (x86_64)

1. Download `FlowWing-<version>-windows-x86_64.exe`
2. Run the installer — it installs to `C:\Program Files\FlowWing\<version>\`
3. The installer automatically adds Flow-Wing's `bin/` directory to your **machine** PATH via PowerShell (requires admin)
4. Open a **new** terminal (PATH is read at shell startup) and verify:

```powershell
FlowWing --version
FlowWing-jit --version
```

On Windows PATH lookup is case-insensitive, so `flowwing --version` also works.

> **AOT linking on Windows without MSVC:** the installer bundles `lld-link.exe` (from LLVM's LLD) next to `FlowWing.exe`. AOT compilation uses this bundled linker directly, so you **don't need to install MSVC Build Tools** to run `flowwing foo.fg`. A Windows SDK is still required for the C runtime libraries (`ucrt.lib`, `kernel32.lib`, …); `lld-link.exe` auto-detects Windows SDK installs via the registry. Most Windows 10/11 developer machines already have these — install the "Windows 10/11 SDK" standalone package from Microsoft if AOT reports missing `.lib` files.

### Linux (x86_64 / amd64)

1. Download `FlowWing-<version>-linux-x86_64.deb`
2. Install with dpkg:

```bash
sudo dpkg -i FlowWing-<version>-linux-x86_64.deb
flowwing --version
flowwing-jit --version
```

The `.deb` installs the SDK under `/usr/local/flow-wing/<version>/` and the package's `postinst` hook creates symlinks in `/usr/local/bin/`:

- `/usr/local/bin/FlowWing`       → `.../bin/FlowWing`
- `/usr/local/bin/flowwing`       → same (lowercase alias)
- `/usr/local/bin/FlowWing-jit`   → `.../bin/FlowWing-jit`
- `/usr/local/bin/flowwing-jit`   → same (lowercase alias)

No manual PATH edits are needed — `/usr/local/bin` is on the default PATH for every mainstream distro. On `apt purge flowwing` / `dpkg -r flowwing` the `prerm` hook removes those symlinks before the versioned install dir is wiped.

### SDK Archives (All Platforms)

Each release also includes a `.zip` archive containing the full SDK tree (`bin/FlowWing`, `bin/FlowWing-jit`, `lib/modules/`, `lib/<platform>/`). Extract and add to PATH:

```bash
# macOS / Linux example
unzip FlowWing-<version>-macos-arm64.zip -d /opt/flowwing
export PATH="/opt/flowwing/bin:$PATH"
FlowWing --version
FlowWing-jit --version
```

```powershell
# Windows example (PowerShell)
Expand-Archive FlowWing-<version>-windows-x86_64.zip -DestinationPath C:\flowwing
$env:Path = "C:\flowwing\bin;$env:Path"
FlowWing --version
```

---

## Method 2: Package Managers

### Homebrew (macOS)

Flow-Wing is distributed via a community tap. The tap formula installs both compiler binaries into `/opt/homebrew/bin/`, so PATH is wired up automatically:

```bash
brew tap kushagra1212/flowwing
brew install flowwing
FlowWing --version
FlowWing-jit --version
```

Or in one shot:

```bash
brew install kushagra1212/flowwing/flowwing
```

> **Note:** The tap ships an Apple Silicon (arm64) macOS SDK zip. On Intel Macs, `brew install` will stop with a clear message; use Linux/Windows binaries or build from source. Linux is supported via the `.deb` asset in the formula.

### Chocolatey (Windows)

The package downloads the release **zip** into the Chocolatey package `tools` folder (full `bin/` + `lib/` tree) and adds `tools/bin` to the **machine** PATH (requires an elevated/admin Chocolatey install). Chocolatey also creates shims for every `.exe` in the package, so `FlowWing` and `FlowWing-jit` are both invokable from any shell:

```powershell
choco install flowwing
FlowWing --version
FlowWing-jit --version
```

If Chocolatey is not installed, first run:

```powershell
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadScript('https://community.chocolatey.org/install.ps1'))
```

### APT (Linux)

Flow-Wing is published to a custom APT repository. After adding the repo:

```bash
curl -fsSL https://kushagra1212.github.io/Flow-Wing/flowwing.gpg.key | sudo gpg --dearmor -o /etc/apt/keyrings/flowwing.gpg && \
echo "deb [signed-by=/etc/apt/keyrings/flowwing.gpg] https://kushagra1212.github.io/Flow-Wing/ ./" | sudo tee /etc/apt/sources.list.d/flowwing.list > /dev/null && \
sudo apt update && sudo apt install -y flowwing
flowwing --version
flowwing-jit --version
```

> **Note:** The APT repository URL is a placeholder — check the official release workflow for the actual repo configuration. The published package is the same `.deb` shipped as a GitHub Release asset, so `postinst`/`prerm` PATH symlinks (`flowwing`, `flowwing-jit`) apply here too.

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

To build a distributable SDK tree containing both `FlowWing` (AOT) and `FlowWing-jit` (JIT):

```bash
# 1. Stage the AOT compiler + modules + runtime libs
make release-aot-configure RELEASE_INSTALL_PREFIX="/path/to/install"
make release-aot-build     RELEASE_INSTALL_PREFIX="/path/to/install"
make release-aot-install   RELEASE_INSTALL_PREFIX="/path/to/install"

# 2. Build the JIT and drop its binary into the same bin/ as FlowWing-jit
make release-jit-build     RELEASE_INSTALL_PREFIX="/path/to/install"
make release-jit-install   RELEASE_INSTALL_PREFIX="/path/to/install"
```

The JIT step reuses the AOT-staged `lib/modules/` and `lib/<platform>/` — only the `FlowWing-jit` binary is added.

Shortcut targets that chain configure + build + install:

```bash
make release-aot RELEASE_INSTALL_PREFIX="/path/to/install"
make release-jit RELEASE_INSTALL_PREFIX="/path/to/install"
```

Final install tree:

```
/path/to/install/
├── bin/
│   ├── FlowWing                # AOT compiler (compiles .fg → native executable)
│   ├── FlowWing-jit            # JIT interpreter (runs .fg directly)
│   ├── clang++                 # Bundled AOT linker driver (Unix only)
│   └── lld-link.exe            # Bundled AOT linker (Windows only, zero MSVC dep)
└── lib/
    ├── modules/                # .fg standard library (vec, Err, io, map, ...)
    ├── <system>-<arch>/        # Runtime libs (libgc.a, built_in_module, etc.)
    ├── libLLVM.dylib|.so.17    # Unix: clang++'s dylib dep (rpath=@loader_path/../lib)
    ├── libclang-cpp.dylib|…    # Unix: clang++'s dylib dep
    └── libzstd.1.dylib         # macOS only: relocated copy, Homebrew path rewritten
```

`src/common/io/PathUtils.hpp :: getAOTLinkerPath()` resolves the correct sibling at runtime, which is why the installer can ship everything needed for zero-dependency AOT compilation (modulo the Windows SDK's C runtime libs, which `lld-link.exe` auto-detects via the registry).

> **Why the extra dylibs under `lib/`?** Our bundled `clang++` was built against shared `libLLVM` / `libclang-cpp` and has an rpath of `@loader_path/../lib` (macOS) / `$ORIGIN/../lib` (Linux). Without those dylibs staged alongside, `clang++` dies at process start on any machine that doesn't also have them in `/opt/homebrew/opt/llvm@17/lib` (macOS) or `ldconfig`'s cache (Linux). On macOS the release workflow additionally rewrites `libLLVM.dylib`'s hardcoded Homebrew reference to `libzstd.1.dylib` to `@rpath/...` and bundles the resolved file.

The CI release workflow (`.github/workflows/release.yml`) wraps these targets, then hands the tree to `build-installer.sh` which produces the platform-native installers — `.dmg` + `.pkg` on macOS, `.exe` (NSIS) on Windows, `.deb` on Linux.

---

## Post-Installation Verification

After installation, verify both compiler binaries and confirm module + linker resolution work end-to-end. The commands below mirror what the release workflow itself runs as a smoke test (`Smoke-test staged SDK` + `verify-install` jobs), so if they pass on your machine, your install is healthy.

### 1. Versions

```bash
FlowWing --version       # AOT compiler
FlowWing-jit --version   # JIT interpreter
```

Expected output: `FlowWing <version> (AOT|JIT) using LLVM 17.x`.

### 2. Hello, World (AOT — exercises the bundled linker)

The AOT compiler does **not** auto-run programs; it produces a native executable and exits. Give it an output path, then run the produced binary:

```bash
cat > /tmp/hello.fg <<'FG'
println("Hello from Flow-Wing!")
FG

FlowWing /tmp/hello.fg -o /tmp/hello && /tmp/hello
```

If this step fails with an error about `clang++` / linker, your install is missing the bundled linker — see [Troubleshooting](#troubleshooting).

### 3. Module resolution (AOT + JIT)

Exercises standard-library modules (`bring vec`, `bring Err`) which live under `<install>/lib/modules/`:

```bash
cat > /tmp/modtest.fg <<'FG'
bring Err
bring vec

var list: vec::Vec = new vec::Vec()
list.push(1)
list.push(2)
list.push(3)

for var i: int = 0 to list.size() - 1 {
  println(list.get(i))
}

var err: Err::Result = Err::error("boom")
println(err.toString())
FG

# JIT: runs immediately
FlowWing-jit /tmp/modtest.fg

# AOT: compile then run
FlowWing /tmp/modtest.fg -o /tmp/modtest && /tmp/modtest
```

Both commands should print `1`, `2`, `3`, followed by the error's string representation. If either fails with `module 'vec' not found` / `module 'Err' not found`, the SDK `lib/modules/` directory was not unpacked or is not at the expected location relative to the binary — see [Troubleshooting](#troubleshooting).

---

## Troubleshooting

### Common Issues

| Symptom | Cause | Fix |
|---------|-------|-----|
| `flowwing: command not found` after `dpkg -i` | `postinst` symlinks under `/usr/local/bin/` were not created (e.g. installed into a container without `/usr/local/bin` on PATH, or `dpkg` postinst skipped by `--no-triggers`) | Call by full path: `/usr/local/flow-wing/<version>/bin/FlowWing --version`. To recreate the symlinks: `sudo ln -sfn /usr/local/flow-wing/<ver>/bin/FlowWing /usr/local/bin/flowwing && sudo ln -sfn /usr/local/flow-wing/<ver>/bin/FlowWing-jit /usr/local/bin/flowwing-jit` |
| `FlowWing` works but `flowwing --version` errors on Linux | Lowercase alias symlink missing | Same fix as above (`ln -sfn .../FlowWing /usr/local/bin/flowwing`) |
| macOS: `zsh: command not found: FlowWing` after DMG install | The DMG installer cannot modify your shell PATH — only the `.pkg`, Homebrew, or a manual `export` can | Switch to the `.pkg` installer (auto-PATH via `/usr/local/bin/` symlinks), use `brew install kushagra1212/flowwing/flowwing`, or `export PATH="/Applications/FlowWing.app/Contents/Resources/FlowWingSDK/bin:$PATH"` (persist in `~/.zshrc`) |
| macOS: `.pkg` installer succeeded but `flowwing` still not found | `/usr/local/bin` not on your shell's PATH (rare on macOS, possible in minimal shells) | Add `/usr/local/bin` to PATH: `echo 'export PATH="/usr/local/bin:$PATH"' >> ~/.zshrc && source ~/.zshrc`. Or call by full path: `/usr/local/flow-wing/current/bin/FlowWing --version` |
| Windows: `flowwing` not found immediately after NSIS install | Machine PATH was updated but your current shell cached the old PATH | Open a **new** terminal (cmd/pwsh/Git Bash) — PATH is read at shell startup |
| Windows: `lld-link: error: could not open 'ucrt.lib'` / `kernel32.lib` during AOT | Windows SDK C-runtime libs missing (the bundled `lld-link.exe` finds them via the registry) | Install the standalone **Windows 10/11 SDK** from Microsoft — you do **not** need the full MSVC Build Tools, just the SDK. After install, reopen the terminal and retry `FlowWing foo.fg` |
| `Couldn't find clang++` / `lld-link` / linker spawn error when compiling AOT | Bundled linker is missing from the install (deleted, or unpacked without preserving permissions) | Copy / reinstall the release. Unix: `<install>/bin/clang++` must sit next to `FlowWing`. Windows: `<install>/bin/lld-link.exe` must sit next to `FlowWing.exe`. As a temporary workaround, Unix users can `brew install llvm@17` / `apt install clang-17` and Windows users can launch from a Developer Command Prompt (where `link.exe` is on PATH) |
| `module 'vec' not found` / `module 'Err' not found` at compile time | `lib/modules/` directory missing or not alongside `bin/` | Verify the install tree: `ls <install>/lib/modules/*.fg` should list `vec-module.fg`, `Err-module.fg`, etc. If unzipping manually, preserve the archive's directory structure. You can also force the lookup with `FLOWWING_MODULES_PATH=/path/to/lib/modules` |
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
