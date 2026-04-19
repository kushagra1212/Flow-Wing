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


#include "BringStatementSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/StringLiteralExpressionSyntax/StringLiteralExpressionSyntax.h"

namespace flow_wing {
namespace syntax {

BringStatementSyntax::BringStatementSyntax(
    const SyntaxToken *bring_keyword_token, const SyntaxToken *open_brace_token,
    std::vector<std::unique_ptr<ExpressionSyntax>> identifier_expressions,
    const SyntaxToken *close_brace_token, const SyntaxToken *from_keyword_token,
    std::unique_ptr<StringLiteralExpressionSyntax> string_literal_expression)
    : m_bring_keyword_token(bring_keyword_token),
      m_open_brace_token(open_brace_token),
      m_identifier_expressions(std::move(identifier_expressions)),
      m_close_brace_token(close_brace_token),
      m_from_keyword_token(from_keyword_token),
      m_string_literal_expression(std::move(string_literal_expression)) {}

NodeKind BringStatementSyntax::getKind() const {
  return NodeKind::kBringStatement;
}

void BringStatementSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::vector<std::unique_ptr<ExpressionSyntax>> &
BringStatementSyntax::getIdentifierExpressions() const {
  return m_identifier_expressions;
}

const std::unique_ptr<StringLiteralExpressionSyntax> &
BringStatementSyntax::getStringLiteralExpression() const {
  return m_string_literal_expression;
}

const std::vector<const SyntaxNode *> &
BringStatementSyntax::getChildren() const {
  if (m_children.empty()) {
    for (const auto &node : {
             static_cast<const SyntaxNode *>(m_bring_keyword_token),
             static_cast<const SyntaxNode *>(m_open_brace_token),
         }) {

      if (node)
        m_children.push_back(node);
    }

    for (const auto &identifier_expression : m_identifier_expressions) {
      if (identifier_expression)
        m_children.push_back(identifier_expression.get());
    }

    for (const auto &node : {
             static_cast<const SyntaxNode *>(m_close_brace_token),
             static_cast<const SyntaxNode *>(m_from_keyword_token),
             static_cast<const SyntaxNode *>(m_string_literal_expression.get()),
         }) {
      if (node)
        m_children.push_back(node);
    }
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing