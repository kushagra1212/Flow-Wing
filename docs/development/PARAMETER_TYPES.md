### The New "Contract":

Here are the rules you've established:

1.  `(a: str)` is **Pass-by-Value**. The function receives a _copy_.
2.  `(inout a: str)` is **Pass-by-Reference**. The function receives a _pointer_ to the original variable.
3.  `as` is a special modifier **only for C FFI** to force a direct, C-compatible memory layout. It's not for general use.
4.  **Semantic Error:** `inout` and `as` used together is an illegal combination.

| Syntax              | `Symbol.m_value_kind` | `Symbol.m_calling_convention` | What it means                                                                  |
| :------------------ | :-------------------- | :---------------------------- | :----------------------------------------------------------------------------- |
| `(a: str)`          | `kByValue`            | `kFlowWing` (default)         | Pass a copy, using the language's standard memory layout (e.g., boxed values). |
| `(inout a: str)`    | `kByReference`        | `kFlowWing` (default)         | Pass a pointer to the original variable.                                       |
| `(a: as str)`       | `kByValue`            | `kC`                          | Pass a copy, using a direct C-compatible memory layout.                        |
| `(inout a: as str)` | **N/A**               | **N/A**                       | **This is a semantic error.**                                                  |
