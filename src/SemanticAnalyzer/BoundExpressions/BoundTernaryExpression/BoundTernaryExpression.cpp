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


#include "BoundTernaryExpression.h"

BoundTernaryExpression::BoundTernaryExpression(
    const DiagnosticUtils::SourceLocation &location,
    std::unique_ptr<BoundExpression> conditionExpression,
    std::unique_ptr<BoundExpression> trueExpression,
    std::unique_ptr<BoundExpression> falseExpression)
    : BoundExpression(location),
      _conditionExpression(std::move(conditionExpression)),
      _trueExpression(std::move(trueExpression)),
      _falseExpression(std::move(falseExpression)) {}

const std::type_info &BoundTernaryExpression::getType() { return typeid(void); }

BinderKindUtils::BoundNodeKind BoundTernaryExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::BoundTernaryExpression;
}

std::vector<BoundNode *> BoundTernaryExpression::getChildren() {
  std::vector<BoundNode *> children;
  if (_children.empty()) {
    if (_conditionExpression)
      children.emplace_back(_conditionExpression.get());
    if (_trueExpression)
      children.emplace_back(_trueExpression.get());
    if (_falseExpression)
      children.emplace_back(_falseExpression.get());
  }

  return children;
}