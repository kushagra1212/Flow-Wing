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


#include "ReturnStatementSyntax.h"

ReturnStatementSyntax::ReturnStatementSyntax(
    std::unique_ptr<SyntaxToken<std::any>> returnKeyword)
    : _returnKeyword(std::move(returnKeyword)) {}

const std::vector<SyntaxNode *> &ReturnStatementSyntax::getChildren() {
  if (_children.empty()) {
    // Add children

    if (_returnKeyword)
      _children.push_back(_returnKeyword.get());

    for (const auto &expression : _expressionList) {
      _children.push_back(expression.get());
    }
  }

  return this->_children;
}

const SyntaxKindUtils::SyntaxKind ReturnStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ReturnStatement;
}

const DiagnosticUtils::SourceLocation
ReturnStatementSyntax::getSourceLocation() const {
  if (_returnKeyword)
    return _returnKeyword->getSourceLocation();

  for (const auto &expression : _expressionList) {
    return expression->getSourceLocation();
  }

  return DiagnosticUtils::SourceLocation();
}
