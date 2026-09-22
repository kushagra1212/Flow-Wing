# Flow-Wing vs C++ Benchmark Report

Generated: 2026-09-22 15:17:05 UTC

## Reference configuration

Machine fingerprint: `14351c92219e`. Compare two reports directly only when this value matches.

| | |
|---|---|
| CPU | Apple M4 Pro |
| Cores | 12 physical / 12 logical |
| Memory | 24.0 GiB |
| OS | Darwin 24.6.0 (arm64) |
| Power source | AC Power |
| Load average (1m, at start) | 4.38 |
| Flow-Wing | 1.0.16 |
| C++ baseline | clang version 17.0.6 (https://github.com/llvm/llvm-project.git 6009708b4367171ccdbf4b5905cb6a803753fe18) |
| Optimization | -O2 (both toolchains) |
| Sampling | 7 iterations x 15 repetitions (compile: 5 repetitions) |

## How to read this report

Each time in milliseconds belongs to the machine listed above. The same times will not appear on different hardware.

**Use the ratio column.** Flow-Wing and C++ ran on the same machine, in the same session, and one statistics engine measured both. The hardware therefore has less effect on the ratio than on the raw time. Read C++ as the reference point, and read the ratio as the Flow-Wing time divided by the C++ time.

Both columns time a process from start to end, so every figure includes process creation. The `00_startup` case measures that cost on its own. A row marked :warning: has a standard deviation above 5% of its median on at least one side. The last digits of such a ratio are noise.

## Execution time

| Case | Flow-Wing (ms) | C++ (ms) | Flow-Wing / C++ | What it measures |
|---|---:|---:|---:|---|
| `00_startup` | 1.11 ± 0.11 | 0.97 ± 0.04 | 1.15x :warning: | An empty program. This measures the cost to create a process, which every other run figure includes. |
| `01_fib_recursive` | 13.96 ± 0.27 | 4.62 ± 0.05 | 3.02x | Recursive Fibonacci with no memoisation. This measures function call cost, argument passing and branch prediction. |
| `02_loop_arith` | 59.98 ± 0.53 | 55.30 ± 0.56 | 1.08x | A tight integer loop with a multiply and a modulo. This measures arithmetic speed and loop code generation. |
| `03_collatz` | 82.04 ± 0.72 | 22.66 ± 0.35 | 3.62x | The longest Collatz chain below N. This measures integer work with many branches and 64-bit values. |
| `04_matmul` | 11.23 ± 0.24 | 2.61 ± 0.04 | 4.31x | A 64x64 integer matrix multiply, repeated. This measures nested loops and access to fixed-size 2D arrays. |
| `05_mandelbrot` | 6.75 ± 0.06 | 2.37 ± 0.25 | 2.85x :warning: | Mandelbrot set membership over a square grid. This measures double-precision arithmetic with a branch on computed data. |
| `06_nbody` | 115.12 ± 0.69 | 21.01 ± 0.35 | 5.48x | A five-body gravity simulation with a square root written by hand. C++ uses -ffp-contract=off because Flow-Wing emits no FMA instructions. Without that flag the two results differ after about 5000 steps. |
| `07_sieve_vec` | 12.01 ± 0.31 | 1.79 ± 0.05 | 6.69x | A Sieve of Eratosthenes over vec::Vec against std::vector. This measures container element access and heap growth. |
| `08_quicksort` | 47.68 ± 0.39 | 7.83 ± 0.06 | 6.09x | A Lomuto quicksort over vec::Vec against std::vector. This measures recursion with many indexed reads and writes. |
| `09_string_build` | 22.16 ± 0.52 | 3.01 ± 0.09 | 7.36x | Repeated string concatenation by value. Both sides build a new string at each step, so this measures allocation and copy cost under the same rules. |
| `10_map_churn` | 74.06 ± 0.65 | 9.77 ± 0.27 | 7.58x | Hash map insert and lookup with string keys, map::Map against std::unordered_map. |
| `11_gc_pressure` | 14.15 ± 0.52 | 2.11 ± 0.22 | 6.71x :warning: | Allocate one short-lived object per iteration and drop it. This compares the Flow-Wing collector against C++ new and delete. |

## Compile time

| Case | Flow-Wing (ms) | C++ (ms) | Flow-Wing / C++ |
|---|---:|---:|---:|
| `00_startup` | 63.93 ± 1.27 | 65.31 ± 0.85 | 0.98x |
| `01_fib_recursive` | 66.31 ± 0.51 | 68.27 ± 0.66 | 0.97x |
| `02_loop_arith` | 68.25 ± 1.57 | 68.69 ± 2.35 | 0.99x |
| `03_collatz` | 67.23 ± 1.04 | 69.72 ± 1.02 | 0.96x |
| `04_matmul` | 77.67 ± 1.40 | 74.27 ± 0.55 | 1.05x |
| `05_mandelbrot` | 66.97 ± 0.94 | 69.80 ± 0.83 | 0.96x |
| `06_nbody` | 72.73 ± 0.97 | 75.02 ± 0.39 | 0.97x |
| `07_sieve_vec` | 77.10 ± 1.77 | 324.68 ± 3.66 | 0.24x |
| `08_quicksort` | 78.65 ± 4.64 | 324.55 ± 7.54 | 0.24x :warning: |
| `09_string_build` | 83.01 ± 0.66 | 270.10 ± 6.05 | 0.31x |
| `10_map_churn` | 74.89 ± 1.46 | 324.57 ± 1.51 | 0.23x |
| `11_gc_pressure` | 71.44 ± 3.44 | 188.14 ± 1.30 | 0.38x |

## Binary size

| Case | Flow-Wing | C++ | Flow-Wing / C++ |
|---|---:|---:|---:|
| `00_startup` | 71.8 KB | 32.6 KB | 2.20x |
| `01_fib_recursive` | 73.5 KB | 32.7 KB | 2.25x |
| `02_loop_arith` | 73.6 KB | 32.7 KB | 2.25x |
| `03_collatz` | 73.7 KB | 32.7 KB | 2.26x |
| `04_matmul` | 73.9 KB | 32.7 KB | 2.26x |
| `05_mandelbrot` | 73.6 KB | 32.7 KB | 2.25x |
| `06_nbody` | 74.4 KB | 32.8 KB | 2.27x |
| `07_sieve_vec` | 111.0 KB | 34.0 KB | 3.27x |
| `08_quicksort` | 111.1 KB | 34.1 KB | 3.26x |
| `09_string_build` | 93.7 KB | 33.7 KB | 2.78x |
| `10_map_churn` | 95.3 KB | 35.4 KB | 2.70x |
| `11_gc_pressure` | 73.8 KB | 32.7 KB | 2.26x |

## Summary

- **run**: the Flow-Wing time is 3.94x the C++ time, as a geometric mean over 12 cases. A value below 1.00 means Flow-Wing is faster.
- **compile**: the Flow-Wing time is 0.58x the C++ time, as a geometric mean over 12 cases. A value below 1.00 means Flow-Wing is faster.

