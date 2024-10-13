#pragma once

#include "../../../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../../../utils/BuiltInFunction/BuiltInFunction.h"
#include "../BoundGlobalScope/BoundGlobalScope.h"
#include "../BoundScope/BoundScope.h"
#include <string>

class SyntaxBinderContext {
  std::unique_ptr<BoundScope> _root;
  FlowWing::DiagnosticHandler *_diagnosticHandler;
  std::string _currentModuleName;
  std::unordered_map<std::string, bool> _moduleDependencyMap;

public:
  SyntaxBinderContext(std::unique_ptr<BoundScope> parent,
                      FlowWing::DiagnosticHandler *diagnosticHandler);

  //? Getters

  FlowWing::DiagnosticHandler *getDiagnosticHandler();
  const bool doesModuleAlreadyExist(const std::string &moduleName);
  const std::string &getCurrentModuleName();
  std::unique_ptr<BoundScope> &getRootRef();

  //? Setters
  void updateModuleDependencyMap(const std::string &moduleName,
                                 const bool &dependencyStatus);
  void setCurrentModuleName(const std::string &moduleName);
  void updateBoundScope(std::unique_ptr<BoundGlobalScope> &scope);
  void insertScope();
  void removeScope();
};
