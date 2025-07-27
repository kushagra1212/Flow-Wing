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
#include "src/syntax/expression/AttributeExpressionSyntax/AttributeExpressionSyntax.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include <memory>

class ObjectExpressionSyntax : public ExpressionSyntax {
private:
  std::vector<std::unique_ptr<AttributeExpressionSyntax>> _attributes;
  std::unique_ptr<SyntaxToken<std::any>> _openBraceToken;
  std::unique_ptr<SyntaxToken<std::any>> _closeBraceToken;

public:
  // Overrides
  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  // Setters
  inline auto
  addAttribute(std::unique_ptr<LiteralExpressionSyntax<std::any>> key,
               std::unique_ptr<ExpressionSyntax> value) -> void {
    std::unique_ptr<AttributeExpressionSyntax> attribute =
        std::make_unique<AttributeExpressionSyntax>();

    attribute->setAttribute(std::move(key), std::move(value));
    _attributes.push_back(std::move(attribute));
  }

  // Getters
  auto getAttributes()
      -> const std::vector<std::unique_ptr<AttributeExpressionSyntax>> & {
    return _attributes;
  }

  auto setOpenBraceToken(std::unique_ptr<SyntaxToken<std::any>> openBraceToken)
      -> void {
    _openBraceToken = std::move(openBraceToken);
  }

  auto
  setCloseBraceToken(std::unique_ptr<SyntaxToken<std::any>> closeBraceToken)
      -> void {
    _closeBraceToken = std::move(closeBraceToken);
  }
};
