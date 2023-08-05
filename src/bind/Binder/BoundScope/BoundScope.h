#pragma once
#include "../../../Common.h"
#include "../../../utils/Utils.h"
#include "../../BoundFunctionDeclaration/BoundFunctionDeclaration.h"
class BoundScope {
public:
  std::map<std::string, struct Utils::Variable> variables;
  std::map<std::string, BoundFunctionDeclaration *> functions;

  BoundScope *parent;

  BoundScope(BoundScope *parent);

  ~BoundScope();

public:
  bool tryDeclareVariable(std::string name,
                          const struct Utils::Variable &initialValue);

  bool tryLookupVariable(std::string name);

  bool tryAssignVariable(std::string name, const struct Utils::Variable &value);

  bool tryDeclareFunction(std::string name, BoundFunctionDeclaration *function);

  bool tryLookupFunction(std::string name);
};