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
#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/NodeKind/NodeKind.h"
#include "src/syntax/expression/AssignmentExpressionSyntax/AssignmentExpressionSyntax.h"
#include "src/syntax/expression/BinaryExpressionSyntax/BinaryExpressionSyntax.h"
#include "src/syntax/expression/BooleanLiteralExpressionSyntax/BooleanLiteralExpressionSyntax.h"
#include "src/syntax/expression/CallExpressionSyntax/CallExpressionSyntax.h"
#include "src/syntax/expression/CharacterLiteralExpressionSyntax/CharacterLiteralExpressionSyntax.h"
#include "src/syntax/expression/DoubleLiteralExpressionSyntax/DoubleLiteralExpressionSyntax.h"
#include "src/syntax/expression/FloatLiteralExpressionSyntax/FloatLiteralExpressionSyntax.h"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/expression/IndexExpressionSyntax/IndexExpressionSyntax.h"
#include "src/syntax/expression/IntegerLiteralExpressionSyntax/IntegerLiteralExpressionSyntax.h"
#include "src/syntax/expression/MemberAccessExpressionSyntax/MemberAccessExpressionSyntax.h"
#include "src/syntax/expression/ModuleAccessExpressionSyntax/ModuleAccessExpressionSyntax.h"
#include "src/syntax/expression/NewExpressionSyntax/NewExpressionSyntax.h"
#include "src/syntax/expression/NirastExpressionSyntax/NirastExpressionSyntax.h"
#include "src/syntax/expression/ParenthesizedExpressionSyntax/ParenthesizedExpressionSyntax.h"
#include "src/syntax/expression/StringLiteralExpressionSyntax/StringLiteralExpressionSyntax.h"
#include "src/syntax/expression/TemplateStringLiteralExpressionSyntax/TemplateStringLiteralExpressionSyntax.h"
#include "src/syntax/expression/TernaryExpressionSyntax/TernaryExpressionSyntax.h"
#include "src/syntax/expression/UnaryExpressionSyntax/UnaryExpressionSyntax.h"
#include "src/utils/LogConfig.h"
#include <cassert>
#include <set>

