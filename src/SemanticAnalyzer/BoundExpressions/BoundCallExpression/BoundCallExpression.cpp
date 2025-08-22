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

#include "BoundCallExpression.h"
#include "src/SemanticAnalyzer/BinderKindUtils.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundLiteralExpression.h"

BoundCallExpression::BoundCallExpression(
    const DiagnosticUtils::SourceLocation &location)
    : BoundExpression(location) {}

void BoundCallExpression::addArgument(
    std::unique_ptr<BoundExpression> argument) {
  _argumentPtrList.push_back(argument.get());
  _arguments.push_back(std::move(argument));
}

const std::vector<std::unique_ptr<BoundExpression>> &
BoundCallExpression::getArgumentsRef() const {
  return _arguments;
}

const std::type_info &BoundCallExpression::getType() {
  return _callerIdentifier->getType();
}

BinderKindUtils::BoundNodeKind BoundCallExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::CallExpression;
}

std::vector<BoundNode *> BoundCallExpression::getChildren() {
  if (_callerIdentifier != nullptr) {
    this->_children.push_back(_callerIdentifier.get());
    for (auto &argument : _arguments) {
      this->_children.push_back(argument.get());
    }
    return _children;
  }

  return _children;
}

std::unique_ptr<BoundLiteralExpression<std::any>> &
BoundCallExpression::getCallerIdentifierPtr() {
  return _callerIdentifier;
}

void BoundCallExpression::setCallerIdentifier(
    std::unique_ptr<BoundLiteralExpression<std::any>> callerIdentifier) {
  _callerIdentifier = std::move(callerIdentifier);
  _callerName = std::any_cast<std::string>(_callerIdentifier->getValue());
}
