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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#include <llvm/IR/Type.h>
#pragma clang diagnostic pop

class LLVMType {
public:
  LLVMType(llvm::Type *type);
  LLVMType(llvm::Type *type, std::vector<llvm::Type *> structTypeList);
  virtual ~LLVMType() = default;

  inline llvm::Type *getType() const { return _type; }

  inline bool isPointer() const { return _type->isPointerTy(); }

  inline bool operator==(const LLVMType &other) const {
    return _type == other._type;
  }

  inline bool operator!=(const LLVMType &other) const {
    return !(*this == other);
  }

  virtual inline llvm::Type *getLLVMType() const { return _type; }

  virtual inline bool isPointerToArray() const { return false; }

  virtual inline bool isPointerToObject() const { return false; }
  virtual inline bool isPointerToFunction() const { return false; }

  virtual inline bool isPointerToPrimitive() const { return false; }

  virtual inline bool isPointerToDynamic() const { return false; }

  inline auto getStructTypeListRef() const
      -> const std::vector<llvm::Type *> & {
    return _structTypeList;
  }

private:
  llvm::Type *_type;
  std::vector<llvm::Type *> _structTypeList;
};
