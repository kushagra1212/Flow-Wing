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


#include "ExpressionBinder.hpp"
#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/common/types/Type.hpp"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/syntax/expression/CallExpressionSyntax/CallExpressionSyntax.h"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include <cassert>
#include <string>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundExpression>
ExpressionBinder::bindCallExpression(syntax::CallExpressionSyntax *expression) {
  assert(expression != nullptr &&
         "CallExpressionBinder::bind: expression is null");

  auto identifier_expression = expression->getIdentifier().get();

  if (identifier_expression->getKind() !=
      syntax::NodeKind::kIdentifierExpression) {
    m_context->reportError(
        diagnostic::DiagnosticCode::kUnexpectedExpression,
        {syntax::toString(identifier_expression->getKind()),
         syntax::toString(syntax::NodeKind::kIdentifierExpression)},
        identifier_expression->getSourceLocation());

    return std::make_unique<BoundErrorExpression>(
        identifier_expression->getSourceLocation());
  }

  auto function_name =
      static_cast<syntax::IdentifierExpressionSyntax *>(identifier_expression)
          ->getValue();

  auto symbol = m_context->getSymbolTable()->lookup(function_name).get();

  if (!symbol) {
    m_context->reportError(diagnostic::DiagnosticCode::kFunctionNotFound,
                           {function_name},
                           identifier_expression->getSourceLocation());
    return std::make_unique<BoundErrorExpression>(
        identifier_expression->getSourceLocation());
  }

  auto function_symbol = static_cast<analysis::FunctionSymbol *>(symbol);

  auto type = function_symbol->getType();

  if (type->getKind() != types::TypeKind::kFunction) {
    m_context->reportError(diagnostic::DiagnosticCode::kTypeIsNotAFunction,
                           {type->getName()},
                           identifier_expression->getSourceLocation());
    return std::make_unique<BoundErrorExpression>(
        identifier_expression->getSourceLocation());
  }

  auto function_type = static_cast<types::FunctionType *>(type.get());

  auto argument_expression = expression->getArgumentExpression().get();

  std::vector<std::unique_ptr<BoundExpression>> arguments;
  std::vector<std::shared_ptr<types::Type>> argument_types;

  if (argument_expression) {
    arguments = bindExpressionList(argument_expression);
    for (const auto &argument : arguments) {
      if (argument->getKind() == NodeKind::kErrorExpression) {
        return std::make_unique<BoundErrorExpression>(
            argument->getSourceLocation());
      }
      argument_types.push_back(argument->getType());
    }
  }

  auto const has_default_value =
      function_type->getDefaultValueStartIndex() != static_cast<size_t>(-1);

  if (has_default_value &&
      argument_types.size() < function_type->getDefaultValueStartIndex()) {
    m_context->reportError(
        diagnostic::DiagnosticCode::kFunctionArgumentCountMismatch,
        {
            function_type->getName(),
            std::to_string(function_type->getDefaultValueStartIndex()),
            std::to_string(arguments.size()),
        },
        identifier_expression->getSourceLocation());

    return std::make_unique<BoundErrorExpression>(
        identifier_expression->getSourceLocation());
  }

  if (!has_default_value &&
      argument_types.size() != function_type->getParameterTypes().size()) {
    m_context->reportError(
        diagnostic::DiagnosticCode::kFunctionArgumentCountMismatch,
        {
            function_type->getName(),
            std::to_string(function_type->getParameterTypes().size()),
            std::to_string(arguments.size()),
        },
        identifier_expression->getSourceLocation());

    return std::make_unique<BoundErrorExpression>(
        identifier_expression->getSourceLocation());
  }

  auto const size = arguments.size();

  for (size_t i = 0; i < size; i++) {
    auto parameter_type = function_type->getParameterTypes()[i]->type;
    auto argument_type = arguments[i]->getType();

    if (argument_type > parameter_type) {
      m_context->reportError(
          diagnostic::DiagnosticCode::kFunctionArgumentTypeMismatch,
          {
              parameter_type->getName(),
              argument_type->getName(),
              function_type->getName(),
          },
          arguments[i]->getSourceLocation());

      return std::make_unique<BoundErrorExpression>(
          arguments[i]->getSourceLocation());
    }
  }

  return std::make_unique<BoundCallExpression>(
      function_symbol, std::move(arguments), expression->getSourceLocation());
}

} // namespace binding
} // namespace flow_wing