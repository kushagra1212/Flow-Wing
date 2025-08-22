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


#include "BoundCustomTypeStatement.h"

BoundCustomTypeStatement::BoundCustomTypeStatement(
    const DiagnosticUtils::SourceLocation &location, bool isExposed)
    : BoundSourceLocation(location), _isExposed(isExposed) {}

BinderKindUtils::BoundNodeKind BoundCustomTypeStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::CustomTypeStatement;
}

std::vector<BoundNode *> BoundCustomTypeStatement::getChildren() {
  if (_children.size() > 0) {
    return _children;
  }

  _children.push_back(_typeName.get());

  for (auto &keyTypePair : _key_type_pairs) {
    _children.push_back(keyTypePair.first.get());
    _children.push_back(keyTypePair.second.get());
  }

  return _children;
}
