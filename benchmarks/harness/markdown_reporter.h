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
#include "system_info.h"

#include <benchmark/benchmark.h>

#include <filesystem>
#include <map>
#include <string>
#include <vector>

namespace fwbench {

// Environment facts rendered into the report header so a result file is
// interpretable months later without the shell history that produced it.
struct ReportEnvironment {
  std::string flowwing_version;
  std::string clang_version;
  std::string optimization;
  SystemInfo system;
  std::string fingerprint;
  int iterations = 0;
  int repetitions = 0;
  int compile_repetitions = 0;
};

// Above this coefficient of variation a measurement is too noisy to compare
// against another run. Five percent is the point where a ratio's third digit
// stops meaning anything on a normally loaded desktop.
inline constexpr double kUnstableCvPercent = 5.0;

// Renders the Flow-Wing vs C++ comparison as markdown.
//
// Google Benchmark's own reporters print one row per run, which makes a
// paired comparison something the reader has to assemble by eye. This
// reporter buffers every run, joins the two implementations of each case, and
// emits side-by-side tables with ratios.
class MarkdownReporter : public benchmark::BenchmarkReporter {
public:
  MarkdownReporter(std::filesystem::path output_path,
                   std::vector<BenchCase> cases, ReportEnvironment environment);

  bool ReportContext(const Context &context) override;
  void ReportRuns(const std::vector<Run> &reports) override;
  void Finalize() override;

private:
  // One measured value with its spread, as reported by Google Benchmark's
  // aggregate runs.
  struct Measurement {
    double median = 0.0;
    double stddev = 0.0;
    double binary_bytes = 0.0;
    bool present = false;

    // Google Benchmark only emits median/stddev rows when a benchmark runs
    // more than once. At --repetitions=1 there are no aggregates at all, so
    // the plain run is used instead and this records which source won, to
    // stop a plain row from overwriting a real median.
    bool median_from_aggregate = false;
  };

  // Keyed by family ("run", "compile") then case name then implementation.
  using CaseTable = std::map<std::string, std::map<std::string, Measurement>>;

  std::filesystem::path m_output_path;
  std::vector<BenchCase> m_cases;
  ReportEnvironment m_environment;
  std::map<std::string, CaseTable> m_families;

  const BenchCase *findCase(const std::string &name) const;
  void writeComparisonTable(std::ostream &out, const std::string &family,
                            const std::string &unit_label,
                            bool include_description) const;
  void writeSizeTable(std::ostream &out) const;
  void writeSummary(std::ostream &out) const;
};

} // namespace fwbench
