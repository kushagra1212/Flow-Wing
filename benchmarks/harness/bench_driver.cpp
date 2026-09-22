/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


//
// FlowWing Compiler
// Copyright (C) 2023-2026 Kushagra Rathore
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//

// =============================================================================
// Flow-Wing vs C++ benchmark driver.
//
// Every case is a pair of programs, bench.fg and bench.cpp. Both must
// compute the same result. The driver builds both, refuses to measure
// anything until their stdout matches byte for byte, and then registers both
// with Google Benchmark so the two columns are produced by one statistics
// engine rather than by two different measuring methods.
// =============================================================================

#include "bench_case.h"
#include "markdown_reporter.h"
#include "process.h"
#include "system_info.h"
#include "toolchain.h"

#include <benchmark/benchmark.h>

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;
using namespace fwbench;

namespace {

// Number of extra executions performed per binary before measurement.
//
// A cold binary takes roughly a hundred times longer than a warm one on this
// project. The first run of a freshly linked executable was measured at
// 506ms against 5ms warm, entirely page-cache effects. Measuring that would
// say nothing about either language.
constexpr int kWarmupRuns = 2;

struct Options {
  fs::path repo_root;
  fs::path cases_dir;
  fs::path build_dir;
  fs::path report_path;
  fs::path flowwing;
  fs::path clangxx;
  std::string optimization = "-O2";
  int iterations = 5;
  int repetitions = 7;

