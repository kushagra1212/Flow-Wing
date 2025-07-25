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


#include "AttributeExpressionSyntax.h"

/*
    OVERIDES
*/

const SyntaxKindUtils::SyntaxKind AttributeExpressionSyntax::getKind() const {
  return SyntaxKindUtils::BracketedExpression;
}

const std::vector<SyntaxNode *> &AttributeExpressionSyntax::getChildren() {
  if (_children.empty()) {
    _children.push_back(_key.get());
    _children.push_back(_value.get());
  }

  return _children;
}

const DiagnosticUtils::SourceLocation
AttributeExpressionSyntax::getSourceLocation() const {
  return this->_key->getSourceLocation();
}