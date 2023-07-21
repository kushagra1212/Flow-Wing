#pragma once
#include "../../../Common.h"
class BoundScope {
public:
  std::unordered_map<std::string, std::any> variables;
  BoundScope *parent;

  BoundScope(BoundScope *parent);

public:
  bool tryDeclareVariable(std::string name, std::any initialValue);

  bool tryLookupVariable(std::string name);

  bool tryAssignVariable(std::string name, std::any value);

  std::vector<std::string> getVariablesKeys();
};