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


#include "BoundExpressionStatement.h"

BoundExpressionStatement::BoundExpressionStatement(
    const DiagnosticUtils::SourceLocation &location,
    std::unique_ptr<BoundExpression> expression)
    : BoundSourceLocation(location) {

  this->_expression = std::move(expression);

  // Add children

  this->_children.push_back(this->_expression.get());
}

std::unique_ptr<BoundExpression> BoundExpressionStatement::getExpression() {
  return std::move(_expression);
}

BinderKindUtils::BoundNodeKind BoundExpressionStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::ExpressionStatement;
}

std::vector<BoundNode *> BoundExpressionStatement::getChildren() {
  return this->_children;
}

std::unique_ptr<BoundExpression> &BoundExpressionStatement::getExpressionPtr() {
  return this->_expression;
}