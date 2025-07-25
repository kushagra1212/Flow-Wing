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


#ifndef __FLOW__WING_VALUE_STACK
#define __FLOW__WING_VALUE_STACK

#include "string"
#include "llvm/IR/Value.h"

class ValueStack {
public:
  std::string typeName;
  llvm::Value *value;
  std::string type;
  llvm::Type *llvmType;
  llvm::Value *dynamicValue;
  ValueStack(const std::string &typeName, llvm::Value *value,
             const std::string &type, llvm::Type *llvmType,
             llvm::Value *dynamicValue)
      : typeName(typeName), value(value), type(type), llvmType(llvmType),
        dynamicValue(dynamicValue) {}

  auto inline getValue() -> llvm::Value * { return value; }
  auto inline getTypeName() -> std::string { return typeName; }
  auto inline getType() -> std::string { return type; }

  auto inline getLLVMType() -> llvm::Type * { return llvmType; }
  auto inline getDynamicValue() -> llvm::Value * { return dynamicValue; }
};

#endif