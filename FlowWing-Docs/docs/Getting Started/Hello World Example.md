---
sidebar_position: 2
---

# Hello World Example

In this section, you'll learn how to write and run a simple "Hello World" program in Flow-Wing.

## A Basic Example

Create a file named `main.fg` with the following content:

```js
print("Hello World")
```

Run the program in Flow-Wing:

**1. Using AOT (Ahead-of-Time) Compilation**

- Compile your program with the following command:

```bash
flowwing -F=main.fg
```

- Run the Executable

```bash
./build/bin/main
```

**2. Using JIT (Just-In-Time) Compilation**

- Alternatively, you can run the program directly without compiling:

```bash
flowwing -F=main.fg
```

**Output:**

```bash
Hello World
```
