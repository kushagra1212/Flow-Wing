---
sidebar_position: 1
---

### Flow-Wing Programming Language

```flowwing
print("Hello, World!")
```

<div style={{ display: 'flex', flexDirection: 'column', alignItems: 'center' }}>
    <img src={require('../../static/img/flowwing-icon.png').default} alt="Flow-Wing Logo" style={{ maxWidth: '100%', height: 'auto' }} />
    <strong style={{ margin: '20px 0' }}>Flow-Wing: A programming language</strong>
</div>

**Flow-Wing** (`.fg` sources) is an LLVM-based language: the same compiler project builds an **ahead-of-time (AOT)** binary that compiles to a native executable, and a separate **just-in-time (JIT)** binary that runs programs without a separate link step. The runtime library uses the **Boehm** garbage collector for heap data.

This site documents the **Flow-Wing language**—syntax, types, `bring`, standard modules, and how to use the **compiler** you installed (or built). **To build the toolchain from source** (LLVM, dependencies, the `make` targets), use the [Flow-Wing](https://github.com/kushagra1212/Flow-Wing) repository and *Getting Started → Installation*.
