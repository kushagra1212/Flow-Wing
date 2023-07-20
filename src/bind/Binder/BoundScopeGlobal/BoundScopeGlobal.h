#pragma once
#include "../../../Common.h"
#include "../../BoundExpression.h"
#include "../../BoundStatement/BoundStatement.h"
class BoundScopeGlobal {
public:
  BoundScopeGlobal(BoundScopeGlobal *previous,
                   std::unordered_map<std::string, std::any> variables,
                   std::vector<std::string> logs, BoundStatement *statement);

public:
  BoundScopeGlobal *previous;
  std::unordered_map<std::string, std::any> variables;
  std::vector<std::string> logs;
  BoundStatement *statement;
};