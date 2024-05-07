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
  if (this->customTypes.find(name) != this->customTypes.end()) {
    return this->customTypes[name];
  }
  if (this->parent == nullptr) {
    return nullptr;
  }
  return this->parent->tryGetCustomType(name);
}

bool BoundScope::tryDeclareCustomType(BoundCustomTypeStatement *customType) {
  if (this->customTypes.find(customType->getTypeNameAsString()) ==
      this->customTypes.end()) {
    this->customTypes[customType->getTypeNameAsString()] = customType;
    return true;
  }

  return false;
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

// Functions

bool BoundScope::tryDeclareMemberFunction(BoundFunctionDeclaration *function) {
  if (this->functions.find(function->getFunctionNameRef()) ==
      this->functions.end()) {

    this->functions[function->getFunctionNameRef()] = function;
    return true;
  }

  return true;
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
