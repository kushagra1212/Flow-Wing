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

#include "BoundFillExpression.h"
#include "src/SemanticAnalyzer/BinderKindUtils.h"

BoundFillExpression::BoundFillExpression(
    const DiagnosticUtils::SourceLocation &location)
    : BoundExpression(location) {}

/*
 * OVERRIDES
 */

const std::type_info &BoundFillExpression::getType() { return typeid(this); }

BinderKindUtils::BoundNodeKind BoundFillExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::BoundFillExpression;
}

std::vector<BoundNode *> BoundFillExpression::getChildren() {

  if (_children.empty()) {
    _children.push_back(_elementToFill.get());
    _children.push_back(_sizeToFill.get());
  }

  return _children;
}

/*
 * SETTERS
 */

void BoundFillExpression::setElementToFill(
    std::unique_ptr<BoundExpression> elementToFill) {
  _elementToFill = std::move(elementToFill);
}

void BoundFillExpression::setSizeToFill(
    std::unique_ptr<BoundExpression> sizeToFill) {
  _sizeToFill = std::move(sizeToFill);
}

/*
 * GETTERS
 */

auto BoundFillExpression::getElementToFillRef() const
    -> const std::unique_ptr<BoundExpression> & {
  return _elementToFill;
}

auto BoundFillExpression::getSizeToFillRef() const
    -> const std::unique_ptr<BoundExpression> & {
  return _sizeToFill;
}