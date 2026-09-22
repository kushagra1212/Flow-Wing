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

#include <filesystem>
#include <string>
#include <vector>

namespace fwbench {

// One benchmark case: a pair of programs that must compute the same thing.
//
// The pairing is the whole point of the suite, so a case is only usable when
// both `bench.fg` and `bench.cpp` exist and produce byte-identical stdout.
struct BenchCase {
  std::string name;                 // directory name, e.g. "01_fib_recursive"
  std::filesystem::path dir;        // absolute path to the case directory
  std::filesystem::path fg_source;  // <dir>/bench.fg
  std::filesystem::path cpp_source; // <dir>/bench.cpp
  std::vector<std::string> args;    // runtime arguments, identical for both
  std::string description;          // one line, rendered into the report

  // Extra flags for the C++ side only.
  //
  // Exists for cases where clang's defaults compute different arithmetic than
  // Flow-Wing does, which would make byte-identical output impossible rather
  // than merely unlikely. Any case that sets this must say why in its
  // description. A baseline that is quietly slowed down is a dishonest
  // benchmark.
  std::vector<std::string> cxx_flags;
};

// Scans `cases_dir` for case directories and parses each `case.conf`.
//
// Returned in directory-name order so the numeric prefixes control report
// ordering. Throws std::runtime_error when a case is malformed. A silently
// skipped case would read as "this workload is fast" in the report.
std::vector<BenchCase> discoverCases(const std::filesystem::path &cases_dir);

} // namespace fwbench
