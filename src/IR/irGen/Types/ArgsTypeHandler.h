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

class ArgsTypeHandler {
private:
  std::unordered_map<std::string, std::vector<std::unique_ptr<LLVMType>>>
      _argsTypeMap;

public:
  inline auto hasArgsType(const std::string &funcName) -> bool {
    return _argsTypeMap.find(funcName) != _argsTypeMap.end();
  }

  inline void addArgsType(const std::string &funcName,
                          std::unique_ptr<LLVMType> argsType) {
    _argsTypeMap[funcName].push_back(std::move(argsType));
  }

  inline const std::vector<std::unique_ptr<LLVMType>> &
  getArgsType(const std::string &funcName) {
    return _argsTypeMap[(funcName)];
  }
};