  // Compiles take whole seconds and vary far less than millisecond-scale
  // program runs, so they need fewer samples to stabilise. Timing them as
  // often as the run/ family would dominate the suite's wall-clock cost
  // without sharpening the number.
  int compile_repetitions = 3;
};

std::string valueOf(const std::string &arg, const std::string &key) {
  const std::string prefix = "--" + key + "=";
  if (arg.rfind(prefix, 0) == 0) {
    return arg.substr(prefix.size());
  }
  return "";
}

// Writes the machine and toolchain facts next to the report.
//
// The markdown is for people; this is for tooling that wants to check two
// reports were produced under the same conditions before diffing them.
void writeEnvironmentSidecar(const fs::path &path,
                             const ReportEnvironment &environment) {
  std::ofstream out(path);
  if (!out) {
    std::cerr << "warning: cannot write " << path << "\n";
    return;
  }

  const SystemInfo &system = environment.system;
  out << "{\n";
  out << "  \"fingerprint\": \"" << environment.fingerprint << "\",\n";
  out << "  \"cpu_model\": \"" << system.cpu_model << "\",\n";
  out << "  \"physical_cores\": " << system.physical_cores << ",\n";
  out << "  \"logical_cores\": " << system.logical_cores << ",\n";
  out << "  \"ram_gib\": " << system.ram_gib << ",\n";
  out << "  \"os\": \"" << system.os << "\",\n";
  out << "  \"arch\": \"" << system.arch << "\",\n";
  out << "  \"power_source\": \"" << system.power_source << "\",\n";
  out << "  \"load_average_1m\": " << system.load_average_1m << ",\n";
  out << "  \"flowwing_version\": \"" << environment.flowwing_version
      << "\",\n";
  out << "  \"cxx_baseline\": \"" << environment.clang_version << "\",\n";
  out << "  \"optimization\": \"" << environment.optimization << "\",\n";
  out << "  \"iterations\": " << environment.iterations << ",\n";
  out << "  \"repetitions\": " << environment.repetitions << ",\n";
  out << "  \"compile_repetitions\": " << environment.compile_repetitions
      << "\n";
  out << "}\n";
}

Options parseOptions(int argc, char **argv) {
  Options options;

  // Default to the repository this driver was built from. The CMake build
  // bakes the path in so the common case needs no arguments at all.
  options.repo_root = FW_BENCH_REPO_ROOT;

  for (int i = 1; i < argc; ++i) {
    const std::string arg = argv[i];
    std::string value;

    if (!(value = valueOf(arg, "repo-root")).empty()) {
      options.repo_root = value;
    } else if (!(value = valueOf(arg, "cases")).empty()) {
      options.cases_dir = value;
    } else if (!(value = valueOf(arg, "out")).empty()) {
      options.report_path = value;
    } else if (!(value = valueOf(arg, "build-dir")).empty()) {
      options.build_dir = value;
    } else if (!(value = valueOf(arg, "flowwing")).empty()) {
      options.flowwing = value;
    } else if (!(value = valueOf(arg, "clang")).empty()) {
      options.clangxx = value;
    } else if (!(value = valueOf(arg, "opt")).empty()) {
      options.optimization = value;
    } else if (!(value = valueOf(arg, "iterations")).empty()) {
      options.iterations = std::stoi(value);
    } else if (!(value = valueOf(arg, "repetitions")).empty()) {
      options.repetitions = std::stoi(value);
    } else if (!(value = valueOf(arg, "compile-repetitions")).empty()) {
      options.compile_repetitions = std::stoi(value);
    }
  }

  if (options.cases_dir.empty()) {
    options.cases_dir = options.repo_root / "benchmarks" / "cases";
  }
  if (options.build_dir.empty()) {
    options.build_dir = options.repo_root / "benchmarks" / "build" / "cases";
  }
  if (options.report_path.empty()) {
    options.report_path =
        options.repo_root / "benchmarks" / "results" / "report.md";
  }
  if (options.flowwing.empty()) {
    options.flowwing = options.repo_root / "build" / "sdk" / "bin" / "FlowWing";
  }
  if (options.clangxx.empty()) {
    options.clangxx =
        options.repo_root / ".fw_dependencies" / "install" / "bin" / "clang++";
  }

  return options;
}

// Compiles one case with one toolchain. Returns false and explains why on
// failure. A benchmark suite that silently drops a case reports a faster
// language than it measured.
bool buildOne(Implementation impl, const BenchCase &bench_case,
              const Toolchain &toolchain, const fs::path &out_binary) {
  fs::create_directories(out_binary.parent_path());
  fs::create_directories(toolchain.scratch_dir / bench_case.name);

  const std::vector<std::string> argv =
      compileCommand(impl, bench_case, toolchain, out_binary);
  const ProcResult result = runProcess(argv);

  if (result.exit_code != 0 || !fs::exists(out_binary)) {
    std::cerr << "\nFAILED to compile " << bench_case.name << " ["
              << implementationName(impl) << "]\n";
    std::cerr << "  command:";
    for (const std::string &arg : argv) {
      std::cerr << " " << arg;
    }
    std::cerr << "\n  exit code: " << result.exit_code << "\n";
    if (!result.err.empty()) {
      std::cerr << result.err << "\n";
    }
    if (!result.out.empty()) {
      std::cerr << result.out << "\n";
    }
    return false;
  }

  return true;
}

// Runs both binaries and requires identical stdout.
//
// This gate does double duty. It proves the two programs really implement the
// same workload, and because both sides must print their result, it stops the
// optimizer in either toolchain from deleting the computation as dead code.
bool checkParity(const BenchCase &bench_case, const fs::path &fw_binary,
                 const fs::path &cpp_binary) {
  const ProcResult fw = runProcess(runCommand(fw_binary, bench_case));
  const ProcResult cpp = runProcess(runCommand(cpp_binary, bench_case));

  if (fw.exit_code != 0 || cpp.exit_code != 0) {
    std::cerr << "\nFAILED to run " << bench_case.name
              << " (flowwing exit " << fw.exit_code << ", cpp exit "
              << cpp.exit_code << ")\n";
    if (!fw.err.empty()) {
      std::cerr << "  flowwing stderr: " << fw.err << "\n";
    }
    if (!cpp.err.empty()) {
      std::cerr << "  cpp stderr: " << cpp.err << "\n";
    }
    return false;
  }

  if (fw.out != cpp.out) {
    std::cerr << "\nPARITY MISMATCH in " << bench_case.name << "\n";
    std::cerr << "  flowwing stdout: " << fw.out << "\n";
    std::cerr << "  cpp stdout     : " << cpp.out << "\n";
    return false;
  }

  // Warm the page cache for both binaries before anything is timed.
  for (int i = 0; i < kWarmupRuns; ++i) {
    runProcess(runCommand(fw_binary, bench_case));
    runProcess(runCommand(cpp_binary, bench_case));
  }

  return true;
}

void registerRunBenchmark(const BenchCase &bench_case, Implementation impl,
                          const fs::path &binary, const Options &options) {
  const std::vector<std::string> argv = runCommand(binary, bench_case);
  const double binary_bytes =
      static_cast<double>(fs::file_size(binary));
  const std::string name = "run/" + bench_case.name + "/" +
                           implementationName(impl);

  benchmark::RegisterBenchmark(
      name,
      [argv, binary_bytes](benchmark::State &state) {
        for (auto _ : state) {
          const ProcResult result = runProcess(argv);
          if (result.exit_code != 0) {
            state.SkipWithError("case binary exited with code " +
                                std::to_string(result.exit_code));
            break;
          }
          benchmark::DoNotOptimize(result.out.data());
        }
        state.counters["binary_bytes"] = binary_bytes;
      })
      ->UseRealTime()
      ->Unit(benchmark::kMillisecond)
      ->Iterations(options.iterations)
      ->Repetitions(options.repetitions)
      ->DisplayAggregatesOnly(true);
}

void registerCompileBenchmark(const BenchCase &bench_case, Implementation impl,
                              const Toolchain &toolchain,
                              const Options &options) {
  // Compile into a throwaway path so repeated timing runs never race with
  // the binaries the run/ benchmarks are executing.
  const fs::path out_binary = options.build_dir / bench_case.name /
                              (std::string(implementationName(impl)) +
                               ".compile-probe");

  const std::vector<std::string> argv =
      compileCommand(impl, bench_case, toolchain, out_binary);
  const std::string name = "compile/" + bench_case.name + "/" +
                           implementationName(impl);

  benchmark::RegisterBenchmark(name,
                               [argv](benchmark::State &state) {
                                 for (auto _ : state) {
                                   const ProcResult result = runProcess(argv);
                                   if (result.exit_code != 0) {
                                     state.SkipWithError(
                                         "compiler exited with code " +
                                         std::to_string(result.exit_code));
                                     break;
                                   }
                                   benchmark::DoNotOptimize(result.out.data());
                                 }
                               })
      ->UseRealTime()
      ->Unit(benchmark::kMillisecond)
      ->Iterations(1)
      ->Repetitions(options.compile_repetitions)
      ->DisplayAggregatesOnly(true);
}

} // namespace

