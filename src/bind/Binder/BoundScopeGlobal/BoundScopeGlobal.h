#pragma once
#include "../../../Common.h"
#include "../../BoundExpression.h"
class BoundScopeGlobal {
public:
  BoundScopeGlobal(BoundScopeGlobal *previous,
                   std::unordered_map<std::string, std::any> variables,
                   std::vector<std::string> logs, BoundExpression *expression);

public:
  BoundScopeGlobal *previous;
  std::unordered_map<std::string, std::any> variables;
  std::vector<std::string> logs;
  BoundExpression *expression;
};