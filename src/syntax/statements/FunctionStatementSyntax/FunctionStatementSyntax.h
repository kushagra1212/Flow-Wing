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
#include "src/syntax/statements/StatementSyntax.h"
#include <memory>

namespace flow_wing {

namespace syntax {

class FunctionStatementSyntax : public StatementSyntax {

public:
  FunctionStatementSyntax(
      const SyntaxToken *fun_keyword,
      std::unique_ptr<ExpressionSyntax> function_identifier,
      const SyntaxToken *open_parenthesis_token,
      std::vector<std::unique_ptr<ExpressionSyntax>> function_parameters,
      std::vector<const SyntaxToken *> comma_tokens,
      const SyntaxToken *close_parenthesis_token,
      const SyntaxToken *right_arrow_token,
      std::unique_ptr<ExpressionSyntax> function_return_type_expression,
      const SyntaxToken *decl_keyword, std::unique_ptr<StatementSyntax> body);

  // Overrides
  NodeKind getKind() const override;
  const std::vector<const SyntaxNode *> &getChildren() const override;
  virtual void accept(visitor::ASTVisitor *visitor) override;

  // Boolean queries
  bool hasBody() const;
  bool hasReturnType() const;

  // Getters
  const std::unique_ptr<ExpressionSyntax> &getIdentifier() const;
  const std::vector<std::unique_ptr<ExpressionSyntax>> &getParameters() const;
  const std::unique_ptr<ExpressionSyntax> &getReturnType() const;
  const std::unique_ptr<StatementSyntax> &getBody() const;

private:
  const SyntaxToken *m_fun_keyword;
  std::unique_ptr<ExpressionSyntax> m_function_identifier;
  const SyntaxToken *m_open_parenthesis_token;
  std::vector<std::unique_ptr<ExpressionSyntax>> m_function_parameters;
  std::vector<const SyntaxToken *> m_comma_tokens;
  const SyntaxToken *m_close_parenthesis_token;
  const SyntaxToken *m_right_arrow_token;
  std::unique_ptr<ExpressionSyntax> m_function_return_type_expression;
  const SyntaxToken *m_decl_keyword;
  std::unique_ptr<StatementSyntax> m_body;

  mutable std::vector<const SyntaxNode *> m_children;
};

} // namespace syntax

} // namespace flow_wing