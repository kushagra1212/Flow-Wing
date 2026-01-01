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

#include "DynamicValueHandler.h"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include <cassert>

namespace flow_wing {
namespace ir_gen {
namespace DynamicValueHandler {

DynamicValueType getDynamicValueTypeTag(llvm::Type *type,
                                        types::Type *flowwing_type) {
  //  char (i32) from int32 (i32)
  if (flowwing_type == analysis::Builtins::m_char_type_instance.get()) {
    return DynamicValueType::CHAR;
  }
  if (type->isIntegerTy(8)) {
    return DynamicValueType::INT8;
  }
  if (type->isIntegerTy(32)) {
    return DynamicValueType::INT32;
  }
  if (type->isIntegerTy(64)) {
    return DynamicValueType::INT64;
  }
  if (type->isFloatTy()) {
    return DynamicValueType::FLOAT32;
  }
  if (type->isDoubleTy()) {
    return DynamicValueType::FLOAT64;
  }
  if (type->isIntegerTy(1)) {
    return DynamicValueType::BOOLEAN;
  }
  if (type->isPointerTy()) {
    return DynamicValueType::STRING;
  }
  assert(false && "Unsupported type for dynamic value");
  return DynamicValueType::NIRAST;
}

llvm::Value *storePrimitiveToDynamic(llvm::Value *rhs_value,
                                     llvm::Type *rhs_type,
                                     llvm::Type *dynamic_struct_type,
                                     llvm::IRBuilder<> *builder,
                                     types::Type *rhs_flowwing_type) {
  llvm::LLVMContext *context = &builder->getContext();

  // Check if it's a null pointer (Nirast)
  if (llvm::isa<llvm::ConstantPointerNull>(rhs_value)) {
    llvm::ConstantInt *type_tag =
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context),
                               static_cast<int>(DynamicValueType::NIRAST));

    llvm::Value *undef_dynamic = llvm::UndefValue::get(dynamic_struct_type);
    llvm::Value *inserted_tag = builder->CreateInsertValue(
        undef_dynamic, type_tag, {0}, "insertedTagValue");

    llvm::Value *nil_value =
        llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context), 0);
    return builder->CreateInsertValue(inserted_tag, nil_value, {1},
                                      "insertedDataValue");
  }

  DynamicValueType type_tag =
      getDynamicValueTypeTag(rhs_type, rhs_flowwing_type);

  llvm::ConstantInt *tag_value = llvm::ConstantInt::get(
      llvm::Type::getInt32Ty(*context), static_cast<uint32_t>(type_tag));

  llvm::Value *undef_dynamic = llvm::UndefValue::get(dynamic_struct_type);
  llvm::Value *inserted_tag = builder->CreateInsertValue(
      undef_dynamic, tag_value, {0}, "insertedTagValue");

  llvm::Value *value_to_store = nullptr;

  // Convert the value to i64 for storage
  if (type_tag == DynamicValueType::INT8 ||
      type_tag == DynamicValueType::INT32 ||
      type_tag == DynamicValueType::INT64 ||
      type_tag == DynamicValueType::CHAR) {
    // Sign-extend to i64
    if (rhs_type->isIntegerTy(8)) {
      value_to_store = builder->CreateSExt(
          rhs_value, llvm::Type::getInt64Ty(*context), "int8_as_i64");
    } else if (rhs_type->isIntegerTy(32)) {
      value_to_store = builder->CreateSExt(
          rhs_value, llvm::Type::getInt64Ty(*context), "int32_as_i64");
    } else {
      value_to_store = rhs_value; // Already i64
    }
  } else if (type_tag == DynamicValueType::BOOLEAN) {
    // Zero-extend boolean to i64
    value_to_store = builder->CreateZExt(
        rhs_value, llvm::Type::getInt64Ty(*context), "bool_as_i64");
  } else if (type_tag == DynamicValueType::STRING) {
    // Convert pointer to i64
    value_to_store = builder->CreatePtrToInt(
        rhs_value, llvm::Type::getInt64Ty(*context), "ptr_as_i64");
  } else if (type_tag == DynamicValueType::FLOAT32) {
    // Bitcast float to i32, then zero-extend to i64
    llvm::Value *bits_as_int32 = builder->CreateBitCast(
        rhs_value, llvm::Type::getInt32Ty(*context), "float32_as_i32");
    value_to_store = builder->CreateZExt(
        bits_as_int32, llvm::Type::getInt64Ty(*context), "float32_as_i64");
  } else if (type_tag == DynamicValueType::FLOAT64) {
    // Bitcast double to i64
    value_to_store = builder->CreateBitCast(
        rhs_value, llvm::Type::getInt64Ty(*context), "float64_as_i64");
  } else {
    assert(false && "Unsupported type for dynamic value storage");
  }

  return builder->CreateInsertValue(inserted_tag, value_to_store, {1},
                                    "insertedDataValue");
}

