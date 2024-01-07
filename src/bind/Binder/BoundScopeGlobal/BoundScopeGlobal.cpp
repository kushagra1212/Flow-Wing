#include "BoundScopeGlobal.h"

BoundScopeGlobal::BoundScopeGlobal(
    std::unique_ptr<BoundScopeGlobal> previous,
    std::unordered_map<std::string, BoundVariableDeclaration *> variables,
    std::unordered_map<std::string, BoundFunctionDeclaration *> functions,
    DiagnosticHandler *diagnosticHandler,
    std::unique_ptr<BoundBlockStatement> statement)
    : variables(variables), functions(functions),
      globalStatement(std::move(statement)), previous(std::move(previous)),
      _diagnosticHandler(diagnosticHandler) {}

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

BoundVariableDeclaration *BoundScopeGlobal::getVariable(std::string name) {
  if (this->variables.find(name) != this->variables.end()) {
    return this->variables[name];
  }
  return this->previous->getVariable(name);
}