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



#include "SemanticAnalysisPass.hpp"
#include "src/ASTBuilder/ASTBuilder.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SemanticAnalyzer/DeclarationAnalyzer/DeclarationAnalyzer.hpp"
#include "src/SemanticAnalyzer/SyntaxBinder/Binder/Binder.hpp"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/CompilationUnitBinder.hpp"
#include "src/compiler/CompilationContext/CompilationContext.h"

namespace flow_wing {

namespace compiler {
namespace pipeline {

std::string SemanticAnalysisPass::getName() const {
  return "Semantic Analysis";
}

ReturnStatus SemanticAnalysisPass::run(CompilationContext &context) {

  binding::BinderContext binder_context(context);
  analysis::DeclarationAnalyzer decl_analyzer(binder_context);

  flow_wing::analysis::Builtins::initialize();

  decl_analyzer.analyze();

  if (context.getDiagnostics()->hasError(
          diagnostic::DiagnosticType::kSemantic)) {
    return ReturnStatus::kFailure;
  }

  analysis::Binder binder(binder_context);
  std::unique_ptr<binding::BoundCompilationUnit> bound_root = binder.bindRoot();

  if (context.getDiagnostics()->hasError(
          diagnostic::DiagnosticType::kSemantic)) {
    return ReturnStatus::kFailure;
  }

  context.setBoundTree(std::move(bound_root));

  return ReturnStatus::kSuccess;
}

} // namespace pipeline
} // namespace compiler
} // namespace flow_wing
