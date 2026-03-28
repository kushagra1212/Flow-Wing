/*
 * Flow-Wing Compiler
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
#include "src/SemanticAnalyzer/BoundExpressions/BoundColonExpression/BoundColonExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundObjectExpression/BoundObjectExpression.hpp"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/common/types/CustomObjectType/CustomObjectType.hpp"
#include "src/common/types/Type.hpp"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/syntax/expression/BinaryExpressionSyntax/BinaryExpressionSyntax.h"
#include "src/syntax/expression/ColonExpressionSyntax/ColonExpressionSyntax.h"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/expression/ObjectExpressionSyntax/ObjectExpressionSyntax.h"
#include "src/utils/LogConfig.h"
#include <cassert>
namespace flow_wing {
namespace binding {

namespace {

void flattenCommaSyntaxList(syntax::ExpressionSyntax *expression,
                            std::vector<syntax::ExpressionSyntax *> &out) {
  while (expression->getKind() == syntax::NodeKind::kBinaryExpression) {
    auto *binary_expr =
        static_cast<syntax::BinaryExpressionSyntax *>(expression);
    if (binary_expr->getOperatorToken()->getTokenKind() ==
        lexer::TokenKind::kCommaToken) {
      out.insert(out.begin(), binary_expr->getRight().get());
      expression = binary_expr->getLeft().get();
    } else {
      break;
    }
  }
  out.insert(out.begin(), expression);
}

} // namespace

std::unique_ptr<BoundExpression>
ExpressionBinder::bindObjectExpression(syntax::ObjectExpressionSyntax *node) {
  return bindObjectExpression(node, nullptr);
}

std::unique_ptr<BoundExpression> ExpressionBinder::bindObjectExpression(
    syntax::ObjectExpressionSyntax *node,
    std::shared_ptr<types::Type> structureTypeHint) {

  types::CustomObjectType *co_hint = nullptr;
  if (structureTypeHint &&
      structureTypeHint->getKind() == types::TypeKind::kObject) {
    co_hint = static_cast<types::CustomObjectType *>(structureTypeHint.get());
  }

  if (!node->getColonExpression().get()) {
    if (co_hint) {
      return BinderContext::createDefaultValueExpression(
          co_hint, node->getSourceLocation());
    }
    auto object_type = std::make_shared<types::CustomObjectType>(
        "object_expression",
        std::map<std::string, std::shared_ptr<types::Type>>{});
    std::map<std::string, std::shared_ptr<types::Type>> empty_map;
    return std::make_unique<BoundObjectExpression>(
        std::move(empty_map), std::vector<std::unique_ptr<BoundExpression>>{},
        object_type, node->getSourceLocation());
  }

  std::map<std::string, std::shared_ptr<types::Type>> field_types_map;
  std::vector<std::unique_ptr<BoundExpression>> colon_expressions;

  if (co_hint) {
    std::vector<syntax::ExpressionSyntax *> flat;
    flattenCommaSyntaxList(node->getColonExpression().get(), flat);
    for (auto *expr : flat) {
      if (expr->getKind() != syntax::NodeKind::kColonExpression) {

        auto error_expression = std::make_unique<BoundErrorExpression>(
            expr->getSourceLocation(),
            diagnostic::DiagnosticCode::kUnexpectedExpression,
            std::vector<flow_wing::diagnostic::DiagnosticArg>{
                toString(expr->getKind()),
                toString(NodeKind::kObjectExpression)});
        m_context->reportError(error_expression.get());
        return std::move(error_expression);
      }
      auto *colon_syntax = static_cast<syntax::ColonExpressionSyntax *>(expr);
      auto *left_expr = colon_syntax->getLeftExpression().get();
      if (left_expr->getKind() != syntax::NodeKind::kIdentifierExpression) {
        auto error_expression = std::make_unique<BoundErrorExpression>(
            left_expr->getSourceLocation(),
            diagnostic::DiagnosticCode::kUnexpectedExpression,
            std::vector<flow_wing::diagnostic::DiagnosticArg>{
                toString(left_expr->getKind()),
                toString(syntax::NodeKind::kIdentifierExpression)});
        m_context->reportError(error_expression.get());
        return std::move(error_expression);
      }
      const std::string field_name =
          static_cast<syntax::IdentifierExpressionSyntax *>(left_expr)
              ->getValue();
      std::shared_ptr<types::Type> field_hint;
      auto it = co_hint->getFieldTypesMap().find(field_name);
      if (it != co_hint->getFieldTypesMap().end())
        field_hint = it->second;
      std::unique_ptr<BoundExpression> right_bound;
      if (field_hint &&
          field_hint->getKind() == types::TypeKind::kObject &&
          colon_syntax->getRightExpression()->getKind() ==
              syntax::NodeKind::kObjectExpression) {
        // Nested `{ a: { ... } }` must use the declared object field type as
        // the struct hint, not `bind()` which would call bindObjectExpression
        // without a hint and infer int8 / wrong aggregate layouts.
        right_bound = bindObjectExpression(
            static_cast<syntax::ObjectExpressionSyntax *>(
                colon_syntax->getRightExpression().get()),
            field_hint);
      } else {
        if (field_hint)
          m_context->pushExpectedType(field_hint);
        right_bound = bind(colon_syntax->getRightExpression().get());
        if (field_hint)
          m_context->popExpectedType();
      }
      if (right_bound->getKind() == NodeKind::kErrorExpression) {
        return right_bound;
      }
      colon_expressions.push_back(std::make_unique<BoundColonExpression>(
          field_name, std::move(right_bound),
          colon_syntax->getSourceLocation()));
      auto *bce =
          static_cast<BoundColonExpression *>(colon_expressions.back().get());
      // Use the declared field type from the struct hint when present. Otherwise
      // literals like `22` bind as int8 and would shrink the aggregate layout
      // (e.g. { i8 }) while the named type T uses int (i32), breaking IR/codegen.
      field_types_map.insert(
          {field_name,
           field_hint ? field_hint : bce->getRightExpression()->getType()});
    }

    for (const auto &[fname, ftype] : co_hint->getFieldTypesMap()) {
      if (field_types_map.find(fname) != field_types_map.end())
        continue;
      auto def = BinderContext::createDefaultValueExpression(
          ftype.get(), node->getSourceLocation());
      if (def->getKind() == NodeKind::kErrorExpression) {
        return def;
      }
      colon_expressions.push_back(std::make_unique<BoundColonExpression>(
          fname, std::move(def), node->getSourceLocation()));
      auto *bce =
          static_cast<BoundColonExpression *>(colon_expressions.back().get());
      field_types_map.insert({fname, bce->getRightExpression()->getType()});
    }
  } else {
    colon_expressions = bindExpressionList(node->getColonExpression().get());
    for (auto &member : colon_expressions) {
      if (member->getKind() == NodeKind::kErrorExpression) {
        return std::move(member);
      }

      if (member->getKind() != NodeKind::kColonExpression) {

        auto error_expression = std::make_unique<BoundErrorExpression>(
            member->getSourceLocation(),
            diagnostic::DiagnosticCode::kUnexpectedExpression,
            std::vector<flow_wing::diagnostic::DiagnosticArg>{
                toString(member->getKind()),
                toString(NodeKind::kObjectExpression)});

        m_context->reportError(error_expression.get());

        return std::move(error_expression);
      }

      auto colon_expression = static_cast<BoundColonExpression *>(member.get());

      field_types_map.insert(
          {colon_expression->getFieldName(),
           colon_expression->getRightExpression()->getType()});
    }
  }

  std::shared_ptr<types::Type> object_type;
  if (structureTypeHint &&
      structureTypeHint->getKind() == types::TypeKind::kObject) {
    auto named =
        std::static_pointer_cast<types::CustomObjectType>(structureTypeHint);
    object_type = std::make_shared<types::CustomObjectType>(
        named->getCustomTypeName(), field_types_map);
  } else {
    object_type = std::make_shared<types::CustomObjectType>("object_expression",
                                                            field_types_map);
  }

  return std::make_unique<BoundObjectExpression>(
      std::move(field_types_map), std::move(colon_expressions), object_type,
      node->getSourceLocation());
}

} // namespace binding
} // namespace flow_wing
