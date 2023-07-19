#include "BoundScopeGlobal.h"

BoundScopeGlobal::BoundScopeGlobal(
    BoundScopeGlobal *previous,
    std::unordered_map<std::string, std::any> variables,
    std::vector<std::string> logs, BoundExpression *expression)
    : previous(previous), variables(variables), logs(logs),
      expression(expression) {}