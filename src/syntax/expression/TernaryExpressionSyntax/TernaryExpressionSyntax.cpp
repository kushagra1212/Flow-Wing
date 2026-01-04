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

#include "TernaryExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"

namespace flow_wing {
namespace syntax {

TernaryExpressionSyntax::TernaryExpressionSyntax(
    std::unique_ptr<ExpressionSyntax> condition_expression,
    const SyntaxToken *question_token,
    std::unique_ptr<ExpressionSyntax> true_expression,
    const SyntaxToken *colon_token,
    std::unique_ptr<ExpressionSyntax> false_expression)
    : m_condition_expression(std::move(condition_expression)),
      m_question_token(question_token),
      m_true_expression(std::move(true_expression)), m_colon_token(colon_token),
      m_false_expression(std::move(false_expression)) {}

syntax::NodeKind TernaryExpressionSyntax::getKind() const {
  return NodeKind::kTernaryExpression;
}

void TernaryExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::unique_ptr<ExpressionSyntax> &
TernaryExpressionSyntax::getConditionExpression() const {
  return m_condition_expression;
}
const SyntaxToken *TernaryExpressionSyntax::getQuestionToken() const {
  return m_question_token;
}
const std::unique_ptr<ExpressionSyntax> &
TernaryExpressionSyntax::getTrueExpression() const {
  return m_true_expression;
}

const std::unique_ptr<ExpressionSyntax> &
TernaryExpressionSyntax::getFalseExpression() const {
  return m_false_expression;
}

const std::vector<const SyntaxNode *> &
TernaryExpressionSyntax::getChildren() const {
  if (m_children.empty()) {
    for (const auto *node :
         {static_cast<const SyntaxNode *>(m_condition_expression.get()),
          static_cast<const SyntaxNode *>(m_question_token),
          static_cast<const SyntaxNode *>(m_true_expression.get()),
          static_cast<const SyntaxNode *>(m_colon_token),
          static_cast<const SyntaxNode *>(m_false_expression.get())}) {
      if (node) {
        m_children.push_back(node);
      }
    }
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing