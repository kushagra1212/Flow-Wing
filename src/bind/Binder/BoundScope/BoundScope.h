#pragma once
#include "../../../Common.h"
#include "../../../utils/Utils.h"
#include "../../BoundCustomTypeStatement/BoundCustomTypeStatement.h"
#include "../../BoundFunctionDeclaration/BoundFunctionDeclaration.h"
#include "../../BoundVariableDeclaration/BoundVariableDeclaration.h"

class BoundScope {
 public:
  std::unordered_map<std::string, BoundVariableDeclaration *> variables;
  std::unordered_map<std::string, BoundFunctionDeclaration *> functions;
  std::unordered_map<std::string, BoundCustomTypeStatement *> customTypes;

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

  // Handle Variables

  bool tryDeclareVariable(const std::string &name,
                          BoundVariableDeclaration *variable);

  bool tryLookupVariable(const std::string &name);
  BoundVariableDeclaration *tryGetVariable(const std::string &name);

  bool tryAssignVariable(const std::string &name,
                         BoundVariableDeclaration *variable);

  // Handle Functions

  bool tryDeclareFunction(BoundFunctionDeclaration *function);

  bool tryLookupFunction(const std::string &name);

  // Handle Custom Types

  bool tryDeclareCustomType(BoundCustomTypeStatement *customType);
  bool tryLookupCustomType(const std::string &name);
};