std::pair<llvm::Value *, llvm::Value *>
extractDynamicValue(llvm::Value *dynamic_value_ptr,
                    llvm::Type *dynamic_struct_type,
                    llvm::IRBuilder<> *builder) {
  llvm::Value *loaded_value = builder->CreateLoad(
      dynamic_struct_type, dynamic_value_ptr, "loadedValue");

  // Extract the type tag (first field, i32)
  llvm::Value *type_tag =
      builder->CreateExtractValue(loaded_value, {0}, "typeTag");

  // Extract the stored value (second field, i64)
  llvm::Value *value_storage =
      builder->CreateExtractValue(loaded_value, {1}, "valueStorage");

  return {value_storage, type_tag};
}

llvm::Value *castStoredValueToType(llvm::Value *stored_value,
                                   DynamicValueType type_tag,
                                   llvm::IRBuilder<> *builder,
                                   llvm::LLVMContext *context) {
  switch (type_tag) {
  case DynamicValueType::INT8: {
    return builder->CreateTrunc(stored_value, llvm::Type::getInt8Ty(*context),
                                "int8Value");
  }
  case DynamicValueType::INT32: {
    return builder->CreateTrunc(stored_value, llvm::Type::getInt32Ty(*context),
                                "int32Value");
  }
  case DynamicValueType::CHAR: {
    return builder->CreateTrunc(stored_value, llvm::Type::getInt32Ty(*context),
                                "charValue");
  }
  case DynamicValueType::INT64: {
    return stored_value; // Already i64
  }
  case DynamicValueType::BOOLEAN: {
    // Compare with 0 to get i1
    return builder->CreateICmpNE(
        stored_value,
        llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context), 0),
        "boolValue");
  }
  case DynamicValueType::STRING: {
    return builder->CreateIntToPtr(
        stored_value, llvm::Type::getInt8PtrTy(*context), "stringPtr");
  }
  case DynamicValueType::FLOAT32: {
    // Truncate to i32, then bitcast to float
    llvm::Value *bits_as_int32 = builder->CreateTrunc(
        stored_value, llvm::Type::getInt32Ty(*context), "float32_bits");
    return builder->CreateBitCast(
        bits_as_int32, llvm::Type::getFloatTy(*context), "float32Value");
  }
  case DynamicValueType::FLOAT64: {
    return builder->CreateBitCast(
        stored_value, llvm::Type::getDoubleTy(*context), "float64Value");
  }
  case DynamicValueType::NIRAST: {
    return llvm::ConstantPointerNull::get(llvm::Type::getInt8PtrTy(*context));
  }
  }
  assert(false && "Unsupported dynamic value type tag");
  return nullptr;
}

