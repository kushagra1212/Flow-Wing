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

#include "src/utils/LogConfig.h"
#include "llvm/IR/Module.h"
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>

class BoundCustomTypeStatement;

namespace FlowWing {
class Type {
  std::string name;
  llvm::Type *type;
  int64_t index = -1;
  BoundCustomTypeStatement *customType;

public:
  Type() = default;
  Type(const std::string &name, llvm::Type *type, int64_t index,
       BoundCustomTypeStatement *customType)
      : name(name), type(type), index(index), customType(customType) {

    CODEGEN_DEBUG_LOG("Type: " + name + " ", type, index);
  }

  const std::string &getName() const { return name; }
  llvm::Type *getType() const { return type; }

  llvm::StructType *getStructType() const {
    if (type && llvm::isa<llvm::StructType>(type)) {
      return llvm::cast<llvm::StructType>(type);
    }

    return nullptr;
  }
  int64_t getIndex() const { return index; }
  BoundCustomTypeStatement *getCustomType() const { return customType; }

  class TypeBuilder {
    std::string name;
    llvm::Type *type = nullptr;
    int64_t index = -1;
    BoundCustomTypeStatement *customType = nullptr;

  public:
    TypeBuilder &setName(const std::string &name) {
      this->name = name;
      return *this;
    }

    TypeBuilder &setType(llvm::Type *type) {
      this->type = type;
      return *this;
    }

    TypeBuilder &setIndex(int64_t index) {
      this->index = index;
      return *this;
    }

    TypeBuilder &setCustomType(BoundCustomTypeStatement *customType) {
      this->customType = customType;
      return *this;
    }

    Type build() { return Type(name, type, index, customType); }
  };
};

} // namespace FlowWing
