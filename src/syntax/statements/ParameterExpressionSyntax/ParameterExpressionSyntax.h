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

#include <memory>

namespace flow_wing {
namespace syntax {

class SyntaxToken;

class ParameterExpressionSyntax : public ExpressionSyntax {

public:
  ParameterExpressionSyntax(
      const SyntaxToken *inout_keyword, const SyntaxToken *const_keyword,
      std::unique_ptr<ExpressionSyntax> identifier_expression,
      const SyntaxToken *colon_token, const SyntaxToken *as_keyword,
      std::unique_ptr<ExpressionSyntax> type_expression,
      const SyntaxToken *equals_token,
      std::unique_ptr<ExpressionSyntax> default_value_expression);

  // Overrides
  NodeKind getKind() const override;
  const std::vector<const SyntaxNode *> &getChildren() const override;
  void accept(visitor::ASTVisitor *visitor) override;

  // Boolean queries
  bool hasTypeExpression() const;
  bool hasDefaultValueExpression() const;

  // Getters
  const SyntaxToken *getInoutKeyword() const;
  const SyntaxToken *getConstKeyword() const;
  const std::unique_ptr<ExpressionSyntax> &getIdentifierExpression() const;
  const SyntaxToken *getColonToken() const;
  const SyntaxToken *getAsKeyword() const;
  const std::unique_ptr<ExpressionSyntax> &getTypeExpression() const;
  const SyntaxToken *getEqualsToken() const;
  const std::unique_ptr<ExpressionSyntax> &getDefaultValueExpression() const;

  // Boolean queries
  bool hasInoutKeyword() const;
  bool hasConstKeyword() const;
  bool hasAsKeyword() const;

private:
  const SyntaxToken *m_inout_keyword;
  const SyntaxToken *m_const_keyword;
  std::unique_ptr<ExpressionSyntax> m_identifier_expression;
  const SyntaxToken *m_colon_token;
  const SyntaxToken *m_as_keyword;
  std::unique_ptr<ExpressionSyntax> m_type_expression;
  const SyntaxToken *m_equals_token;
  std::unique_ptr<ExpressionSyntax> m_default_value_expression;

  mutable std::vector<const SyntaxNode *> m_children;
};
} // namespace syntax
} // namespace flow_wing