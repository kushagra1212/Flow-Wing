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


#include "FillExpressionSyntax.h"

/*
    OVERRIDES

*/

const SyntaxKindUtils::SyntaxKind FillExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::FillExpression;
}

const std::vector<SyntaxNode *> &FillExpressionSyntax::getChildren() {
  if (_children.size() > 0) return _children;

  _children.push_back(_sizeToFillExpression.get());
  _children.push_back(_elementExpression.get());

  return _children;
}

const DiagnosticUtils::SourceLocation FillExpressionSyntax::getSourceLocation()
    const {
  if (this->_sizeToFillExpression)
    return this->_sizeToFillExpression->getSourceLocation();

  if (this->_elementExpression)
    return this->_elementExpression->getSourceLocation();

  return DiagnosticUtils::SourceLocation();
}

/*
    SETTERS
*/

void FillExpressionSyntax::setSizeToFillExpression(
    std::unique_ptr<ExpressionSyntax> sizeToFillExpression) {
  this->_sizeToFillExpression = std::move(sizeToFillExpression);
}

void FillExpressionSyntax::setElementExpression(
    std::unique_ptr<ExpressionSyntax> elementExpression) {
  this->_elementExpression = std::move(elementExpression);
}

/*
    GETTERS
*/

auto FillExpressionSyntax::getSizeToFillExpressionRef() const
    -> const std::unique_ptr<ExpressionSyntax> & {
  return this->_sizeToFillExpression;
}

auto FillExpressionSyntax::getElementExpressionRef() const
    -> const std::unique_ptr<ExpressionSyntax> & {
  return this->_elementExpression;
}
