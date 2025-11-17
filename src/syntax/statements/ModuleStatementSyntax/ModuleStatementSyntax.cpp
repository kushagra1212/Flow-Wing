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


#include "ModuleStatementSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace syntax {

ModuleStatementSyntax::ModuleStatementSyntax(
    const SyntaxToken *module_keyword_token,
    const SyntaxToken *open_bracket_token,
    std::unique_ptr<ExpressionSyntax> module_name_identifier_expression,
    const SyntaxToken *close_bracket_token,
    std::vector<std::unique_ptr<StatementSyntax>> module_statements,
    const SyntaxToken *end_of_file_token)
    : m_module_keyword_token(module_keyword_token),
      m_open_bracket_token(open_bracket_token),
      m_module_name_identifier_expression(
          std::move(module_name_identifier_expression)),
      m_close_bracket_token(close_bracket_token),
      m_module_statements(std::move(module_statements)),
      m_end_of_file_token(end_of_file_token) {}

NodeKind ModuleStatementSyntax::getKind() const {
  return NodeKind::kModuleStatement;
}

void ModuleStatementSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::vector<const SyntaxNode *> &
ModuleStatementSyntax::getChildren() const {
  if (m_children.empty()) {
    for (const auto *node :
         {static_cast<const SyntaxNode *>(m_module_keyword_token),
          static_cast<const SyntaxNode *>(m_open_bracket_token),
          static_cast<const SyntaxNode *>(
              m_module_name_identifier_expression.get()),
          static_cast<const SyntaxNode *>(m_close_bracket_token)}) {
      if (node) {
        m_children.push_back(node);
      }
    }
    for (const auto &node : m_module_statements) {
      if (node) {
        m_children.push_back(node.get());
      }
    }
    if (m_end_of_file_token) {
      m_children.push_back(m_end_of_file_token);
    }
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing