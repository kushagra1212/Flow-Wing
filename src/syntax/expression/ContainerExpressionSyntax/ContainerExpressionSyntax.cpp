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

#include "ContainerExpressionSyntax.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxKindUtils.h"

/*
  OVERRIDES
*/

const SyntaxKindUtils::SyntaxKind ContainerExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ContainerExpression;
}

const std::vector<SyntaxNode *> &ContainerExpressionSyntax::getChildren() {
  if (_children.size() > 0)
    return _children;

  if (_openBracket)
    _children.push_back(_openBracket.get());

  for (auto &element : this->_elements)
    _children.push_back(element.get());

  if (_closeBracket)
    _children.push_back(_closeBracket.get());
  return _children;
}

const DiagnosticUtils::SourceLocation
ContainerExpressionSyntax::getSourceLocation() const {
  if (this->_elements.size() == 0) {
    if (_openBracket)
      return _openBracket->getSourceLocation();

    if (_closeBracket)
      return _closeBracket->getSourceLocation();
  }

  return this->_elements[0]->getSourceLocation();
}

/*
  SETTERS
*/

auto ContainerExpressionSyntax::setElement(
    std::unique_ptr<ExpressionSyntax> element) -> void {
  this->_elements.push_back(std::move(element));
}

/*
  GETTERS
*/

auto ContainerExpressionSyntax::getElementsRef() const
    -> const std::vector<std::unique_ptr<ExpressionSyntax>> & {
  return this->_elements;
}
