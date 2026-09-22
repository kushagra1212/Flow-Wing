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

#include "src/common/cli/CliReporter.h"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/compiler/pipeline/ICompilationPass.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <system_error>

namespace flow_wing {
namespace compiler {
namespace pipeline {

// Shared tail of the four dumper passes (tokens, ast, sem, ir).
//
// With --dump the content goes to the console. Otherwise it is written to
// <output-dir>/<file_name>, creating the directory first.
//
// Each pass used to open its own std::ofstream and never check it. An
// ofstream on a path whose directory does not exist fails silently, so a
// missing --output-dir printed "<label> dumped to <path>", exited 0, and
// left nothing on disk.
inline ReturnStatus emitArtifact(CompilationContext &context,
                                 const std::string &label,
                                 const std::string &file_name,
                                 const std::string &content) {
  if (context.getOptions().dump) {
    flow_wing::cli::Reporter::message(content);
    return ReturnStatus::kSuccess;
  }

  const std::string &output_dir = context.getOptions().output_dir;
  const std::string path = output_dir + "/" + file_name;

  std::error_code dir_error;
  std::filesystem::create_directories(output_dir, dir_error);
  if (dir_error) {
    flow_wing::cli::Reporter::error("Could not create output directory '" +
                                    output_dir + "': " + dir_error.message());
    return ReturnStatus::kFailure;
  }

  std::ofstream file(path);
  file << content;
  file.close();
  if (!file) {
    flow_wing::cli::Reporter::error("Could not write " + path);
    return ReturnStatus::kFailure;
  }

  flow_wing::cli::Reporter::message(label + " dumped to " + path);
  return ReturnStatus::kSuccess;
}

} // namespace pipeline
} // namespace compiler
} // namespace flow_wing
