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
#include "src/syntax/expression/TemplateStringLiteralExpressionSyntax/TemplateStringLiteralExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/NodeKind/NodeKind.h"
#include <cassert>
#include <string>

namespace flow_wing {
namespace syntax {

TemplateStringLiteralExpressionSyntax ::TemplateStringLiteralExpressionSyntax(
    const SyntaxToken *token)
    : m_token(token), m_value(std::any_cast<std::string>(token->getValue())) {}

// Overrides
NodeKind TemplateStringLiteralExpressionSyntax ::getKind() const {
  return NodeKind::kTemplateStringLiteralExpression;
}

void TemplateStringLiteralExpressionSyntax::accept(
    visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::vector<const SyntaxNode *> &
TemplateStringLiteralExpressionSyntax ::getChildren() const {
  if (m_children.empty()) {
    if (m_token)
      m_children.push_back(m_token);
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing