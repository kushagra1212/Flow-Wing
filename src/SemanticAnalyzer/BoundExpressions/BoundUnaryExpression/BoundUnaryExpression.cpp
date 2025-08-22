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

#include "BoundUnaryExpression.h"
#include "src/SemanticAnalyzer/BinderKindUtils.h"

BoundUnaryExpression::BoundUnaryExpression(

    const DiagnosticUtils::SourceLocation &location,
    BinderKindUtils::BoundUnaryOperatorKind op,
    std::unique_ptr<BoundExpression> operand)
    : BoundExpression(location) {
  this->_op = op;
  this->_operand = std::move(operand);

  this->_children.push_back(this->_operand.get());
}

const std::type_info &BoundUnaryExpression::getType() {
  return this->_operand->getType();
}

BinderKindUtils::BoundNodeKind BoundUnaryExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::UnaryExpression;
}

std::vector<BoundNode *> BoundUnaryExpression::getChildren() {
  return this->_children;
}

std::unique_ptr<BoundExpression> &BoundUnaryExpression::getOperandPtr() {
  return this->_operand;
}

BinderKindUtils::BoundUnaryOperatorKind &BoundUnaryExpression::getOperator() {
  return this->_op;
}

llvm::AllocaInst *BoundUnaryExpression::getDynamicValueVariableAddress() {
  return this->_dynamicValueVariableAddress;
}

void BoundUnaryExpression::setDynamicValueVariableAddress(
    llvm::AllocaInst *dynamicValueVariableAddress) {
  this->_dynamicValueVariableAddress = dynamicValueVariableAddress;
}