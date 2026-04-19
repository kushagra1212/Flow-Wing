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

#include "FunctionReturnTypeExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"

namespace flow_wing {
namespace syntax {

FunctionReturnTypeExpressionSyntax::FunctionReturnTypeExpressionSyntax(
    const SyntaxToken *as_keyword,
    std::vector<std::unique_ptr<ExpressionSyntax>> type_expressions,
    std::vector<const SyntaxToken *> comma_tokens)
    : m_as_keyword(as_keyword), m_type_expressions(std::move(type_expressions)),
      m_comma_tokens(std::move(comma_tokens)) {}

syntax::NodeKind FunctionReturnTypeExpressionSyntax::getKind() const {
  return NodeKind::kFunctionReturnTypeExpression;
}

void FunctionReturnTypeExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::vector<std::unique_ptr<ExpressionSyntax>> &
FunctionReturnTypeExpressionSyntax::getTypeExpressions() const {
  return m_type_expressions;
}

bool FunctionReturnTypeExpressionSyntax::hasAsKeyword() const {
  return m_as_keyword != nullptr;
}

const std::vector<const SyntaxNode *> &
FunctionReturnTypeExpressionSyntax::getChildren() const {
  if (m_children.empty()) {
    if (m_as_keyword) {
      m_children.push_back(m_as_keyword);
    }
    for (const auto &node : m_type_expressions) {
      m_children.push_back(node.get());
    }
    for (const auto *node : m_comma_tokens) {
      m_children.push_back(node);
    }
  }

  return m_children;
}
} // namespace syntax
} // namespace flow_wing