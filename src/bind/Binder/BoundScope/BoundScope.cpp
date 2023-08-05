#include "BoundScope.h"

BoundScope::BoundScope(BoundScope *parent) : parent(parent) {}

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
    std::string name, const struct Utils::FunctionSymbol &function) {
  if (this->functions.find(name) == this->functions.end()) {

    this->functions[name] = function;
    return true;
  }

  return false;
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

BoundScope::~BoundScope() {
  // /delete this->parent;
}