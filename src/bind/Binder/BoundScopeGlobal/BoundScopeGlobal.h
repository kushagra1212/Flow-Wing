#ifndef BOUNDSCOPEGLOBAL_H
#define BOUNDSCOPEGLOBAL_H
#include "../../../Common.h"
#include "../../../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../../../utils/Utils.h"
#include "../../BoundClassStatement/BoundClassStatement.h"
#include "../../BoundCustomTypeStatement/BoundCustomTypeStatement.h"
#include "../../BoundExpression.h"
#include "../../BoundFunctionDeclaration/BoundFunctionDeclaration.h"
#include "../../BoundStatement/BoundStatement.h"
#include "../../BoundVariableDeclaration/BoundVariableDeclaration.h"

class BoundScopeGlobal {
public:
  BoundScopeGlobal(
      std::unique_ptr<BoundScopeGlobal> previous,
      std::unordered_map<std::string, BoundVariableDeclaration *> variables,
      std::unordered_map<std::string, std::any> variablesValues,
      std::unordered_map<std::string, BoundFunctionDeclaration *> functions,
      std::unordered_map<std::string, BoundCustomTypeStatement *> customTypes,
      std::unordered_map<std::string, BoundClassStatement *> classes,
      FLowWing::DiagnosticHandler *diagnosticHandler,
      std::unique_ptr<BoundBlockStatement> statement);

  bool tryLookupVariable(std::string name);
  bool tryAssignVariable(std::string name, BoundVariableDeclaration *value);
  BoundVariableDeclaration *getVariable(std::string name);

  bool tryLookupVariableValue(std::string name);

  bool tryAssignVariableValue(std::string name, std::any value);

  std::any getVariableValue(std::string name);

public:
  std::unique_ptr<BoundScopeGlobal> previous;
  std::unordered_map<std::string, BoundVariableDeclaration *> variables;
  std::unordered_map<std::string, BoundCustomTypeStatement *> customTypes;
  std::unordered_map<std::string, BoundClassStatement *> classes;
  std::unordered_map<std::string, std::any> variablesValues;
  std::unordered_map<std::string, BoundFunctionDeclaration *> functions;
  FLowWing::DiagnosticHandler *_diagnosticHandler;
  std::unique_ptr<BoundBlockStatement> globalStatement;
};

#endif