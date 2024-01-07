#include "BoundScope.h"

BoundScope::BoundScope(std::unique_ptr<BoundScope> parent)
    : parent(std::move(parent)), breakable(false), continuable(false),
      functionCounted(0) {}

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
  return this->parent->tryGetVariable(name);
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

bool BoundScope::tryDeclareFunction(BoundFunctionDeclaration *function) {
  if (this->functions.find(function->getFunctionNameRef()) !=
      this->functions.end()) {

    return false;
  }

  if (this->parent) {
    return this->parent->tryDeclareFunction(function);
  }

  this->functions[function->getFunctionNameRef()] = function;
  return true;
}

bool BoundScope::tryLookupFunction(const std::string &name) {
  if (this->functions.find(name) != this->functions.end()) {
    return true;
  }
  if (this->parent == nullptr) {
    return false;
  }
  return this->parent->tryLookupFunction(name);
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

bool BoundScope::tryLookupCustomType(const std::string &name) {
  if (this->customTypes.find(name) != this->customTypes.end()) {
    return true;
  }
  if (this->parent == nullptr) {
    return false;
  }
  return this->parent->tryLookupCustomType(name);
}

bool BoundScope::tryDeclareCustomType(BoundCustomTypeStatement *customType) {
  if (this->customTypes.find(customType->getTypeNameAsString()) !=
      this->customTypes.end()) {

    return false;
  }

  if (this->parent) {
    return this->parent->tryDeclareCustomType(customType);
  }

  this->customTypes[customType->getTypeNameAsString()] = customType;
  return true;
}
