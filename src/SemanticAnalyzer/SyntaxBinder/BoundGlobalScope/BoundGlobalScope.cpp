#include "BoundGlobalScope.h"

BoundGlobalScope::BoundGlobalScope(
    std::unique_ptr<BoundGlobalScope> previous, BoundScope *scope,
    std::unordered_map<std::string, std::any> variablesValues,
    FlowWing::DiagnosticHandler *diagnosticHandler,
    std::unique_ptr<BoundBlockStatement> statement)
    : variables(scope->variables), functions(scope->functions),
      customTypes(scope->customTypes), classes(scope->classes),
      modules(scope->modules), variablesValues(variablesValues),
      globalStatement(std::move(statement)), previous(std::move(previous)),
      _diagnosticHandler(diagnosticHandler) {}

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