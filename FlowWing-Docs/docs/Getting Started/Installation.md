---
sidebar_position: 1
---

# Installation

## Install a prebuilt build (start here)

1. Open the Flow-Wing **[GitHub Releases](https://github.com/kushagra1212/Flow-Wing/releases)** page and download the file that matches your computer (see the table in the next section). The **installer** (`.pkg`, `.exe`, or `.deb`) is usually the easiest path; a **`.zip` SDK** is the portable “unpack and use” option.
2. Run the installer (or unpack the zip) and, if the installer offers it, let it add the tools to your **PATH** so you can run **`flowwing`** and **`flowwing-jit`** from a terminal.
3. Check that the compiler is visible:

   ```bash
   flowwing --version
   flowwing-jit --version
   ```

   On some setups the commands are **`FlowWing`**, **`FlowWing-jit`**, or **`FlowWing.exe`**—use the names your install added to **PATH**, or the **`bin`** folder inside the SDK you unpacked.

You now have the **AOT** compiler (build a native app from **`.fg`**) and the **JIT** tool (run **`.fg`** in one step, no separate app binary to launch). Next, try *Getting Started → Hello World Example* and *Language Fundamentals → Flow-Wing CLI*.

## Which file is for me?

| Your system | What to look for in the release |
|-------------|---------------------------------|
| **Mac with Apple Silicon (M1/M2/M3…)** | **`.pkg` or `.dmg`**, or the **macOS arm64** **`.zip`** |
| **Windows 64-bit** | **`.exe` installer** or the **windows-x86_64** **`.zip`** |
| **Linux 64-bit (x86_64)** | **`.deb`** (where that fits your distro) or the **linux-x86_64** **`.zip`** |

Release assets are named with the **version tag** (for example **`FlowWing-v0.0.4-macos-arm64.pkg`**)—pick the same tag on the [releases](https://github.com/kushagra1212/Flow-Wing/releases) page for every file you download.

A full **SDK** install gives you the **`bin`** tools (**`flowwing` / `FlowWing`**, **`flowwing-jit` / `FlowWing-jit`**) plus **`lib/modules/`** (standard **`.fg` library**) and the pieces the compiler needs to **link** AOT output on your machine, without you installing **LLVM** yourself for normal use.

**Optional:** *Homebrew*, *Chocolatey*, and *apt* may also ship Flow-Wing, but the feed can update **slower** than a fresh download on **GitHub Releases**—if something is missing or old, get the build from the release page first.

## Build from source (developers)

For a full clone of the [Flow-Wing](https://github.com/kushagra1212/Flow-Wing) repository you need a C/C++ toolchain and **Python 3** (for tests and scripts). **LLVM 17 is downloaded and built automatically** by the first `make` step — you do not need to install it separately. On **macOS** also install `automake`, `autoconf`, and `libtool` (`brew install automake autoconf libtool`); on **Linux** use `apt-get install automake autoconf libtool`.

From the repo root:

```bash
make deps-install-debug
make build-aot-debug       # or: make build-jit-debug
```

The compiler is staged at **`build/sdk/bin/FlowWing`**. See the **Hello World** page for **`make run-aot-debug`** and **`make run-jit-debug`**, and the main repo’s **`AGENTS.md`** for more **make** targets and conventions.

**Release / installer style builds** (what produces the public installers) use the **Release** dependency target and the **`release-aot`** / **`release-jit`** make targets with `RELEASE_INSTALL_PREFIX` — that workflow is for maintainers; details are in the section below.

## Details (CI, release workflow, and file naming)

- **Where the installers come from:** when a [release](https://github.com/kushagra1212/Flow-Wing/releases) is **published** on GitHub, automation builds the macOS, Windows, and Linux artifacts and uploads them to that release. The process is defined in the repo as **`.github/workflows/release.yml`** (a **`workflow_dispatch`** run can also be used for a dry run with a test tag). You do not need to read that file to install Flow-Wing; it is there for **transparency and contributors**.

- **What the matrix produces:** the same **Release** job builds **macOS arm64** (**.pkg**, **.dmg**, **.zip**), **Windows x86_64** (**.exe** NSIS, **.zip**), and **Linux x86_64** (**.deb**, **.zip**), each containing **FlowWing (AOT)** and **FlowWing-jit (JIT)**, the bundled AOT **linker** and **lib** layout described above.

- **Package manager publishing** (Homebrew, Chocolatey, apt) and **extension** publishing run in follow-up steps of that workflow; they can **lag** the assets on the release page, which is why the table above points beginners at **GitHub Releases** first.

## This documentation site

This site (syntax, **CLI**, standard modules) is published at [flow-wing-docs.vercel.app](https://flow-wing-docs.vercel.app/). The **Docusaurus** project lives in the **`FlowWing-Docs`** folder next to the compiler repository.
