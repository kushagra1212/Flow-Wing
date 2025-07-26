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

#include "GlobalStatementSyntax.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/statements/StatementSyntax.h"

GlobalStatementSyntax::GlobalStatementSyntax(
    std::unique_ptr<StatementSyntax> statement) {
  this->_statement = std::move(statement);
}

std::unique_ptr<StatementSyntax> GlobalStatementSyntax::getStatement() {
  return std::move(_statement);
}

const SyntaxKindUtils::SyntaxKind GlobalStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::GlobalStatement;
}

const std::vector<SyntaxNode *> &GlobalStatementSyntax::getChildren() {
  if (_children.empty()) {
    _children.push_back(_statement.get());
  }

  return this->_children;
}

const DiagnosticUtils::SourceLocation
GlobalStatementSyntax::getSourceLocation() const {
  return _statement->getSourceLocation();
}

std::unique_ptr<StatementSyntax> &GlobalStatementSyntax::getStatementPtr() {
  return _statement;
}