void generateDynamicDispatch(
    llvm::Value *dynamic_value_ptr, llvm::Type *dynamic_struct_type,
    llvm::IRBuilder<> *builder, llvm::LLVMContext *context,
    const std::function<void(llvm::Value *, DynamicValueType)> &handler) {
  llvm::Function *parent_func = builder->GetInsertBlock()->getParent();

  struct TypeHandler {
    llvm::BasicBlock *check_bb;
    llvm::BasicBlock *handle_bb;
    DynamicValueType type;
  };

  TypeHandler handlers[] = {
      {llvm::BasicBlock::Create(*context, "check.string", parent_func),
       llvm::BasicBlock::Create(*context, "handle.string", parent_func),
       DynamicValueType::STRING},
      {llvm::BasicBlock::Create(*context, "check.char", parent_func),
       llvm::BasicBlock::Create(*context, "handle.char", parent_func),
       DynamicValueType::CHAR},
      {llvm::BasicBlock::Create(*context, "check.int32", parent_func),
       llvm::BasicBlock::Create(*context, "handle.int32", parent_func),
       DynamicValueType::INT32},
      {llvm::BasicBlock::Create(*context, "check.int64", parent_func),
       llvm::BasicBlock::Create(*context, "handle.int64", parent_func),
       DynamicValueType::INT64},
      {llvm::BasicBlock::Create(*context, "check.float32", parent_func),
       llvm::BasicBlock::Create(*context, "handle.float32", parent_func),
       DynamicValueType::FLOAT32},
      {llvm::BasicBlock::Create(*context, "check.float64", parent_func),
       llvm::BasicBlock::Create(*context, "handle.float64", parent_func),
       DynamicValueType::FLOAT64},
      {llvm::BasicBlock::Create(*context, "check.boolean", parent_func),
       llvm::BasicBlock::Create(*context, "handle.boolean", parent_func),
       DynamicValueType::BOOLEAN},
      {llvm::BasicBlock::Create(*context, "check.int8", parent_func),
       llvm::BasicBlock::Create(*context, "handle.int8", parent_func),
       DynamicValueType::INT8},
      {llvm::BasicBlock::Create(*context, "check.nirast", parent_func),
       llvm::BasicBlock::Create(*context, "handle.nirast", parent_func),
       DynamicValueType::NIRAST},
  };

  llvm::BasicBlock *merge_bb =
      llvm::BasicBlock::Create(*context, "merge", parent_func);

  auto [value_storage, type_tag] =
      extractDynamicValue(dynamic_value_ptr, dynamic_struct_type, builder);

  builder->CreateBr(handlers[0].check_bb);

  const int num_types = sizeof(handlers) / sizeof(handlers[0]);

  for (int i = 0; i < num_types; i++) {
    // Check the type
    builder->SetInsertPoint(handlers[i].check_bb);
    llvm::Value *is_type = builder->CreateICmpEQ(
        type_tag,
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context),
                               static_cast<uint32_t>(handlers[i].type)));
    builder->CreateCondBr(is_type, handlers[i].handle_bb,
                          i == num_types - 1 ? merge_bb
                                             : handlers[i + 1].check_bb);

    // Handle the type
    builder->SetInsertPoint(handlers[i].handle_bb);
    llvm::Value *casted_value = castStoredValueToType(
        value_storage, handlers[i].type, builder, context);
    handler(casted_value, handlers[i].type);
    builder->CreateBr(merge_bb);
  }

  builder->SetInsertPoint(merge_bb);
}

types::Type *getTypeFromDynamicValueType(DynamicValueType type_tag) {
  switch (type_tag) {
  case DynamicValueType::INT8:
    return analysis::Builtins::m_int8_type_instance.get();
  case DynamicValueType::INT32:
    return analysis::Builtins::m_int32_type_instance.get();
  case DynamicValueType::INT64:
    return analysis::Builtins::m_int64_type_instance.get();
  case DynamicValueType::FLOAT32:
    return analysis::Builtins::m_deci32_type_instance.get();
  case DynamicValueType::FLOAT64:
    return analysis::Builtins::m_deci_type_instance.get();
  case DynamicValueType::BOOLEAN:
    return analysis::Builtins::m_bool_type_instance.get();
  case DynamicValueType::STRING:
    return analysis::Builtins::m_str_type_instance.get();
  case DynamicValueType::NIRAST:
    return analysis::Builtins::m_nirast_type_instance.get();
  case DynamicValueType::CHAR:
    return analysis::Builtins::m_char_type_instance.get();
  }
  assert(false && "Unsupported dynamic value type tag");
  return nullptr;
}

} // namespace DynamicValueHandler
} // namespace ir_gen
} // namespace flow_wing
