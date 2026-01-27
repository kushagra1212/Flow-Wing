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

#include "src/IRGen/FlowWingConstants/FlowWingConstants.hpp"
#include "src/IRGen/IRGenContext/IRGenContext.hpp"
#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/utils/LogConfig.h"

// clang-format off
 #include "llvm/IR/Constants.h"
 #include "llvm/IR/IRBuilder.h"
 #include "llvm/IR/Module.h"
 #include "llvm/IR/Type.h"
 #include "llvm/IR/Value.h"
// clang-format on

namespace flow_wing {
namespace ir_gen {

llvm::Value *IRGenerator::convertToString(llvm::Value *value, llvm::Type *type,
                                          bool is_char) {
  auto &builder = *m_ir_gen_context.getLLVMBuilder();
  auto *module = m_ir_gen_context.getLLVMModule();

  // 1. Boolean (i1) -> "true" / "false"
  if (type->isIntegerTy(1)) {
    auto *trueStr = builder.CreateGlobalStringPtr("true");
    auto *falseStr = builder.CreateGlobalStringPtr("false");
    return builder.CreateSelect(value, trueStr, falseStr, "bool_str");
  }

  // 2. Character (i8) -> fg_ctos(char)
  if (is_char) {
    auto *func = module->getFunction(constants::functions::kCtos_fn);

    assert(func && "Function fg_ctos not found");

    return builder.CreateCall(func, {value}, "char_to_str");
  }

  if (type->isIntegerTy(8)) {
    auto *func = module->getFunction(constants::functions::kI8tos_fn);
    assert(func && "Function fg_i8tos not found");
    return builder.CreateCall(func, {value}, "int8_to_str");
  }

  // 3. Integer (i32) -> fg_itos(int)
  if ((type->isIntegerTy(32))) {
    auto *func = module->getFunction(constants::functions::kItos_fn);
    // Safety check if declaration is missing
    assert(func && "Function fg_itos not found");
    return builder.CreateCall(func, {value}, "int_to_str");
  }

  // 4. Long Integer (i64) -> fg_lltos(long long)
  if (type->isIntegerTy(64)) {
    auto *func = module->getFunction(constants::functions::kLltos_fn);
    assert(func && "Function fg_lltos not found");

    return builder.CreateCall(func, {value}, "long_to_str");
  }

  // 5. Float (float) -> Cast to Double -> fg_dtos(double)
  if (type->isFloatTy()) {
    auto *func = module->getFunction(constants::functions::kFtos_fn);
    assert(func && "Function fg_ftos not found");
    return builder.CreateCall(func, {value}, "float_to_str");
  }

  // 6. Double (double) -> fg_dtos(double)
  if (type->isDoubleTy()) {
    auto *func = module->getFunction(constants::functions::kDtos_fn);
    assert(func && "Function fg_dtos not found");
    return builder.CreateCall(func, {value}, "dbl_to_str");
  }

  // 7. String / Pointer (i8*) -> Return as is
  if (type->isPointerTy()) {
    return value;
  }

  // Fallback
  return builder.CreateGlobalStringPtr("<unknown_type>");
}

llvm::Value *IRGenerator::convertToInt64(llvm::Value *value, llvm::Type *type) {
  auto &builder = *m_ir_gen_context.getLLVMBuilder();
  auto *ctx = m_ir_gen_context.getLLVMContext();
  auto *module = m_ir_gen_context.getLLVMModule();
  auto int64_type = llvm::Type::getInt64Ty(*ctx);
  if (type->isIntegerTy(64)) {
    return value;
  }

  if (type->isIntegerTy(1)) {
    return builder.CreateZExt(value, int64_type);
  }

  if (type->isIntegerTy(8) || type->isIntegerTy(32)
      // It handles the char type as well
  ) {
    return builder.CreateSExt(value, int64_type);
  }

  if (type->isFloatTy() || type->isDoubleTy()) {
    return builder.CreateFPToSI(value, int64_type);
  }

  return builder.CreateCall(
      module->getFunction(constants::functions::kString_to_long_fn), {value},
      "string_to_long_long");
}

llvm::Value *IRGenerator::convertToInt32(llvm::Value *value, llvm::Type *type) {
  auto &builder = *m_ir_gen_context.getLLVMBuilder();
  auto *ctx = m_ir_gen_context.getLLVMContext();
  auto *module = m_ir_gen_context.getLLVMModule();
  auto int32_type = llvm::Type::getInt32Ty(*ctx);
  if (type->isIntegerTy(32)) {
    return value;
  }
  if (type->isIntegerTy(1)) {
    return builder.CreateZExt(value, int32_type);
  }

  if (type->isIntegerTy(8)) {
    return builder.CreateSExt(value, int32_type);
  }

  if (type->isIntegerTy(64)) {
    return builder.CreateTrunc(value, int32_type);
  }

  if (type->isFloatTy() || type->isDoubleTy()) {
    return builder.CreateFPToSI(value, int32_type);
  }

  return builder.CreateCall(
      module->getFunction(constants::functions::kString_to_int_fn), {value},
      "string_to_int");
}

llvm::Value *IRGenerator::convertToChar(llvm::Value *value, llvm::Type *type) {
  auto &builder = *m_ir_gen_context.getLLVMBuilder();
  auto *ctx = m_ir_gen_context.getLLVMContext();
  auto *module = m_ir_gen_context.getLLVMModule();
  auto int32_type = llvm::Type::getInt32Ty(*ctx);

  if (type->isIntegerTy(32)) {
    return value;
  }
  if (type->isIntegerTy(1)) {
    return builder.CreateZExt(value, int32_type);
  }

  if (type->isIntegerTy(8)) {
    return builder.CreateSExt(value, int32_type);
  }

  if (type->isIntegerTy(64)) {
    return builder.CreateTrunc(value, int32_type);
  }

  if (type->isFloatTy() || type->isDoubleTy()) {
    return builder.CreateFPToSI(value, int32_type);
  }

  return builder.CreateCall(
      module->getFunction(constants::functions::kString_to_char_fn), {value},
      "string_to_char");
}

llvm::Value *IRGenerator::convertToInt8(llvm::Value *value, llvm::Type *type) {
  auto &builder = *m_ir_gen_context.getLLVMBuilder();
  auto *ctx = m_ir_gen_context.getLLVMContext();
  auto *module = m_ir_gen_context.getLLVMModule();
  auto int8_type = llvm::Type::getInt8Ty(*ctx);
  if (type->isIntegerTy(8)) {
    return value;
  }

  if (type->isIntegerTy(1)) {
    return builder.CreateZExt(value, int8_type);
  }

  if (type->isIntegerTy(32) || type->isIntegerTy(64)) {
    return builder.CreateTrunc(value, int8_type);
  }

  if (type->isFloatTy() || type->isDoubleTy()) {
    return builder.CreateFPToSI(value, int8_type);
  }

  auto *string_to_char_function =
      module->getFunction(constants::functions::kString_to_int_fn);
  assert(string_to_char_function && "Function string_to_char not found");

  auto *callResult =
      builder.CreateCall(string_to_char_function, {value}, "string_to_int_raw");

  return builder.CreateTrunc(callResult, int8_type, "string_to_int_raw");
}

llvm::Value *IRGenerator::convertToDouble(llvm::Value *value,
                                          llvm::Type *type) {
  auto &builder = *m_ir_gen_context.getLLVMBuilder();
  auto *ctx = m_ir_gen_context.getLLVMContext();
  auto *module = m_ir_gen_context.getLLVMModule();
  auto double_type = llvm::Type::getDoubleTy(*ctx);
  if (type->isDoubleTy()) {
    return value;
  }
  if (type->isFloatTy()) {
    return builder.CreateFPExt(value, double_type);
  }
  if (type->isIntegerTy(1)) {
    return builder.CreateUIToFP(value, double_type);
  }

  if (type->isIntegerTy(8) || type->isIntegerTy(32) || type->isIntegerTy(64)) {
    return builder.CreateSIToFP(value, double_type);
  }

  return builder.CreateCall(
      module->getFunction(constants::functions::kString_to_double_fn), {value},
      "string_to_double");
}

llvm::Value *IRGenerator::convertToFloat(llvm::Value *value, llvm::Type *type) {
  auto &builder = *m_ir_gen_context.getLLVMBuilder();
  auto *ctx = m_ir_gen_context.getLLVMContext();
  auto *module = m_ir_gen_context.getLLVMModule();

  // Target type: 32-bit Float
  auto decimal32_type = llvm::Type::getFloatTy(*ctx);

  if (type->isFloatTy()) {
    return value;
  }

  if (type->isDoubleTy()) {
    return builder.CreateFPCast(value, decimal32_type);
  }

  if (type->isIntegerTy(1)) {
    return builder.CreateUIToFP(value, decimal32_type);
  }

  if (type->isIntegerTy(8) || type->isIntegerTy(32) || type->isIntegerTy(64)) {
    return builder.CreateSIToFP(value, decimal32_type);
  }

  auto string_to_float_function =
      module->getFunction(constants::functions::kString_to_float_fn);
  assert(string_to_float_function && "Function string_to_float not found");

  return builder.CreateCall(string_to_float_function, {value},
                            "string_to_float");
}

llvm::Value *IRGenerator::convertToBool(llvm::Value *value, llvm::Type *type) {
  auto &builder = *m_ir_gen_context.getLLVMBuilder();
  auto *module = m_ir_gen_context.getLLVMModule();

  if (type->isIntegerTy(1)) {
    return value;
  }
  if (type->isIntegerTy(8) || type->isIntegerTy(32) || type->isIntegerTy(64)) {
    return builder.CreateICmpNE(value,
                                llvm::ConstantInt::get(value->getType(), 0));
  }

  if (type->isFloatTy() || type->isDoubleTy()) {
    return builder.CreateFCmpONE(value,
                                 llvm::ConstantFP::get(value->getType(), 0.0));
  }

  auto *string_length_function = module->getFunction(
      flow_wing::ir_gen::constants::functions::kString_length_fn);

  assert(string_length_function && "Function string_length not found");

  return builder.CreateICmpNE(
      builder.CreateCall(string_length_function, {value}), builder.getInt32(0),
      "string_length_is_zero");
}

llvm::Value *IRGenerator::convertToTargetType(llvm::Value *value,
                                              types::Type *target_type,
                                              types::Type *source_type) {
  auto *source_llvm_type = value->getType();

  // Integer types
  if (target_type == analysis::Builtins::m_int8_type_instance.get()) {
    return convertToInt8(value, source_llvm_type);
  }
  if (target_type == analysis::Builtins::m_int32_type_instance.get()) {
    return convertToInt32(value, source_llvm_type);
  }
  if (target_type == analysis::Builtins::m_int64_type_instance.get()) {
    return convertToInt64(value, source_llvm_type);
  }

  // Decimal types
  if (target_type == analysis::Builtins::m_deci32_type_instance.get()) {
    return convertToFloat(value, source_llvm_type);
  }
  if (target_type == analysis::Builtins::m_deci_type_instance.get()) {
    return convertToDouble(value, source_llvm_type);
  }

  // Char type
  if (target_type == analysis::Builtins::m_char_type_instance.get()) {
    return convertToChar(value, source_llvm_type);
  }

  // Bool type
  if (target_type == analysis::Builtins::m_bool_type_instance.get()) {
    return convertToBool(value, source_llvm_type);
  }

  // String type - handled separately
  if (target_type == analysis::Builtins::m_str_type_instance.get()) {
    bool is_char =
        source_type == analysis::Builtins::m_char_type_instance.get();
    return convertToString(value, source_llvm_type, is_char);
  }

  if (target_type->getKind() == types::TypeKind::kObject) {
    return getTempObject(target_type, source_type, value);
  }

  return value;
}

} // namespace ir_gen
} // namespace flow_wing