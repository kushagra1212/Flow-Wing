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


#include "BoundVariableExpression.h"

BoundVariableExpression::BoundVariableExpression(
    const DiagnosticUtils::SourceLocation &location,
    std::unique_ptr<BoundLiteralExpression<std::any>> identiferExpression,
    const bool &isConstant, BoundTypeExpression *variableTypeExp)
    : BoundExpression(location),
      _identiferExpression(std::move(identiferExpression)),
      _isConstant(isConstant), _variableTypeExp(variableTypeExp) {}

const std::type_info &BoundVariableExpression::getType() {
  return this->_identiferExpression->getType();
}

BinderKindUtils::BoundNodeKind BoundVariableExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::VariableExpression;
}

std::vector<BoundNode *> BoundVariableExpression::getChildren() {
  if (_children.empty()) {

    if (_identiferExpression)
      this->_children.push_back(this->_identiferExpression.get());
    if (_dotExpressionList.size()) {
      for (const auto &dotExpression : _dotExpressionList) {
        this->_children.push_back(dotExpression.get());
      }
    }
  }

  return this->_children;
}
