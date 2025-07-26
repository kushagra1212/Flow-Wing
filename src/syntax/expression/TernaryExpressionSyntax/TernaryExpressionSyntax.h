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
class TernaryExpressionSyntax : public ExpressionSyntax {
  std::unique_ptr<SyntaxToken<std::any>> _questionToken;
  std::unique_ptr<SyntaxToken<std::any>> _colonToken;

  std::unique_ptr<ExpressionSyntax> _conditionExpression;
  std::unique_ptr<ExpressionSyntax> _trueExpression;
  std::unique_ptr<ExpressionSyntax> _falseExpression;

public:
  TernaryExpressionSyntax() = default;
  const virtual SyntaxKindUtils::SyntaxKind getKind() const override;
  const virtual std::vector<SyntaxNode *> &getChildren() override;
  const virtual DiagnosticUtils::SourceLocation
  getSourceLocation() const override;

  inline auto
  addConditionExpression(std::unique_ptr<ExpressionSyntax> conditionExpression)
      -> void {
    _conditionExpression = std::move(conditionExpression);
  }

  inline auto
  addQuestionToken(std::unique_ptr<SyntaxToken<std::any>> questionToken)
      -> void {
    _questionToken = std::move(questionToken);
  }

  inline auto
  addTrueExpression(std::unique_ptr<ExpressionSyntax> trueExpression) -> void {
    _trueExpression = std::move(trueExpression);
  }

  inline auto addColonToken(std::unique_ptr<SyntaxToken<std::any>> colonToken)
      -> void {
    _colonToken = std::move(colonToken);
  }

  inline auto
  addFalseExpression(std::unique_ptr<ExpressionSyntax> falseExpression)
      -> void {
    _falseExpression = std::move(falseExpression);
  }

  inline auto getConditionExpressionRef() const
      -> const std::unique_ptr<ExpressionSyntax> & {
    return _conditionExpression;
  }

  inline auto getTrueExpressionRef() const
      -> const std::unique_ptr<ExpressionSyntax> & {
    return _trueExpression;
  }

  inline auto getFalseExpressionRef() const
      -> const std::unique_ptr<ExpressionSyntax> & {
    return _falseExpression;
  }
};