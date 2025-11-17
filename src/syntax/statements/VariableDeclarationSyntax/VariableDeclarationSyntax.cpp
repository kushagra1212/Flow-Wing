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


#include "VariableDeclarationSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace syntax {

VariableDeclarationSyntax::VariableDeclarationSyntax(
    const SyntaxToken *const_keyword_token,
    const SyntaxToken *var_keyword_token,
    std::vector<std::unique_ptr<DeclaratorExpressionSyntax>> declarators,
    std::vector<const SyntaxToken *> comma_tokens,
    std::unique_ptr<ExpressionSyntax> initializer_expression)
    : m_const_keyword_token(const_keyword_token),
      m_var_keyword_token(var_keyword_token),
      m_declarators(std::move(declarators)),
      m_comma_tokens(std::move(comma_tokens)),
      m_initializer_expression(std::move(initializer_expression)) {}

NodeKind VariableDeclarationSyntax::getKind() const {
  return NodeKind::kVariableDeclaration;
}

void VariableDeclarationSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

// getters

const std::vector<std::unique_ptr<DeclaratorExpressionSyntax>> &
VariableDeclarationSyntax::getDeclarators() const {
  return m_declarators;
}

const std::unique_ptr<ExpressionSyntax> &
VariableDeclarationSyntax::getInitializerExpression() const {
  return m_initializer_expression;
}

// boolean queries

bool VariableDeclarationSyntax::hasConstKeyword() const {
  return m_const_keyword_token != nullptr;
}

const std::vector<const SyntaxNode *> &
VariableDeclarationSyntax::getChildren() const {
  if (m_children.empty()) {
    for (const auto &child :
         {static_cast<const SyntaxNode *>(m_const_keyword_token),
          static_cast<const SyntaxNode *>(m_var_keyword_token)}) {
      if (child) {
        m_children.push_back(child);
      }
    }

    const size_t size = std::max(m_declarators.size(), m_comma_tokens.size());
    for (size_t i = 0; i < size; i++) {
      if (i < m_declarators.size() && m_declarators[i]) {
        m_children.push_back(m_declarators[i].get());
      }
      if (i < m_comma_tokens.size() && m_comma_tokens[i]) {
        m_children.push_back(m_comma_tokens[i]);
      }
    }

    if (m_initializer_expression)
      m_children.push_back(m_initializer_expression.get());
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing