/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
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

#include "src/utils/LogConfig.h"
#include <optional>
#include <sstream>
#include <string>
#include <vector>

namespace flow_wing {

enum class OptimizationLevel {
  O0 = 0, // No optimization
  O1 = 1, // Basic optimizations
  O2 = 2, // Aggressive speed optimizations
  O3 = 3  // Full optimization
};

struct CompilerOptions {
  // Input sources
  std::string input_file_path;
  std::optional<std::string> code_content; // For --code flag

  // Compiler modes
  int8_t show_help = 0;
  int8_t show_version = 0;
  int8_t format_source = 0;
  int8_t format_print = 0;
  int8_t enable_server = 0;
  int8_t enable_linker_warnings = 0;
  int8_t dump = 0;

  enum class OutputType {
    kExe,
    kObj,
    kLLVM_IR,
    kAstJson,
    kTokensJson,
    kSemJson
  };

  OutputType output_type = OutputType::kExe;
  std::string output_dir = "./build";
  // Compilation settings
  OptimizationLevel optimization_level = OptimizationLevel::O0;
  std::string entry_point = "main"; // Default entry point

  // Linker settings
  std::vector<std::string> library_paths;
  std::vector<std::string> link_libraries;
  std::vector<std::string> frameworks;

  std::string toString() const {
    std::stringstream ss;

    auto getString = [](int8_t value) -> std::string {
      return value == 0 ? "No" : "Yes";
    };

    const char *separator = " | ";
    ss << "Input file path: " << input_file_path << separator;

    if (!code_content->empty()) {
      ss << "Code content: " << code_content.value() << separator;
    }

    if (!output_dir.empty()) {
      ss << "Output directory: " << output_dir << separator;
    }

    ss << "Show help: " << getString(show_help) << separator;
    ss << "Show version: " << getString(show_version) << separator;
    ss << "Format source: " << getString(format_source) << separator;
    ss << "Format print: " << getString(format_print) << separator;
    ss << "Enable server: " << getString(enable_server) << separator;
    ss << "Enable linker warnings: " << getString(enable_linker_warnings)
       << separator;
    ss << "Optimization level: "
       << std::to_string(static_cast<int>(optimization_level)) << separator;
    ss << "Entry point: " << entry_point << separator;

    return ss.str();
  }
};

} // namespace flow_wing