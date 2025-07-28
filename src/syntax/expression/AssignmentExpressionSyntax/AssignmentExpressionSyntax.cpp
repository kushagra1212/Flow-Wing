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

#include "AssignmentExpressionSyntax.h"
#include "src/diagnostics/DiagnosticUtils/DiagnosticUtils.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxKindUtils.h"

AssignmentExpressionSyntax::AssignmentExpressionSyntax(
    std::unique_ptr<ExpressionSyntax> left,
    SyntaxKindUtils::SyntaxKind operatorToken,
    std::unique_ptr<ExpressionSyntax> right, bool needDefaultInitialize)
    : _left(std::move(left)), _right(std::move(right)),
      _operatorTokenKind(operatorToken),
      _needDefaultInitialize(needDefaultInitialize) {}

SyntaxKindUtils::SyntaxKind AssignmentExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::AssignmentExpression;
}

const std::vector<SyntaxNode *> &AssignmentExpressionSyntax::getChildren() {
  if (_children.empty()) {
    // Add children
    if (_left)
      this->_children.push_back(_left.get());

    if (_right)
      this->_children.push_back(_right.get());
  }

  return this->_children;
}
const DiagnosticUtils::SourceLocation
AssignmentExpressionSyntax::getSourceLocation() const {
  if (_left)
    return _left->getSourceLocation();

  if (_right)
    return _right->getSourceLocation();

  return DiagnosticUtils::SourceLocation();
}

std::unique_ptr<ExpressionSyntax> AssignmentExpressionSyntax::getRight() {
  return std::move(this->_right);
}

std::unique_ptr<ExpressionSyntax> AssignmentExpressionSyntax::getLeft() {
  return std::move(this->_left);
}

std::unique_ptr<ExpressionSyntax> &AssignmentExpressionSyntax::getRightRef() {
  return this->_right;
}

std::unique_ptr<ExpressionSyntax> &AssignmentExpressionSyntax::getLeftRef() {
  return this->_left;
}