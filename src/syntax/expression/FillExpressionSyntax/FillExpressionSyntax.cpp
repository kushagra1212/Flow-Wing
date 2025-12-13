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

#include "FillExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace syntax {

FillExpressionSyntax::FillExpressionSyntax(
    const syntax::SyntaxToken *open_bracket,
    std::unique_ptr<ExpressionSyntax> size_to_fill_expression,
    const syntax::SyntaxToken *fill_keyword,
    std::unique_ptr<ExpressionSyntax> element_expression,
    const syntax::SyntaxToken *close_bracket)
    : m_open_bracket(open_bracket),
      m_size_to_fill_expression(std::move(size_to_fill_expression)),
      m_fill_keyword(fill_keyword),
      m_element_expression(std::move(element_expression)),
      m_close_bracket(close_bracket) {}

NodeKind FillExpressionSyntax::getKind() const {
  return NodeKind::kFillExpression;
}

void FillExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::unique_ptr<ExpressionSyntax> &
FillExpressionSyntax::getSizeToFillExpression() const {
  return m_size_to_fill_expression;
}

const std::unique_ptr<ExpressionSyntax> &
FillExpressionSyntax::getElementExpression() const {
  return m_element_expression;
}

const std::vector<const SyntaxNode *> &
FillExpressionSyntax::getChildren() const {

  if (m_children.empty()) {

    for (const auto *node :
         {static_cast<const SyntaxNode *>(m_open_bracket),
          static_cast<const SyntaxNode *>(m_size_to_fill_expression.get()),
          static_cast<const SyntaxNode *>(m_fill_keyword),
          static_cast<const SyntaxNode *>(m_element_expression.get()),
          static_cast<const SyntaxNode *>(m_close_bracket)}) {
      if (node) {
        m_children.push_back(node);
      }
    }
  }

  return m_children;
}

} // namespace syntax
} // namespace flow_wing