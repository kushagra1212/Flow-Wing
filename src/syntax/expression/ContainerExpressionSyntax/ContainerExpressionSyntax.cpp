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

#include "ContainerExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"

namespace flow_wing {
namespace syntax {

ContainerExpressionSyntax::ContainerExpressionSyntax(
    const syntax::SyntaxToken *open_bracket,
    std::vector<std::unique_ptr<ExpressionSyntax>> elements,
    std::vector<const syntax::SyntaxToken *> comma_tokens,
    const syntax::SyntaxToken *close_bracket)
    : m_open_bracket(open_bracket), m_elements(std::move(elements)),
      m_comma_tokens(comma_tokens), m_close_bracket(close_bracket) {}

ContainerExpressionSyntax::ContainerExpressionSyntax(
    const syntax::SyntaxToken *open_bracket,
    const syntax::SyntaxToken *close_bracket)
    : m_open_bracket(open_bracket), m_close_bracket(close_bracket) {}

NodeKind ContainerExpressionSyntax::getKind() const {
  return NodeKind::kContainerExpression;
}

void ContainerExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::vector<const SyntaxNode *> &
ContainerExpressionSyntax::getChildren() const {

  if (m_children.empty()) {

    if (m_open_bracket) {
      m_children.push_back(m_open_bracket);
    }

    size_t size = std::max(m_elements.size(), m_comma_tokens.size());

    for (size_t i = 0; i < size; i++) {
      if (i < m_elements.size() && m_elements[i]) {
        m_children.push_back(m_elements[i].get());
      }
      if (i < m_comma_tokens.size() && m_comma_tokens[i]) {
        m_children.push_back(m_comma_tokens[i]);
      }
    }

    if (m_close_bracket) {
      m_children.push_back(m_close_bracket);
    }
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing