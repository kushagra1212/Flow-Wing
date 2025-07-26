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

#include "ParameterSyntax.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"

ParameterSyntax::ParameterSyntax(
    std::unique_ptr<SyntaxToken<std::any>> identifierToken) {
  this->_identifierToken = std::move(identifierToken);
}

const SyntaxKindUtils::SyntaxKind ParameterSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ParameterSyntax;
}

const DiagnosticUtils::SourceLocation
ParameterSyntax::getSourceLocation() const {
  return this->_identifierToken->getSourceLocation();
}

const std::vector<SyntaxNode *> &ParameterSyntax::getChildren() {
  if (_children.empty()) {
    // Add children
    _children.push_back(_identifierToken.get());
  }

  return this->_children;
}

std::unique_ptr<SyntaxToken<std::any>> &
ParameterSyntax::getIdentifierTokenPtr() {
  return this->_identifierToken;
}