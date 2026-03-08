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

#pragma once

#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"
#include <memory>
namespace flow_wing {
namespace syntax {

class SyntaxToken;

class ForStatementSyntax : public StatementSyntax {

public:
  ForStatementSyntax(const SyntaxToken *for_keyword,
                     const SyntaxToken *open_parenthesis_token,
                     std::unique_ptr<StatementSyntax> variable_declaration,
                     std::unique_ptr<ExpressionSyntax> assignment_expression,
                     const SyntaxToken *to_keyword,
                     std::unique_ptr<ExpressionSyntax> upper_bound,
                     const SyntaxToken *step_colon_token,
                     std::unique_ptr<ExpressionSyntax> step,
                     const SyntaxToken *close_parenthesis_token,
                     std::unique_ptr<StatementSyntax> body);
  // Overrides
  NodeKind getKind() const override;
  const std::vector<const SyntaxNode *> &getChildren() const override;
  void accept(visitor::ASTVisitor *visitor) override;

  // Getters
  const std::unique_ptr<StatementSyntax> &getVariableDeclaration() const;
  const std::unique_ptr<ExpressionSyntax> &getAssignmentExpression() const;
  const std::unique_ptr<ExpressionSyntax> &getUpperBound() const;
  const std::unique_ptr<ExpressionSyntax> &getStep() const;
  const std::unique_ptr<StatementSyntax> &getBody() const;

private:
  const SyntaxToken *m_for_keyword;
  const SyntaxToken *m_open_parenthesis_token;
  std::unique_ptr<StatementSyntax> m_variable_declaration;
  std::unique_ptr<ExpressionSyntax> m_assignment_expression;
  const SyntaxToken *m_to_keyword;
  std::unique_ptr<ExpressionSyntax> m_upper_bound;
  const SyntaxToken *m_step_colon_token;
  std::unique_ptr<ExpressionSyntax> m_step;
  const SyntaxToken *m_close_parenthesis_token;
  std::unique_ptr<StatementSyntax> m_body;

  mutable std::vector<const SyntaxNode *> m_children;
};
} // namespace syntax
} // namespace flow_wing