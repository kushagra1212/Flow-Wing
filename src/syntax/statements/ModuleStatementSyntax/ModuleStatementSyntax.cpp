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

#include "ModuleStatementSyntax.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"

const SyntaxKindUtils::SyntaxKind ModuleStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ModuleStatement;
}

const DiagnosticUtils::SourceLocation
ModuleStatementSyntax::getSourceLocation() const {

  if (_moduleKeyword)
    return _moduleKeyword->getSourceLocation();

  if (_openBracketToken)
    return _openBracketToken->getSourceLocation();

  if (_moduleName)
    return _moduleName->getSourceLocation();

  if (_closeBracketToken)
    return _closeBracketToken->getSourceLocation();

  for (const auto &s : _statements) {
    return s->getSourceLocation();
  }

  return DiagnosticUtils::SourceLocation();
}

const std::vector<SyntaxNode *> &ModuleStatementSyntax::getChildren() {
  if (_children.empty()) {

    //! BUG: Not Showing up as Chiild in lsp
    // if (_moduleKeyword)
    //   this->_children.push_back(_moduleKeyword.get());

    if (_openBracketToken)
      this->_children.push_back(_openBracketToken.get());

    if (_moduleName)
      this->_children.push_back(_moduleName.get());

    if (_closeBracketToken)
      this->_children.push_back(_closeBracketToken.get());

    for (const auto &s : _statements) {
      _children.push_back(s.get());
    }
  }

  return this->_children;
}