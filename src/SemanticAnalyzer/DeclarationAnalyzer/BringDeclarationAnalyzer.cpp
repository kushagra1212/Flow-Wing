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


#include "DeclarationAnalyzer.hpp"
#include "src/common/io/FileUtils.h"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/compiler/CompilerOptions/CompilerOptions.h"
#include "src/compiler/pipeline/CompilationPipeline.h"
#include "src/compiler/pipeline/passes/LexerPass/LexerPass.h"
#include "src/compiler/pipeline/passes/ParsingPass/ParsingPass.h"
#include "src/compiler/pipeline/passes/SemanticAnalysisPass/SemanticAnalysisPass.hpp"
#include "src/compiler/pipeline/passes/SourceLoaderPass.h"
#include "src/syntax/expression/StringLiteralExpressionSyntax/StringLiteralExpressionSyntax.h"
#include "src/syntax/statements/BringStatementSyntax/BringStatementSyntax.h"

namespace flow_wing {

void analysis::DeclarationAnalyzer::visit(syntax::BringStatementSyntax *node) {

  auto absolute_file_path =
      std::filesystem::absolute(node->getStringLiteralExpression()->getValue())
          .string();

  CompilerOptions options;
  options.input_file_path = absolute_file_path;

  flow_wing::CompilationContext context(options);

  flow_wing::compiler::pipeline::CompilationPipeline pipeline;

  pipeline.addPass(
      std::make_unique<flow_wing::compiler::pipeline::SourceLoaderPass>());
  pipeline.addPass(
      std::make_unique<flow_wing::compiler::pipeline::LexerPass>());
  pipeline.addPass(
      std::make_unique<flow_wing::compiler::pipeline::ParsingPass>());
  pipeline.addPass(
      std::make_unique<flow_wing::compiler::pipeline::SemanticAnalysisPass>());

  auto pipeline_status = pipeline.run(context);

  if (pipeline_status ==
      flow_wing::compiler::pipeline::ReturnStatus::kFailure) {
    m_binder_context.reportError(
        diagnostic::DiagnosticCode::kFileContainsErrors, {absolute_file_path},
        node->getStringLiteralExpression()->getSourceLocation());
    return;
  }

  [[maybe_unused]] auto ast = context.getAst().get();
}
} // namespace flow_wing