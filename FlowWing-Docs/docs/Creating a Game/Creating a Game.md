---
sidebar_position: 8
title: Games and graphics (raylib)
sidebar_label: Games and graphics (raylib)
---

# Games and graphics (raylib)

## What to expect

**Flow-Wing** can drive **2D/3D games and apps** the same way you would from C: you **`bring raylib`** in your **`.fg`** source, and you pass **native link options** to the **Flow-Wing** compiler (library search path **`-L`**, system library **`-l`**, and on **macOS** often **`--framework`** for GL/windowing). The **`raylib`** you use is the one **installed on your machine**; the language ships the **module bindings**, not a copy of the game engine.

1. **Install** the compiler and (separately) a **raylib** build for your OS—see the main repo **[INSTALL](https://github.com/kushagra1212/Flow-Wing/blob/main/docs/INSTALL.md)** and your platform’s **raylib** install guide.
2. In code: **`bring raylib`**, then create a **`raylib::Window`**, run an **update / draw** loop, load textures and handle input the way the **`raylib`** module exposes in Flow-Wing.
3. On the **command line:** compile with the same **`-L` / `-l`** (and **frameworks** on Mac) you would use for a small **C + raylib** program. All flags are in *Language Fundamentals → **Flow-Wing CLI***.

If you are new to the toolchain, do *Getting Started → **Installation*** and *Hello World* first, then come back here.

## Quick example

A minimal game window in Flow-Wing with raylib:

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

Compile it by passing the **raylib** library to the linker:

- **Windows:** `raylib.lib`
- **Linux:** `libraylib.so`
- **macOS:** `libraylib.dylib`

Example:

```bash
flowwing game.fg -o game -L/path/to/raylib -l raylib
```

## Two demos in the main repository (clone required)

The **open-source** Flow-Wing tree (not the docs site alone) includes ready-made samples under **`docs/demo/`**—use them once you can compile **`.fg`** and have **raylib** on disk:

| Demo | Path | What it is |
|------|------|------------|
| **Bird** | **`docs/demo/bird-game/bird.fg`** | **Single file** flappy-style game: classes, parallax, textures, a simple menu loop. Good first read. |
| **Platformer** | **`docs/demo/platform-game/main.fg`** (plus **`Player.fg`**, **`Platform.fg`**, **…** in the same folder) | **Multi-file** “side-scroller” style: local **`bring` from `"./…"`** next to **`.fg`**. Run the compiler on **`main.fg`** with your **current directory** in **`docs/demo/platform-game`** so those paths resolve. |

These are **learning examples** shipped with the repo; they are not a separate product or engine.

### How to run a demo (pattern)

- **Build the compiler** from the repo (or use a **prebuilt** SDK) so you have **`flowwing` / `FlowWing`** on your **PATH** or a path to the **`bin`** tool.
- **Point `-L` at the directory** that contains your **raylib** import library / shared library, and add **`-l raylib`** (or the name your **OS** uses). On **macOS** you may need **several** **`--framework`** options for **Cocoa / OpenGL**—match what **raylib**’s C examples use on that OS.
- **Bird** — from the repository root, you can do something like (paths are **examples only**; fix **`-L`** to your **raylib** install):

  ```bash
  cd docs/demo/bird-game
  FlowWing bird.fg -o bird -L/usr/local/lib -l raylib
  ./bird
  ```

  On **Windows**, the library name and paths differ (often **`.lib`** next to the compiler or under **vcpkg** / a **raylib** SDK); use the same **`-L` / `-l`** style as in the **CLI** page.

- **Platform** — `cd` into **`docs/demo/platform-game`**, compile **`main.fg`** the same way (raylib **`-L` / `-l`**, plus frameworks on **Mac**). The entry file pulls **`./Player.fg`**, **`./utils.fg`**, etc. via **`bring`**, so the **current working directory** and **import paths** must match how you invoke **FlowWing** (the compiler resolves **`bring "…"`** from the **`.fg` file’s directory**—see the **modules** section of the docs if imports fail).

If linking fails, the issue is almost always **raylib not found** or **missing system frameworks**—not Flow-Wing syntax. Fix **`-L` / `-l` / `--framework`**, then re-run.

## More detail: linking, other libraries, and another repo

- **Not only raylib** — any C library you can link from a **C** toolchain on your **OS** is fair game: pass **`-L`**, **`-l`**, and on **macOS** **`--framework`** the same way. Games are a popular use; the mechanism is the same for other native code.
- **Why linking matters** — **`bring raylib`** tells the **compiler** about **types and calls**; the **linker** still needs a real **raylib** binary. That is why **AOT** builds require correct **`-L` / `-l`**. The **Release**-style **SDK** bundles a **C++**-style **linker driver** for **Flow-Wing** output; you still supply the **raylib** **library** you built or installed.
- **External project** — an older, repo-sized sample also lives on GitHub: **[Bird-Game-in-FlowWing](https://github.com/kushagra1212/Bird-Game-in-FlowWing/tree/main)**. It is **not** the same path as **`docs/demo/bird-game`**; treat it as an extra reference if you outgrow the in-tree demos.
- **Assets** — the in-repo demos may expect **image files** next to the **`.fg`** (e.g. under **`file::__DIR__`** or paths in the code). Run from the right folder, or copy assets with your build.

## See also

- *Language Fundamentals → **Flow-Wing CLI*** — **`-L`**, **`-l`**, **`--framework`**
- *Getting Started → **Installation*** — a working **bin** and **lib/modules** layout
- **Advanced** topics on **`bring`**, **modules**, and **objects** for larger games
