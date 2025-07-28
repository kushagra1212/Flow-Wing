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

#include "IndexExpressionSyntax.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/LiteralExpressionSyntax/LiteralExpressionSyntax.h"

IndexExpressionSyntax::IndexExpressionSyntax(
    std::unique_ptr<LiteralExpressionSyntax<std::any>> identifierExpression)
    : _identifierExpression(std::move(identifierExpression)) {}

std::unique_ptr<LiteralExpressionSyntax<std::any>> &
IndexExpressionSyntax::getIndexIdentifierExpressionRef() {
  return this->_identifierExpression;
}

SyntaxKindUtils::SyntaxKind IndexExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::IndexExpression;
}
const std::vector<SyntaxNode *> &IndexExpressionSyntax::getChildren() {
  if (_children.size() > 0)
    return _children;

  if (_selfKeyword)
    _children.emplace_back(_selfKeyword.get());

  _children.emplace_back(this->_identifierExpression.get());

  for (const auto &item : this->_indexExpressions) {
    _children.emplace_back(item.get());
  }
  if (_variableExpression) {
    _children.emplace_back(_variableExpression.get());
  }
  return _children;
}
const DiagnosticUtils::SourceLocation
IndexExpressionSyntax::getSourceLocation() const {
  return this->_identifierExpression->getSourceLocation();
}