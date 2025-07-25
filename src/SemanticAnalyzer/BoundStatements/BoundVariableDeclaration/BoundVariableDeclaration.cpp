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


#include "BoundVariableDeclaration.h"

BoundVariableDeclaration::BoundVariableDeclaration(
    const DiagnosticUtils::SourceLocation &location,
    const std::string &variableName, bool isConst, bool isExposed)
    : BoundSourceLocation(location), _variableName(variableName),
      _isConst(isConst), _isExposed(isExposed) {}

std::unique_ptr<BoundExpression> BoundVariableDeclaration::getInitializer() {
  return std::move(_initializer);
}

BinderKindUtils::BoundNodeKind BoundVariableDeclaration::getKind() const {
  return BinderKindUtils::BoundNodeKind::VariableDeclaration;
}

BinderKindUtils::MemoryKind BoundVariableDeclaration::getMemoryKind() const {
  return _memoryKind;
};

bool BoundVariableDeclaration::isConst() const { return _isConst; }

std::vector<BoundNode *> BoundVariableDeclaration::getChildren() {
  if (_children.empty()) {
    if (_typeExp)
      _children.push_back(this->_typeExp.get());
    if (_identifier)
      _children.push_back(this->_identifier.get());
    if (_initializer)
      _children.push_back(this->_initializer.get());
  }

  return this->_children;
}

std::unique_ptr<BoundExpression> &
BoundVariableDeclaration::getInitializerPtr() {
  return this->_initializer;
}

const std::string &BoundVariableDeclaration::getVariableName() const {
  return _variableName;
}
