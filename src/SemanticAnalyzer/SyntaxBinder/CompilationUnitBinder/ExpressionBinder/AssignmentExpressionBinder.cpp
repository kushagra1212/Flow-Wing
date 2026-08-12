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
#include "src/SemanticAnalyzer/BoundExpressions/BoundBinaryOperator/BoundBinaryOperator.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundIndexExpression/BoundIndexExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundModuleAccessExpression/BoundModuleAccessExpression.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/ExpressionBinder/ExpressionBinder.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/common/types/Type.hpp"
#include "src/syntax/expression/AssignmentExpressionSyntax/AssignmentExpressionSyntax.h"
#include "src/syntax/expression/BinaryExpressionSyntax/BinaryExpressionSyntax.h"
#include "src/syntax/expression/ObjectExpressionSyntax/ObjectExpressionSyntax.h"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/compiler/diagnostics/DiagnosticCode.h"

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

// Rejects anything that cannot be assigned to: a non-variable symbol, a const,
// or an expression that is not an L-Value. Returns nullptr when the target is
// fine. Reports the diagnostic itself.
std::unique_ptr<BoundErrorExpression>
ExpressionBinder::validateAssignmentTarget(
    BoundExpression *left_expression,
    const diagnostic::SourceLocation &location) {

  auto reportNonVariable = [&](analysis::Symbol *symbol) {
    auto error_expression = std::make_unique<BoundErrorExpression>(
        location, diagnostic::DiagnosticCode::kAssignmentToNonVariable,
        std::vector<flow_wing::diagnostic::DiagnosticArg>{symbol->getName()});
    m_context->reportError(error_expression.get());
    return error_expression;
  };

  auto reportNonLValue = [&]() {
    auto error = std::make_unique<BoundErrorExpression>(
        location, diagnostic::DiagnosticCode::kAssignmentToNonLValue,
        std::vector<flow_wing::diagnostic::DiagnosticArg>{});
    m_context->reportError(error.get());
    return error;
  };

  auto reportIfConst = [&](BoundExpression *target)
      -> std::unique_ptr<BoundErrorExpression> {
    auto const_error = checkConstantVariableAssignment(target, location);
    if (const_error != nullptr) {
      m_context->reportError(const_error.get());
      return const_error;
    }
    return nullptr;
  };

  switch (left_expression->getKind()) {
  case NodeKind::kIdentifierExpression: {
    auto id_expr = static_cast<BoundIdentifierExpression *>(left_expression);
    auto symbol = id_expr->getSymbol();

    // Variable Check
    if (symbol->getKind() != analysis::SymbolKind::kVariable &&
        symbol->getKind() != analysis::SymbolKind::kParameter) {
      return reportNonVariable(symbol);
    }

    // Const Check
    return reportIfConst(left_expression);
  }
  case NodeKind::kIndexExpression: {
    return nullptr;
  }
  case NodeKind::kMemberAccessExpression: {
    // Check if the base object is a constant variable
    return reportIfConst(left_expression);
  }
  case NodeKind::kModuleAccessExpression: {
    // e.g. local::x = ... — inner expression is the name within the module
    auto *mod_expr =
        static_cast<BoundModuleAccessExpression *>(left_expression);
    BoundExpression *inner = mod_expr->getMemberAccessExpression().get();
    switch (inner->getKind()) {
    case NodeKind::kIdentifierExpression: {
      auto *id_expr = static_cast<BoundIdentifierExpression *>(inner);
      analysis::Symbol *symbol = id_expr->getSymbol();
      if (symbol->getKind() != analysis::SymbolKind::kVariable &&
          symbol->getKind() != analysis::SymbolKind::kParameter) {
        return reportNonVariable(symbol);
      }
      return reportIfConst(inner);
    }
    case NodeKind::kMemberAccessExpression: {
      return reportIfConst(inner);
    }
    case NodeKind::kIndexExpression: {
      return nullptr;
    }
    default: {
      return reportNonLValue();
    }
    }
  }
  default: {
    return reportNonLValue();
  }
  }
}

