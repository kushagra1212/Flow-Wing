#pragma once
#include "../../../Common.h"
#include "../../../utils/Utils.h"
#include "../../BoundExpression.h"
#include "../../BoundStatement/BoundStatement.h"
class BoundScopeGlobal {
public:
  BoundScopeGlobal(BoundScopeGlobal *previous,
                   std::map<std::string, Utils::Variable> variables,
                   std::vector<std::string> logs, BoundStatement *statement);

public:
  BoundScopeGlobal *previous;
  std::map<std::string, Utils::Variable> variables;
  std::vector<std::string> logs;
  BoundStatement *statement;
};