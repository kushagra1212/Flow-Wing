#include "BoundScope.h"

BoundScope::BoundScope(std::shared_ptr<BoundScope> parent)
    : parent(parent), breakable(false), continuable(false), functionCounted(0) {
}

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

bool BoundScope::tryDeclareVariable(
    std::string name, const struct Utils::Variable &initialValue) {
  if (this->variables.find(name) == this->variables.end()) {

    this->variables[name] = initialValue;
    return true;
  }

  return false;
}

bool BoundScope::tryLookupVariable(std::string name) {
  if (this->variables.find(name) != this->variables.end()) {
    return true;
  }
  if (this->parent == nullptr) {
    return false;
  }
  return this->parent->tryLookupVariable(name);
}

bool BoundScope::tryAssignVariable(std::string name,
                                   const struct Utils::Variable &value) {
  if (this->variables.find(name) != this->variables.end()) {
    this->variables[name] = value;
    return true;
  }
  if (this->parent == nullptr) {
    return false;
  }
  return this->parent->tryAssignVariable(name, value);
}

bool BoundScope::tryDeclareFunction(
    std::string name, std::shared_ptr<BoundFunctionDeclaration> function) {
  if (this->functions.find(name) != this->functions.end()) {

    return false;
  }

  if (this->parent) {
    return this->parent->tryDeclareFunction(name, function);
  }

  this->functions[name] = function;
  return true;
}

bool BoundScope::tryLookupFunction(std::string name) {
  if (this->functions.find(name) != this->functions.end()) {
    return true;
  }
  if (this->parent == nullptr) {
    return false;
  }
  return this->parent->tryLookupFunction(name);
}

std::vector<std::shared_ptr<BoundFunctionDeclaration>>
BoundScope::getAllFunctions() {
  std::vector<std::shared_ptr<BoundFunctionDeclaration>> result;
  if (this->parent != nullptr) {
    result = this->parent->getAllFunctions();
  }
  for (auto &function : this->functions) {
    result.push_back(function.second);
  }
  return result;
}
