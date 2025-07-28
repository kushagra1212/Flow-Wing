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

#include "ObjectExpressionSyntax.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxKindUtils.h"

SyntaxKindUtils::SyntaxKind ObjectExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ObjectExpression;
}
const std::vector<SyntaxNode *> &ObjectExpressionSyntax::getChildren() {
  if (_children.empty()) {

    _children.push_back(_openBraceToken.get());
    _children.push_back(_closeBraceToken.get());

    for (auto &attribute : _attributes) {
      _children.push_back(attribute.get());
    }
  }

  return _children;
}
const DiagnosticUtils::SourceLocation
ObjectExpressionSyntax::getSourceLocation() const {
  if (_openBraceToken)
    return _openBraceToken->getSourceLocation();
  if (_closeBraceToken)
    return _closeBraceToken->getSourceLocation();

  if (_attributes.size() > 0)
    return _attributes[0]->getSourceLocation();

  return DiagnosticUtils::SourceLocation();
}