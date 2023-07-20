#include "BoundScopeGlobal.h"

BoundScopeGlobal::BoundScopeGlobal(
    BoundScopeGlobal *previous,
    std::unordered_map<std::string, std::any> variables,
    std::vector<std::string> logs, BoundStatement *statement)
    : previous(previous), variables(variables), logs(logs),
      statement(statement) {}