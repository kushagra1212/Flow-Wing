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

#include "src/common/Common.h"

// clang-format off
#include "src/diagnostics/Diagnostic/diagnostic_push.h"
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include "src/diagnostics/Diagnostic/diagnostic_pop.h"
// clang-format on

class TypeTable {
private:
  std::unordered_map<std::string, llvm::StructType *> _type_map;
  std::unordered_map<std::string, size_t> _key_index_map;
  std::unordered_map<std::string, llvm::Type *> _element_map;

public:
  llvm::StructType *getType(const std::string &name);
  bool updateType(const std::string &name, llvm::StructType *type);
  void setType(const std::string &name, llvm::StructType *type);

  inline size_t getIndex(const std::string &name) {
    if (_key_index_map.find(name) != _key_index_map.end()) {
      return _key_index_map[name];
    }
    return -1; // Not found
  }

  inline void setIndex(const std::string &name, size_t value) {
    _key_index_map[name] = value;
  }

  inline llvm::Type *getElementType(const std::string &name) {
    if (_element_map.find(name) != _element_map.end()) {
      return _element_map[name];
    }
    return nullptr; // Not found
  }

  inline void setElementType(const std::string &name, llvm::Type *value) {
    _element_map[name] = value;
  }
};
