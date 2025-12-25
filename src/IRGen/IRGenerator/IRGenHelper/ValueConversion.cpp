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

#include "src/IRGen/FlowWingConstants/FlowWingConstants.hpp"
#include "src/IRGen/IRGenContext/IRGenContext.hpp"
#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"

// clang-format off
 #include "llvm/IR/Constants.h"
 #include "llvm/IR/IRBuilder.h"
 #include "llvm/IR/Module.h"
 #include "llvm/IR/Type.h"
 #include "llvm/IR/Value.h"
// clang-format on

namespace flow_wing {
namespace ir_gen {

llvm::Value *IRGenerator::convertToString(llvm::Value *value,
                                          llvm::Type *type) {
  auto &builder = *m_ir_gen_context.getLLVMBuilder();
  auto *module = m_ir_gen_context.getLLVMModule();
  auto *ctx = m_ir_gen_context.getLLVMContext();

  // 1. Boolean (i1) -> "true" / "false"
  if (type->isIntegerTy(1)) {
    auto *trueStr = builder.CreateGlobalStringPtr("true");
    auto *falseStr = builder.CreateGlobalStringPtr("false");
    return builder.CreateSelect(value, trueStr, falseStr, "bool_str");
  }

  // 2. Character (i8) -> fg_ctos(char)
  if (type->isIntegerTy(8)) {
    auto *func = module->getFunction(constants::functions::kCtos_fn);
    if (!func) {
      auto *charPtrTy = llvm::Type::getInt8PtrTy(*ctx);
      auto *i8Ty = llvm::Type::getInt8Ty(*ctx);
      func = llvm::Function::Create(
          llvm::FunctionType::get(charPtrTy, {i8Ty}, false),
          llvm::Function::ExternalLinkage, constants::functions::kCtos_fn,
          module);
    }
    return builder.CreateCall(func, {value}, "char_to_str");
  }

  // 3. Integer (i32) -> fg_itos(int)
  if (type->isIntegerTy(32)) {
    auto *func = module->getFunction(constants::functions::kItos_fn);
    // Safety check if declaration is missing
    if (!func) {
      auto *charPtrTy = llvm::Type::getInt8PtrTy(*ctx);
      auto *i32Ty = llvm::Type::getInt32Ty(*ctx);
      func = llvm::Function::Create(
          llvm::FunctionType::get(charPtrTy, {i32Ty}, false),
          llvm::Function::ExternalLinkage, constants::functions::kItos_fn,
          module);
    }
    return builder.CreateCall(func, {value}, "int_to_str");
  }

  // 4. Long Integer (i64) -> fg_lltos(long long)
  if (type->isIntegerTy(64)) {
    auto *func = module->getFunction(constants::functions::kLltos_fn);
    if (!func) {
      auto *charPtrTy = llvm::Type::getInt8PtrTy(*ctx);
      auto *i64Ty = llvm::Type::getInt64Ty(*ctx);
      func = llvm::Function::Create(
          llvm::FunctionType::get(charPtrTy, {i64Ty}, false),
          llvm::Function::ExternalLinkage, constants::functions::kLltos_fn,
          module);
    }
    return builder.CreateCall(func, {value}, "long_to_str");
  }

  // 5. Float (float) -> Cast to Double -> fg_dtos(double)
  if (type->isFloatTy()) {
    auto *func = module->getFunction(constants::functions::kFtos_fn);
    if (!func) {
      auto *charPtrTy = llvm::Type::getInt8PtrTy(*ctx);
      func = llvm::Function::Create(
          llvm::FunctionType::get(charPtrTy, {type}, false),
          llvm::Function::ExternalLinkage, constants::functions::kFtos_fn,
          module);
    }
    return builder.CreateCall(func, {value}, "float_to_str");
  }

  // 6. Double (double) -> fg_dtos(double)
  if (type->isDoubleTy()) {
    auto *func = module->getFunction(constants::functions::kDtos_fn);
    if (!func) {
      auto *charPtrTy = llvm::Type::getInt8PtrTy(*ctx);
      auto *dblTy = llvm::Type::getDoubleTy(*ctx);
      func = llvm::Function::Create(
          llvm::FunctionType::get(charPtrTy, {dblTy}, false),
          llvm::Function::ExternalLinkage, constants::functions::kDtos_fn,
          module);
    }
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

  if (type->isIntegerTy(1) || type->isIntegerTy(8) || type->isIntegerTy(32)) {
    return builder.CreateZExt(value, int64_type);
  }

  if (type->isFloatTy() || type->isDoubleTy()) {
    return builder.CreateFPToSI(value, int64_type);
  }

  return builder.CreateCall(
      module->getFunction(constants::functions::kString_to_long_fn), {value},
      "string_to_long_long");
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
    // Converts 'true' (1) to 1.0, not -1.0
    return builder.CreateUIToFP(value, decimal32_type);
  }

  if (type->isIntegerTy(8) || type->isIntegerTy(32) || type->isIntegerTy(64)) {
    return builder.CreateSIToFP(value, decimal32_type);
  }

  return builder.CreateCall(
      module->getFunction(constants::functions::kString_to_float_fn), {value},
      "string_to_float");
}

} // namespace ir_gen
} // namespace flow_wing