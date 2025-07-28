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
#include <llvm/IR/DerivedTypes.h>
#pragma clang diagnostic pop

#include "src/IR/irGen/Types/LLVMType/LLVMType.h"

class LLVMObjectType : public LLVMType {
public:
  LLVMObjectType(llvm::Type *type, llvm::StructType *structType);

  virtual ~LLVMObjectType() = default;

  virtual inline bool isPointerToObject() const override { return true; }

  inline llvm::StructType *getStructType() const { return _structType; }

  virtual inline llvm::Type *getLLVMType() const override {
    return _structType;
  }

private:
  llvm::StructType *_structType;
};
