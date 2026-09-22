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

#pragma once

#include "src/compiler/BuildProgress/BuildHistory.hpp"
#include "src/compiler/CompilerOptions/CompilerOptions.h"
#include <chrono>
#include <filesystem>
#include <string>
#include <string_view>

namespace flow_wing {
namespace compiler {

// Cargo-style build lines on stderr, ending with the change against the last
// comparable build:
//
//      Compiling framework/cli-module.fg
//      Compiling main.fg
//        Linking build/bin/main
//       Finished main in 1.12s (22 files, -4.92s vs last build)
//
// Owned by the root CompilationContext. Every method does nothing when the
// build is not shown, so call sites never need to check.
class BuildProgress {
public:
  BuildProgress(const CompilerOptions &options,
                const std::string &absolute_entry_path);

  bool shown() const { return m_shown; }

  void unit(const std::string &absolute_path);
  void linking(const std::string &binary_path);

  // Prints the Finished line and records the build time. Runs at most once:
  // the JIT calls it before running the program, and main.cpp's call after
  // the pipeline must then do nothing.
  void finished();
  void running();

  // Parse and semantic errors stop a build before the entry's own Compiling
  // line fires, so a failed build that printed no unit names the entry here,
  // just before the diagnostics.
  void failed();

private:
  void line(std::string_view verb, const std::string &text) const;
  std::string display(const std::filesystem::path &absolute_path) const;
  std::string historyKey() const;
  std::string delta(long long now_ms) const;

  CompilerOptions m_options;
  std::filesystem::path m_entry;
  BuildHistory m_history;
  std::chrono::steady_clock::time_point m_start;
  bool m_shown = false;
  bool m_colour = false;
  bool m_finished = false;
  int m_units = 0;
};

} // namespace compiler
} // namespace flow_wing
