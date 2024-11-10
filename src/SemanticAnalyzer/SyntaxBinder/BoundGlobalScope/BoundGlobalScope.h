#ifndef BOUND_SCOPE_GLOBAL_H
#define BOUND_SCOPE_GLOBAL_H
#include "../../../common/Common.h"
#include "../../../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../../../utils/Utils.h"
#include "../../BoundExpressions/BoundExpression/BoundExpression.h"
#include "../../BoundStatements/BoundClassStatement/BoundClassStatement.h"
#include "../../BoundStatements/BoundCustomTypeStatement/BoundCustomTypeStatement.h"
#include "../../BoundStatements/BoundFunctionDeclaration/BoundFunctionDeclaration.h"
#include "../../BoundStatements/BoundModuleStatement/BoundModuleStatement.h"
#include "../../BoundStatements/BoundStatement/BoundStatement.h"
#include "../../BoundStatements/BoundVariableDeclaration/BoundVariableDeclaration.h"
#include "../BoundScope/BoundScope.h"

class BoundGlobalScope {
public:
  BoundGlobalScope(std::unique_ptr<BoundGlobalScope> previous,
                   BoundScope *scope,
                   std::unordered_map<std::string, std::any> variablesValues,
                   FlowWing::DiagnosticHandler *diagnosticHandler,
                   std::unique_ptr<BoundBlockStatement> statement);

  bool tryLookupVariable(std::string name);
  bool tryAssignVariable(std::string name, BoundVariableDeclaration *value);
  BoundVariableDeclaration *getVariable(std::string name);

  bool tryLookupVariableValue(std::string name);

  bool tryAssignVariableValue(std::string name, std::any value);

  std::any getVariableValue(std::string name);

public:
  std::unique_ptr<BoundGlobalScope> previous;
  std::unordered_map<std::string, BoundVariableDeclaration *> variables;
  std::unordered_map<std::string, BoundCustomTypeStatement *> customTypes;
  std::unordered_map<std::string, BoundClassStatement *> classes;
  std::unordered_map<std::string, BoundModuleStatement *> modules;
  std::unordered_map<std::string, std::any> variablesValues;
  std::unordered_map<std::string, BoundFunctionDeclaration *> functions;
  FlowWing::DiagnosticHandler *_diagnosticHandler;
  std::unique_ptr<BoundBlockStatement> globalStatement;
};

#endif