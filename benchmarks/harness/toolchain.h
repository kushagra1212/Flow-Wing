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

#pragma once

#include "bench_case.h"

#include <filesystem>
#include <string>
#include <vector>

namespace fwbench {

// Which language a given measurement belongs to. Every benchmark family is
// registered once per implementation so both columns go through the same
// statistics engine.
enum class Implementation { FlowWing, Cpp };

const char *implementationName(Implementation impl);

// The two compilers under comparison, plus the flags each is driven with.
//
// `clangxx` defaults to the clang bundled in .fw_dependencies rather than the
// system compiler. FlowWing generates code through LLVM 17, so comparing
// against clang 17 keeps the measurement about the language and its runtime
// instead of about which LLVM release happened to be installed.
struct Toolchain {
  std::filesystem::path flowwing;
  std::filesystem::path clangxx;
  std::string optimization = "-O2";
  std::string cxx_standard = "c++20";
  std::filesystem::path scratch_dir;

  // macOS SDK path for the bundled clang. Empty elsewhere, and empty when
  // detection fails. See detectMacOsSysroot().
  std::string sysroot;

  std::string flowwingVersion() const;
  std::string clangVersion() const;
};

// Resolves the macOS SDK via `xcrun --show-sdk-path`, or returns an empty
// string off Apple platforms.
//
// The clang in .fw_dependencies is a plain upstream build with no Apple
// driver configuration, so it cannot find <cstdio> without being told where
// the SDK is. cmake/dependencies.cmake does the same lookup for the AOT
// linker; this is the benchmark suite's copy of that step.
std::string detectMacOsSysroot();

// Builds the argv for compiling one case. Both are pure functions so the
// driver can use them for the initial build and then re-run the exact same
// command inside the `compile/` timing benchmarks.
std::vector<std::string>
compileCommand(Implementation impl, const BenchCase &bench_case,
               const Toolchain &toolchain,
               const std::filesystem::path &out_binary);

// Path of the executable produced for a case under a given implementation.
std::filesystem::path binaryPath(Implementation impl,
                                 const BenchCase &bench_case,
                                 const std::filesystem::path &build_dir);

// argv for running an already-built case binary, with the case's arguments.
std::vector<std::string> runCommand(const std::filesystem::path &binary,
                                    const BenchCase &bench_case);

} // namespace fwbench
