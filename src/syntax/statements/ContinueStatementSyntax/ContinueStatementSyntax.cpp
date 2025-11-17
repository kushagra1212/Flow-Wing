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


#include "ContinueStatementSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace syntax {

ContinueStatementSyntax::ContinueStatementSyntax(
    const SyntaxToken *continue_keyword)
    : m_continue_keyword(continue_keyword) {}

NodeKind ContinueStatementSyntax::getKind() const {
  return NodeKind::kContinueStatement;
}

void ContinueStatementSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::vector<const SyntaxNode *> &
ContinueStatementSyntax::getChildren() const {
  if (m_children.empty()) {
    if (m_continue_keyword)
      m_children.push_back(m_continue_keyword);
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing