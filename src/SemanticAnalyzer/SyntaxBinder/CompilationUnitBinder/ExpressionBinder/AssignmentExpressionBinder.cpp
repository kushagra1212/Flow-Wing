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
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/ExpressionBinder/ExpressionBinder.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/common/types/Type.hpp"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/syntax/expression/AssignmentExpressionSyntax/AssignmentExpressionSyntax.h"

#include "src/common/Symbol/VariableSymbol.hpp"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include <cassert>
namespace flow_wing {
namespace binding {

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

    if (*right_type > *left_type) {

      auto error_expression = std::make_unique<BoundErrorExpression>(
          expression->getSourceLocation(),
          diagnostic::DiagnosticCode::kAssignmentExpressionTypeMismatch,
          std::vector<flow_wing::diagnostic::DiagnosticArg>{
              left_expression->getType()->getName(),
              right_expression->getType()->getName()});

      m_context->reportError(error_expression.get());
      return std::move(error_expression);
    }

    switch (left_expression->getKind()) {
    case NodeKind::kIdentifierExpression: {
      auto id_expr =
          static_cast<BoundIdentifierExpression *>(left_expression.get());
      auto symbol = id_expr->getSymbol();

      // Variable Check
      if (symbol->getKind() != analysis::SymbolKind::kVariable) {
        auto error_expression = std::make_unique<BoundErrorExpression>(
            expression->getSourceLocation(),
            diagnostic::DiagnosticCode::kAssignmentToNonVariable,
            std::vector<flow_wing::diagnostic::DiagnosticArg>{
                symbol->getName()});
        m_context->reportError(error_expression.get());
        return std::move(error_expression);
      }

      // Const Check
      auto var_sym = static_cast<analysis::VariableSymbol *>(symbol);
      if (var_sym->isConst()) {
        auto error_expression = std::make_unique<BoundErrorExpression>(
            expression->getSourceLocation(),
            diagnostic::DiagnosticCode::kInvalidAssignmentToConstantVariable,
            std::vector<flow_wing::diagnostic::DiagnosticArg>{
                symbol->getName()});
        m_context->reportError(error_expression.get());
        return std::move(error_expression);
      }
      break;
    }
    case NodeKind::kIndexExpression: {
      assert(false && "Index expression is not supported for assignment");
      break;
    }
    case NodeKind::kMemberAccessExpression:
      assert(false &&
             "Member access expression is not supported for assignment");
      break;
    default: {
      auto error = std::make_unique<BoundErrorExpression>(
          expression->getSourceLocation(),
          diagnostic::DiagnosticCode::kAssignmentToNonLValue,
          std::vector<flow_wing::diagnostic::DiagnosticArg>{});
      m_context->reportError(error.get());
      return std::move(error);
    }
    }
  }

  return std::make_unique<BoundAssignmentExpression>(
      std::move(left_expressions), std::move(right_expressions),
      is_full_re_assignment, expression->getSourceLocation());
}

} // namespace binding
} // namespace flow_wing