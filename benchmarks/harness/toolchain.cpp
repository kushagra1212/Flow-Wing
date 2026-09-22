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

#include "toolchain.h"

#include "process.h"

#include <sstream>

namespace fs = std::filesystem;

namespace fwbench {

namespace {

std::string firstLine(const std::string &text) {
  std::istringstream stream(text);
  std::string line;
  std::getline(stream, line);
  return line;
}

} // namespace

const char *implementationName(Implementation impl) {
  return impl == Implementation::FlowWing ? "flowwing" : "cpp";
}

std::string detectMacOsSysroot() {
#if defined(__APPLE__)
  const ProcResult result =
      runProcess({"/usr/bin/xcrun", "--show-sdk-path"});
  if (result.exit_code != 0) {
    return "";
  }
  std::string path = result.out;
  while (!path.empty() && (path.back() == '\n' || path.back() == ' ')) {
    path.pop_back();
  }
  return path;
#else
  return "";
#endif
}

std::string Toolchain::flowwingVersion() const {
  const ProcResult result = runProcess({flowwing.string(), "--version"});
  // `--version` prints a two-line banner; the version itself is on line two.
  std::istringstream stream(result.out);
  std::string line;
  std::string last;
  while (std::getline(stream, line)) {
    if (!line.empty()) {
      last = line;
    }
  }
  const std::string prefix = "Version: ";
  if (last.rfind(prefix, 0) == 0) {
    last = last.substr(prefix.size());
  }
  return last.empty() ? "unknown" : last;
}

std::string Toolchain::clangVersion() const {
  const ProcResult result = runProcess({clangxx.string(), "--version"});
  return firstLine(result.out);
}

fs::path binaryPath(Implementation impl, const BenchCase &bench_case,
                    const fs::path &build_dir) {
  return build_dir / bench_case.name /
         (std::string(implementationName(impl)) + ".bin");
}

std::vector<std::string> compileCommand(Implementation impl,
                                        const BenchCase &bench_case,
                                        const Toolchain &toolchain,
                                        const fs::path &out_binary) {
  if (impl == Implementation::FlowWing) {
    // -OD keeps the compiler's intermediate artifacts inside the scratch
    // tree. Without it FlowWing writes a ./build directory next to whatever
    // the driver's working directory happens to be.
    return {toolchain.flowwing.string(),
            bench_case.fg_source.string(),
            toolchain.optimization,
            "-OD",
            (toolchain.scratch_dir / bench_case.name).string(),
            "-o",
            out_binary.string()};
  }

  std::vector<std::string> argv{toolchain.clangxx.string(),
                                "-std=" + toolchain.cxx_standard,
                                toolchain.optimization};

  if (!toolchain.sysroot.empty()) {
    argv.push_back("-isysroot");
    argv.push_back(toolchain.sysroot);
  }

  for (const std::string &flag : bench_case.cxx_flags) {
    argv.push_back(flag);
  }

  argv.push_back(bench_case.cpp_source.string());
  argv.push_back("-o");
  argv.push_back(out_binary.string());
  return argv;
}

std::vector<std::string> runCommand(const fs::path &binary,
                                    const BenchCase &bench_case) {
  std::vector<std::string> argv;
  argv.reserve(bench_case.args.size() + 1);
  argv.push_back(binary.string());
  for (const std::string &arg : bench_case.args) {
    argv.push_back(arg);
  }
  return argv;
}

} // namespace fwbench
