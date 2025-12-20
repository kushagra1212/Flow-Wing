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

#include "src/common/cli/CliInfo.h"
#include "src/common/io/FileUtils.h"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/compiler/diagnostics/Diagnostic.h"
#include "src/compiler/diagnostics/DiagnosticFactory.h"
#include "src/compiler/pipeline/ICompilationPass.h"
#include "src/utils/LogConfig.h"

namespace flow_wing {
namespace compiler {
namespace pipeline {

class SourceLoaderPass : public ICompilationPass {
public:
  std::string getName() const override { return "Source Loader"; }

  ReturnStatus run(CompilationContext &context) override {
    const auto &opts = context.getOptions();

    if (!opts.code_content->empty()) {
      // Handle --code flag: read content directly from options.
      context.setSourceLines(flow_wing::io::FileUtils::readLinesFromString(
          opts.code_content.value()));

      SOURCE_LOADER_DEBUG_LOG(
          "Source loaded successfully from code content with size: ",
          opts.code_content.value().size());
      return ReturnStatus::kSuccess;
    }

    // Handle file input.
    const std::string &file_path = opts.input_file_path;
    auto file_content = flow_wing::io::FileUtils::readLines(file_path);

    if (!file_content) {
      context.getDiagnostics()->report(
          flow_wing::diagnostic::DiagnosticFactory::create(
              flow_wing::diagnostic::DiagnosticCode::kUnableToOpenFile,
              {file_path, flow_wing::cli::CliInfo::kUsageString},
              flow_wing::diagnostic::SourceLocation(0, 0, 0),
              flow_wing::diagnostic::DiagnosticLevel::kError,
              flow_wing::diagnostic::DiagnosticType::kFileSystem));

      return ReturnStatus::kFailure;
    }

    context.setSourceLines(std::move(file_content.value()));

    SOURCE_LOADER_DEBUG_LOG("Source loaded successfully from file", file_path);

    return ReturnStatus::kSuccess;
  }
};

} // namespace pipeline
} // namespace compiler
} // namespace flow_wing