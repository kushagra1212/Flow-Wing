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

#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundLiteralExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundTypeExpression/BoundTypeExpression.h"
#include "src/SemanticAnalyzer/BoundSourceLocation/BoundSourceLocation.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundCustomTypeStatement/BoundCustomTypeStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundFunctionDeclaration/BoundFunctionDeclaration.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundVariableDeclaration/BoundVariableDeclaration.h"
#include "src/common/constants/FlowWingUtilsConstants.h"

class BoundClassStatement : public BoundStatement, public BoundSourceLocation {
  std::string _className;
  std::string _parentClassName;
  BoundClassStatement *_parentClass = nullptr;
  std::vector<std::unique_ptr<BoundVariableDeclaration>> _memberVariables;

  std::vector<BoundVariableDeclaration *> _allMemberVariables;

  std::vector<std::string> _allFunctionNames;
  std::unordered_map<std::string, uint64_t> _allFunctionNamesMap;

  std::vector<std::unique_ptr<BoundStatement>> _memberFunctions;
  std::vector<std::unique_ptr<BoundStatement>> _customTypes;
  std::vector<
      std::pair<BoundLiteralExpression<std::any> *, BoundTypeExpression *>>
      _key_type_pairs;
  bool _isExposed;

public:
  BoundClassStatement(const DiagnosticUtils::SourceLocation &location);

  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  inline auto setClassName(std::string className) -> void {
    _className = className;
  }

  inline auto setParentClassName(std::string parentClassName) -> void {
    _parentClassName = parentClassName;
  }

  inline auto setParentClass(BoundClassStatement *parentClass) -> void {
    _parentClass = parentClass;
  }

  inline auto addMemberVariable(std::unique_ptr<BoundVariableDeclaration> var)
      -> void {
    _memberVariables.push_back(std::move(var));
  }

  inline auto addMemberVariablePtr(BoundVariableDeclaration *var) -> void {

    for (auto &v : _allMemberVariables) {
      if (v->getVariableName() == var->getVariableName()) {
        v = var;
        return;
      }
    }

    _allMemberVariables.push_back(var);
  }

  inline auto addFunctionName(std::string name) -> void {

    for (auto &v : _allFunctionNames) {
      if (v == name) {
        return;
      }
    }
    _allFunctionNamesMap[name] = _allFunctionNames.size();
    _allFunctionNames.push_back(name);
  }

  inline auto hasFunctionName(std::string name) -> bool {
    return _allFunctionNamesMap.find(name) != _allFunctionNamesMap.end();
  }

  inline auto setIsExposed(bool isExposed) -> void { _isExposed = isExposed; }

  inline auto addCustomType(std::unique_ptr<BoundStatement> type) -> void {

    _customTypes.push_back(std::move(type));
  }

  inline auto addMemberFunction(std::unique_ptr<BoundStatement> fun) -> void {
    _memberFunctions.push_back(std::move(fun));
  }

  inline auto addKeyTypePair(BoundLiteralExpression<std::any> *key,
                             BoundTypeExpression *type) -> void {

    for (auto &v : _key_type_pairs) {
      if (v.first == key) {
        v.second = type;
        return;
      }
    }

    _key_type_pairs.push_back(std::make_pair(key, type));
  }
  inline auto getCustomTypesRef()
      -> std::vector<std::unique_ptr<BoundStatement>> & {
    return _customTypes;
  }
  inline auto getClassName() -> std::string { return _className; }

  inline auto getMemberVariablesRef()
      -> std::vector<std::unique_ptr<BoundVariableDeclaration>> & {
    return _memberVariables;
  }

  inline auto getAllFunctionNamesRef() -> std::vector<std::string> & {
    return _allFunctionNames;
  }

  inline auto getParentClass() -> BoundClassStatement * { return _parentClass; }

  inline auto getAllMemberVariablesRef()
      -> std::vector<BoundVariableDeclaration *> & {
    return _allMemberVariables;
  }

  inline auto tryGetCustomLocalType(std::string typeName)
      -> BoundCustomTypeStatement * {
    for (auto &v : _customTypes) {
      BoundCustomTypeStatement *customType =
          dynamic_cast<BoundCustomTypeStatement *>(v.get());

      if (customType->getTypeNameAsString() == typeName) {
        return customType;
      }
    }
    return nullptr;
  }

  inline auto tryGetCustomType(std::string typeName)
      -> BoundCustomTypeStatement * {

    auto type = this->tryGetCustomLocalType(typeName);
    if (type) {
      return type;
    }

    if (this->_parentClass) {

      return this->_parentClass->tryGetCustomType(typeName);
    }

    return nullptr;
  }

  inline auto getMemberFunctionsRef()
      -> std::vector<std::unique_ptr<BoundStatement>> & {
    return _memberFunctions;
  }

  inline auto getKeyPairsRef() -> std::vector<
      std::pair<BoundLiteralExpression<std::any> *, BoundTypeExpression *>> & {
    return _key_type_pairs;
  }

  inline auto getParentClassName() -> std::string { return _parentClassName; }

  inline auto getInitializerMemberFunction() -> BoundFunctionDeclaration * {
    for (auto &fun : _memberFunctions) {
      BoundFunctionDeclaration *fd =
          static_cast<BoundFunctionDeclaration *>(fun.get());
      if (fd->getFunctionNameRef() ==
          _className + FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX + "init")
        return fd;
    }
    return nullptr;
  }

  inline auto getMemberFunction(std::string functionName)
      -> BoundFunctionDeclaration * {
    for (auto &fun : _memberFunctions) {
      BoundFunctionDeclaration *fd =
          static_cast<BoundFunctionDeclaration *>(fun.get());
      if (fd->getFunctionNameRef() == functionName)
        return fd;
    }
    return nullptr;
  }

  inline auto getActualFunctionNameIfExists(std::string functionName)
      -> std::string {

    for (auto &fun : this->getMemberFunctionsRef()) {
      BoundFunctionDeclaration *fd =
          static_cast<BoundFunctionDeclaration *>(fun.get());

      if (fd->getFunctionNameRef().substr(
              fd->getFunctionNameRef().find(
                  FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX) +
              1) == functionName) {
        return this->_className +
               FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX + functionName;
      }
    }
    if (this->_parentClass) {
      return this->_parentClass->getActualFunctionNameIfExists(functionName);
    }
    return "";
  }
  inline auto isExposed() -> bool { return _isExposed; }
};
