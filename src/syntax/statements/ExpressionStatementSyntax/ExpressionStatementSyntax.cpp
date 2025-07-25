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


#include "ExpressionStatementSyntax.h"

ExpressionStatementSyntax::ExpressionStatementSyntax(
    std::unique_ptr<ExpressionSyntax> expression) {
  this->_expression = std::move(expression);
}

std::unique_ptr<ExpressionSyntax> ExpressionStatementSyntax::getExpression() {
  return std::move(this->_expression);
}
std::unique_ptr<ExpressionSyntax> &
ExpressionStatementSyntax::getExpressionPtr() {
  return this->_expression;
}
const SyntaxKindUtils::SyntaxKind ExpressionStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ExpressionStatement;
}

const std::vector<SyntaxNode *> &ExpressionStatementSyntax::getChildren() {
  if (_children.empty()) {
    // Add children
    _children.push_back(_expression.get());
  }

  return this->_children;
}

const DiagnosticUtils::SourceLocation
ExpressionStatementSyntax::getSourceLocation() const {
  return this->_expression->getSourceLocation();
}