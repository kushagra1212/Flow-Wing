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


#include "ElseClauseSyntax.h"

ElseClauseSyntax::ElseClauseSyntax(
    std::unique_ptr<SyntaxToken<std::any>> elseKeyword,
    std::unique_ptr<BlockStatementSyntax> statement) {
  this->_elseKeyword = std::move(elseKeyword);
  this->_statement = std::move(statement);
}

std::unique_ptr<SyntaxToken<std::any>> ElseClauseSyntax::getElseKeyword() {
  return std::move(_elseKeyword);
}

std::unique_ptr<BlockStatementSyntax> ElseClauseSyntax::getStatement() {
  return std::move(_statement);
}

const SyntaxKindUtils::SyntaxKind ElseClauseSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ElseClause;
}

const std::vector<SyntaxNode *> &ElseClauseSyntax::getChildren() {
  if (_children.empty()) {
    // Add children

    _children.push_back(_elseKeyword.get());
    _children.push_back(_statement.get());
  }

  return this->_children;
}

const DiagnosticUtils::SourceLocation
ElseClauseSyntax::getSourceLocation() const {
  return this->_elseKeyword->getSourceLocation();
}

std::unique_ptr<SyntaxToken<std::any>> &ElseClauseSyntax::getElseKeywordRef() {
  return this->_elseKeyword;
}
std::unique_ptr<BlockStatementSyntax> &ElseClauseSyntax::getStatementRef() {
  return this->_statement;
}
