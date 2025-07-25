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


#include "BoundWhileStatement.h"

BoundWhileStatement::BoundWhileStatement(

    const DiagnosticUtils::SourceLocation &location,
    std::unique_ptr<BoundExpression> condition,
    std::unique_ptr<BoundStatement> body)
    : BoundSourceLocation(location), _condition(std::move(condition)),
      _body(std::move(body)) {

  this->_children.push_back(this->_condition.get());
  this->_children.push_back(this->_body.get());
}

std::unique_ptr<BoundExpression> BoundWhileStatement::getCondition() {
  return std::move(_condition);
}

std::unique_ptr<BoundStatement> BoundWhileStatement::getBody() {
  return std::move(_body);
}

BinderKindUtils::BoundNodeKind BoundWhileStatement::getKind() const {

  return BinderKindUtils::BoundNodeKind::WhileStatement;
}

std::vector<BoundNode *> BoundWhileStatement::getChildren() {
  return this->_children;
}

std::unique_ptr<BoundExpression> &BoundWhileStatement::getConditionPtr() {
  return this->_condition;
}
std::unique_ptr<BoundStatement> &BoundWhileStatement::getBodyPtr() {
  return this->_body;
}