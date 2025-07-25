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


#include "BoundArrayVariableExpression.h"

BoundArrayVariableExpression::BoundArrayVariableExpression(
    const DiagnosticUtils::SourceLocation &location,
    std::unique_ptr<BoundLiteralExpression<std::any>> identiferExpression,
    const bool &isConstant, BoundTypeExpression *variableTypeExp)
    : BoundVariableExpression(location, std::move(identiferExpression),
                              isConstant, variableTypeExp) {}

const std::type_info &BoundArrayVariableExpression::getType() {
  return typeid(std::vector<std::any>);
}

BinderKindUtils::BoundNodeKind BoundArrayVariableExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::ArrayVariableExpression;
}

std::vector<BoundNode *> BoundArrayVariableExpression::getChildren() {
  if (this->_children.size() == 0) {
    this->_children.push_back(this->getIdentifierExpressionPtr().get());
    for (const auto &sizeExpression : this->_sizeExpressions) {
      this->_children.push_back(sizeExpression.get());
    }
  }

  return this->_children;
}

void BoundArrayVariableExpression::addSizeExpression(
    std::unique_ptr<BoundExpression> sizeExpression) {
  this->_sizeExpressions.push_back(std::move(sizeExpression));
}

const std::vector<std::unique_ptr<BoundExpression>> &
BoundArrayVariableExpression::getSizeExpressionsRef() const {
  return this->_sizeExpressions;
}