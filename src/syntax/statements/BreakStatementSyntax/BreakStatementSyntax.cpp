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


#include "BreakStatementSyntax.h"

BreakStatementSyntax::BreakStatementSyntax(
    std::unique_ptr<SyntaxToken<std::any>> breakKeyword) {
  this->_breakKeyword = std::move(breakKeyword);
}

std::unique_ptr<SyntaxToken<std::any>> BreakStatementSyntax::getBreakKeyword() {
  return std::move(_breakKeyword);
}
const SyntaxKindUtils::SyntaxKind BreakStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::BreakStatement;
}

const std::vector<SyntaxNode *> &BreakStatementSyntax::getChildren() {
  if (_children.empty()) {
    // Add children
    _children.push_back(_breakKeyword.get());
  }

  return this->_children;
}

const DiagnosticUtils::SourceLocation
BreakStatementSyntax::getSourceLocation() const {
  return _breakKeyword->getSourceLocation();
}

std::unique_ptr<SyntaxToken<std::any>> &
BreakStatementSyntax::getBreakKeywordPtr() {
  return _breakKeyword;
}
