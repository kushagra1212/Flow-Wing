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

#include "CleanupPass.hpp"
#include "src/IRGen/FlowWingConstants/FlowWingConstants.hpp"
#include "src/common/cli/CliReporter.h"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/utils/LogConfig.h"

namespace flow_wing {

namespace compiler {
namespace pipeline {

std::string CleanupPass::getName() const { return "Cleanup"; }

ReturnStatus CleanupPass::run(CompilationContext &context) {
  namespace fs = std::filesystem;

  auto safeRemove = [&](const fs::path &targetPath) {
    // Avoids deleting empty or root paths
    if (targetPath.empty() || targetPath == targetPath.root_path() ||
        targetPath == ".") {
      return;
    }

    std::error_code ec;
    fs::remove_all(targetPath, ec);
    DEBUG_LOG(" [INFO]: Deleting directory: ", targetPath.string());

    if (ec) {
      // For Windows this may happen if a file is still "open" or "locked"
      DEBUG_LOG(" [ERROR]: Could not clean up '" + targetPath.string() +
                    "'. Error: ",
                ec.message());
    }
  };

  safeRemove(fs::path(context.getTempDirectoryPath()));

  safeRemove(fs::path(flow_wing::ir_gen::constants::paths::kObject_files_dir));

  return ReturnStatus::kSuccess;
}
} // namespace pipeline
} // namespace compiler
} // namespace flow_wing
