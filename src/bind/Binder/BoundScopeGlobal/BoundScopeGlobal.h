#pragma once
#include "../../../Common.h"
#include "../../../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../../../utils/Utils.h"
#include "../../BoundExpression.h"
#include "../../BoundFunctionDeclaration/BoundFunctionDeclaration.h"
#include "../../BoundStatement/BoundStatement.h"
#include "../../BoundVariableDeclaration/BoundVariableDeclaration.h"

class BoundScopeGlobal {
 public:
  BoundScopeGlobal(
      std::unique_ptr<BoundScopeGlobal> previous,
      std::unordered_map<std::string, BoundVariableDeclaration *> variables,
      std::unordered_map<std::string, BoundFunctionDeclaration *> functions,
      DiagnosticHandler *diagnosticHandler,
      std::unique_ptr<BoundBlockStatement> statement);

  bool tryLookupVariable(std::string name);
  bool tryAssignVariable(std::string name, BoundVariableDeclaration *value);
  BoundVariableDeclaration *getVariable(std::string name);

 public:
  std::unique_ptr<BoundScopeGlobal> previous;
  std::unordered_map<std::string, BoundVariableDeclaration *> variables;
  std::unordered_map<std::string, BoundFunctionDeclaration *> functions;
  DiagnosticHandler *_diagnosticHandler;
  std::unique_ptr<BoundBlockStatement> globalStatement;
};