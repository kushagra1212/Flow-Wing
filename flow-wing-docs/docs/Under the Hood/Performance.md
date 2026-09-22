---
sidebar_position: 4
title: Performance
---

# Performance

Flow-Wing compiles ahead of time through LLVM. This page shows how its speed
compares to C++, and gives the measurements behind the comparison.

The result in one line: the generated code is close to C++, but the runtime
library is slower. A tight integer loop runs at 1.08x the C++ time. Programs
that use `vec`, `map`, `text` or the garbage collector run at 6.1x to 7.6x.

Compilation is the other way round. Flow-Wing compiles at 0.58x the clang
time as a geometric mean, and it is faster than clang on eleven of the twelve
benchmarks.

:::info Absolute times do not transfer to other machines
Each time in milliseconds belongs to one machine. The **ratio** is the number
you can reuse. Flow-Wing and C++ ran on the same machine, in the same session,
and the same tool measured both. The hardware therefore has less effect on the
ratio than on the raw time.

Quote the ratios. To get times for your own hardware, read
[Estimating for your machine](#estimating-for-your-machine).
:::

## Reference configuration

All numbers on this page come from one run of the benchmark suite in the
compiler repository. The machine is listed in full, because you need it to
compare your own results.

| | |
|---|---|
| **CPU** | Apple M4 Pro |
| **Cores** | 12 physical, 12 logical |
| **Memory** | 24 GiB |
| **OS** | Darwin 24.6.0 (arm64) |
| **Power** | AC mains, not battery |
| **Flow-Wing** | 1.0.16 |
| **C++ baseline** | clang 17.0.6 |
| **Optimization** | `-O2` for both compilers |
| **Sampling** | 7 iterations, 15 repetitions, median reported |
| **Machine fingerprint** | `14351c92219e` |

The source report is `benchmarks/results/2026-09-22T15-15-25Z/report.md` in
the compiler repository.

The C++ baseline is clang 17. Flow-Wing generates code through LLVM 17, so
both sides use the same compiler backend version. A different clang version
would measure changes in LLVM itself, not differences between the languages.

## Execution time

A lower number is better. A ratio of `1.00x` means the same speed as C++.

| Benchmark | Flow-Wing | C++ | Ratio | What it tests |
|---|---:|---:|---:|---|
| Tight integer loop | 60.0 ms | 55.3 ms | **1.08x** | arithmetic speed, loop code generation |
| Mandelbrot | 6.8 ms | 2.4 ms | 2.85x | `deci` math, branch on computed data |
| Recursive Fibonacci | 14.0 ms | 4.6 ms | 3.02x | function call cost, argument passing |
| Collatz chains | 82.0 ms | 22.7 ms | 3.62x | many branches, `int64` values |
| 64x64 matrix multiply | 11.2 ms | 2.6 ms | 4.31x | nested loops, 2D array access |
| N-body simulation | 115.1 ms | 21.0 ms | 5.48x | floating point, array access |
| Quicksort over `vec` | 47.7 ms | 7.8 ms | 6.09x | recursion, indexed read and write |
| Sieve over `vec` | 12.0 ms | 1.8 ms | 6.69x | container access, heap growth |
| Allocation churn | 14.2 ms | 2.1 ms | 6.71x | garbage collector against `new` and `delete` |
| String building | 22.2 ms | 3.0 ms | 7.36x | string allocation and copying |
| Hash map churn | 74.1 ms | 9.8 ms | 7.58x | `map::Map` against `std::unordered_map` |
| Empty program | 1.1 ms | 1.0 ms | 1.15x | process start cost |

**Geometric mean: 3.94x the C++ time.**

Read the spread, not the mean. The mean hides the fact that the ratios differ
by a factor of seven across the table.

Arithmetic is almost free. Flow-Wing gives LLVM the same kind of IR that a C
compiler gives it, and LLVM optimizes it the same way. The extra cost comes
from two areas.

**Function calls and branches cost about 3x.** Flow-Wing does not inline
across its own function boundaries as often as clang does.

**Runtime library operations cost 6.1x to 7.6x.** The `vec`, `map` and `text`
modules call through a handle-based FFI layer, and they box their elements. A
`std::vector<int>` is a flat array, and the C++ optimizer can see through it
completely.

That order matters when you tune a Flow-Wing program. Move container access
out of a hot loop first. Tuning arithmetic gives a much smaller gain.

### Floating point and FMA

The n-body result needs one qualification. Flow-Wing does not emit **fused
multiply-add** (FMA) instructions. Clang at `-O2` does emit them. To make both
sides compute the same arithmetic, the C++ program in that benchmark uses
`-ffp-contract=off`.

The 5.48x figure therefore makes C++ look slower than it is on floating-point
code. A normal C++ build with FMA is faster again. It also shows that FMA
support is a possible improvement for Flow-Wing on numeric programs.

## Compile time

Flow-Wing compiles faster than clang on almost every program. It has no
preprocessor, it does not include header text, and it does not instantiate
templates.

| Benchmark | Flow-Wing | C++ | Ratio |
|---|---:|---:|---:|
| Hash map churn | 74.9 ms | 324.6 ms | **0.23x** |
| Sieve over `vec` | 77.1 ms | 324.7 ms | 0.24x |
| Quicksort over `vec` | 78.7 ms | 324.6 ms | 0.24x |
| String building | 83.0 ms | 270.1 ms | 0.31x |
| Allocation churn | 71.4 ms | 188.1 ms | 0.38x |
| Collatz chains | 67.2 ms | 69.7 ms | 0.96x |
| Empty program | 63.9 ms | 65.3 ms | 0.98x |
| Tight integer loop | 68.3 ms | 68.7 ms | 0.99x |
| 64x64 matrix multiply | 77.7 ms | 74.3 ms | 1.05x |

**Geometric mean: 0.58x the C++ time.**

The gap is largest where C++ reads headers. `#include <unordered_map>` costs
clang about a quarter of a second before it compiles any user code. `bring map`
costs Flow-Wing almost nothing.

Where neither language pays for headers the two are level, within a few
percent of each other.

:::info Large fixed-size arrays are safe to declare
Declaring a fixed-size array costs the same whatever its length. The compiler
initialises the whole array with a single `memset`, so the work it does no
longer grows with the element count.

| Declaration | Compile time |
|---|---:|
| `int[10000]` | 0.10 s |
| `bool[100000]` | 0.16 s |
| `str[100000]` | 0.22 s |
| `int[1000000]` | 1.01 s |

This was not always true. Earlier releases emitted one store instruction per
element, which made `bool[10000]` take 77 seconds to compile and crashed the
compiler outright above about 100,000 elements. The matrix multiply benchmark
declares three `int[64][64]` arrays and took 11.9 seconds to compile; it now
takes 78 ms.
:::

## Binary size

A Flow-Wing executable is 2.2x to 3.3x the size of the same program built with
clang. A program that prints one line is about 72 KB, against 33 KB from
clang.

The minimum size comes from the statically linked runtime. Every binary
contains the garbage collector and the scheduler. Each `bring vec` or
`bring map` adds about 20 KB to 40 KB more.

## Estimating for your machine

Ratios apply to other machines reasonably well. Absolute times do not. Use the
C++ column as your reference point:

1. Run the suite on your machine. The steps are below.
2. Divide your C++ time by the C++ time on this page, for the same benchmark.
   The result is your **machine scale factor**.
3. Multiply the Flow-Wing times on this page by that factor.

**Example.** Your machine runs the tight integer loop in 120 ms with C++. This
page shows 55.3 ms. Your scale factor is `120 / 55.3`, which is about 2.2. So
expect Flow-Wing times near 2.2 times those on this page, or about 130 ms for
that benchmark.

How well a ratio applies to your machine depends on what the benchmark tests.

| Benchmark group | How well the ratio applies |
|---|---|
| Arithmetic, calls, branches | **Good.** These depend on the CPU execution units and the branch predictor, which affect both languages in a similar way. |
| Containers, allocation, GC | **Medium.** These depend on cache size and memory bandwidth. Flow-Wing boxes its elements, so it uses more memory. A machine with a smaller cache usually makes these ratios larger. |
| Empty program, compile time | **Poor.** Process creation, the filesystem and the linker control these times. They differ a lot between operating systems and disks. |

These three rows are expectations, not measurements. The suite has only run on
the reference machine above. Treat any estimate as approximate. Run the suite
yourself if a number affects a decision.

## Method

The suite is in `benchmarks/` in the compiler repository. Each benchmark is a
**pair** of programs, one `.fg` and one `.cpp`, that use the same algorithm.

**One tool measures both sides.** Each side is a Google Benchmark benchmark
that starts a process and times it from start to end. Neither language gets
measurement support that the other does not have. Every time includes process
creation, which is what the empty-program row measures.

**The suite checks the output before it measures.** The two programs must
print the same bytes to stdout, or the suite stops with an error. This proves
that they do the same work. It also stops either optimizer from deleting the
computation, because both programs must print a result.

**The command line supplies the workload size.** A value such as `fib(32)` is
therefore not a compile-time constant, and clang cannot compute it in advance.

**The suite reports wall-clock time, not CPU time.** The harness waits for the
child process, so its own CPU time means nothing.

**The suite warms up every binary before it measures.** The first run of a new
executable took 506 ms, against 5 ms once warm. The difference is page cache
behaviour.

**The suite reports medians with a standard deviation.** It marks any result
whose deviation is more than 5% of its median. Such a result is too noisy to
compare.

## Reproducing these numbers

Build the compiler first, then run the suite:

```bash
make build-aot-release
./benchmarks/run.sh
```

Each run writes a report and an `environment.json` file. The JSON file records
the CPU, the core count, the memory, the OS, the power source and the compiler
versions:

```
benchmarks/results/<timestamp>/report.md
benchmarks/results/<timestamp>/environment.json
benchmarks/results/latest
```

You can change the sampling. The script also accepts Google Benchmark flags:

```bash
./benchmarks/run.sh --iterations=10 --repetitions=15
./benchmarks/run.sh --opt=-O3
./benchmarks/run.sh --benchmark_filter='run/.*map'
```

Compare your report to this page only if the machine fingerprints match. If
they differ, compare the ratio columns and ignore the millisecond columns.

The suite runs on macOS and Linux. The report marks any run made on battery
power. Do not quote those numbers, because laptops reduce their clock speed
enough to change every result.
