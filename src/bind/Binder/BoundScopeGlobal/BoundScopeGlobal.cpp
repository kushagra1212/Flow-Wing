#include "BoundScopeGlobal.h"

BoundScopeGlobal::BoundScopeGlobal(
    std::unique_ptr<BoundScopeGlobal> previous,
    std::unordered_map<std::string, BoundVariableDeclaration *> variables,
    std::unordered_map<std::string, std::any> variablesValues,
    std::unordered_map<std::string, BoundFunctionDeclaration *> functions,
    std::unordered_map<std::string, BoundCustomTypeStatement *> customTypes,
    std::unordered_map<std::string, BoundClassStatement *> classes,
    std::unordered_map<std::string, BoundModuleStatement *> modules,
    FlowWing::DiagnosticHandler *diagnosticHandler,
    std::unique_ptr<BoundBlockStatement> statement)
    : variables(variables), functions(functions), customTypes(customTypes),
      classes(classes), modules(modules), variablesValues(variablesValues),
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

bool BoundScopeGlobal::tryLookupVariableValue(std::string name) {
  if (this->variablesValues.find(name) != this->variablesValues.end()) {
    return true;
  }
  if (this->previous == nullptr) {
    return false;
  }
  return this->previous->tryLookupVariableValue(name);
}

bool BoundScopeGlobal::tryAssignVariableValue(std::string name,
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

std::any BoundScopeGlobal::getVariableValue(std::string name) {
  if (this->variablesValues.find(name) != this->variablesValues.end()) {
    return this->variablesValues[name];
  }
  return this->previous->getVariableValue(name);
}