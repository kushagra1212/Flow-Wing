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

#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"
namespace flow_wing {
namespace syntax {

class SyntaxToken;

class WhileStatementSyntax : public StatementSyntax {

public:
  WhileStatementSyntax(const SyntaxToken *while_keyword,
                       std::unique_ptr<ExpressionSyntax> condition,
                       std::unique_ptr<StatementSyntax> statement);

  // Overrides
  NodeKind getKind() const override;
  const std::vector<const SyntaxNode *> &getChildren() const override;
  void accept(visitor::ASTVisitor *visitor) override;
  // Getters
  const std::unique_ptr<ExpressionSyntax> &getCondition() const;
  const std::unique_ptr<StatementSyntax> &getStatement() const;

private:
  const SyntaxToken *m_while_keyword;
  std::unique_ptr<ExpressionSyntax> m_condition;
  std::unique_ptr<StatementSyntax> m_statement;

  mutable std::vector<const SyntaxNode *> m_children;
};
} // namespace syntax
} // namespace flow_wing