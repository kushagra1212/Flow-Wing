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


#include "BoundBringStatement.h"

BoundBringStatement::BoundBringStatement(
    const DiagnosticUtils::SourceLocation &location,
    FlowWing::DiagnosticHandler *diagnosticHandler)
    : BoundSourceLocation(location) {
  this->_diagnosticHandler = diagnosticHandler;
}

BinderKindUtils::BoundNodeKind BoundBringStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::BringStatement;
}

std::vector<BoundNode *> BoundBringStatement::getChildren() {
  if (this->_children.empty()) {
    if (this->_globalScope) {
      for (auto &boundStatement :
           this->_globalScope.get()->globalStatement->getStatements()) {
        this->_children.push_back(boundStatement.get());
      }
    }
  }
  return this->_children;
}

FlowWing::DiagnosticHandler *
BoundBringStatement::getDiagnosticHandlerPtr() const {
  return this->_diagnosticHandler;
}

const std::unique_ptr<BoundGlobalScope> &
BoundBringStatement::getGlobalScopePtr() const {
  return this->_globalScope;
}