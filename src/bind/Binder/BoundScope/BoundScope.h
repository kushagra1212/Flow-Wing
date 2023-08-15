#pragma once
#include "../../../Common.h"
#include "../../../utils/Utils.h"
#include "../../BoundFunctionDeclaration/BoundFunctionDeclaration.h"
class BoundScope {
public:
  std::map<std::string, struct Utils::Variable> variables;
  std::map<std::string, BoundFunctionDeclaration *> functions;

  bool breakable, continuable;
  int functionCounted;

  std::unique_ptr<BoundScope> parent;

  BoundScope(std::unique_ptr<BoundScope> parent);

public:
  void makeBreakableAndContinuable();

  bool isBreakable();
  bool isContinuable();

  bool isInFunction();

  void incrementFunctionCount();
  void decrementFunctionCount();

  std::vector<BoundFunctionDeclaration *> getAllFunctions();

  bool tryDeclareVariable(std::string name,
                          const struct Utils::Variable &initialValue);

  bool tryLookupVariable(std::string name);

  bool tryAssignVariable(std::string name, const struct Utils::Variable &value);

  bool tryDeclareFunction(std::string name, BoundFunctionDeclaration *function);

  bool tryLookupFunction(std::string name);
};