namespace flow_wing {
namespace binding {

ExpressionBinder::ExpressionBinder(BinderContext *context)
    : m_context(context) {}

std::unique_ptr<BoundExpression>
ExpressionBinder::bind(syntax::ExpressionSyntax *expression) {
  switch (expression->getKind()) {

  // ---- Assignment Expressions ----
  case syntax::NodeKind::kAssignmentExpression:
    return bindAssignmentExpression(
        static_cast<syntax::AssignmentExpressionSyntax *>(expression));

    // ---- Binary Expressions ----
  case syntax::NodeKind::kBinaryExpression:
    return bindBinaryExpression(
        static_cast<syntax::BinaryExpressionSyntax *>(expression));

    // ---- Call Expressions ----
  case syntax::NodeKind::kCallExpression:
    return bindCallExpression(
        static_cast<syntax::CallExpressionSyntax *>(expression));

    // ---- Identifier Expressions ----
  case syntax::NodeKind::kIdentifierExpression:
    return bindIdentifierExpression(
        static_cast<syntax::IdentifierExpressionSyntax *>(expression));

    // ---- Index Expressions ----
  case syntax::NodeKind::kIndexExpression:
    return bindIndexExpression(
        static_cast<syntax::IndexExpressionSyntax *>(expression));

    // ---- Literal Expressions ----

  case syntax::NodeKind::kNumberLiteralExpression:
    return bindLiteralExpression(
        static_cast<syntax::IntegerLiteralExpressionSyntax *>(expression));
  case syntax::NodeKind::kDoubleLiteralExpression:
    return bindLiteralExpression(
        static_cast<syntax::DoubleLiteralExpressionSyntax *>(expression));
  case syntax::NodeKind::kFloatLiteralExpression:
    return bindLiteralExpression(
        static_cast<syntax::FloatLiteralExpressionSyntax *>(expression));
  case syntax::NodeKind::kCharacterLiteralExpression:
    return bindLiteralExpression(
        static_cast<syntax::CharacterLiteralExpressionSyntax *>(expression));
  case syntax::NodeKind::kStringLiteralExpression:
    return bindLiteralExpression(
        static_cast<syntax::StringLiteralExpressionSyntax *>(expression));
  case syntax::NodeKind::kTemplateStringLiteralExpression:
    return bindLiteralExpression(
        static_cast<syntax::TemplateStringLiteralExpressionSyntax *>(
            expression));
  case syntax::NodeKind::kBooleanLiteralExpression:
    return bindLiteralExpression(
        static_cast<syntax::BooleanLiteralExpressionSyntax *>(expression));
  case syntax::NodeKind::kNirastExpression:
    return bindLiteralExpression(
        static_cast<syntax::NirastExpressionSyntax *>(expression));

    // ---- Member Access Expressions ----
  case syntax::NodeKind::kMemberAccessExpression:
    return bindMemberAccessExpression(
        static_cast<syntax::MemberAccessExpressionSyntax *>(expression));

    // ---- Module Access Expressions ----
  case syntax::NodeKind::kModuleAccessExpression:
    return bindModuleAccessExpression(
        static_cast<syntax::ModuleAccessExpressionSyntax *>(expression));

    // ---- New Expressions ----
  case syntax::NodeKind::kNewExpression:
    return bindNewExpression(
        static_cast<syntax::NewExpressionSyntax *>(expression));

    // ---- Ternary Expressions ----
  case syntax::NodeKind::kTernaryExpression:
    return bindTernaryExpression(
        static_cast<syntax::TernaryExpressionSyntax *>(expression));

    // ---- Unary Expressions ----
  case syntax::NodeKind::kUnaryExpression:
    return bindUnaryExpression(
        static_cast<syntax::UnaryExpressionSyntax *>(expression));

  case syntax::NodeKind::kParenthesizedExpression:
    return bindParenthesizedExpression(
        static_cast<syntax::ParenthesizedExpressionSyntax *>(expression));
  default:
    BINDER_DEBUG_LOG("Unexpected expression kind for ExpressionBinder: ",
                     toString(expression->getKind()));
    assert(false && "Unexpected expression kind for ExpressionBinder");
    return nullptr;
  }
}

std::vector<std::unique_ptr<BoundExpression>>
ExpressionBinder::bindExpressionList(syntax::ExpressionSyntax *expression) {
  assert(expression != nullptr &&
         "ExpressionBinder::bindExpressionList: expression is null");

  std::vector<std::unique_ptr<BoundExpression>> expressions;

  while (expression->getKind() == syntax::NodeKind::kBinaryExpression) {
    auto binary_expr =
        static_cast<syntax::BinaryExpressionSyntax *>(expression);

    if (binary_expr->getOperatorToken()->getTokenKind() ==
        lexer::TokenKind::kCommaToken) {
      expressions.insert(expressions.begin(),
                         bind(binary_expr->getRight().get()));
      expression = binary_expr->getLeft().get();
    } else {
      break;
    }
  }

  // First item in the list
  expressions.insert(expressions.begin(), bind(expression));
  return expressions;
}

std::pair<bool, std::shared_ptr<types::Type>>
ExpressionBinder::isUnaryAllowedType(lexer::TokenKind operator_token_kind,
                                     std::shared_ptr<types::Type> type) {

  static const std::set<types::Type *> allowed_types_for_plus_minus_operator = {
      // integers
      analysis::Builtins::m_int32_type_instance.get(),
      analysis::Builtins::m_int8_type_instance.get(),
      analysis::Builtins::m_int64_type_instance.get(),

      // decimals
      analysis::Builtins::m_deci_type_instance.get(),
      analysis::Builtins::m_deci32_type_instance.get(),

      // dynamic
      analysis::Builtins::m_dynamic_type_instance.get()};

  static const std::set<types::Type *> allowed_types_for_bang_operator = {
      // booleans
      analysis::Builtins::m_bool_type_instance.get(),

      // decimals
      analysis::Builtins::m_deci_type_instance.get(),
      analysis::Builtins::m_deci32_type_instance.get(),

      // integers
      analysis::Builtins::m_int32_type_instance.get(),
      analysis::Builtins::m_int8_type_instance.get(),
      analysis::Builtins::m_int64_type_instance.get(),

      // dynamic
      analysis::Builtins::m_dynamic_type_instance.get(),

      // nir
      analysis::Builtins::m_nirast_type_instance.get(),

      // strings
      analysis::Builtins::m_str_type_instance.get(),

      // chars
      analysis::Builtins::m_char_type_instance.get(),

      // classes
      // type->getKind() == types::TypeKind::kClass

  };

  static const std::set<types::Type *> allowed_types_for_tilde_operator = {
      // integers
      analysis::Builtins::m_int8_type_instance.get(),
      analysis::Builtins::m_int32_type_instance.get(),
      analysis::Builtins::m_int64_type_instance.get(),

      // dynamic
      analysis::Builtins::m_dynamic_type_instance.get(),
  };

  auto isAllowedType = [&](const std::set<types::Type *> &allowed_types) {
    if (std::find(allowed_types.begin(), allowed_types.end(), type.get()) ==
        allowed_types.end()) {

      return false;
    }
    return true;
  };

  switch (operator_token_kind) {
  case lexer::TokenKind::kPlusToken:
  case lexer::TokenKind::kMinusToken: {
    return {isAllowedType(allowed_types_for_plus_minus_operator), type};
  }
  case lexer::TokenKind::kBangToken: {

    // The result type of '!' is always boolean
    return {type->getKind() == types::TypeKind::kClass ||
                isAllowedType(allowed_types_for_bang_operator),
            analysis::Builtins::m_bool_type_instance};
  }
  case lexer::TokenKind::kTildeToken: {
    return {isAllowedType(allowed_types_for_tilde_operator), type};
  }
  default:
    assert(false && "Unexpected unary operator");
    return {false, nullptr};
  }
}

} // namespace binding
} // namespace flow_wing