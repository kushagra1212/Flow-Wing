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

#include "ParenthesizedExpressionSyntax.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"

ParenthesizedExpressionSyntax::ParenthesizedExpressionSyntax(
    std::unique_ptr<SyntaxToken<std::any>> openParenthesisToken,
    std::unique_ptr<ExpressionSyntax> expression,
    std::unique_ptr<SyntaxToken<std::any>> closeParenthesisToken) {
  this->_openParenthesisToken = std::move(openParenthesisToken);
  this->_expression = std::move(expression);
  this->_closeParenthesisToken = std::move(closeParenthesisToken);
}

std::unique_ptr<SyntaxToken<std::any>>
ParenthesizedExpressionSyntax::getOpenParenthesisToken() {
  return std::move(this->_openParenthesisToken);
}

std::unique_ptr<ExpressionSyntax>
ParenthesizedExpressionSyntax::getExpression() {
  return std::move(this->_expression);
}

std::unique_ptr<SyntaxToken<std::any>>
ParenthesizedExpressionSyntax::getCloseParenthesisToken() {
  return std::move(this->_closeParenthesisToken);
}

const SyntaxKindUtils::SyntaxKind
ParenthesizedExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ParenthesizedExpression;
}
const std::vector<SyntaxNode *> &ParenthesizedExpressionSyntax::getChildren() {
  if (_children.empty()) {
    // Add children
    this->_children.emplace_back(_openParenthesisToken.get());
    this->_children.emplace_back(_expression.get());
    this->_children.emplace_back(_closeParenthesisToken.get());
  }

  return this->_children;
}

const DiagnosticUtils::SourceLocation
ParenthesizedExpressionSyntax::getSourceLocation() const {
  return this->_openParenthesisToken->getSourceLocation();
}

std::unique_ptr<SyntaxToken<std::any>> &
ParenthesizedExpressionSyntax::getOpenParenthesisTokenRef() {
  return this->_openParenthesisToken;
}

std::unique_ptr<ExpressionSyntax> &
ParenthesizedExpressionSyntax::getExpressionRef() {
  return this->_expression;
}

std::unique_ptr<SyntaxToken<std::any>> &
ParenthesizedExpressionSyntax::getCloseParenthesisTokenRef() {
  return this->_closeParenthesisToken;
}