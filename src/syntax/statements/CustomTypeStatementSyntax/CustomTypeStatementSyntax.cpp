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


#include "CustomTypeStatementSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace syntax {

CustomTypeStatementSyntax::CustomTypeStatementSyntax(
    const SyntaxToken *type_keyword,
    std::unique_ptr<ExpressionSyntax> type_name,
    const SyntaxToken *equals_token, const SyntaxToken *open_brace_token,
    std::vector<std::unique_ptr<FieldDeclarationSyntax>> field_declarations,
    const SyntaxToken *close_brace_token)
    : m_type_keyword(type_keyword), m_type_name(std::move(type_name)),
      m_equals_token(equals_token), m_open_brace_token(open_brace_token),
      m_field_declarations(std::move(field_declarations)),
      m_close_brace_token(close_brace_token) {}

NodeKind CustomTypeStatementSyntax::getKind() const {
  return NodeKind::kCustomTypeStatement;
}

void CustomTypeStatementSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::unique_ptr<ExpressionSyntax> &
CustomTypeStatementSyntax::getTypeName() const {
  return m_type_name;
}

const std::vector<std::unique_ptr<FieldDeclarationSyntax>> &
CustomTypeStatementSyntax::getFieldDeclarations() const {
  return m_field_declarations;
}

const std::vector<const SyntaxNode *> &
CustomTypeStatementSyntax::getChildren() const {
  if (m_children.empty()) {

    for (const auto &child :
         {static_cast<const SyntaxNode *>(m_type_keyword),
          static_cast<const SyntaxNode *>(m_type_name.get()),
          static_cast<const SyntaxNode *>(m_equals_token),
          static_cast<const SyntaxNode *>(m_open_brace_token)}) {
      if (child)
        m_children.push_back(static_cast<const SyntaxNode *>(child));
    }

    for (const auto &field_declaration : m_field_declarations) {
      if (field_declaration)
        m_children.push_back(
            static_cast<const SyntaxNode *>(field_declaration.get()));
    }

    if (m_close_brace_token)
      m_children.push_back(
          static_cast<const SyntaxNode *>(m_close_brace_token));
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing