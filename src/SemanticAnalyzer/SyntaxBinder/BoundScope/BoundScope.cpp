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

#include "BoundScope.h"

BoundScope::BoundScope(std::unique_ptr<BoundScope> parent)
    : breakable(false), continuable(false), functionCounted(0),
      parent(std::move(parent)) {}

bool BoundScope::isInFunction() {
  if (this->functionCounted) {
    return true;
  }

  if (this->parent == nullptr) {
    return false;
  }

  return this->parent->isInFunction();
}

void BoundScope::incrementFunctionCount() { this->functionCounted++; }

void BoundScope::decrementFunctionCount() {
  if (this->functionCounted > 0) {
    this->functionCounted--;
  }
}

void BoundScope::makeBreakableAndContinuable() {
  this->breakable = true;
  this->continuable = true;
}

bool BoundScope::isBreakable() {
  if (this->breakable) {
    return true;
  }

  if (this->parent == nullptr) {
    return false;
  }

  return this->parent->isBreakable();
}

bool BoundScope::isInsideInitFunction() {
  if (this->_insideInitFunction) {
    return true;
  }

  if (this->parent == nullptr) {
    return false;
  }

  return this->parent->isInsideInitFunction();
}

bool BoundScope::isContinuable() {
  if (this->continuable) {
    return true;
  }

  if (this->parent == nullptr) {
    return false;
  }

  return this->parent->isContinuable();
}

bool BoundScope::tryDeclareVariable(const std::string &name,
                                    BoundVariableDeclaration *variable) {
  if (this->variables.find(name) == this->variables.end()) {
    this->variables[name] = variable;
    return true;
  }

  return false;
}

bool BoundScope::tryDeclareVariableGlobal(const std::string &name,
                                          BoundVariableDeclaration *variable) {
  if (this->variables.find(name) != this->variables.end()) {
    return false;
  }

  if (this->parent) {
    return this->parent->tryDeclareVariableGlobal(name, variable);
  }

  this->variables[name] = variable;
  return true;
}

bool BoundScope::tryLookupVariable(const std::string &name) {
  if (this->variables.find(name) != this->variables.end()) {
    return true;
  }
  if (this->parent == nullptr) {
    return false;
  }
  return this->parent->tryLookupVariable(name);
}

BoundVariableDeclaration *BoundScope::tryGetVariable(const std::string &name) {
  if (this->variables.find(name) != this->variables.end()) {
    return this->variables[name];
  }

  if (this->parent)
    return this->parent->tryGetVariable(name);

  return nullptr;
}

bool BoundScope::tryAssignVariable(const std::string &name,
                                   BoundVariableDeclaration *variable) {
  if (this->variables.find(name) != this->variables.end()) {
    this->variables[name] = variable;
    return true;
  }
  if (this->parent == nullptr) {
    return false;
  }
  return this->parent->tryAssignVariable(name, variable);
}

// Custom Types

BoundCustomTypeStatement *
BoundScope::tryGetCustomType(const std::string &name) {
  std::string typeName = Utils::getActualTypeName(name);

  if (this->customTypes.find(typeName) != this->customTypes.end())
    return this->customTypes[typeName];

  if (this->parent)
    return this->parent->tryGetCustomType(typeName);

  return nullptr;
}

bool BoundScope::tryDeclareCustomType(BoundCustomTypeStatement *customType) {

  std::string typeName =
      Utils::getActualTypeName(customType->getTypeNameAsString());

  if (this->customTypes.find(typeName) == this->customTypes.end()) {
    this->customTypes[typeName] = customType;
    return true;
  }

  if (this->parent) {
    return this->parent->tryDeclareCustomType(customType);
  }

  return false;
}

bool BoundScope::tryDeclareCustomTypeGlobal(
    BoundCustomTypeStatement *customType) {
  std::string typeName =
      Utils::getActualTypeName(customType->getTypeNameAsString());

  if (this->customTypes.find(typeName) != this->customTypes.end()) {
    return false;
  }

  if (this->parent) {
    return this->parent->tryDeclareCustomTypeGlobal(customType);
  }

  this->customTypes[typeName] = customType;
  return true;
}

// Class
BoundClassStatement *BoundScope::tryGetClass(const std::string &name) {
  if (this->classes.find(name) != this->classes.end()) {
    return this->classes[name];
  }
  if (this->parent == nullptr) {
    return nullptr;
  }
  return this->parent->tryGetClass(name);
}

bool BoundScope::tryDeclareClass(BoundClassStatement *_class) {
  if (this->classes.find(_class->getClassName()) == this->classes.end()) {
    this->classes[_class->getClassName()] = _class;
    return true;
  }

  return false;
}

bool BoundScope::tryDeclareClassGlobal(BoundClassStatement *_class) {

  if (this->classes.find(_class->getClassName()) != this->classes.end()) {
    return false;
  }

  if (this->parent) {
    return this->parent->tryDeclareClassGlobal(_class);
  }

  this->classes[_class->getClassName()] = _class;
  return true;
}

// Module

BoundModuleStatement *BoundScope::tryGetModule(const std::string &name) {
  if (this->modules.find(name) != this->modules.end()) {
    return this->modules[name];
  }
  if (this->parent == nullptr) {
    return nullptr;
  }
  return this->parent->tryGetModule(name);
}

bool BoundScope::tryDeclareModule(BoundModuleStatement *module) {
  if (this->modules.find(module->getModuleName()) == this->modules.end()) {
    this->modules[module->getModuleName()] = module;
    return true;
  }

  return false;
}

bool BoundScope::tryDeclareModuleGlobal(BoundModuleStatement *module) {

  if (this->modules.find(module->getModuleName()) != this->modules.end()) {
    return false;
  }

  if (this->parent) {
    return this->parent->tryDeclareModuleGlobal(module);
  }

  this->modules[module->getModuleName()] = module;
  return true;
}

// Functions

bool BoundScope::tryDeclareMemberFunction(BoundFunctionDeclaration *function) {
  if (this->functions.find(function->getFunctionNameRef()) ==
      this->functions.end()) {

    this->functions[function->getFunctionNameRef()] = function;
    return true;
  }

  return false;
}

bool BoundScope::tryDeclareFunctionGlobal(BoundFunctionDeclaration *function) {
  if (this->functions.find(function->getFunctionNameRef()) !=
      this->functions.end()) {
    return false;
  }

  if (this->parent) {
    return this->parent->tryDeclareFunctionGlobal(function);
  }

  this->functions[function->getFunctionNameRef()] = function;
  return true;
}

BoundFunctionDeclaration *BoundScope::tryGetFunction(const std::string &name) {
  if (this->functions.find(name) != this->functions.end()) {
    return this->functions[name];
  }
  if (this->parent == nullptr) {
    return nullptr;
  }
  return this->parent->tryGetFunction(name);
}

std::vector<BoundFunctionDeclaration *> BoundScope::getAllFunctions() {
  std::vector<BoundFunctionDeclaration *> result;
  if (this->parent != nullptr) {
    result = this->parent->getAllFunctions();
  }
  for (auto &function : this->functions) {
    result.push_back(function.second);
  }
  return result;
}
