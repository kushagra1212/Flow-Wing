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


#include "BoundFunctionDeclaration.h"

BoundFunctionDeclaration::BoundFunctionDeclaration(
    const DiagnosticUtils::SourceLocation &location, bool isExposed)
    : BoundSourceLocation(location), _isExposed(isExposed) {}

BinderKindUtils::BoundNodeKind BoundFunctionDeclaration::getKind() const {
  return BinderKindUtils::BoundNodeKind::FunctionDeclaration;
}

std::vector<BoundNode *> BoundFunctionDeclaration::getChildren() {
  if (this->_children.size() == 0) {
    this->_children.push_back(this->_body.get());
    for (const auto &parameter : this->_parameters) {
      this->_children.push_back(parameter.get());
    }

    for (const auto &returnTypeExpr : this->_returnTypeExprList) {
      this->_children.push_back(returnTypeExpr.get());
    }
  }

  return this->_children;
}

void BoundFunctionDeclaration::addParameter(
    std::unique_ptr<BoundVariableDeclaration> parameter) {

  if (!parameter->getInitializerPtr()) {
    _minNumberOfParametersNeeded++;
  }

  this->_parameters.push_back(std::move(parameter));
}

void BoundFunctionDeclaration::setFunctionName(
    const std::string &functionName) {
  this->_functionName = functionName;
}

void BoundFunctionDeclaration::setFunctionBody(
    std::unique_ptr<BoundBlockStatement> body) {
  this->_body = std::move(body);
}
