#pragma once
#include "../../../Common.h"
#include "../../../utils/Utils.h"
class BoundScope {
public:
  std::map<std::string, struct Utils::Variable> variables;
  BoundScope *parent;

  BoundScope(BoundScope *parent);

public:
  bool tryDeclareVariable(std::string name,
                          const struct Utils::Variable &initialValue);

  bool tryLookupVariable(std::string name);

  bool tryAssignVariable(std::string name, const struct Utils::Variable &value);

  std::vector<std::string> getVariablesKeys();
};