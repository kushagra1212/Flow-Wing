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

#include "DeclarationAnalyzer.hpp"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SemanticAnalyzer/TypeResolver/TypeResolver.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/syntax/expression/FunctionReturnTypeExpressionSyntax/FunctionReturnTypeExpressionSyntax.h"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "src/syntax/statements/FunctionStatementSyntax/FunctionStatementSyntax.h"
#include "src/syntax/statements/ParameterExpressionSyntax/ParameterExpressionSyntax.h"
#include <cassert>

namespace flow_wing {

void analysis::DeclarationAnalyzer::visit(
    syntax::FunctionStatementSyntax *node) {

  auto function_identifier = static_cast<syntax::IdentifierExpressionSyntax *>(
      node->getIdentifier().get());

  auto function_name = function_identifier->getValue();

  auto symbol_table = m_binder_context.getSymbolTable().get();

  if (Builtins::isBuiltInFunction(function_name)) {
    m_binder_context.reportError(
        diagnostic::DiagnosticCode::kFunctionNameConflictsWithBuiltin,
        {function_name}, function_identifier->getSourceLocation());
    return;
  }

  std::vector<std::shared_ptr<types::ParameterType>> params;
  std::vector<std::shared_ptr<types::ReturnType>> return_types;

  size_t default_value_start_index = static_cast<size_t>(-1), count = 0;

  for (auto &param : node->getParameters()) {
    auto param_expression =
        static_cast<syntax::ParameterExpressionSyntax *>(param.get());
    auto param_type =
        m_binder_context.getTypeResolver()->resolveParameterExpression(
            param_expression);

    auto current_param_name =
        static_cast<syntax::IdentifierExpressionSyntax *>(
            param_expression->getIdentifierExpression().get())
            ->getValue();

    if (default_value_start_index != static_cast<size_t>(-1) &&
        !param_expression->hasDefaultValueExpression()) {
      m_binder_context.reportError(
          diagnostic::DiagnosticCode::
              kExpectedADefaultValueAfterTheFirstOptionalParameter,
          {function_name, current_param_name},
          param_expression->getSourceLocation());

      return;
    }

    if (default_value_start_index == static_cast<size_t>(-1) &&
        param_expression->hasDefaultValueExpression()) {
      default_value_start_index = count;
    }

    params.push_back(param_type);
    count++;
  }

  auto has_return_type = node->hasReturnType();

  if (has_return_type) {
    return_types = m_binder_context.getTypeResolver()->resolveReturnType(
        static_cast<syntax::FunctionReturnTypeExpressionSyntax *>(
            node->getReturnType().get()));
  } else {
    auto inferred = inferReturnType(
        static_cast<syntax::BlockStatementSyntax *>(node->getBody().get()));
    if (inferred && !inferred->isNthg()) {
      return_types.push_back(std::make_shared<types::ReturnType>(inferred));
    } else {
      return_types.push_back(std::make_shared<types::ReturnType>(
          analysis::Builtins::m_nthg_type_instance));
    }
  }

  auto function_type = std::make_shared<types::FunctionType>(
      std::move(params), std::move(return_types), default_value_start_index,
      false);

  auto function_symbol =
      std::make_shared<analysis::FunctionSymbol>(function_name, function_type);

  if (const std::string *mod = m_binder_context.peekModuleName()) {
    function_symbol->setMangledName(*mod + std::string("_fw_") + function_name);
  }

  if (!symbol_table->define(function_symbol)) {
    m_binder_context.reportError(
        diagnostic::DiagnosticCode::kFunctionAlreadyDeclared, {function_name},
        function_identifier->getSourceLocation());
    return;
  }

  function_symbol->setDeclarationSite(
      m_binder_context.getCompilationContext().getAbsoluteSourceFilePath(),
      function_identifier->getSourceLocation());
}

std::shared_ptr<types::Type> analysis::DeclarationAnalyzer::inferReturnType(
    syntax::BlockStatementSyntax *body) {

  return m_binder_context.getTypeResolver()->inferImplicitReturnTypeFromBody(body);
}

} // namespace flow_wing