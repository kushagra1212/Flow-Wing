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
class ContainerExpressionSyntax : public ExpressionSyntax {
private:
  std::vector<std::unique_ptr<ExpressionSyntax>> _elements;
  std::unique_ptr<SyntaxToken<std::any>> _openBracket;
  std::unique_ptr<SyntaxToken<std::any>> _closeBracket;

public:
  // Overrides
  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  // Setters
  auto setElement(std::unique_ptr<ExpressionSyntax> element) -> void;

  // Getters
  auto getElementsRef() const
      -> const std::vector<std::unique_ptr<ExpressionSyntax>> &;

  inline auto
  setOpenBracketToken(std::unique_ptr<SyntaxToken<std::any>> openBracket)
      -> void {
    _openBracket = std::move(openBracket);
  }

  inline auto
  setCloseBracketToken(std::unique_ptr<SyntaxToken<std::any>> closeBracket)
      -> void {
    _closeBracket = std::move(closeBracket);
  }
};
