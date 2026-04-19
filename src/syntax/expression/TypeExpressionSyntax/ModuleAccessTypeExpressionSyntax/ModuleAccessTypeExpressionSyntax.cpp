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

#include "ModuleAccessTypeExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"

namespace flow_wing {
namespace syntax {

ModuleAccessTypeExpressionSyntax::ModuleAccessTypeExpressionSyntax(
    std::unique_ptr<IdentifierExpressionSyntax> module_identifier_expression,
    const SyntaxToken *colon_colon_token,
    std::unique_ptr<ExpressionSyntax> type_expression)
    : m_module_identifier_expression(std::move(module_identifier_expression)),
      m_colon_colon_token(colon_colon_token),
      m_type_expression(std::move(type_expression)) {}

NodeKind ModuleAccessTypeExpressionSyntax::getKind() const {
  return NodeKind::kModuleAccessTypeExpression;
}

void ModuleAccessTypeExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::unique_ptr<IdentifierExpressionSyntax> &
ModuleAccessTypeExpressionSyntax::getModuleIdentifier() const {
  return m_module_identifier_expression;
}

const std::unique_ptr<ExpressionSyntax> &
ModuleAccessTypeExpressionSyntax::getTypeExpression() const {
  return m_type_expression;
}

const std::vector<const SyntaxNode *> &
ModuleAccessTypeExpressionSyntax::getChildren() const {
  if (m_children.empty()) {
    for (const auto &node :
         {static_cast<const SyntaxNode *>(m_module_identifier_expression.get()),
          static_cast<const SyntaxNode *>(m_colon_colon_token),
          static_cast<const SyntaxNode *>(m_type_expression.get())}) {
      if (node)
        m_children.emplace_back(node);
    }
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing