# Flow-Wing vs C++ Benchmark Report

Generated: 2026-09-22 14:39:06 UTC

## Reference configuration

Machine fingerprint: `14351c92219e`. Compare two reports directly only when this value matches.

| | |
|---|---|
| CPU | Apple M4 Pro |
| Cores | 12 physical / 12 logical |
| Memory | 24.0 GiB |
| OS | Darwin 24.6.0 (arm64) |
| Power source | AC Power |
| Load average (1m, at start) | 4.15 |
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
| `00_startup` | 1.17 ± 0.13 | 1.05 ± 0.03 | 1.11x :warning: | An empty program. This measures the cost to create a process, which every other run figure includes. |
| `01_fib_recursive` | 15.30 ± 0.28 | 5.01 ± 0.11 | 3.05x | Recursive Fibonacci with no memoisation. This measures function call cost, argument passing and branch prediction. |
| `02_loop_arith` | 65.23 ± 0.57 | 58.01 ± 0.68 | 1.12x | A tight integer loop with a multiply and a modulo. This measures arithmetic speed and loop code generation. |
| `03_collatz` | 87.93 ± 0.56 | 23.54 ± 0.68 | 3.74x | The longest Collatz chain below N. This measures integer work with many branches and 64-bit values. |
| `04_matmul` | 11.87 ± 0.20 | 2.76 ± 0.04 | 4.29x | A 64x64 integer matrix multiply, repeated. This measures nested loops and access to fixed-size 2D arrays. |
| `05_mandelbrot` | 7.31 ± 0.41 | 2.47 ± 0.15 | 2.96x :warning: | Mandelbrot set membership over a square grid. This measures double-precision arithmetic with a branch on computed data. |
| `06_nbody` | 120.21 ± 0.92 | 21.69 ± 0.33 | 5.54x | A five-body gravity simulation with a square root written by hand. C++ uses -ffp-contract=off because Flow-Wing emits no FMA instructions. Without that flag the two results differ after about 5000 steps. |
| `07_sieve_vec` | 12.47 ± 0.09 | 2.17 ± 0.46 | 5.74x :warning: | A Sieve of Eratosthenes over vec::Vec against std::vector. This measures container element access and heap growth. |
| `08_quicksort` | 48.13 ± 0.42 | 8.38 ± 0.11 | 5.74x | A Lomuto quicksort over vec::Vec against std::vector. This measures recursion with many indexed reads and writes. |
| `09_string_build` | 23.30 ± 0.36 | 3.31 ± 0.10 | 7.04x | Repeated string concatenation by value. Both sides build a new string at each step, so this measures allocation and copy cost under the same rules. |
| `10_map_churn` | 76.52 ± 0.74 | 10.14 ± 0.24 | 7.54x | Hash map insert and lookup with string keys, map::Map against std::unordered_map. |
| `11_gc_pressure` | 14.53 ± 0.27 | 1.84 ± 0.09 | 7.90x | Allocate one short-lived object per iteration and drop it. This compares the Flow-Wing collector against C++ new and delete. |

## Compile time

| Case | Flow-Wing (ms) | C++ (ms) | Flow-Wing / C++ |
|---|---:|---:|---:|
| `00_startup` | 68.05 ± 0.90 | 70.92 ± 3.81 | 0.96x :warning: |
| `01_fib_recursive` | 74.63 ± 6.99 | 74.17 ± 1.52 | 1.01x :warning: |
| `02_loop_arith` | 71.50 ± 0.89 | 74.99 ± 1.27 | 0.95x |
| `03_collatz` | 71.89 ± 2.25 | 73.82 ± 1.33 | 0.97x |
| `04_matmul` | 11928.27 ± 62.29 | 79.57 ± 37.25 | 149.90x :warning: |
| `05_mandelbrot` | 74.75 ± 1.14 | 76.63 ± 7.41 | 0.98x :warning: |
| `06_nbody` | 80.42 ± 3.20 | 81.14 ± 1.50 | 0.99x |
| `07_sieve_vec` | 81.94 ± 1.20 | 341.13 ± 35.05 | 0.24x :warning: |
| `08_quicksort` | 81.57 ± 2.82 | 339.36 ± 8.32 | 0.24x |
| `09_string_build` | 87.18 ± 2.10 | 285.52 ± 10.44 | 0.31x |
| `10_map_churn` | 79.19 ± 1.27 | 338.58 ± 9.56 | 0.23x |
| `11_gc_pressure` | 75.24 ± 3.63 | 189.97 ± 0.76 | 0.40x |

## Binary size

| Case | Flow-Wing | C++ | Flow-Wing / C++ |
|---|---:|---:|---:|
| `00_startup` | 71.8 KB | 32.6 KB | 2.20x |
| `01_fib_recursive` | 73.5 KB | 32.7 KB | 2.25x |
| `02_loop_arith` | 73.6 KB | 32.7 KB | 2.25x |
| `03_collatz` | 73.7 KB | 32.7 KB | 2.26x |
| `04_matmul` | 138.5 KB | 32.7 KB | 4.23x |
| `05_mandelbrot` | 73.6 KB | 32.7 KB | 2.25x |
| `06_nbody` | 74.4 KB | 32.8 KB | 2.27x |
| `07_sieve_vec` | 111.0 KB | 34.0 KB | 3.27x |
| `08_quicksort` | 111.1 KB | 34.1 KB | 3.26x |
| `09_string_build` | 93.7 KB | 33.7 KB | 2.78x |
| `10_map_churn` | 95.3 KB | 35.4 KB | 2.70x |
| `11_gc_pressure` | 73.8 KB | 32.7 KB | 2.26x |

## Summary

- **run**: the Flow-Wing time is 3.94x the C++ time, as a geometric mean over 12 cases. A value below 1.00 means Flow-Wing is faster.
- **compile**: the Flow-Wing time is 0.88x the C++ time, as a geometric mean over 12 cases. A value below 1.00 means Flow-Wing is faster.

