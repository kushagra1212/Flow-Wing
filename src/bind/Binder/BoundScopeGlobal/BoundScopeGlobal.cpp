#include "BoundScopeGlobal.h"

BoundScopeGlobal::BoundScopeGlobal(
    std::unique_ptr<BoundScopeGlobal> previous,
    std::map<std::string, struct Utils::Variable> variables,
    std::map<std::string, BoundFunctionDeclaration *> functions,
    DiagnosticHandler *diagnosticHandler,
    std::unique_ptr<BoundBlockStatement> statement)
    : variables(variables), functions(functions) {

  this->globalStatement = std::move(statement);

  this->previous = std::move(previous);
  this->_diagnosticHandler = diagnosticHandler;
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