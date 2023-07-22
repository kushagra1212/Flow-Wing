#include "BoundScopeGlobal.h"

BoundScopeGlobal::BoundScopeGlobal(
    BoundScopeGlobal *previous,
    std::map<std::string, struct Utils::Variable> variables,
    std::vector<std::string> logs, BoundStatement *statement)
    : previous(previous), variables(variables), logs(logs),
      statement(statement) {}