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

class ModuleStatementSyntax : public StatementSyntax {

public:
  ModuleStatementSyntax(
      const SyntaxToken *module_keyword_token,
      const SyntaxToken *open_bracket_token,
      std::unique_ptr<ExpressionSyntax> module_name_identifier_expression,
      const SyntaxToken *close_bracket_token,
      std::vector<std::unique_ptr<StatementSyntax>> module_statements,
      const SyntaxToken *end_of_file_token);

  // Overrides
  NodeKind getKind() const override;
  const std::vector<const SyntaxNode *> &getChildren() const override;
  void accept(visitor::ASTVisitor *visitor) override;
  // Getters
  const std::unique_ptr<ExpressionSyntax> &getModuleNameExpression() const;
  const std::vector<std::unique_ptr<StatementSyntax>> &
  getModuleMemberStatements() const;

private:
  const SyntaxToken *m_module_keyword_token;
  const SyntaxToken *m_open_bracket_token;
  std::unique_ptr<ExpressionSyntax> m_module_name_identifier_expression;
  const SyntaxToken *m_close_bracket_token;
  std::vector<std::unique_ptr<StatementSyntax>> m_module_statements;
  const SyntaxToken *m_end_of_file_token;

  mutable std::vector<const SyntaxNode *> m_children;
};
} // namespace syntax
} // namespace flow_wing