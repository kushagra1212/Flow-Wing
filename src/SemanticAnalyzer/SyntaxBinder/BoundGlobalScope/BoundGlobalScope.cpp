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

#include "BoundGlobalScope.h"

BoundGlobalScope::BoundGlobalScope(
    std::unique_ptr<BoundGlobalScope> previous, BoundScope *scope,
    std::unordered_map<std::string, std::any> variablesValues,
    FlowWing::DiagnosticHandler *diagnosticHandler,
    std::unique_ptr<BoundBlockStatement> statement)
    : previous(std::move(previous)), variables(scope->variables),
      customTypes(scope->customTypes), classes(scope->classes),
      modules(scope->modules), variablesValues(variablesValues),
      functions(scope->functions), _diagnosticHandler(diagnosticHandler),
      globalStatement(std::move(statement)) {}

bool BoundGlobalScope::tryLookupVariable(std::string name) {
  if (this->variables.find(name) != this->variables.end()) {
    return true;
  }
  if (this->previous == nullptr) {
    return false;
  }
  return this->previous->tryLookupVariable(name);
}

bool BoundGlobalScope::tryAssignVariable(std::string name,
                                         BoundVariableDeclaration *value) {
  if (this->variables.find(name) != this->variables.end()) {
    this->variables[name] = value;
    return true;
  }
  if (this->previous == nullptr) {
    return false;
  }
  return this->previous->tryAssignVariable(name, value);
}

BoundVariableDeclaration *BoundGlobalScope::getVariable(std::string name) {
  if (this->variables.find(name) != this->variables.end()) {
    return this->variables[name];
  }
  return this->previous->getVariable(name);
}

bool BoundGlobalScope::tryLookupVariableValue(std::string name) {
  if (this->variablesValues.find(name) != this->variablesValues.end()) {
    return true;
  }
  if (this->previous == nullptr) {
    return false;
  }
  return this->previous->tryLookupVariableValue(name);
}

bool BoundGlobalScope::tryAssignVariableValue(std::string name,
                                              std::any value) {
  if (this->variablesValues.find(name) != this->variablesValues.end()) {
    this->variablesValues[name] = value;
    return true;
  }
  if (this->previous == nullptr) {
    return false;
  }
  return this->previous->tryAssignVariableValue(name, value);
}

std::any BoundGlobalScope::getVariableValue(std::string name) {
  if (this->variablesValues.find(name) != this->variablesValues.end()) {
    return this->variablesValues[name];
  }
  return this->previous->getVariableValue(name);
}