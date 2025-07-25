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


#include "VariableDeclarationSyntax.h"

const SyntaxKindUtils::SyntaxKind VariableDeclarationSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::VariableDeclaration;
}

const std::vector<SyntaxNode *> &VariableDeclarationSyntax::getChildren() {
  if (_children.size())
    return this->_children;

  if (_exposeKeyword)
    _children.push_back(_exposeKeyword.get());

  if (_inout_keyword)
    _children.push_back(_inout_keyword.get());

  if (_keyword)
    _children.push_back(_keyword.get());

  if (_identifier)
    _children.push_back(_identifier.get());

  if (_asKeyword)
    _children.push_back(_asKeyword.get());

  if (_typeExpr)
    _children.push_back(_typeExpr.get());

  if (_newKeyword)
    _children.push_back(_newKeyword.get());

  if (_initializer) {
    _children.push_back(_initializer.get());
  }

  return this->_children;
}

const DiagnosticUtils::SourceLocation
VariableDeclarationSyntax::getSourceLocation() const {
  if (_exposeKeyword)
    return this->_exposeKeyword->getSourceLocation();
  if (_keyword)
    return this->_keyword->getSourceLocation();
  if (_identifier)
    return this->_identifier->getSourceLocation();
  if (_asKeyword)
    return this->_asKeyword->getSourceLocation();
  if (_typeExpr)
    return this->_typeExpr->getSourceLocation();
  if (_initializer)
    return this->_initializer->getSourceLocation();
  return DiagnosticUtils::SourceLocation();
}
