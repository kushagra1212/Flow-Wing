---
sidebar_position: 2
---

# Hello World

## 1. Create a small program

Create a new file called **`main.fg`** in a folder of your choice and put this in it:

```text
print("Hello World")
```

You can use any editor. Flow-Wing source files use the **`.fg`** extension.

## 2. Run it (after *Installation*)

You need a Flow-Wing compiler on your **PATH** or the full **SDK** unpacked so you can run the **`bin`** tools—see *Getting Started → Installation*.

**Compile to an app, then run it (AOT)** — typical when your command is **`flowwing`**, **`FlowWing`**, or **`FlowWing.exe`:**

```bash
flowwing main.fg -o myapp
./myapp
```

On Windows, use a **`.exe`** name with **`-o`** (for example **`-o myapp.exe`**) and run **`.\myapp.exe`**.

**Run the script in one go (JIT)** — if you installed the **JIT** binary as **`flowwing-jit`** / **`FlowWing-jit`** (see *Flow-Wing CLI*), you can skip a separate app file:

```bash
flowwing-jit main.fg
```

The **same `main.fg`** works for both; which command you have depends on your install (many SDKs include **both** AOT and JIT names).

## 3. Expected output

```text
Hello World
```

## 4. If you build the compiler from the GitHub repository

This is for people hacking on Flow-Wing itself. From the repo root, after **Installation**-style `make` steps and an AOT build (for example **`make build-aot-debug`**), the staged tool is under **`build/sdk/bin/`**:

```bash
./build/sdk/bin/FlowWing main.fg -o build/bin/main
./build/bin/main
```

**Or** one step:

```bash
make run-aot-debug FILE=path/to/main.fg
```

**JIT from source:** if you used **`make build-jit-debug`**, the file **`build/sdk/bin/FlowWing`** may run **`main.fg`** directly in one step—same path as in the *Flow-Wing CLI* page. The last **`make build-aot-***` or **`build-jit-***` you ran decides what that one binary does.

**Tip:** with AOT, pass **`-o some/path`** when you want a **fixed** output name. Without **`-o`**, the compiler may still emit a binary under a default build directory, sometimes with an **unstable** name (for example a hash) so parallel builds do not overwrite each other.

## Entry point and `fg_main` (optional detail)

The short program above is only **top-level** code; you do not need a **`fg_main`** function for that. When you add a real **entry** function, the usual name is **`fg_main`**, and you **do not** define a top-level C-style **`main`** in **`.fg`** (that name is reserved for the host the compiler links in). You can set another entry with **`--entry-point`** (**`-e`**) on the **CLI**; see *Language Fundamentals → Flow-Wing CLI*.
