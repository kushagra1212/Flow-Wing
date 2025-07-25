/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#pragma once
#include "../../../common/Common.h"
#include "../../../utils/Utils.h"
#include "../../BoundStatements/BoundClassStatement/BoundClassStatement.h"
#include "../../BoundStatements/BoundCustomTypeStatement/BoundCustomTypeStatement.h"
#include "../../BoundStatements/BoundFunctionDeclaration/BoundFunctionDeclaration.h"
#include "../../BoundStatements/BoundModuleStatement/BoundModuleStatement.h"
#include "../../BoundStatements/BoundVariableDeclaration/BoundVariableDeclaration.h"

class BoundScope {
public:
  std::unordered_map<std::string, BoundVariableDeclaration *> variables;
  std::unordered_map<std::string, BoundFunctionDeclaration *> functions;
  std::unordered_map<std::string, BoundCustomTypeStatement *> customTypes;
  std::unordered_map<std::string, BoundClassStatement *> classes;
  std::unordered_map<std::string, BoundModuleStatement *> modules;
  std::string _className = "";
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

  bool tryDeclareVariableGlobal(const std::string &name,
                                BoundVariableDeclaration *variable);

  bool tryLookupVariable(const std::string &name);

  BoundVariableDeclaration *tryGetVariable(const std::string &name);

  bool tryAssignVariable(const std::string &name,
                         BoundVariableDeclaration *variable);

  // Handle Functions

  bool tryDeclareMemberFunction(BoundFunctionDeclaration *function);
  bool tryDeclareFunctionGlobal(BoundFunctionDeclaration *function);
  BoundFunctionDeclaration *tryGetFunction(const std::string &name);

  // Handle Custom Types

  bool tryDeclareCustomType(BoundCustomTypeStatement *customType);
  bool tryDeclareCustomTypeGlobal(BoundCustomTypeStatement *customType);
  BoundCustomTypeStatement *tryGetCustomType(const std::string &name);

  // Handle Class Declaration

  bool tryDeclareClass(BoundClassStatement *customType);
  bool tryDeclareClassGlobal(BoundClassStatement *_class);
  BoundClassStatement *tryGetClass(const std::string &name);

  bool tryDeclareModule(BoundModuleStatement *module);
  bool tryDeclareModuleGlobal(BoundModuleStatement *module);
  BoundModuleStatement *tryGetModule(const std::string &name);

  bool isInsideInitFunction();
  inline auto getClassName() -> std::string {
    if (this->_className != "")
      return this->_className;

    if (this->parent)
      return this->parent->getClassName();

    return "";
  }

  inline auto setClassName(const std::string &name) { _className = name; }

  inline auto setInsideInitFunction(bool value) { _insideInitFunction = value; }

private:
  bool _insideInitFunction = false;
};