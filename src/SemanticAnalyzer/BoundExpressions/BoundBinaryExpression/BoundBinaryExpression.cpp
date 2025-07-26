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

#include "BoundBinaryExpression.h"
#include "src/SemanticAnalyzer/BinderKindUtils.h"

BoundBinaryExpression::BoundBinaryExpression(
    const DiagnosticUtils::SourceLocation &location,
    std::unique_ptr<BoundExpression> left,
    BinderKindUtils::BoundBinaryOperatorKind op,
    std::unique_ptr<BoundExpression> right)
    : BoundExpression(location) {
  this->_op = op;

  this->_left = std::move(left);
  this->_right = std::move(right);

  // TODO:

  _children.push_back(_left.get());
  _children.push_back(_right.get());
}

const std::type_info &BoundBinaryExpression::getType() {
  return typeid(BoundBinaryExpression);
}

BinderKindUtils::BoundBinaryOperatorKind BoundBinaryExpression::getOperator() {
  return _op;
}

std::unique_ptr<BoundExpression> BoundBinaryExpression::getLeft() {
  return std::move(_left);
}

std::unique_ptr<BoundExpression> BoundBinaryExpression::getRight() {
  return std::move(_right);
}
BinderKindUtils::BoundNodeKind BoundBinaryExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::BinaryExpression;
}
std::vector<BoundNode *> BoundBinaryExpression::getChildren() {
  return _children;
}

std::unique_ptr<BoundExpression> &BoundBinaryExpression::getLeftPtr() {
  return _left;
}

std::unique_ptr<BoundExpression> &BoundBinaryExpression::getRightPtr() {
  return _right;
}

llvm::AllocaInst *BoundBinaryExpression::getDynamicValueVariableAddress() {
  return _dynamicValueVariableAddress;
}

void BoundBinaryExpression::setDynamicValueVariableAddress(
    llvm::AllocaInst *dynamicValueVariableAddress) {
  _dynamicValueVariableAddress = dynamicValueVariableAddress;
}