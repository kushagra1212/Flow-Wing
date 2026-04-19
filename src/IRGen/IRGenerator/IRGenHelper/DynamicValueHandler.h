/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
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

// clang-format off
#include "src/compiler/diagnostics/DiagnosticPush.hpp"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "src/compiler/diagnostics/DiagnosticPop.hpp"
// clang-format on

#include <functional>

namespace flow_wing {
namespace types {
class Type;
}
namespace ir_gen {

// Dynamic value type tags
enum class DynamicValueType {
  INT8 = 0,
  INT32 = 1,
  INT64 = 2,
  FLOAT32 = 3,
  FLOAT64 = 4,
  STRING = 5,
  BOOLEAN = 6,
  NIRAST = 7,
  CHAR = 8,
  OBJECT = 9,
  ARRAY = 10,
};

class IRGenContext;

namespace DynamicValueHandler {

// Store a primitive value into a dynamic value struct
llvm::Value *storePrimitiveToDynamic(llvm::Value *rhs_value,
                                     llvm::Type *rhs_type,
                                     llvm::Type *dynamic_struct_type,
                                     llvm::IRBuilder<> *builder,
                                     types::Type *rhs_flowwing_type = nullptr);

// Extract the stored value from a dynamic value struct based on its type tag
// Returns the extracted value and its type tag
std::pair<llvm::Value *, llvm::Value *>
extractDynamicValue(llvm::Value *dynamic_value_ptr,
                    llvm::Type *dynamic_struct_type,
                    llvm::IRBuilder<> *builder);

// Cast a stored value (i64) to the appropriate LLVM type based on the type tag
llvm::Value *castStoredValueToType(llvm::Value *stored_value,
                                   DynamicValueType type_tag,
                                   llvm::IRBuilder<> *builder,
                                   llvm::LLVMContext *context);

// Generate a dispatch block that extracts and casts a dynamic value,
// then calls the handler with the casted value and its type tag
[[deprecated]] void generateDynamicDispatch(
    llvm::Value *dynamic_value_ptr, llvm::Type *dynamic_struct_type,
    llvm::IRBuilder<> *builder, llvm::LLVMContext *context,
    const std::function<void(llvm::Value *, DynamicValueType)> &handler);

// Determine the dynamic value type tag from an LLVM type
// flowwing_type is optional but needed to distinguish char (i32) from int32
// (i32)
DynamicValueType getDynamicValueTypeTag(llvm::Type *type,
                                        types::Type *flowwing_type = nullptr);

// Get the FlowWing Type instance from a DynamicValueType enum
types::Type *getTypeFromDynamicValueType(DynamicValueType type_tag);

} // namespace DynamicValueHandler
} // namespace ir_gen
} // namespace flow_wing
