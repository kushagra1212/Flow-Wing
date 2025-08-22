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

#include "UnaryExpressionSyntax.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"

UnaryExpressionSyntax::UnaryExpressionSyntax(
    std::unique_ptr<SyntaxToken<std::any>> operatorToken,
    std::unique_ptr<ExpressionSyntax> operand) {
  this->_operatorToken = std::move(operatorToken);
  this->_operand = std::move(operand);
}

SyntaxKindUtils::SyntaxKind UnaryExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::UnaryExpression;
}

const std::vector<SyntaxNode *> &UnaryExpressionSyntax::getChildren() {
  if (this->_children.size() == 0) {
    // Add children
    this->_children.emplace_back(this->_operatorToken.get());
    this->_children.emplace_back(this->_operand.get());
  }

  return this->_children;
}

const DiagnosticUtils::SourceLocation
UnaryExpressionSyntax::getSourceLocation() const {
  return this->_operatorToken->getSourceLocation();
}

std::unique_ptr<SyntaxToken<std::any>> &
UnaryExpressionSyntax::getOperatorTokenRef() {
  return this->_operatorToken;
}

std::unique_ptr<ExpressionSyntax> &UnaryExpressionSyntax::getOperandRef() {
  return this->_operand;
}
