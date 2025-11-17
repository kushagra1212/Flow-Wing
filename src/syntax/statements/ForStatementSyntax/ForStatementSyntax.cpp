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


#include "ForStatementSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace syntax {

ForStatementSyntax::ForStatementSyntax(
    const SyntaxToken *for_keyword, const SyntaxToken *open_parenthesis_token,
    std::unique_ptr<StatementSyntax> variable_declaration,
    std::unique_ptr<ExpressionSyntax> assignment_expression,
    const SyntaxToken *to_keyword,
    std::unique_ptr<ExpressionSyntax> upper_bound,
    const SyntaxToken *step_colon_token, std::unique_ptr<ExpressionSyntax> step,
    const SyntaxToken *close_parenthesis_token,
    std::unique_ptr<StatementSyntax> body)
    : m_for_keyword(for_keyword),
      m_open_parenthesis_token(open_parenthesis_token),
      m_variable_declaration(std::move(variable_declaration)),
      m_assignment_expression(std::move(assignment_expression)),
      m_to_keyword(to_keyword), m_upper_bound(std::move(upper_bound)),
      m_step_colon_token(step_colon_token), m_step(std::move(step)),
      m_close_parenthesis_token(close_parenthesis_token),
      m_body(std::move(body)) {}

NodeKind ForStatementSyntax::getKind() const { return NodeKind::kForStatement; }

void ForStatementSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::unique_ptr<StatementSyntax> &
ForStatementSyntax::getVariableDeclaration() const {
  return m_variable_declaration;
}
const std::unique_ptr<ExpressionSyntax> &
ForStatementSyntax::getAssignmentExpression() const {
  return m_assignment_expression;
}
const std::unique_ptr<ExpressionSyntax> &
ForStatementSyntax::getUpperBound() const {
  return m_upper_bound;
}
const std::unique_ptr<ExpressionSyntax> &ForStatementSyntax::getStep() const {
  return m_step;
}

const std::unique_ptr<StatementSyntax> &ForStatementSyntax::getBody() const {
  return m_body;
}

const std::vector<const SyntaxNode *> &ForStatementSyntax::getChildren() const {
  if (m_children.empty()) {

    for (const auto &node :
         {static_cast<const SyntaxNode *>(m_for_keyword),
          static_cast<const SyntaxNode *>(m_open_parenthesis_token),
          static_cast<const SyntaxNode *>(m_variable_declaration.get()),
          static_cast<const SyntaxNode *>(m_assignment_expression.get()),
          static_cast<const SyntaxNode *>(m_to_keyword),
          static_cast<const SyntaxNode *>(m_upper_bound.get()),
          static_cast<const SyntaxNode *>(m_step_colon_token),
          static_cast<const SyntaxNode *>(m_step.get()),
          static_cast<const SyntaxNode *>(m_close_parenthesis_token),
          static_cast<const SyntaxNode *>(m_body.get())}) {
      if (node)
        m_children.push_back(node);
    }
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing