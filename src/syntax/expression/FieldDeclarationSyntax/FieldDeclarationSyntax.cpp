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
#include "src/syntax/expression/FieldDeclarationSyntax/FieldDeclarationSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"

namespace flow_wing {
namespace syntax {

FieldDeclarationSyntax::FieldDeclarationSyntax(
    std::unique_ptr<ExpressionSyntax> key_expression,
    const SyntaxToken *colon_token,
    std::unique_ptr<ExpressionSyntax> value_expression)
    : m_key_expression(std::move(key_expression)), m_colon_token(colon_token),
      m_value_expression(std::move(value_expression)) {}

// Overrides
NodeKind FieldDeclarationSyntax::getKind() const {
  return NodeKind::kFieldDeclarationExpression;
}

void FieldDeclarationSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::unique_ptr<ExpressionSyntax> &
FieldDeclarationSyntax::getKey() const {
  return m_key_expression;
}

const std::unique_ptr<ExpressionSyntax> &
FieldDeclarationSyntax::getValue() const {
  return m_value_expression;
}

const std::vector<const SyntaxNode *> &
FieldDeclarationSyntax::getChildren() const {
  if (m_children.empty()) {
    for (const auto &child :
         {static_cast<const SyntaxNode *>(m_key_expression.get()),
          static_cast<const SyntaxNode *>(m_colon_token),
          static_cast<const SyntaxNode *>(m_value_expression.get())}) {
      if (child) {
        m_children.push_back(child);
      }
    }
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing