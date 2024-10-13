#include "SyntaxBinderContext.h"

SyntaxBinderContext::SyntaxBinderContext(
    std::unique_ptr<BoundScope> parent,
    FlowWing::DiagnosticHandler *diagnosticHandler)
    : _root(std::make_unique<BoundScope>(std::move(parent))),
      _diagnosticHandler(diagnosticHandler) {
  BuiltInFunction::setupBuiltInFunctions();
}

//? Getters

FlowWing::DiagnosticHandler *SyntaxBinderContext::getDiagnosticHandler() {
  return _diagnosticHandler;
}

const bool
SyntaxBinderContext::doesModuleAlreadyExist(const std::string &moduleName) {
  return _moduleDependencyMap.find(moduleName) != _moduleDependencyMap.end();
}

const std::string &SyntaxBinderContext::getCurrentModuleName() {
  return _currentModuleName;
}

std::unique_ptr<BoundScope> &SyntaxBinderContext::getRootRef() { return _root; }

//? Setters

void SyntaxBinderContext::updateModuleDependencyMap(
    const std::string &moduleName, const bool &dependencyStatus) {
  _moduleDependencyMap[moduleName] = dependencyStatus;
}

void SyntaxBinderContext::setCurrentModuleName(const std::string &moduleName) {
  _currentModuleName = moduleName;
}

void SyntaxBinderContext::insertScope() {
  _root = std::make_unique<BoundScope>(std::move(_root));
}

void SyntaxBinderContext::removeScope() { _root = std::move(_root->parent); }

void SyntaxBinderContext::updateBoundScope(
    std::unique_ptr<BoundGlobalScope> &scope) {
  _root->variables = scope->variables;
  _root->functions = scope->functions;
  _root->customTypes = scope->customTypes;
  _root->classes = scope->classes;
  _root->modules = scope->modules;
}