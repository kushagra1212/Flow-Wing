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

#include "ParameterExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace syntax {

ParameterExpressionSyntax::ParameterExpressionSyntax(
    const SyntaxToken *inout_keyword, const SyntaxToken *const_keyword,
    std::unique_ptr<ExpressionSyntax> identifier_expression,
    const SyntaxToken *colon_token, const SyntaxToken *as_keyword,
    std::unique_ptr<ExpressionSyntax> type_expression,
    const SyntaxToken *equals_token,
    std::unique_ptr<ExpressionSyntax> default_value_expression)
    : m_inout_keyword(inout_keyword), m_const_keyword(const_keyword),
      m_identifier_expression(std::move(identifier_expression)),
      m_colon_token(colon_token), m_as_keyword(as_keyword),
      m_type_expression(std::move(type_expression)),
      m_equals_token(equals_token),
      m_default_value_expression(std::move(default_value_expression)) {}

NodeKind ParameterExpressionSyntax::getKind() const {
  return NodeKind::kParameterExpression;
}

void ParameterExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

// Boolean queries
bool ParameterExpressionSyntax::hasTypeExpression() const {
  return m_type_expression != nullptr;
}

bool ParameterExpressionSyntax::hasDefaultValueExpression() const {
  return m_default_value_expression != nullptr;
}

// Getters

const SyntaxToken *ParameterExpressionSyntax::getInoutKeyword() const {
  return m_inout_keyword;
}
const SyntaxToken *ParameterExpressionSyntax::getConstKeyword() const {
  return m_const_keyword;
}
const std::unique_ptr<ExpressionSyntax> &
ParameterExpressionSyntax::getIdentifierExpression() const {
  return m_identifier_expression;
}
const SyntaxToken *ParameterExpressionSyntax::getColonToken() const {
  return m_colon_token;
}
const SyntaxToken *ParameterExpressionSyntax::getAsKeyword() const {
  return m_as_keyword;
}
const std::unique_ptr<ExpressionSyntax> &
ParameterExpressionSyntax::getTypeExpression() const {
  return m_type_expression;
}
const SyntaxToken *ParameterExpressionSyntax::getEqualsToken() const {
  return m_equals_token;
}
const std::unique_ptr<ExpressionSyntax> &
ParameterExpressionSyntax::getDefaultValueExpression() const {
  return m_default_value_expression;
}

// Boolean queries
bool ParameterExpressionSyntax::hasInoutKeyword() const {
  return m_inout_keyword != nullptr;
}

bool ParameterExpressionSyntax::hasConstKeyword() const {
  return m_const_keyword != nullptr;
}

bool ParameterExpressionSyntax::hasAsKeyword() const {
  return m_as_keyword != nullptr;
}

const std::vector<const SyntaxNode *> &
ParameterExpressionSyntax::getChildren() const {
  if (m_children.empty()) {

    for (const auto &node :
         {static_cast<const SyntaxNode *>(m_inout_keyword),
          static_cast<const SyntaxNode *>(m_const_keyword),
          static_cast<const SyntaxNode *>(m_identifier_expression.get()),
          static_cast<const SyntaxNode *>(m_colon_token),
          static_cast<const SyntaxNode *>(m_as_keyword),
          static_cast<const SyntaxNode *>(m_type_expression.get()),
          static_cast<const SyntaxNode *>(m_equals_token),
          static_cast<const SyntaxNode *>(m_default_value_expression.get())}) {
      if (node) {
        m_children.push_back(node);
      }
    }
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing