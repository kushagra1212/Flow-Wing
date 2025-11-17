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


#include "SwitchStatementSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace syntax {

SwitchStatementSyntax::SwitchStatementSyntax(
    const SyntaxToken *switch_keyword,
    std::unique_ptr<ExpressionSyntax> switch_condition_expression,
    const SyntaxToken *open_brace_token,
    std::vector<std::unique_ptr<StatementSyntax>> case_statements,
    const SyntaxToken *close_brace_token)
    : m_switch_keyword(switch_keyword),
      m_switch_condition_expression(std::move(switch_condition_expression)),
      m_open_brace_token(open_brace_token),
      m_case_statements(std::move(case_statements)),
      m_close_brace_token(close_brace_token) {}

NodeKind SwitchStatementSyntax::getKind() const {
  return NodeKind::kSwitchStatement;
}

void SwitchStatementSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::unique_ptr<ExpressionSyntax> &
SwitchStatementSyntax::getSwitchConditionExpression() const {
  return m_switch_condition_expression;
}

const std::vector<std::unique_ptr<StatementSyntax>> &
SwitchStatementSyntax::getCaseStatements() const {
  return m_case_statements;
}

const std::vector<const SyntaxNode *> &
SwitchStatementSyntax::getChildren() const {
  if (m_children.empty()) {
    for (const auto &child :
         {static_cast<const SyntaxNode *>(m_switch_keyword),
          static_cast<const SyntaxNode *>(m_switch_condition_expression.get()),
          static_cast<const SyntaxNode *>(m_open_brace_token)}) {
      if (child)
        m_children.push_back(child);
    }

    for (const auto &case_statement : m_case_statements) {
      if (case_statement)
        m_children.push_back(case_statement.get());
    }

    if (m_close_brace_token)
      m_children.push_back(m_close_brace_token);
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing