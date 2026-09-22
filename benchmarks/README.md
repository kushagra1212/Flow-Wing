# Flow-Wing benchmarks

This suite compares Flow-Wing against C++ on execution time, compile time and
binary size. Each benchmark is a pair of programs that use the same algorithm.

```bash
./benchmarks/run.sh
```

Each run writes a directory named with a timestamp:

```
results/<timestamp>/report.md          the comparison, for people to read
results/<timestamp>/environment.json   the machine and toolchain record
results/latest                         a link to the most recent run
```

The suite needs `build/sdk/bin/FlowWing`. Build the compiler first with
`make build-aot-release`.

The published results are in the language documentation, under
**Under the Hood → Performance**. Update that page when the numbers here
change by a large amount.

## Ratios transfer to other machines, absolute times do not

A time in milliseconds belongs to the machine that produced it. The **ratio**
column is the number worth quoting. Flow-Wing and C++ run on the same machine,
in the same session, and one statistics engine measures both. The hardware
therefore has less effect on the ratio than on the raw time.

Every report starts with the reference configuration. It records the CPU
model, the physical and logical core counts, the memory size, the OS and
kernel, the power source, the load average at start, and both compiler
versions. It also gives a short **machine fingerprint**. The fingerprint is a
hash of the fields that decide whether two reports can be compared.

Compare two reports directly only when their fingerprints match. When the
fingerprints differ, compare the ratio columns and ignore the millisecond
columns.

The report states two conditions instead of leaving the reader to find them:

- **Battery power.** A laptop reduces its clock speed when you unplug it, and
  that changes every result. The report shows a warning, and you should not
  quote such a run.
- **A busy machine.** The report shows a warning when the one-minute load
  average at start is more than half the logical core count. Other work on the
  machine makes the measured times longer.

The report also marks a single row when its standard deviation is more than 5%
of its median. The last digits of such a ratio are noise.

## What a case is

Each case is a directory under `cases/`. It holds three files:

| File | Contents |
|---|---|
| `bench.fg` | the Flow-Wing program |
| `bench.cpp` | the C++ program, which uses the same algorithm |
| `case.conf` | the runtime arguments and a one-line description |

`case.conf` uses `key = value` lines. A `#` starts a comment:

```ini
args = 32
cxx_flags = -ffp-contract=off
description = What this case measures, in one line.
```

`args` and `cxx_flags` are optional. `description` is required, and the report
shows it. If you cannot describe a case in one line, it probably measures more
than one thing.

## How the suite keeps the comparison fair

**One tool measures both sides.** Each side is a Google Benchmark benchmark
that starts a process and times it from start to end. Neither side gets
measurement support inside the process. Every figure therefore includes process
creation. The `00_startup` case measures an empty program in both languages,
so you can see that cost instead of guessing it.

**The suite reports real time, not CPU time.** The driver waits in `waitpid`
while the child process runs, so the driver uses almost no CPU time. Each
benchmark uses `UseRealTime()`. The CPU column would measure the driver.

**Both sides use the same LLVM version.** The C++ baseline is the clang in
`.fw_dependencies/install/bin/clang++`, not the system compiler. Flow-Wing
generates code through LLVM 17, so a clang 17 baseline keeps the result about
the language and its runtime. Use `--clang=<path>` to choose a different
compiler.

**The suite checks the output before it measures.** It runs each case once per
language, and the two stdout streams must match byte for byte. The suite stops
with an error when they differ. This check does two things. It proves that the
two programs do the same work, and it stops either optimizer from deleting the
computation, because both programs must print a result.

**The command line supplies the workload size.** A literal `fib(32)` in C++ is
a constant expression, and clang can compute it during compilation. That would
report a C++ baseline of almost zero. Reading the value at runtime prevents
this.

**The suite warms up every binary.** The first run of a newly linked binary
took 506 ms in this project, against 5 ms once warm. The cause is the page
cache. The driver runs each binary three times before it measures.

**The suite samples compiles less often than runs.** A compile takes seconds
and varies little, so `--compile-repetitions` defaults to 3. A program run
takes milliseconds and varies more, so `--repetitions` defaults to 9.

## Sampling options

`run.sh` passes all its arguments to the driver. The driver also accepts the
Google Benchmark flags.

| Flag | Default | Meaning |
|---|---|---|
| `--iterations=N` | 5 | runs per repetition, for `run/` benchmarks |
| `--repetitions=N` | 9 | repetitions used for the median and deviation |
| `--compile-repetitions=N` | 3 | repetitions for `compile/` benchmarks |
| `--opt=-ON` | `-O2` | optimization level, used for both compilers |
| `--flowwing=<path>` | `build/sdk/bin/FlowWing` | the compiler to test |
| `--clang=<path>` | the bundled clang 17 | the C++ baseline |
| `--benchmark_filter=<regex>` | none | the Google Benchmark case filter |

## Two Flow-Wing problems this suite found

Both problems appeared while the suite was built. One is fixed, one is still
open. You can reproduce both from the committed cases.

**Flow-Wing does not emit FMA instructions.** Clang at `-O2` uses
`-ffp-contract=on` and emits fused multiply-add. Flow-Wing emits none. In
`06_nbody` this produces a difference of one unit in the last place. The
simulation is chaotic, so after about 5000 steps the two languages report
completely different results. The case sets `cxx_flags = -ffp-contract=off` so
that both sides compute the same arithmetic. The cost is that the C++ baseline
in that case does not use the FPU as well as it could. The gap in that case
will grow when Flow-Wing emits `llvm.fmuladd`.

**Large fixed-size array declarations were slow to compile, then failed.**
Fixed in the compiler; `04_matmul` is the regression test for it.

The binder built one bound element per array slot, and each became a
`getelementptr` and a `store` in the IR. `int[64][64]` produced 4096 of each,
and `04_matmul` declares three such arrays. Worse, the aggregate default store
that follows the allocation was a single `store [N x T]` instruction, which
SelectionDAG expands one element at a time while selecting machine
instructions.

| Declaration | Before | After |
|---|---:|---:|
| `int[10000]` | 2.98 s | 0.10 s |
| `bool[10000]` | 77 s | 0.13 s |
| `bool[100000]` | SIGSEGV | 0.16 s |
| `str[100000]` | SIGSEGV | 0.22 s |
| `int[1000000]` | SIGSEGV | 1.01 s |
| `04_matmul` | 11.9 s (149.90x clang) | 78 ms (1.05x clang) |

Two changes fixed it. `ContainerExpressionIrGen.cpp` skips the per-element
loop when the container is the binder's synthesised all-defaults fill, because
the array is already initialised by then. `EmitTypedStore.cpp` replaced the
aggregate store with an `llvm.memset` for zero defaults, and with a private
constant plus `llvm.memcpy` for non-zero ones such as `str[N]`, whose slots
hold pointers to the shared empty string rather than nulls.

Both are now constant cost in the element count. The crash above 100000
elements is gone, and `04_matmul` compiles faster than clang.

## Adding a case

1. Create the directory: `mkdir cases/12_my_case`.
2. Write `bench.fg` and `bench.cpp`. They must compute the same result and
   print the same output.
3. Write `case.conf` with `args` and a `description`.
4. Run `./benchmarks/run.sh --benchmark_filter=12_my_case`.

Choose a workload size that takes at least 10 ms for one run. A shorter run is
dominated by the process creation cost that `00_startup` measures.

Use `int64` accumulators and modular arithmetic. Flow-Wing's `int` is 32-bit,
and signed overflow is undefined behaviour in C++. A workload that overflows
gives different results on the two sides for reasons unrelated to speed.

Two points of Flow-Wing syntax cause most mistakes when you write a case:

- `/` is floating-point division, including on integers. Write integer
  division as `Int32(a / b)`.
- There is no `>>` operator. A newline ends a statement, and `;` does not.

## Dependencies and limits

`benchmarks/CMakeLists.txt` fetches Google Benchmark v1.9.1 with
`FetchContent` and pins it by SHA-256. The suite does not add it to
`cmake/deps_builder`. CI hashes `deps.lock` in that directory to decide whether
to rebuild LLVM and the other dependencies on all three platforms, and that
rebuild takes about three hours. A tool used only for development must not be
able to trigger it.

The driver starts child processes with `posix_spawn`, so it runs on macOS and
Linux only. To support Windows, add a `CreateProcess` path to
`harness/process.cpp`. On Windows, `benchmarks/CMakeLists.txt` stops during
configuration with that message instead of building a driver that cannot work.
