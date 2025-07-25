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


#include "BoundBlockStatement.h"
BoundBlockStatement::BoundBlockStatement(
    const DiagnosticUtils::SourceLocation &location, bool global)
    : BoundSourceLocation(location) {
  this->_global = global;
}
BoundBlockStatement::BoundBlockStatement(
    const DiagnosticUtils::SourceLocation &location)
    : BoundSourceLocation(location) {
  BoundBlockStatement(location, false);
}

std::vector<std::unique_ptr<BoundStatement>> &
BoundBlockStatement::getStatements() {
  return _statements;
}

void BoundBlockStatement::addStatement(
    std::unique_ptr<BoundStatement> statement) {
  this->_statements.push_back(std::move(statement));
}

bool BoundBlockStatement::getGlobal() const { return this->_global; }

BinderKindUtils::BoundNodeKind BoundBlockStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::BlockStatement;
}

std::vector<BoundNode *> BoundBlockStatement::getChildren() {
  if (this->_children.size() == 0) {
    for (const auto &st : this->_statements) {
      this->_children.push_back((BoundNode *)(st.get()));
    }
  }
  return this->_children;
}
