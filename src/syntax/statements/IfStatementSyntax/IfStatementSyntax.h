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
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "src/syntax/statements/ElseClauseSyntax/ElseClauseSyntax.h"
#include "src/syntax/statements/OrIfStatementSyntax/OrIfStatementSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"
#include <memory>
namespace flow_wing {
namespace syntax {

class SyntaxToken;

class IfStatementSyntax : public StatementSyntax {

public:
  IfStatementSyntax(
      const SyntaxToken *if_keyword,
      std::unique_ptr<ExpressionSyntax> condition_expression,
      std::unique_ptr<StatementSyntax> statement,
      std::vector<std::unique_ptr<OrIfStatementSyntax>> or_if_statements,
      std::unique_ptr<ElseClauseSyntax> else_clause);

  // Overrides
  NodeKind getKind() const override;
  const std::vector<const SyntaxNode *> &getChildren() const override;
  void accept(visitor::ASTVisitor *visitor) override;

  // Getters
  const std::unique_ptr<ExpressionSyntax> &getConditionExpression() const;
  const std::unique_ptr<StatementSyntax> &getStatement() const;
  const std::vector<std::unique_ptr<OrIfStatementSyntax>> &
  getOrIfStatements() const;
  const std::unique_ptr<ElseClauseSyntax> &getElseClause() const;

private:
  const SyntaxToken *m_if_keyword;
  std::unique_ptr<ExpressionSyntax> m_condition_expression;
  std::unique_ptr<StatementSyntax> m_statement;
  std::vector<std::unique_ptr<OrIfStatementSyntax>> m_or_if_statements;
  std::unique_ptr<ElseClauseSyntax> m_else_clause;

  mutable std::vector<const SyntaxNode *> m_children;
};
} // namespace syntax
} // namespace flow_wing