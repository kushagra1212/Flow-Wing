#include "BoundScope.h"

BoundScope::BoundScope(BoundScope *parent) : parent(parent) {}

bool BoundScope::tryDeclareVariable(std::string name) {

  this->variables[name] = std::any();
  return true;
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

bool BoundScope::tryAssignVariable(std::string name, std::any value) {
  if (this->variables.find(name) != this->variables.end()) {
    this->variables[name] = value;
    return true;
  }
  if (this->parent == nullptr) {
    return false;
  }
  return this->parent->tryAssignVariable(name, value);
}

std::vector<std::string> BoundScope::getVariablesKeys() {
  std::vector<std::string> variables;
  for (auto &variable : this->variables) {
    variables.push_back(variable.first);
  }
  return variables;
}