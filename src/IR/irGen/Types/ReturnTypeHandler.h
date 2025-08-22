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

#include "LLVMType/LLVMArrayType/LLVMArrayType.h"

class ReturnType {
private:
  std::unique_ptr<LLVMType> _returnType;
  bool _hasAsReturnType = false;

public:
  ReturnType(std::unique_ptr<LLVMType> returnType, bool hasAsReturnType) {
    _returnType = (std::move(returnType));
    _hasAsReturnType = (hasAsReturnType);
  }

  inline std::unique_ptr<LLVMType> &getReturnType() { return _returnType; }

  inline bool hasAsReturnType() const { return _hasAsReturnType; }
};

class ReturnTypeHandler {
private:
  std::unordered_map<std::string, std::vector<std::unique_ptr<ReturnType>>>
      _returnTypeMap;

public:
  inline void addReturnType(const std::string &funcName,
                            std::unique_ptr<LLVMType> returnType,
                            bool hasAsReturnType) {
    _returnTypeMap[funcName].push_back(
        std::make_unique<ReturnType>(std::move(returnType), hasAsReturnType));
  }

  inline std::unique_ptr<LLVMType> &getReturnType(const std::string &funcName,
                                                  const uint64_t &index) {
    return _returnTypeMap[funcName][index]->getReturnType();
  }

  inline auto getReturnTypeListRef(const std::string &funcName) -> auto & {
    return _returnTypeMap[funcName];
  }

  inline bool hasAsReturnType(const std::string &funcName,
                              const uint64_t &index) {
    return _returnTypeMap[funcName][index]->hasAsReturnType();
  }

  inline auto isHavingReturnTypeAsParameter(const std::string &funcName,
                                            const uint64_t &index) -> bool {
    if (this->hasAsReturnType(funcName, index))
      return false;

    if (this->getReturnType(funcName, index)->getLLVMType()->isVoidTy())
      return false;

    return true;
  }
};
