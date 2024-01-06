#pragma once
#include "../../../Common.h"
#include "../../../utils/Utils.h"
#include "../../BoundCustomTypeStatement/BoundCustomTypeStatement.h"
#include "../../BoundFunctionDeclaration/BoundFunctionDeclaration.h"
class BoundScope {
public:
  std::map<std::string, struct Utils::Variable> variables;
  std::map<std::string, BoundFunctionDeclaration *> functions;
  std::map<std::string, BoundCustomTypeStatement *> customTypes;

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

  bool tryDeclareVariable(const std::string &name,
                          const struct Utils::Variable &initialValue);

  bool tryLookupVariable(const std::string &name);

  bool tryAssignVariable(const std::string &name,
                         const struct Utils::Variable &value);

  bool tryDeclareFunction(BoundFunctionDeclaration *function);

  bool tryLookupFunction(const std::string &name);

  Utils::Variable tryGetVariable(const std::string &name);

  bool tryDeclareCustomType(BoundCustomTypeStatement *customType);
  bool tryLookupCustomType(const std::string &name);
};