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

#include "ExpressionBinder.hpp"
#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundParenthesizedExpression/BoundParenthesizedExpression.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/common/types/Type.hpp"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/syntax/expression/CallExpressionSyntax/CallExpressionSyntax.h"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/utils/LogConfig.h"
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

    auto error_expression = std::make_unique<BoundErrorExpression>(
        identifier_expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kUnexpectedExpression,
        std::vector<flow_wing::diagnostic::DiagnosticArg>{
            syntax::toString(identifier_expression->getKind()),
            syntax::toString(syntax::NodeKind::kIdentifierExpression)});

    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  auto function_name =
      static_cast<syntax::IdentifierExpressionSyntax *>(identifier_expression)
          ->getValue();

  auto handleCallExpression =
      [&](analysis::Symbol *symbol) -> std::unique_ptr<BoundExpression> {
    if (!symbol) {

      auto error_expression = std::make_unique<BoundErrorExpression>(
          identifier_expression->getSourceLocation(),
          diagnostic::DiagnosticCode::kFunctionNotFound,
          std::vector<flow_wing::diagnostic::DiagnosticArg>{function_name});

      return std::move(error_expression);
    }

    auto function_symbol = static_cast<analysis::FunctionSymbol *>(symbol);

    auto type = function_symbol->getType();

    if (type->getKind() != types::TypeKind::kFunction) {
      auto error_expression = std::make_unique<BoundErrorExpression>(
          identifier_expression->getSourceLocation(),
          diagnostic::DiagnosticCode::kTypeIsNotAFunction,
          std::vector<flow_wing::diagnostic::DiagnosticArg>{type->getName()});

      return std::move(error_expression);
    }

    auto function_type = static_cast<types::FunctionType *>(type.get());
    DEBUG_LOG("Function Type", "Function Type", function_type->getName());

    auto argument_expression = expression->getArgumentExpression().get();

    std::vector<std::unique_ptr<BoundExpression>> arguments;
    std::vector<std::shared_ptr<types::Type>> argument_types;

    if (argument_expression) {
      arguments = bindExpressionList(argument_expression);
      for (auto &argument : arguments) {
        if (argument->getKind() == NodeKind::kErrorExpression) {
          return std::move(argument);
        }
        argument_types.push_back(argument->getType());
      }
    }

    auto const has_default_value =
        function_type->getDefaultValueStartIndex() != static_cast<size_t>(-1);

    if (has_default_value &&
        argument_types.size() < function_type->getDefaultValueStartIndex()) {

      auto error_expression = std::make_unique<BoundErrorExpression>(
          identifier_expression->getSourceLocation(),
          diagnostic::DiagnosticCode::kFunctionArgumentCountMismatch,
          std::vector<flow_wing::diagnostic::DiagnosticArg>{
              function_name + "(" + function_type->getName() + ")",
              std::to_string(function_type->getDefaultValueStartIndex()),
              std::to_string(arguments.size()),
          });

      return std::move(error_expression);
    }

    if (!has_default_value &&
        argument_types.size() != function_type->getParameterTypes().size() &&
        !function_type->isVariadic()) {

      auto error_expression = std::make_unique<BoundErrorExpression>(
          identifier_expression->getSourceLocation(),
          diagnostic::DiagnosticCode::kFunctionArgumentCountMismatch,
          std::vector<flow_wing::diagnostic::DiagnosticArg>{
              function_name + "(" + function_type->getName() + ")",
              std::to_string(function_type->getParameterTypes().size()),
              std::to_string(arguments.size()),
          });

      return std::move(error_expression);
    }

    auto const size = arguments.size();

    if (!function_type->isVariadic()) {
      for (size_t i = 0; i < size; i++) {
        auto param = function_type->getParameterTypes()[i];
        auto parameter_type = param->type;
        auto argument_type = arguments[i]->getType();

        DEBUG_LOG("Argument Type", "Argument Type", argument_type->getName());
        DEBUG_LOG("Parameter Type", "Parameter Type",
                  parameter_type->getName());

        // inout parameters require an lvalue (variable, index, or member access)
        if (param->value_kind == types::ValueKind::kByReference) {
          const BoundExpression *e = arguments[i].get();
          while (e &&
                 e->getKind() == NodeKind::kParenthesizedExpression) {
            e = static_cast<const BoundParenthesizedExpression *>(e)
                    ->getExpression()
                    .get();
          }
          const bool is_lvalue =
              e &&
              (e->getKind() == NodeKind::kIdentifierExpression ||
               e->getKind() == NodeKind::kIndexExpression ||
               e->getKind() == NodeKind::kMemberAccessExpression);
          if (!is_lvalue) {
            auto error_expression = std::make_unique<BoundErrorExpression>(
                arguments[i]->getSourceLocation(),
                diagnostic::DiagnosticCode::kLiteralCannotBePassedToInoutParameter,
                std::vector<flow_wing::diagnostic::DiagnosticArg>{
                    function_name + "(" + function_type->getName() + ")"});
            return std::move(error_expression);
          }
        }

        if (*argument_type > *parameter_type) {

          auto error_expression = std::make_unique<BoundErrorExpression>(
              arguments[i]->getSourceLocation(),
              diagnostic::DiagnosticCode::kFunctionArgumentTypeMismatch,
              std::vector<flow_wing::diagnostic::DiagnosticArg>{
                  parameter_type->getName(), argument_type->getName(),
                  function_name + "(" + function_type->getName() + ")"});

          return std::move(error_expression);
        }
      }
    }

    return std::make_unique<BoundCallExpression>(
        function_symbol, std::move(arguments), expression->getSourceLocation());
  };

  auto builtins_symbol_itr =
      analysis::Builtins::m_functions_symbols_map.find(function_name);

  std::unique_ptr<BoundExpression> result;
  if (builtins_symbol_itr !=
      analysis::Builtins::m_functions_symbols_map.end()) {

    DEBUG_LOG("Builtins Symbol Itr", "Builtins Symbol Itr",
              builtins_symbol_itr->second.size());
    for (const auto &symbol : builtins_symbol_itr->second) {

      result = handleCallExpression(symbol.get());
      if (result->getKind() != NodeKind::kErrorExpression) {
        break;
      }
      result = nullptr;
    }
  }

  if (!result) {
    auto symbols = m_context->getSymbolTable()->lookup(function_name);
    result = handleCallExpression(symbols.get());
  }

  if (result->getKind() == NodeKind::kErrorExpression) {

    m_context->reportError(static_cast<BoundErrorExpression *>(result.get()));
  }

  return result;
}

} // namespace binding
} // namespace flow_wing