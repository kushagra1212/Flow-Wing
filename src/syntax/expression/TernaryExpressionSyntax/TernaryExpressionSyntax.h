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

#pragma once

#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include <memory>

namespace flow_wing {

namespace syntax {

class TernaryExpressionSyntax : public ExpressionSyntax {

public:
  TernaryExpressionSyntax(
      std::unique_ptr<ExpressionSyntax> condition_expression,
      const SyntaxToken *question_token,
      std::unique_ptr<ExpressionSyntax> true_expression,
      const SyntaxToken *colon_token,
      std::unique_ptr<ExpressionSyntax> false_expression);

  // Overrides
  NodeKind getKind() const override;
  const std::vector<const SyntaxNode *> &getChildren() const override;
  void accept(visitor::ASTVisitor *visitor) override;
  // Getters
  const std::unique_ptr<ExpressionSyntax> &getConditionExpression() const;
  const SyntaxToken *getQuestionToken() const;
  const std::unique_ptr<ExpressionSyntax> &getTrueExpression() const;
  const std::unique_ptr<ExpressionSyntax> &getFalseExpression() const;

private:
  std::unique_ptr<ExpressionSyntax> m_condition_expression;
  const SyntaxToken *m_question_token;
  std::unique_ptr<ExpressionSyntax> m_true_expression;
  const SyntaxToken *m_colon_token;
  std::unique_ptr<ExpressionSyntax> m_false_expression;

  mutable std::vector<const SyntaxNode *> m_children;
};

} // namespace syntax

} // namespace flow_wing