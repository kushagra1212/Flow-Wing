# Flow-Wing vs C++ Benchmark Report

Generated: 2026-09-22 16:56:46 UTC

## Reference configuration

Machine fingerprint: `14351c92219e`. Compare two reports directly only when this value matches.

| | |
|---|---|
| CPU | Apple M4 Pro |
| Cores | 12 physical / 12 logical |
| Memory | 24.0 GiB |
| OS | Darwin 24.6.0 (arm64) |
| Power source | AC Power |
| Load average (1m, at start) | 3.16 |
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
| `00_startup` | 1.12 ± 0.08 | 1.01 ± 0.03 | 1.10x :warning: | An empty program. This measures the cost to create a process, which every other run figure includes. |
| `01_fib_recursive` | 8.51 ± 0.14 | 4.74 ± 0.09 | 1.79x | Recursive Fibonacci with no memoisation. This measures function call cost, argument passing and branch prediction. |
| `02_loop_arith` | 55.69 ± 1.60 | 55.47 ± 0.67 | 1.00x | A tight integer loop with a multiply and a modulo. This measures arithmetic speed and loop code generation. |
| `03_collatz` | 70.03 ± 0.68 | 22.70 ± 0.36 | 3.08x | The longest Collatz chain below N. This measures integer work with many branches and 64-bit values. |
| `04_matmul` | 3.50 ± 0.12 | 2.71 ± 0.23 | 1.29x :warning: | A 64x64 integer matrix multiply, repeated. This measures nested loops and access to fixed-size 2D arrays. |
| `05_mandelbrot` | 2.62 ± 0.18 | 2.36 ± 0.12 | 1.11x :warning: | Mandelbrot set membership over a square grid. This measures double-precision arithmetic with a branch on computed data. |
| `06_nbody` | 21.35 ± 0.40 | 21.14 ± 0.31 | 1.01x | A five-body gravity simulation with a square root written by hand. C++ uses -ffp-contract=off because Flow-Wing emits no FMA instructions. Without that flag the two results differ after about 5000 steps. |
| `07_sieve_vec` | 11.06 ± 0.28 | 1.85 ± 0.05 | 5.99x | A Sieve of Eratosthenes over vec::Vec against std::vector. This measures container element access and heap growth. |
| `08_quicksort` | 39.19 ± 0.36 | 8.00 ± 0.09 | 4.90x | A Lomuto quicksort over vec::Vec against std::vector. This measures recursion with many indexed reads and writes. |
| `09_string_build` | 22.49 ± 0.52 | 3.11 ± 0.06 | 7.24x | Repeated string concatenation by value. Both sides build a new string at each step, so this measures allocation and copy cost under the same rules. |
| `10_map_churn` | 75.54 ± 1.01 | 10.03 ± 0.49 | 7.53x | Hash map insert and lookup with string keys, map::Map against std::unordered_map. |
| `11_gc_pressure` | 14.01 ± 0.22 | 1.74 ± 0.09 | 8.05x :warning: | Allocate one short-lived object per iteration and drop it. This compares the Flow-Wing collector against C++ new and delete. |

## Compile time

| Case | Flow-Wing (ms) | C++ (ms) | Flow-Wing / C++ |
|---|---:|---:|---:|
| `00_startup` | 68.61 ± 3.68 | 67.39 ± 0.64 | 1.02x :warning: |
| `01_fib_recursive` | 70.82 ± 0.85 | 70.48 ± 0.59 | 1.00x |
| `02_loop_arith` | 74.07 ± 2.52 | 70.75 ± 3.73 | 1.05x :warning: |
| `03_collatz` | 72.46 ± 16.38 | 71.36 ± 1.67 | 1.02x :warning: |
| `04_matmul` | 88.59 ± 14.74 | 75.96 ± 1.18 | 1.17x :warning: |
| `05_mandelbrot` | 75.06 ± 2.63 | 73.38 ± 1.86 | 1.02x |
| `06_nbody` | 83.17 ± 6.22 | 77.76 ± 0.72 | 1.07x :warning: |
| `07_sieve_vec` | 82.76 ± 1.09 | 341.11 ± 30.51 | 0.24x :warning: |
| `08_quicksort` | 87.49 ± 2.30 | 327.91 ± 6.87 | 0.27x |
| `09_string_build` | 102.00 ± 4.55 | 274.61 ± 6.76 | 0.37x |
| `10_map_churn` | 82.83 ± 2.08 | 332.28 ± 4.93 | 0.25x |
| `11_gc_pressure` | 76.04 ± 4.23 | 185.30 ± 1.52 | 0.41x :warning: |

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
| `09_string_build` | 93.4 KB | 33.7 KB | 2.77x |
| `10_map_churn` | 95.3 KB | 35.4 KB | 2.69x |
| `11_gc_pressure` | 73.8 KB | 32.7 KB | 2.26x |

## Summary

- **run**: the Flow-Wing time is 2.64x the C++ time, as a geometric mean over 12 cases. A value below 1.00 means Flow-Wing is faster.
- **compile**: the Flow-Wing time is 0.62x the C++ time, as a geometric mean over 12 cases. A value below 1.00 means Flow-Wing is faster.

