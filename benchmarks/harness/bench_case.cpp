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

#include "bench_case.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace fs = std::filesystem;

namespace fwbench {

namespace {

std::string trim(const std::string &text) {
  const auto first = text.find_first_not_of(" \t\r\n");
  if (first == std::string::npos) {
    return "";
  }
  const auto last = text.find_last_not_of(" \t\r\n");
  return text.substr(first, last - first + 1);
}

std::vector<std::string> splitWhitespace(const std::string &text) {
  std::istringstream stream(text);
  std::vector<std::string> parts;
  std::string part;
  while (stream >> part) {
    parts.push_back(part);
  }
  return parts;
}

} // namespace

std::vector<BenchCase> discoverCases(const fs::path &cases_dir) {
  if (!fs::is_directory(cases_dir)) {
    throw std::runtime_error("cases directory not found: " +
                             cases_dir.string());
  }

  std::vector<fs::path> dirs;
  for (const auto &entry : fs::directory_iterator(cases_dir)) {
    if (entry.is_directory()) {
      dirs.push_back(entry.path());
    }
  }
  std::sort(dirs.begin(), dirs.end());

  std::vector<BenchCase> cases;
  for (const fs::path &dir : dirs) {
    const fs::path conf = dir / "case.conf";
    if (!fs::exists(conf)) {
      throw std::runtime_error("case is missing case.conf: " + dir.string());
    }

    BenchCase bench_case;
    bench_case.name = dir.filename().string();
    bench_case.dir = dir;
    bench_case.fg_source = dir / "bench.fg";
    bench_case.cpp_source = dir / "bench.cpp";

    if (!fs::exists(bench_case.fg_source)) {
      throw std::runtime_error("case is missing bench.fg: " + dir.string());
    }
    if (!fs::exists(bench_case.cpp_source)) {
      throw std::runtime_error("case is missing bench.cpp: " + dir.string());
    }

    std::ifstream stream(conf);
    std::string line;
    while (std::getline(stream, line)) {
      const std::string trimmed = trim(line);
      if (trimmed.empty() || trimmed[0] == '#') {
        continue;
      }

      const auto eq = trimmed.find('=');
      if (eq == std::string::npos) {
        throw std::runtime_error("malformed line in " + conf.string() + ": " +
                                 trimmed);
      }

      const std::string key = trim(trimmed.substr(0, eq));
      const std::string value = trim(trimmed.substr(eq + 1));

      if (key == "args") {
        bench_case.args = splitWhitespace(value);
      } else if (key == "cxx_flags") {
        bench_case.cxx_flags = splitWhitespace(value);
      } else if (key == "description") {
        bench_case.description = value;
      } else {
        throw std::runtime_error("unknown key '" + key + "' in " +
                                 conf.string());
      }
    }

    if (bench_case.description.empty()) {
      throw std::runtime_error("case.conf has no description: " +
                               conf.string());
    }

    cases.push_back(std::move(bench_case));
  }

  if (cases.empty()) {
    throw std::runtime_error("no cases found under " + cases_dir.string());
  }

  return cases;
}

} // namespace fwbench