int main(int argc, char **argv) {
  const Options options = parseOptions(argc, argv);

  fs::create_directories(options.report_path.parent_path());

  // Google Benchmark only routes a custom file reporter to disk when
  // --benchmark_out is set, and exits with an error otherwise. The driver
  // owns the report path, so the flag is synthesised here from --out rather
  // than being something the caller has to remember to pass twice.
  const std::string out_flag = "--benchmark_out=" + options.report_path.string();

  std::vector<char *> forwarded(argv, argv + argc);
  forwarded.push_back(const_cast<char *>(out_flag.c_str()));
  int forwarded_argc = static_cast<int>(forwarded.size());

  benchmark::Initialize(&forwarded_argc, forwarded.data());

  Toolchain toolchain;
  toolchain.flowwing = options.flowwing;
  toolchain.clangxx = options.clangxx;
  toolchain.optimization = options.optimization;
  toolchain.scratch_dir = options.build_dir / "scratch";
  toolchain.sysroot = detectMacOsSysroot();

  if (!fs::exists(toolchain.flowwing)) {
    std::cerr << "error: FlowWing not found at " << toolchain.flowwing
              << "\n       build it first with `make build-aot-release`.\n";
    return 1;
  }
  if (!fs::exists(toolchain.clangxx)) {
    std::cerr << "error: clang++ not found at " << toolchain.clangxx << "\n";
    return 1;
  }

  std::vector<BenchCase> cases;
  try {
    cases = discoverCases(options.cases_dir);
  } catch (const std::exception &error) {
    std::cerr << "error: " << error.what() << "\n";
    return 1;
  }

  std::cout << "Building " << cases.size() << " cases with both toolchains\n";

  for (const BenchCase &bench_case : cases) {
    const fs::path fw_binary =
        binaryPath(Implementation::FlowWing, bench_case, options.build_dir);
    const fs::path cpp_binary =
        binaryPath(Implementation::Cpp, bench_case, options.build_dir);

    if (!buildOne(Implementation::FlowWing, bench_case, toolchain, fw_binary) ||
        !buildOne(Implementation::Cpp, bench_case, toolchain, cpp_binary)) {
      return 1;
    }

    if (!checkParity(bench_case, fw_binary, cpp_binary)) {
      return 1;
    }

    std::cout << "  ok  " << bench_case.name << "\n";

    registerRunBenchmark(bench_case, Implementation::FlowWing, fw_binary,
                         options);
    registerRunBenchmark(bench_case, Implementation::Cpp, cpp_binary, options);
    registerCompileBenchmark(bench_case, Implementation::FlowWing, toolchain,
                             options);
    registerCompileBenchmark(bench_case, Implementation::Cpp, toolchain,
                             options);
  }

  ReportEnvironment environment;
  environment.flowwing_version = toolchain.flowwingVersion();
  environment.clang_version = toolchain.clangVersion();
  environment.optimization = options.optimization;
  environment.system = collectSystemInfo();
  environment.fingerprint = machineFingerprint(environment.system);
  environment.iterations = options.iterations;
  environment.repetitions = options.repetitions;
  environment.compile_repetitions = options.compile_repetitions;

  writeEnvironmentSidecar(
      options.report_path.parent_path() / "environment.json", environment);

  benchmark::ConsoleReporter console;
  MarkdownReporter markdown(options.report_path, cases, environment);

  std::cout << "\nAll cases verified. Measuring.\n\n";
  benchmark::RunSpecifiedBenchmarks(&console, &markdown);
  benchmark::Shutdown();

  return 0;
}
