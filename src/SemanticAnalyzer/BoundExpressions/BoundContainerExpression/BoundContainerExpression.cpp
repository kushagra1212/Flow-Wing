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

#include "BoundContainerExpression.h"
#include "src/SemanticAnalyzer/BinderKindUtils.h"

BoundContainerExpression::BoundContainerExpression(
    const DiagnosticUtils::SourceLocation &location)
    : BoundExpression(location) {}

/*
  OVERRIDES
*/

const std::type_info &BoundContainerExpression::getType() {
  return typeid(std::vector<std::unique_ptr<BoundExpression>>);
}

BinderKindUtils::BoundNodeKind BoundContainerExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::BoundContainerExpression;
}

std::vector<BoundNode *> BoundContainerExpression::getChildren() {
  if (_children.size() > 0)
    return _children;

  for (auto &element : this->_elements)
    _children.push_back(element.get());

  return _children;
}

/*
  SETTERS
*/

void BoundContainerExpression::setElement(
    std::unique_ptr<BoundExpression> element) {
  this->_elements.push_back(std::move(element));
}

/*
  GETTERS
*/

auto BoundContainerExpression::getElementsRef() const
    -> const std::vector<std::unique_ptr<BoundExpression>> & {
  return this->_elements;
}