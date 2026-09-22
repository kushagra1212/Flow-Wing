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

#include "markdown_reporter.h"

#include <algorithm>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;

namespace fwbench {

namespace {

std::vector<std::string> splitOnSlash(const std::string &text) {
  std::vector<std::string> parts;
  std::istringstream stream(text);
  std::string part;
  while (std::getline(stream, part, '/')) {
    parts.push_back(part);
  }
  return parts;
}

std::string formatFixed(double value, int precision) {
  std::ostringstream out;
  out << std::fixed << std::setprecision(precision) << value;
  return out.str();
}

// Renders a ratio as "1.83x". The direction is stated in the table header
// rather than encoded in the value, so a bare number is never ambiguous.
std::string formatRatio(double numerator, double denominator) {
  if (denominator <= 0.0 || numerator <= 0.0) {
    return "n/a";
  }
  return formatFixed(numerator / denominator, 2) + "x";
}

std::string formatBytes(double bytes) {
  if (bytes <= 0.0) {
    return "n/a";
  }
  if (bytes < 1024.0) {
    return formatFixed(bytes, 0) + " B";
  }
  return formatFixed(bytes / 1024.0, 1) + " KB";
}

// Spread of a measurement as a percentage of its own median.
//
// Stands in for a coefficient of variation, which is normally stddev over
// mean. Using the median keeps it consistent with the figure actually printed
// in the table, so a flagged row is flagged relative to the number the reader
// is looking at.
double spreadPercent(double median, double stddev) {
  if (median <= 0.0) {
    return 0.0;
  }
  return (stddev / median) * 100.0;
}

std::string currentTimestamp() {
  const std::time_t now = std::time(nullptr);
  std::tm utc{};
#if defined(_WIN32)
  gmtime_s(&utc, &now);
#else
  gmtime_r(&now, &utc);
#endif
  char buffer[32];
  std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S UTC", &utc);
  return buffer;
}

} // namespace

MarkdownReporter::MarkdownReporter(fs::path output_path,
                                   std::vector<BenchCase> cases,
                                   ReportEnvironment environment)
    : m_output_path(std::move(output_path)), m_cases(std::move(cases)),
      m_environment(std::move(environment)) {}

bool MarkdownReporter::ReportContext(const Context & /*context*/) {
  // Everything worth recording is already in m_environment; Google
  // Benchmark's own context block duplicates it in a less readable form.
  return true;
}

void MarkdownReporter::ReportRuns(const std::vector<Run> &reports) {
  for (const Run &run : reports) {
    // Google Benchmark also emits a "cv" aggregate, but its value is a bare
    // ratio that GetAdjustedRealTime() then scales by the time unit, which
    // inflates it a thousandfold at kMillisecond. Deriving the spread from
    // stddev and median instead keeps everything in one unit.
    const bool is_plain = run.aggregate_name.empty();
    if (!is_plain && run.aggregate_name != "median" &&
        run.aggregate_name != "stddev") {
      continue;
    }

    const std::vector<std::string> parts =
        splitOnSlash(run.run_name.function_name);
    if (parts.size() != 3) {
      continue;
    }

    Measurement &measurement = m_families[parts[0]][parts[1]][parts[2]];
    measurement.present = true;

    if (run.aggregate_name == "stddev") {
      measurement.stddev = run.GetAdjustedRealTime();
      continue;
    }

    // A real median always wins over a single plain run.
    if (is_plain && measurement.median_from_aggregate) {
      continue;
    }

    measurement.median = run.GetAdjustedRealTime();
    measurement.median_from_aggregate = !is_plain;

    const auto counter = run.counters.find("binary_bytes");
    if (counter != run.counters.end()) {
      measurement.binary_bytes = counter->second.value;
    }
  }
}

const BenchCase *MarkdownReporter::findCase(const std::string &name) const {
  const auto match = std::find_if(
      m_cases.begin(), m_cases.end(),
      [&name](const BenchCase &item) { return item.name == name; });
  return match == m_cases.end() ? nullptr : &*match;
}

void MarkdownReporter::writeComparisonTable(std::ostream &out,
                                            const std::string &family,
                                            const std::string &unit_label,
                                            bool include_description) const {
  const auto family_entry = m_families.find(family);
  if (family_entry == m_families.end()) {
    out << "_No results recorded._\n\n";
    return;
  }

  out << "| Case | Flow-Wing (" << unit_label << ") | C++ (" << unit_label
      << ") | Flow-Wing / C++ |";
  if (include_description) {
    out << " What it measures |";
  }
  out << "\n|---|---:|---:|---:|";
  if (include_description) {
    out << "---|";
  }
  out << "\n";

  for (const auto &[case_name, by_impl] : family_entry->second) {
    const auto fw = by_impl.find("flowwing");
    const auto cpp = by_impl.find("cpp");

    const double fw_value = fw == by_impl.end() ? 0.0 : fw->second.median;
    const double cpp_value = cpp == by_impl.end() ? 0.0 : cpp->second.median;
    const double fw_dev = fw == by_impl.end() ? 0.0 : fw->second.stddev;
    const double cpp_dev = cpp == by_impl.end() ? 0.0 : cpp->second.stddev;

    const bool unstable = spreadPercent(fw_value, fw_dev) > kUnstableCvPercent ||
                          spreadPercent(cpp_value, cpp_dev) > kUnstableCvPercent;

    out << "| `" << case_name << "` | " << formatFixed(fw_value, 2) << " ± "
        << formatFixed(fw_dev, 2) << " | " << formatFixed(cpp_value, 2)
        << " ± " << formatFixed(cpp_dev, 2) << " | "
        << formatRatio(fw_value, cpp_value)
        << (unstable ? " :warning:" : "") << " |";

    if (include_description) {
      const BenchCase *bench_case = findCase(case_name);
      out << " " << (bench_case ? bench_case->description : "") << " |";
    }
    out << "\n";
  }
  out << "\n";
}

void MarkdownReporter::writeSizeTable(std::ostream &out) const {
  const auto family_entry = m_families.find("run");
  if (family_entry == m_families.end()) {
    out << "_No results recorded._\n\n";
    return;
  }

  out << "| Case | Flow-Wing | C++ | Flow-Wing / C++ |\n";
  out << "|---|---:|---:|---:|\n";

  for (const auto &[case_name, by_impl] : family_entry->second) {
    const auto fw = by_impl.find("flowwing");
    const auto cpp = by_impl.find("cpp");

    const double fw_bytes = fw == by_impl.end() ? 0.0 : fw->second.binary_bytes;
    const double cpp_bytes =
        cpp == by_impl.end() ? 0.0 : cpp->second.binary_bytes;

    out << "| `" << case_name << "` | " << formatBytes(fw_bytes) << " | "
        << formatBytes(cpp_bytes) << " | " << formatRatio(fw_bytes, cpp_bytes)
        << " |\n";
  }
  out << "\n";
}

void MarkdownReporter::writeSummary(std::ostream &out) const {
  // A geometric mean is the right average for ratios: it is insensitive to
  // which side is chosen as the denominator, where an arithmetic mean is not.
  for (const std::string &family : {std::string("run"), std::string("compile")}) {
    const auto family_entry = m_families.find(family);
    if (family_entry == m_families.end()) {
      continue;
    }

    double log_sum = 0.0;
    int counted = 0;
    for (const auto &[case_name, by_impl] : family_entry->second) {
      const auto fw = by_impl.find("flowwing");
      const auto cpp = by_impl.find("cpp");
      if (fw == by_impl.end() || cpp == by_impl.end()) {
        continue;
      }
      if (fw->second.median <= 0.0 || cpp->second.median <= 0.0) {
        continue;
      }
      log_sum += std::log(fw->second.median / cpp->second.median);
      ++counted;
    }

    if (counted == 0) {
      continue;
    }

    const double geomean = std::exp(log_sum / counted);
    out << "- **" << family << "**: the Flow-Wing time is "
        << formatFixed(geomean, 2) << "x the C++ time, as a geometric mean "
        << "over " << counted
        << " cases. A value below 1.00 means Flow-Wing is faster.\n";
  }
  out << "\n";
}

void MarkdownReporter::Finalize() {
  // Google Benchmark owns this stream: it is the file opened from
  // --benchmark_out, which the driver always sets. Writing here rather than
  // to our own ofstream keeps the suite on the library's intended contract
  // for a file reporter.
  std::ostream &out = GetOutputStream();

  out << "# Flow-Wing vs C++ Benchmark Report\n\n";
  out << "Generated: " << currentTimestamp() << "\n\n";

  const SystemInfo &system = m_environment.system;

  out << "## Reference configuration\n\n";
  out << "Machine fingerprint: `" << m_environment.fingerprint
      << "`. Compare two reports directly only when this value matches.\n\n";

  out << "| | |\n|---|---|\n";
  out << "| CPU | " << system.cpu_model << " |\n";
  out << "| Cores | " << system.physical_cores << " physical / "
      << system.logical_cores << " logical |\n";
  out << "| Memory | " << formatFixed(system.ram_gib, 1) << " GiB |\n";
  out << "| OS | " << system.os << " (" << system.arch << ") |\n";
  out << "| Power source | " << system.power_source << " |\n";
  out << "| Load average (1m, at start) | "
      << formatFixed(system.load_average_1m, 2) << " |\n";
  out << "| Flow-Wing | " << m_environment.flowwing_version << " |\n";
  out << "| C++ baseline | " << m_environment.clang_version << " |\n";
  out << "| Optimization | " << m_environment.optimization
      << " (both toolchains) |\n";
  out << "| Sampling | " << m_environment.iterations << " iterations x "
      << m_environment.repetitions << " repetitions (compile: "
      << m_environment.compile_repetitions << " repetitions) |\n\n";

  if (system.power_source == "Battery Power") {
    out << ":warning: **This run used battery power.** A laptop reduces its "
           "clock speed when you unplug it. Treat these times as a lower "
           "limit. Connect the machine to mains and run the suite again "
           "before you quote any number.\n\n";
  }
  if (system.load_average_1m > static_cast<double>(system.logical_cores) / 2.0 &&
      system.logical_cores > 0) {
    out << ":warning: **The machine was busy when this run started.** The "
           "load average was "
        << formatFixed(system.load_average_1m, 2) << " across "
        << system.logical_cores
        << " logical cores. Other work on the machine makes the measured "
           "times longer.\n\n";
  }

  out << "## How to read this report\n\n";
  out << "Each time in milliseconds belongs to the machine listed above. The "
         "same times will not appear on different hardware.\n\n";
  out << "**Use the ratio column.** Flow-Wing and C++ ran on the same "
         "machine, in the same session, and one statistics engine measured "
         "both. The hardware therefore has less effect on the ratio than on "
         "the raw time. Read C++ as the reference point, and read the ratio "
         "as the Flow-Wing time divided by the C++ time.\n\n";
  out << "Both columns time a process from start to end, so every figure "
         "includes process creation. The `00_startup` case measures that cost "
         "on its own. A row marked :warning: has a standard deviation above "
      << formatFixed(kUnstableCvPercent, 0)
      << "% of its median on at least one side. The last digits of such a "
         "ratio are noise.\n\n";

  out << "## Execution time\n\n";
  writeComparisonTable(out, "run", "ms", true);

  out << "## Compile time\n\n";
  writeComparisonTable(out, "compile", "ms", false);

  out << "## Binary size\n\n";
  writeSizeTable(out);

  out << "## Summary\n\n";
  writeSummary(out);

  std::cout << "\nReport written to " << m_output_path << "\n";
}

} // namespace fwbench
