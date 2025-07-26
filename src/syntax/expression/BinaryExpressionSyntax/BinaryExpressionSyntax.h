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

class BinaryExpressionSyntax : public ExpressionSyntax {
private:
  std::unique_ptr<ExpressionSyntax> _left;
  std::unique_ptr<SyntaxToken<std::any>> _operatorToken;
  std::unique_ptr<ExpressionSyntax> _right;

public:
  BinaryExpressionSyntax(std::unique_ptr<ExpressionSyntax> left,
                         std::unique_ptr<SyntaxToken<std::any>> operatorToken,
                         std::unique_ptr<ExpressionSyntax> right);

  std::unique_ptr<ExpressionSyntax> getLeft();
  std::unique_ptr<SyntaxToken<std::any>> getOperatorToken();
  std::unique_ptr<ExpressionSyntax> getRight();

  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<ExpressionSyntax> &getLeftRef();
  std::unique_ptr<SyntaxToken<std::any>> &getOperatorTokenRef();
  std::unique_ptr<ExpressionSyntax> &getRightRef();
};