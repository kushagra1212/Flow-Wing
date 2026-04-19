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

#include "src/syntax/expression/ModuleAccessExpressionSyntax/ModuleAccessExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"

namespace flow_wing {
namespace syntax {

ModuleAccessExpressionSyntax::ModuleAccessExpressionSyntax(
    std::unique_ptr<ExpressionSyntax> module_name_expression,
    const SyntaxToken *colon_colon_token,
    std::unique_ptr<ExpressionSyntax> member_access_expression)
    : m_module_name_expression(std::move(module_name_expression)),
      m_colon_colon_token(std::move(colon_colon_token)),
      m_member_access_expression(std::move(member_access_expression)) {}

// Overrides
NodeKind ModuleAccessExpressionSyntax::getKind() const {
  return NodeKind::kModuleAccessExpression;
}

const std::unique_ptr<ExpressionSyntax> &
ModuleAccessExpressionSyntax::getModuleNameExpression() const {
  return m_module_name_expression;
}
const std::unique_ptr<ExpressionSyntax> &
ModuleAccessExpressionSyntax::getMemberAccessExpression() const {
  return m_member_access_expression;
}

void ModuleAccessExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::vector<const SyntaxNode *> &
ModuleAccessExpressionSyntax::getChildren() const {
  if (m_children.empty()) {
    for (const auto &node :
         {static_cast<const SyntaxNode *>(m_module_name_expression.get()),
          static_cast<const SyntaxNode *>(m_colon_colon_token),
          static_cast<const SyntaxNode *>(m_member_access_expression.get())}) {
      if (node)
        m_children.emplace_back(node);
    }
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing