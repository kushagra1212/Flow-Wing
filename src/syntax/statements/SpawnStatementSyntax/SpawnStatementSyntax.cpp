/*
 * FlowWing Compiler
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

#include "SpawnStatementSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace syntax {

SpawnStatementSyntax::SpawnStatementSyntax(
    const SyntaxToken *spawn_keyword,
    std::unique_ptr<ExpressionSyntax> call_expression)
    : m_spawn_keyword(spawn_keyword),
      m_call_expression(std::move(call_expression)) {}

NodeKind SpawnStatementSyntax::getKind() const {
  return NodeKind::kSpawnStatement;
}

void SpawnStatementSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::unique_ptr<ExpressionSyntax> &
SpawnStatementSyntax::getCallExpression() const {
  return m_call_expression;
}

const SyntaxToken *SpawnStatementSyntax::getSpawnKeyword() const {
  return m_spawn_keyword;
}

const std::vector<const SyntaxNode *> &
SpawnStatementSyntax::getChildren() const {
  if (m_children.empty()) {
    for (const auto &child :
         {static_cast<const SyntaxNode *>(m_spawn_keyword),
          static_cast<const SyntaxNode *>(m_call_expression.get())}) {
      if (child) {
        m_children.push_back(child);
      }
    }
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing
