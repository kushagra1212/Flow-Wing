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

class FillExpressionSyntax : public ExpressionSyntax {
private:
  std::unique_ptr<ExpressionSyntax> _sizeToFillExpression;
  std::unique_ptr<ExpressionSyntax> _elementExpression;

public:
  // Overrides
  SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  // Setters

  void setSizeToFillExpression(
      std::unique_ptr<ExpressionSyntax> sizeToFillExpression);

  void
  setElementExpression(std::unique_ptr<ExpressionSyntax> elementExpression);

  // Getters
  auto getSizeToFillExpressionRef() const
      -> const std::unique_ptr<ExpressionSyntax> &;

  auto getElementExpressionRef() const
      -> const std::unique_ptr<ExpressionSyntax> &;
};
