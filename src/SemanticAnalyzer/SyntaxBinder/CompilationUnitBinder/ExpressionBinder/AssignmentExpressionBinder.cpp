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

#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundIdentifierExpression/BoundIdentifierExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundMemberAccessExpression/BoundMemberAccessExpression.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/ExpressionBinder/ExpressionBinder.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/common/types/Type.hpp"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/syntax/expression/AssignmentExpressionSyntax/AssignmentExpressionSyntax.h"

#include "src/common/Symbol/VariableSymbol.hpp"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/utils/LogConfig.h"
#include <cassert>
namespace flow_wing {
namespace binding {

const BoundExpression *ExpressionBinder::getBaseIdentifierFromMemberAccess(
    const BoundExpression *expression) {
  if (expression->getKind() != NodeKind::kMemberAccessExpression) {
    return expression;
  }

  auto member_expr =
      static_cast<const BoundMemberAccessExpression *>(expression);
  auto current_expression = member_expr->getLeftExpression().get();

  while (current_expression->getKind() == NodeKind::kMemberAccessExpression) {
    auto nested_member_expr =
        static_cast<const BoundMemberAccessExpression *>(current_expression);
    current_expression = nested_member_expr->getLeftExpression().get();
  }

  return current_expression;
}

std::unique_ptr<BoundErrorExpression>
ExpressionBinder::checkConstantVariableAssignment(
    const BoundExpression *left_expression,
    const diagnostic::SourceLocation &location) {
  const BoundExpression *base_expression = left_expression;

  if (left_expression->getKind() == NodeKind::kMemberAccessExpression) {
    base_expression = getBaseIdentifierFromMemberAccess(left_expression);
  }

  if (base_expression->getKind() != NodeKind::kIdentifierExpression) {
    return nullptr;
  }

  auto base_id_expr =
      static_cast<const BoundIdentifierExpression *>(base_expression);
  auto base_symbol =
      const_cast<BoundIdentifierExpression *>(base_id_expr)->getSymbol();

  if (base_symbol->getKind() != analysis::SymbolKind::kVariable) {
    return nullptr;
  }

  auto base_var_sym =
      static_cast<const analysis::VariableSymbol *>(base_symbol);

  if (base_var_sym->isConst()) {
    return std::make_unique<BoundErrorExpression>(
        location,
        diagnostic::DiagnosticCode::kInvalidAssignmentToConstantVariable,
        std::vector<flow_wing::diagnostic::DiagnosticArg>{
            base_symbol->getName()});
  }

  return nullptr;
}

std::unique_ptr<BoundExpression> ExpressionBinder::bindAssignmentExpression(
    syntax::AssignmentExpressionSyntax *expression) {

  auto left_expressions = bindExpressionList(expression->getLeft().get());

  for (auto &left_expression : left_expressions) {
    if (left_expression->getKind() == NodeKind::kErrorExpression) {
      return std::move(left_expression);
    }
  }

  auto right_expressions = bindExpressionList(expression->getRight().get());

  for (auto &right_expression : right_expressions) {
    if (right_expression->getKind() == NodeKind::kErrorExpression) {
      return std::move(right_expression);
    }
  }

  auto is_full_re_assignment = expression->isFullReAssignment();

  if (left_expressions.size() != right_expressions.size()) {

    auto error_expression = std::make_unique<BoundErrorExpression>(
        expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kAssignmentExpressionCountMismatch,
        std::vector<flow_wing::diagnostic::DiagnosticArg>{
            std::to_string(left_expressions.size()),
            std::to_string(right_expressions.size())});

    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  size_t size = left_expressions.size();

  for (size_t i = 0; i < size; i++) {
    auto &left_expression = left_expressions[i];
    auto &right_expression = right_expressions[i];

    auto right_type = right_expression->getType();
    auto left_type = left_expression->getType();

    switch (left_expression->getKind()) {
    case NodeKind::kIdentifierExpression: {
      auto id_expr =
          static_cast<BoundIdentifierExpression *>(left_expression.get());
      auto symbol = id_expr->getSymbol();

      // Variable Check
      if (symbol->getKind() != analysis::SymbolKind::kVariable &&
          symbol->getKind() != analysis::SymbolKind::kParameter) {
        auto error_expression = std::make_unique<BoundErrorExpression>(
            expression->getSourceLocation(),
            diagnostic::DiagnosticCode::kAssignmentToNonVariable,
            std::vector<flow_wing::diagnostic::DiagnosticArg>{
                symbol->getName()});
        m_context->reportError(error_expression.get());
        return std::move(error_expression);
      }

      // Const Check
      auto const_error = checkConstantVariableAssignment(
          left_expression.get(), expression->getSourceLocation());
      if (const_error != nullptr) {
        m_context->reportError(const_error.get());
        return std::move(const_error);
      }

      break;
    }
    case NodeKind::kIndexExpression: {
      break;
    }
    case NodeKind::kMemberAccessExpression: {
      // Check if the base object is a constant variable
      auto const_error = checkConstantVariableAssignment(
          left_expression.get(), expression->getSourceLocation());
      if (const_error != nullptr) {
        m_context->reportError(const_error.get());
        return std::move(const_error);
      }
      break;
    }
    default: {
      auto error = std::make_unique<BoundErrorExpression>(
          expression->getSourceLocation(),
          diagnostic::DiagnosticCode::kAssignmentToNonLValue,
          std::vector<flow_wing::diagnostic::DiagnosticArg>{});
      m_context->reportError(error.get());
      return std::move(error);
    }
    }

    // Special handling for dynamic types
    if (left_type->isDynamic()) {
      // Left is dynamic: right must be dynamic or primitive
      if (!right_type->isDynamic() && !right_type->isPrimitive()) {
        auto error_expression = std::make_unique<BoundErrorExpression>(
            expression->getSourceLocation(),
            diagnostic::DiagnosticCode::kAssignmentExpressionTypeMismatch,
            std::vector<flow_wing::diagnostic::DiagnosticArg>{
                left_expression->getType()->getName(),
                right_expression->getType()->getName()});
        m_context->reportError(error_expression.get());
        return std::move(error_expression);
      }
      // Dynamic can hold any primitive or dynamic, so allow it
    } else if (right_type->isDynamic()) {
      // Right is dynamic: left must be a type that can hold the dynamic value
      // This will be checked at runtime via dispatch, but we allow it
      // semantically (the dynamic value will be extracted and converted to left
      // type)
    } else if (*right_type > *left_type) {

      BINDER_DEBUG_LOG("Left Type: ", left_type->getName());
      BINDER_DEBUG_LOG("Right Type: ", right_type->getName());

      // Normal type mismatch check
      auto error_expression = std::make_unique<BoundErrorExpression>(
          expression->getSourceLocation(),
          diagnostic::DiagnosticCode::kAssignmentExpressionTypeMismatch,
          std::vector<flow_wing::diagnostic::DiagnosticArg>{
              left_expression->getType()->getName(),
              right_expression->getType()->getName()});

      m_context->reportError(error_expression.get());
      return std::move(error_expression);
    }
  }

  return std::make_unique<BoundAssignmentExpression>(
      std::move(left_expressions), std::move(right_expressions),
      is_full_re_assignment, expression->getSourceLocation());
}

} // namespace binding
} // namespace flow_wing