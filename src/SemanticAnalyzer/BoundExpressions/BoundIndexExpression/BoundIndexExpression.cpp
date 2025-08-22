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

#include "BoundIndexExpression.h"

BoundIndexExpression::BoundIndexExpression(
    const DiagnosticUtils::SourceLocation &location,
    std::unique_ptr<BoundLiteralExpression<std::any>> boundIdentifierExpression)
    : BoundExpression(location),
      _boundIdentifierExpression(std::move(boundIdentifierExpression)) {}

const std::type_info &BoundIndexExpression::getType() {
  return _boundIdentifierExpression->getType();
}

BinderKindUtils::BoundNodeKind BoundIndexExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::IndexExpression;
}

std::vector<BoundNode *> BoundIndexExpression::getChildren() {
  if (_children.size() == 0) {
    _children.push_back(_boundIdentifierExpression.get());
    for (const auto &item : _boundIndexExpressions) {
      _children.push_back(item.get());
    }
    if (_variableExpression) {
      _children.push_back(_variableExpression.get());
    }
  }

  return _children;
}

std::unique_ptr<BoundLiteralExpression<std::any>> &
BoundIndexExpression::getBoundIdentifierExpression() {
  return _boundIdentifierExpression;
}
