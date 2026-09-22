# Flow-Wing vs C++ Benchmark Report

Generated: 2026-09-22 16:58:21 UTC

## Reference configuration

Machine fingerprint: `14351c92219e`. Compare two reports directly only when this value matches.

| | |
|---|---|
| CPU | Apple M4 Pro |
| Cores | 12 physical / 12 logical |
| Memory | 24.0 GiB |
| OS | Darwin 24.6.0 (arm64) |
| Power source | AC Power |
| Load average (1m, at start) | 3.26 |
| Flow-Wing | 1.0.16 |
| C++ baseline | clang version 17.0.6 (https://github.com/llvm/llvm-project.git 6009708b4367171ccdbf4b5905cb6a803753fe18) |
| Optimization | -O3 (both toolchains) |
| Sampling | 7 iterations x 15 repetitions (compile: 5 repetitions) |

## How to read this report

Each time in milliseconds belongs to the machine listed above. The same times will not appear on different hardware.

**Use the ratio column.** Flow-Wing and C++ ran on the same machine, in the same session, and one statistics engine measured both. The hardware therefore has less effect on the ratio than on the raw time. Read C++ as the reference point, and read the ratio as the Flow-Wing time divided by the C++ time.

Both columns time a process from start to end, so every figure includes process creation. The `00_startup` case measures that cost on its own. A row marked :warning: has a standard deviation above 5% of its median on at least one side. The last digits of such a ratio are noise.

## Execution time

| Case | Flow-Wing (ms) | C++ (ms) | Flow-Wing / C++ | What it measures |
|---|---:|---:|---:|---|
| `00_startup` | 1.09 ± 0.10 | 1.01 ± 0.04 | 1.08x :warning: | An empty program. This measures the cost to create a process, which every other run figure includes. |
| `01_fib_recursive` | 8.53 ± 0.20 | 4.43 ± 0.07 | 1.92x | Recursive Fibonacci with no memoisation. This measures function call cost, argument passing and branch prediction. |
| `02_loop_arith` | 55.84 ± 0.70 | 55.88 ± 0.53 | 1.00x | A tight integer loop with a multiply and a modulo. This measures arithmetic speed and loop code generation. |
| `03_collatz` | 70.06 ± 0.66 | 22.80 ± 0.35 | 3.07x | The longest Collatz chain below N. This measures integer work with many branches and 64-bit values. |
| `04_matmul` | 3.09 ± 0.05 | 2.72 ± 0.21 | 1.14x :warning: | A 64x64 integer matrix multiply, repeated. This measures nested loops and access to fixed-size 2D arrays. |
| `05_mandelbrot` | 2.69 ± 0.06 | 2.40 ± 0.06 | 1.12x | Mandelbrot set membership over a square grid. This measures double-precision arithmetic with a branch on computed data. |
| `06_nbody` | 21.21 ± 0.21 | 21.05 ± 0.36 | 1.01x | A five-body gravity simulation with a square root written by hand. C++ uses -ffp-contract=off because Flow-Wing emits no FMA instructions. Without that flag the two results differ after about 5000 steps. |
| `07_sieve_vec` | 11.02 ± 0.23 | 1.84 ± 0.04 | 5.99x | A Sieve of Eratosthenes over vec::Vec against std::vector. This measures container element access and heap growth. |
| `08_quicksort` | 39.24 ± 0.49 | 8.08 ± 0.06 | 4.86x | A Lomuto quicksort over vec::Vec against std::vector. This measures recursion with many indexed reads and writes. |
| `09_string_build` | 22.73 ± 0.33 | 3.12 ± 0.05 | 7.27x | Repeated string concatenation by value. Both sides build a new string at each step, so this measures allocation and copy cost under the same rules. |
| `10_map_churn` | 75.94 ± 0.95 | 9.96 ± 0.29 | 7.63x | Hash map insert and lookup with string keys, map::Map against std::unordered_map. |
| `11_gc_pressure` | 14.20 ± 0.37 | 1.75 ± 0.05 | 8.14x | Allocate one short-lived object per iteration and drop it. This compares the Flow-Wing collector against C++ new and delete. |

## Compile time

| Case | Flow-Wing (ms) | C++ (ms) | Flow-Wing / C++ |
|---|---:|---:|---:|
| `00_startup` | 66.32 ± 0.99 | 66.81 ± 1.49 | 0.99x |
| `01_fib_recursive` | 71.46 ± 1.85 | 70.82 ± 0.65 | 1.01x |
| `02_loop_arith` | 72.73 ± 0.59 | 71.65 ± 0.63 | 1.02x |
| `03_collatz` | 73.44 ± 1.05 | 71.73 ± 0.92 | 1.02x |
| `04_matmul` | 89.02 ± 7.20 | 75.55 ± 0.86 | 1.18x :warning: |
| `05_mandelbrot` | 74.51 ± 4.84 | 73.88 ± 4.94 | 1.01x :warning: |
| `06_nbody` | 84.07 ± 1.72 | 78.77 ± 3.91 | 1.07x |
| `07_sieve_vec` | 82.89 ± 0.79 | 334.39 ± 3.21 | 0.25x |
| `08_quicksort` | 87.23 ± 0.93 | 339.98 ± 8.49 | 0.26x |
| `09_string_build` | 103.99 ± 3.70 | 275.76 ± 1.34 | 0.38x |
| `10_map_churn` | 82.52 ± 8.78 | 333.03 ± 6.21 | 0.25x :warning: |
| `11_gc_pressure` | 73.80 ± 2.80 | 186.78 ± 1.85 | 0.40x |

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

- **run**: the Flow-Wing time is 2.63x the C++ time, as a geometric mean over 12 cases. A value below 1.00 means Flow-Wing is faster.
- **compile**: the Flow-Wing time is 0.62x the C++ time, as a geometric mean over 12 cases. A value below 1.00 means Flow-Wing is faster.

