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


#ifndef __FLOWWING__LLVM_PRIMITIVE_TYPE_H__
#define __FLOWWING__LLVM_PRIMITIVE_TYPE_H__

#include <llvm/IR/DerivedTypes.h>

#include "../LLVMType.h"

class LLVMPrimitiveType : public LLVMType {
public:
  LLVMPrimitiveType(llvm::Type *type, llvm::Type *primitiveType);

  virtual inline const bool isPointerToPrimitive() const override {
    return true;
  }

  inline llvm::Type *getPrimitiveType() const { return _primitiveType; }

  virtual inline llvm::Type *getLLVMType() const override {
    return _primitiveType;
  }

private:
  llvm::Type *_type;
  llvm::Type *_primitiveType;
};

#endif // __FLOWWING__LLVM_PRIMITIVE_TYPE_H__