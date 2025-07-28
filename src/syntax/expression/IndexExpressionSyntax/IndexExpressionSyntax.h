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
#include "src/syntax/expression/LiteralExpressionSyntax/LiteralExpressionSyntax.h"
#include <any>
#include <memory>
#include <vector>

template <typename T> class LiteralExpressionSyntax;
template <typename T> class SyntaxToken;

class IndexExpressionSyntax : public ExpressionSyntax {
private:
  std::unique_ptr<LiteralExpressionSyntax<std::any>> _identifierExpression;
  std::vector<std::unique_ptr<ExpressionSyntax>> _indexExpressions;
  std::unique_ptr<ExpressionSyntax> _variableExpression;
  std::unique_ptr<SyntaxToken<std::any>> _selfKeyword;
  bool _isObject = false;

public:
  IndexExpressionSyntax(
      std::unique_ptr<LiteralExpressionSyntax<std::any>> identifierExpression);

  inline auto addIndexExpression(std::unique_ptr<ExpressionSyntax> item)
      -> void {
    this->_indexExpressions.push_back(std::move(item));
  }

  inline auto
  addVariableExpression(std::unique_ptr<ExpressionSyntax> variableExpression)
      -> void {
    _isObject = true;
    _variableExpression = std::move(variableExpression);
  }

  inline auto addSelfKeyword(std::unique_ptr<SyntaxToken<std::any>> selfKeyword)
      -> void {
    _selfKeyword = std::move(selfKeyword);
  }

  inline auto getIndexExpressionsRef() const
      -> const std::vector<std::unique_ptr<ExpressionSyntax>> & {
    return this->_indexExpressions;
  }

  inline auto getVariableExpressionRef() const
      -> const std::unique_ptr<ExpressionSyntax> & {
    return _variableExpression;
  }

  inline auto getIsSelf() -> bool { return _selfKeyword != nullptr; }

  inline auto isObject() const -> bool { return _isObject; }

  std::unique_ptr<LiteralExpressionSyntax<std::any>> &
  getIndexIdentifierExpressionRef();

  SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;
};
