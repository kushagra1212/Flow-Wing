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
#include "src/syntax/expression/DimensionClauseExpressionSyntax/DimensionClauseExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"

namespace flow_wing {
namespace syntax {

DimensionClauseExpressionSyntax::DimensionClauseExpressionSyntax(
    const SyntaxToken *open_bracket,
    std::unique_ptr<ExpressionSyntax> size_literal,
    const SyntaxToken *close_bracket)
    : m_open_bracket(std::move(open_bracket)),
      m_size_literal(std::move(size_literal)),
      m_close_bracket(std::move(close_bracket)) {}

// Overrides
NodeKind DimensionClauseExpressionSyntax::getKind() const {
  return NodeKind::kDimensionClauseExpression;
}

void DimensionClauseExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const SyntaxToken *DimensionClauseExpressionSyntax::getOpenBracket() const {
  return m_open_bracket;
}
const SyntaxToken *DimensionClauseExpressionSyntax::getCloseBracket() const {
  return m_close_bracket;
}
const std::unique_ptr<ExpressionSyntax> &
DimensionClauseExpressionSyntax::getSizeLiteral() const {
  return m_size_literal;
}

const std::vector<const SyntaxNode *> &
DimensionClauseExpressionSyntax::getChildren() const {
  if (m_children.empty()) {
    for (const auto &node :
         {static_cast<const SyntaxNode *>(m_open_bracket),
          static_cast<const SyntaxNode *>(m_size_literal.get()),
          static_cast<const SyntaxNode *>(m_close_bracket)}) {
      if (node)
        m_children.emplace_back(node);
    }
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing