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

#include "ClassStatementSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"

namespace flow_wing {
namespace syntax {

ClassStatementSyntax::ClassStatementSyntax(
    const SyntaxToken *class_keyword_token,
    std::unique_ptr<ExpressionSyntax> class_name_identifier_expr,
    const SyntaxToken *extends_keyword_token,
    std::unique_ptr<ExpressionSyntax> parent_class_identifier_expr,
    const SyntaxToken *open_brace_token,
    std::vector<std::unique_ptr<StatementSyntax>> class_member_statements,
    const SyntaxToken *close_brace_token)
    : m_class_keyword_token(class_keyword_token),
      m_class_name_identifier_expr(std::move(class_name_identifier_expr)),
      m_extends_keyword_token(extends_keyword_token),
      m_parent_class_identifier_expr(std::move(parent_class_identifier_expr)),
      m_open_brace_token(open_brace_token),
      m_class_member_statements(std::move(class_member_statements)),
      m_close_brace_token(close_brace_token) {}

syntax::NodeKind ClassStatementSyntax::getKind() const {
  return NodeKind::kClassStatement;
}

void ClassStatementSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::unique_ptr<ExpressionSyntax> &
ClassStatementSyntax::getClassNameIdentifierExpr() const {
  return m_class_name_identifier_expr;
}

const std::unique_ptr<ExpressionSyntax> &
ClassStatementSyntax::getParentClassIdentifierExpr() const {
  return m_parent_class_identifier_expr;
}

const std::vector<std::unique_ptr<StatementSyntax>> &
ClassStatementSyntax::getClassMemberStatements() const {
  return m_class_member_statements;
}

const std::vector<const SyntaxNode *> &
ClassStatementSyntax::getChildren() const {
  if (m_children.empty()) {
    for (const auto *node :
         {static_cast<const SyntaxNode *>(m_class_keyword_token),
          static_cast<const SyntaxNode *>(m_class_name_identifier_expr.get()),
          static_cast<const SyntaxNode *>(m_extends_keyword_token),
          static_cast<const SyntaxNode *>(m_parent_class_identifier_expr.get()),
          static_cast<const SyntaxNode *>(m_open_brace_token)}) {
      if (node) {
        m_children.push_back(node);
      }
    }
    for (const auto &node : m_class_member_statements) {
      if (node) {
        m_children.push_back(node.get());
      }
    }

    if (m_close_brace_token) {
      m_children.push_back(m_close_brace_token);
    }
  }
  return m_children;
}
} // namespace syntax
} // namespace flow_wing