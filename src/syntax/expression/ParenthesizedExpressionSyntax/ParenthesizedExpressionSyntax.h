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
#include <any>
#include <memory>

template <typename T> class SyntaxToken;

class ParenthesizedExpressionSyntax : public ExpressionSyntax {
private:
  std::unique_ptr<SyntaxToken<std::any>> _openParenthesisToken;
  std::unique_ptr<ExpressionSyntax> _expression;
  std::unique_ptr<SyntaxToken<std::any>> _closeParenthesisToken;

public:
  ParenthesizedExpressionSyntax(
      std::unique_ptr<SyntaxToken<std::any>> openParenthesisToken,
      std::unique_ptr<ExpressionSyntax> expression,
      std::unique_ptr<SyntaxToken<std::any>> closeParenthesisToken);

  std::unique_ptr<SyntaxToken<std::any>> getOpenParenthesisToken();
  std::unique_ptr<ExpressionSyntax> getExpression();
  std::unique_ptr<SyntaxToken<std::any>> getCloseParenthesisToken();

  SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<SyntaxToken<std::any>> &getOpenParenthesisTokenRef();
  std::unique_ptr<ExpressionSyntax> &getExpressionRef();
  std::unique_ptr<SyntaxToken<std::any>> &getCloseParenthesisTokenRef();
};