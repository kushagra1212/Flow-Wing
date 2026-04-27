---
sidebar_position: 1
---

import CodeBlock from "@site/src/components/common/CodeBlock";

### Flow-Wing Programming Language

<CodeBlock code={
`print("Hello, World!")
`} language="fg"/>

<div style={{ display: 'flex', flexDirection: 'column', alignItems: 'center' }}>
    <img src={require('../../static/img/flowwing-icon.png').default} alt="Flow-Wing Logo" style={{ maxWidth: '100%', height: 'auto' }} />
    <strong style={{ margin: '20px 0' }}>Flow-Wing: A programming language</strong>
</div>

**Flow-Wing** (`.fg` sources) builds on LLVM. One compiler project gives you two tools: an **ahead-of-time (AOT)** binary that compiles to a native executable, and a separate **just-in-time (JIT)** binary that runs programs in one step. The runtime uses the **Boehm** garbage collector for heap data — you never pair allocations with manual `free`.

This site is your guide to the **Flow-Wing language**: syntax, types, `bring`, standard modules, and how to use the **compiler** you installed (or built). To **build the toolchain from source** (LLVM, dependencies, the `make` targets), head to the [Flow-Wing](https://github.com/kushagra1212/Flow-Wing) repository and follow *Getting Started → Installation*.
