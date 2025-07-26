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

#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include <any>
#include <llvm/IR/DerivedTypes.h>
#include <map>

class BoundExpression;
template <typename T> class BoundLiteralExpression;

class BoundCallExpression : public BoundExpression {
private:
  std::unique_ptr<BoundLiteralExpression<std::any>> _callerIdentifier;
  std::vector<std::unique_ptr<BoundExpression>> _arguments;
  std::vector<BoundExpression *> _argumentPtrList;
  std::map<uint64_t, std::pair<llvm::Value *, llvm::Type *>> _argumentsMap;
  std::string _callerName = "";
  std::vector<llvm::Type *> _returnTypeList;
  bool _hasNewKeyword = false;
  bool _isSuperFunctionCall = false;

public:
  BoundCallExpression(const DiagnosticUtils::SourceLocation &location);

  const std::type_info &getType() override;
  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  void addArgument(std::unique_ptr<BoundExpression> argument);
  void setCallerIdentifier(
      std::unique_ptr<BoundLiteralExpression<std::any>> callerIdentifier);

  const std::vector<std::unique_ptr<BoundExpression>> &getArgumentsRef() const;
  std::unique_ptr<BoundLiteralExpression<std::any>> &getCallerIdentifierPtr();
  inline auto getCallerNameRef() const -> const std::string & {
    return _callerName;
  }

  inline auto setHasNewKeyword(bool hasNewKeyword) -> void {
    _hasNewKeyword = hasNewKeyword;
  }

  inline auto hasNewKeyword() const -> bool { return _hasNewKeyword; }

  inline auto setCallerName(std::string name) -> void { _callerName = name; }

  inline auto setArgumentAlloca(uint64_t index,
                                std::pair<llvm::Value *, llvm::Type *> value)
      -> void {
    _argumentsMap[index] = value;
  }

  inline auto addReturnTypeToList(llvm::Type *returnType) -> void {
    _returnTypeList.push_back(returnType);
  }

  inline auto getArgumentPtrList() -> std::vector<BoundExpression *> & {
    return _argumentPtrList;
  }

  inline auto getReturnTypeList() const -> const std::vector<llvm::Type *> & {
    return _returnTypeList;
  }

  inline auto setSuperFunctionCall(bool isSuperFunctionCall) -> void {
    _isSuperFunctionCall = isSuperFunctionCall;
  }

  inline auto getIsSuperFunctionCall() const -> bool {
    return _isSuperFunctionCall;
  }

  inline auto getArgumentAlloca(uint64_t index)
      -> std::pair<llvm::Value *, llvm::Type *> {
    return _argumentsMap[index];
  }

  inline auto doesArgumentAllocaExist(uint64_t index) -> bool {
    return _argumentsMap.find(index) != _argumentsMap.end() &&
           _argumentsMap[index].first != nullptr &&
           _argumentsMap[index].second != nullptr;
  }
};
