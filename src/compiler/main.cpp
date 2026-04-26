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

#include "src/common/cli/CliReporter.h"
#include "src/common/cli/CommandLineParser/CommandLineParser.h"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/compiler/diagnostics/DiagnosticReporter/DiagnosticReporter.h"
#include "src/compiler/diagnostics/formatters/ConsoleFormatter.h"
#include "src/compiler/pipeline/CompilationPipeline.h"
#include "src/compiler/pipeline/ICompilationPass.h"
#include "src/compiler/pipeline/PipelineFactory.hpp"
#include "src/utils/LogConfig.h"

#include <cstring>
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {

  flow_wing::cli::CommandLineParser parser;
  auto parseResult = parser.parse(argc, argv);

  switch (parseResult.status) {
  case flow_wing::cli::ParseStatus::kSuccess: {
    const auto &options = parseResult.options.value();
    std::string entry_file_path = options.input_file_path;
    flow_wing::CompilationContext context(options, entry_file_path);
    flow_wing::compiler::pipeline::PipelineFactory factory;

    flow_wing::compiler::pipeline::CompilationPipeline pipeline =
        factory.build(options);

    auto pipeline_status = pipeline.run(context);

    if (pipeline_status ==
        flow_wing::compiler::pipeline::ReturnStatus::kFailure) {
      auto reporter = flow_wing::diagnostic::DiagnosticReporter(
          std::cerr,
          std::make_unique<flow_wing::diagnostic::ConsoleFormatter>());

      reporter.report(*context.getDiagnostics(), context);
      std::cerr.flush();
      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
  }

  case flow_wing::cli::ParseStatus::kFailure:
    flow_wing::cli::Reporter::error(parseResult.message.value());
    return EXIT_FAILURE;

  case flow_wing::cli::ParseStatus::kCleanExit:
    return EXIT_SUCCESS;
  }

  return EXIT_SUCCESS;
}