// `x += e` means `x = x + e` with the target evaluated once. The target and the
// operand are bound here and the underlying binary operator is type-checked;
// the load-operate-store itself is emitted in IR generation, which already has
// the target's address in hand.
std::unique_ptr<BoundExpression>
ExpressionBinder::bindCompoundAssignmentExpression(
    syntax::AssignmentExpressionSyntax *expression) {

  const lexer::TokenKind compound_operator =
      expression->getCompoundBinaryOperator();
  const auto &location = expression->getSourceLocation();

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

  // `a, b += 1, 2` has no single sensible reading — the target must be one
  // L-Value so that `x = x op e` is well defined.
  if (left_expressions.size() != 1 || right_expressions.size() != 1 ||
      right_expressions[0]->isMultipleType()) {
    size_t right_count = right_expressions.size();
    if (right_count == 1 && right_expressions[0]->isMultipleType()) {
      right_count = right_expressions[0]->getMultipleTypes().size();
    }
    auto error_expression = std::make_unique<BoundErrorExpression>(
        location,
        diagnostic::DiagnosticCode::kCompoundAssignmentMultiTargetNotAllowed,
        std::vector<flow_wing::diagnostic::DiagnosticArg>{
            expression->getOperatorToken()->getText(),
            std::to_string(std::max(left_expressions.size(), right_count))});
    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  if (auto target_error =
          validateAssignmentTarget(left_expressions[0].get(), location)) {
    return std::move(target_error);
  }

  // A character of a `str` is written through fg_string_set rather than stored
  // into a slot, so there is nothing to load-operate-store. Reject it rather
  // than silently dropping the operator.
  if (left_expressions[0]->getKind() == NodeKind::kIndexExpression) {
    auto *index_expression =
        static_cast<BoundIndexExpression *>(left_expressions[0].get());
    auto base_type = index_expression->getLeftExpression()->getType();
    if (base_type == analysis::Builtins::m_str_type_instance ||
        base_type->isDynamic()) {
      auto error_expression = std::make_unique<BoundErrorExpression>(
          location,
          diagnostic::DiagnosticCode::kInvalidBinaryOperationWithTypes,
          std::vector<flow_wing::diagnostic::DiagnosticArg>{
              expression->getOperatorToken()->getText(),
              base_type->getName(), right_expressions[0]->getType()->getName()});
      m_context->reportError(error_expression.get());
      return std::move(error_expression);
    }
  }

  auto left_type = left_expressions[0]->getType();
  auto right_type = right_expressions[0]->getType();

  // `x += e` is only valid when `x + e` is — reuse the binary operator rules so
  // the two can never disagree.
  auto binary_operator =
      BoundBinaryOperator::bind(compound_operator, left_type, right_type);

  if (binary_operator == nullptr) {
    auto error_expression = std::make_unique<BoundErrorExpression>(
        location, diagnostic::DiagnosticCode::kInvalidBinaryOperationWithTypes,
        std::vector<flow_wing::diagnostic::DiagnosticArg>{
            lexer::toString(compound_operator), left_type->getName(),
            right_type->getName()});
    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  // ...and the result has to fit back into the target.
  auto result_type = binary_operator->getResultType();
  if (!left_type->isDynamic() && !result_type->isDynamic() &&
      *result_type > *left_type) {
    auto error_expression = std::make_unique<BoundErrorExpression>(
        location, diagnostic::DiagnosticCode::kAssignmentExpressionTypeMismatch,
        std::vector<flow_wing::diagnostic::DiagnosticArg>{
            left_type->getName(), result_type->getName()});
    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  return std::make_unique<BoundAssignmentExpression>(
      std::move(left_expressions), std::move(right_expressions),
      expression->isFullReAssignment(), location, compound_operator);
}

std::unique_ptr<BoundExpression> ExpressionBinder::bindAssignmentExpression(
    syntax::AssignmentExpressionSyntax *expression) {

  auto isCommaTopLevel = [](syntax::ExpressionSyntax *e) -> bool {
    if (e->getKind() != syntax::NodeKind::kBinaryExpression)
      return false;
    auto *bin = static_cast<syntax::BinaryExpressionSyntax *>(e);
    return bin->getOperatorToken()->getTokenKind() ==
           lexer::TokenKind::kCommaToken;
  };

  if (expression->isFullReAssignment() &&
      expression->getRight()->getKind() ==
          syntax::NodeKind::kObjectExpression &&
      !isCommaTopLevel(expression->getLeft().get())) {
    auto left_expressions = bindExpressionList(expression->getLeft().get());
    for (auto &le : left_expressions) {
      if (le->getKind() == NodeKind::kErrorExpression) {
        return std::move(le);
      }
    }
    if (left_expressions.size() == 1) {
      auto lt = left_expressions[0]->getType();
      if (lt->getKind() == types::TypeKind::kObject) {
        auto right = bindObjectExpression(
            static_cast<syntax::ObjectExpressionSyntax *>(
                expression->getRight().get()),
            lt);
        if (right->getKind() == NodeKind::kErrorExpression) {
          return right;
        }
        std::vector<std::unique_ptr<BoundExpression>> right_expressions;
        right_expressions.push_back(std::move(right));
        return std::make_unique<BoundAssignmentExpression>(
            std::move(left_expressions), std::move(right_expressions),
            expression->isFullReAssignment(),
            expression->getSourceLocation());
      }
    }
  }

  if (expression->isCompoundAssignment()) {
    return bindCompoundAssignmentExpression(expression);
  }

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

  // Flatten right-hand side count (one multi-return expr counts as N values)
  size_t total_right_count = 0;
  for (const auto &expr : right_expressions) {
    if (expr->isMultipleType()) {
      total_right_count += expr->getMultipleTypes().size();
    } else {
      total_right_count += 1;
    }
  }

  if (total_right_count != left_expressions.size()) {
    auto error_expression = std::make_unique<BoundErrorExpression>(
        expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kAssignmentExpressionCountMismatch,
        std::vector<flow_wing::diagnostic::DiagnosticArg>{
            std::to_string(left_expressions.size()),
            std::to_string(total_right_count)});

    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  // Type-check each left against corresponding flattened right type
  size_t var_idx = 0;
  for (auto &right_expression : right_expressions) {
    if (right_expression && right_expression->getKind() == NodeKind::kErrorExpression) {
      return std::move(right_expression);
    }

    std::vector<std::shared_ptr<types::Type>> right_types;
    bool is_multi = right_expression->isMultipleType();
    if (is_multi) {
      right_types = right_expression->getMultipleTypes();
    } else {
      right_types.push_back(right_expression->getType());
    }

    for (const auto &right_type : right_types) {
      if (var_idx >= left_expressions.size())
        break;

      if (right_type->isNthg()) {
        auto error_expression = std::make_unique<BoundErrorExpression>(
            expression->getSourceLocation(),
            diagnostic::DiagnosticCode::kAssignmentExpressionTypeMismatch,
            std::vector<flow_wing::diagnostic::DiagnosticArg>{
                left_expressions[var_idx]->getType()->getName(),
                right_type->getName()});
        m_context->reportError(error_expression.get());
        return std::move(error_expression);
      }

      auto &left_expression = left_expressions[var_idx];
      auto left_type = left_expression->getType();

      if (auto target_error = validateAssignmentTarget(
              left_expression.get(), expression->getSourceLocation())) {
        return std::move(target_error);
      }

      // Special handling for dynamic types
      if (left_type->isDynamic()) {
        // Left is dynamic: right must be dynamic or primitive
        if (!right_type->isDynamic() && !right_type->isPrimitive()) {
          auto error_expression = std::make_unique<BoundErrorExpression>(
              expression->getSourceLocation(),
              diagnostic::DiagnosticCode::kAssignmentExpressionTypeMismatch,
              std::vector<flow_wing::diagnostic::DiagnosticArg>{
                  left_type->getName(), right_type->getName()});
          m_context->reportError(error_expression.get());
          return std::move(error_expression);
        }
        // Dynamic can hold any primitive or dynamic, so allow it
      } else if (right_type->isDynamic()) {
        // Right is dynamic: left must be a type that can hold the dynamic value
        // This will be checked at runtime via dispatch, but we allow it
        // semantically (the dynamic value will be extracted and converted to
        // left type)
      } else if (*right_type > *left_type) {

        BINDER_DEBUG_LOG("Left Type: ", left_type->getName());
        BINDER_DEBUG_LOG("Right Type: ", right_type->getName());

        // Normal type mismatch check
        auto error_expression = std::make_unique<BoundErrorExpression>(
            expression->getSourceLocation(),
            diagnostic::DiagnosticCode::kAssignmentExpressionTypeMismatch,
            std::vector<flow_wing::diagnostic::DiagnosticArg>{
                left_type->getName(), right_type->getName()});

        m_context->reportError(error_expression.get());
        return std::move(error_expression);
      }

      var_idx++;
    }
  }

  return std::make_unique<BoundAssignmentExpression>(
      std::move(left_expressions), std::move(right_expressions),
      is_full_re_assignment, expression->getSourceLocation());
}

} // namespace binding
} // namespace flow_wing