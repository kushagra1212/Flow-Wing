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
#include <any>
#include <memory>
#include <vector>

class ExpressionSyntax;
template <typename T> class SyntaxToken;

class ReturnStatementSyntax : public StatementSyntax {
private:
  std::unique_ptr<SyntaxToken<std::any>> _returnKeyword;
  std::vector<std::unique_ptr<ExpressionSyntax>> _expressionList;

public:
  ReturnStatementSyntax(std::unique_ptr<SyntaxToken<std::any>> returnKeyword);

  /*
    Overrides
  */

  const std::vector<SyntaxNode *> &getChildren() override;
  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  /*
    Setters
  */
  inline auto addReturnExpression(std::unique_ptr<ExpressionSyntax> expression)
      -> void {
    _expressionList.push_back(std::move(expression));
  }

  /*
    Getters
  */

  inline auto getReturnExpressionListRef() const
      -> const std::vector<std::unique_ptr<ExpressionSyntax>> & {
    return _expressionList;
  }

  inline auto getReturnKeywordRef() const
      -> const std::unique_ptr<SyntaxToken<std::any>> & {
    return _returnKeyword;
  }
};