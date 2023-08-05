#pragma once
#include "../../../Common.h"
#include "../../../utils/Utils.h"
#include "../../BoundExpression.h"
#include "../../BoundFunctionDeclaration/BoundFunctionDeclaration.h"
#include "../../BoundStatement/BoundStatement.h"
class BoundScopeGlobal {
public:
  BoundScopeGlobal(BoundScopeGlobal *previous,
                   std::map<std::string, Utils::Variable> variables,
                   std::map<std::string, BoundFunctionDeclaration *> functions,
                   std::vector<std::string> logs, BoundStatement *statement);

  ~BoundScopeGlobal();
  bool tryLookupVariable(std::string name);
  bool tryAssignVariable(std::string name, const struct Utils::Variable &value);
  Utils::Variable getVariable(std::string name);

public:
  BoundScopeGlobal *previous;
  std::map<std::string, Utils::Variable> variables;
  std::map<std::string, BoundFunctionDeclaration *> functions;
  std::vector<std::string> logs;
  BoundStatement *statement;
};