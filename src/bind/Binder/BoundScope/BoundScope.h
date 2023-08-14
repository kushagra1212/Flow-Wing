#pragma once
#include "../../../Common.h"
#include "../../../utils/Utils.h"
#include "../../BoundFunctionDeclaration/BoundFunctionDeclaration.h"
class BoundScope {
public:
  std::map<std::string, struct Utils::Variable> variables;
  std::map<std::string, std::shared_ptr<BoundFunctionDeclaration>> functions;

  bool breakable, continuable;
  int functionCounted;

  std::shared_ptr<BoundScope> parent;

  BoundScope(std::shared_ptr<BoundScope> parent);

public:
  void makeBreakableAndContinuable();

  bool isBreakable();
  bool isContinuable();

  bool isInFunction();

  void incrementFunctionCount();
  void decrementFunctionCount();

  std::vector<std::shared_ptr<BoundFunctionDeclaration>> getAllFunctions();

  bool tryDeclareVariable(std::string name,
                          const struct Utils::Variable &initialValue);

  bool tryLookupVariable(std::string name);

  bool tryAssignVariable(std::string name, const struct Utils::Variable &value);

  bool tryDeclareFunction(std::string name,
                          std::shared_ptr<BoundFunctionDeclaration> function);

  bool tryLookupFunction(std::string name);
};