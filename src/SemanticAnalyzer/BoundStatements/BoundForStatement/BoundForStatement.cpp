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


#include "BoundForStatement.h"

BoundForStatement::BoundForStatement(
    const DiagnosticUtils::SourceLocation &location,
    std::unique_ptr<BoundStatement> initialization,
    std::unique_ptr<BoundExpression> upperBound,
    std::unique_ptr<BoundExpression> boundStepExpression,
    std::unique_ptr<BoundStatement> statement)
    : BoundSourceLocation(location) {
  this->_initialization = std::move(initialization);
  this->_upperBound = std::move(upperBound);
  this->_boundStepExpression = std::move(boundStepExpression);
  this->_statement = std::move(statement);

  this->_children.push_back(this->_initialization.get());
  this->_children.push_back(this->_upperBound.get());

  if (this->_boundStepExpression != nullptr)
    this->_children.push_back(this->_boundStepExpression.get());
  this->_children.push_back(this->_statement.get());
}

std::unique_ptr<BoundStatement> BoundForStatement::getInitialization() {

  return std::move(this->_initialization);
}

std::unique_ptr<BoundStatement> BoundForStatement::getStatement() {

  return std::move(this->_statement);
}

std::unique_ptr<BoundExpression> BoundForStatement::getUpperBound() {

  return std::move(this->_upperBound);
}

std::unique_ptr<BoundExpression> BoundForStatement::getStepExpression() {

  return std::move(this->_boundStepExpression);
}
BinderKindUtils::BoundNodeKind BoundForStatement::getKind() const {

  return BinderKindUtils::BoundNodeKind::ForStatement;
}

std::vector<BoundNode *> BoundForStatement::getChildren() {

  return this->_children;
}

std::unique_ptr<BoundStatement> &BoundForStatement::getInitializationPtr() {
  return this->_initialization;
}

std::unique_ptr<BoundStatement> &BoundForStatement::getStatementPtr() {
  return this->_statement;
}

std::unique_ptr<BoundExpression> &BoundForStatement::getUpperBoundPtr() {
  return this->_upperBound;
}

std::unique_ptr<BoundExpression> &BoundForStatement::getStepExpressionPtr() {
  return this->_boundStepExpression;
}