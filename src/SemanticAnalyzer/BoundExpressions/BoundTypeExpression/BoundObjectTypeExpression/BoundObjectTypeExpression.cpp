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


#include "BoundObjectTypeExpression.h"

BoundObjectTypeExpression::BoundObjectTypeExpression(
    const DiagnosticUtils::SourceLocation &location,
    const SyntaxKindUtils::SyntaxKind &type)
    : BoundTypeExpression(location, type), _typeName("") {}

std::vector<BoundNode *> BoundObjectTypeExpression::getChildren() {
  if (this->_children.empty()) {
    this->_children.push_back(this->_objectTypeIdentifier.get());
  }

  return this->_children;
}

BinderKindUtils::BoundNodeKind BoundObjectTypeExpression::getKind() const {
  return BinderKindUtils::BoundObjectTypeExpression;
}