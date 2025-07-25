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


#include "SemanticAnalyzer.h"
#include "BoundStatements/BoundBlockStatement/BoundBlockStatement.h"

std::unique_ptr<BoundGlobalScope> SemanticAnalyzer::analyzeGlobalScope(
    std::unique_ptr<BoundGlobalScope> previousGlobalScope,
    CompilationUnitSyntax *syntax,
    FlowWing::DiagnosticHandler *diagnosticHandler) {

  std::unique_ptr<SyntaxBinder> binder =
      std::make_unique<SyntaxBinder>(nullptr, diagnosticHandler);

  std::unordered_map<std::string, std::any> prevVariablesValues;

  if (previousGlobalScope) {
    binder->getContextRef()->updateBoundScope(previousGlobalScope);
    prevVariablesValues = previousGlobalScope->variablesValues;
  }
  std::unique_ptr<BoundBlockStatement> root(
      static_cast<BoundBlockStatement *>(binder->bind(syntax).release()));

  return std::make_unique<BoundGlobalScope>(
      std::move(previousGlobalScope),
      binder->getContextRef()->getRootRef().get(), prevVariablesValues,
      diagnosticHandler, std::move(root));
}