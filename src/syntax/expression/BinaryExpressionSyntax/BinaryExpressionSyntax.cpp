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

#include "BinaryExpressionSyntax.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"

BinaryExpressionSyntax::BinaryExpressionSyntax(
    std::unique_ptr<ExpressionSyntax> left,
    std::unique_ptr<SyntaxToken<std::any>> operatorToken,
    std::unique_ptr<ExpressionSyntax> right) {
  this->_left = std::move(left);
  this->_operatorToken = std::move(operatorToken);
  this->_right = std::move(right);
}

std::unique_ptr<ExpressionSyntax> BinaryExpressionSyntax::getLeft() {
  return std::move(this->_left);
}

std::unique_ptr<SyntaxToken<std::any>>
BinaryExpressionSyntax::getOperatorToken() {
  return std::move(this->_operatorToken);
}

std::unique_ptr<ExpressionSyntax> BinaryExpressionSyntax::getRight() {
  return std::move(this->_right);
}

const SyntaxKindUtils::SyntaxKind BinaryExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::BinaryExpression;
}

const std::vector<SyntaxNode *> &BinaryExpressionSyntax::getChildren() {
  if (_children.empty()) {
    // Add children

    this->_children.emplace_back(_left.get());
    this->_children.emplace_back(_operatorToken.get());
    this->_children.emplace_back(_right.get());
  }

  return this->_children;
}

const DiagnosticUtils::SourceLocation
BinaryExpressionSyntax::getSourceLocation() const {
  return this->_operatorToken->getSourceLocation();
}

std::unique_ptr<ExpressionSyntax> &BinaryExpressionSyntax::getLeftRef() {
  return this->_left;
}

std::unique_ptr<SyntaxToken<std::any>> &
BinaryExpressionSyntax::getOperatorTokenRef() {
  return this->_operatorToken;
}

std::unique_ptr<ExpressionSyntax> &BinaryExpressionSyntax::getRightRef() {
  return this->_right;
}