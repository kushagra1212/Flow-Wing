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

#include "ArrayTypeExpressionSyntax.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxKindUtils.h"

ArrayTypeExpressionSyntax::ArrayTypeExpressionSyntax(
    std::unique_ptr<SyntaxToken<std::any>> type)
    : TypeExpressionSyntax(std::move(type)) {}

const std::vector<SyntaxNode *> &ArrayTypeExpressionSyntax::getChildren() {
  if (this->_children.empty()) {
    if (_nonTrivialElementType)
      _children.push_back(this->_nonTrivialElementType.get());
    if (_elementType)
      _children.push_back(this->_elementType.get());
    for (auto &dimension : this->_dimensions) {
      this->_children.push_back(dimension.get());
    }
  }

  return this->_children;
}

const SyntaxKindUtils::SyntaxKind ArrayTypeExpressionSyntax::getKind() const {
  return SyntaxKindUtils::ArrayTypeExpression;
}
const DiagnosticUtils::SourceLocation
ArrayTypeExpressionSyntax::getSourceLocation() const {
  if (_elementType)
    return this->_elementType->getSourceLocation();
  if (_nonTrivialElementType)
    return this->_nonTrivialElementType->getSourceLocation();

  for (auto &dimension : this->_dimensions) {
    if (dimension)
      return dimension->getSourceLocation();
  }

  return DiagnosticUtils::SourceLocation();
}