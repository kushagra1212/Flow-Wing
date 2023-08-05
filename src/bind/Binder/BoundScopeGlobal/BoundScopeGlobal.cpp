#include "BoundScopeGlobal.h"

BoundScopeGlobal::BoundScopeGlobal(
    BoundScopeGlobal *previous,
    std::map<std::string, struct Utils::Variable> variables,
    std::map<std::string, BoundFunctionDeclaration *> functions,
    std::vector<std::string> logs, BoundStatement *statement)
    : previous(previous), variables(variables), logs(logs),
      statement(statement), functions(functions) {}

BoundScopeGlobal::~BoundScopeGlobal() {
  delete this->statement;
  delete this->previous;
}

bool BoundScopeGlobal::tryLookupVariable(std::string name) {
  if (this->variables.find(name) != this->variables.end()) {
    return true;
  }
  if (this->previous == nullptr) {
    return false;
  }
  return this->previous->tryLookupVariable(name);
}

bool BoundScopeGlobal::tryAssignVariable(std::string name,
                                         const struct Utils::Variable &value) {
  if (this->variables.find(name) != this->variables.end()) {
    this->variables[name] = value;
    return true;
  }
  if (this->previous == nullptr) {
    return false;
  }
  return this->previous->tryAssignVariable(name, value);
}

Utils::Variable BoundScopeGlobal::getVariable(std::string name) {
  if (this->variables.find(name) != this->variables.end()) {
    return this->variables[name];
  }
  return this->previous->getVariable(name);
}