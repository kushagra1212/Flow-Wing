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


#include "CustomTypeStatementSyntax.h"

/*
    OVERRIDES

*/

const SyntaxKindUtils::SyntaxKind CustomTypeStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::CustomTypeStatement;
}

const std::vector<SyntaxNode *> &CustomTypeStatementSyntax::getChildren() {
  if (_children.size() > 0)
    return _children;

  if (this->_exposeKeyword)
    _children.push_back(this->_exposeKeyword.get());

  _children.push_back(this->_typeName.get());

  for (const auto &keyTypePair : this->_key_type_pairs) {
    _children.push_back(keyTypePair.get());
  }

  return _children;
}

const DiagnosticUtils::SourceLocation
CustomTypeStatementSyntax::getSourceLocation() const {
  return this->_typeName->getSourceLocation();
}