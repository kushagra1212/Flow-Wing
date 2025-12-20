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


#include "IRGenerator.hpp"
#include "src/IRGen/FlowWingConstants/FlowWingConstants.hpp"
#include "src/IRGen/IRGenContext/IRGenContext.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"

// clang-format off
#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
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
    auto *func = module->getFunction("fg_ctos");
    if (!func) {
      auto *charPtrTy = llvm::Type::getInt8PtrTy(*ctx);
      auto *i8Ty = llvm::Type::getInt8Ty(*ctx);
      func = llvm::Function::Create(
          llvm::FunctionType::get(charPtrTy, {i8Ty}, false),
          llvm::Function::ExternalLinkage, "fg_ctos", module);
    }
    return builder.CreateCall(func, {value}, "char_to_str");
  }

  // 3. Integer (i32) -> fg_itos(int)
  if (type->isIntegerTy(32)) {
    auto *func = module->getFunction("fg_itos");
    // Safety check if declaration is missing
    if (!func) {
      auto *charPtrTy = llvm::Type::getInt8PtrTy(*ctx);
      auto *i32Ty = llvm::Type::getInt32Ty(*ctx);
      func = llvm::Function::Create(
          llvm::FunctionType::get(charPtrTy, {i32Ty}, false),
          llvm::Function::ExternalLinkage, "fg_itos", module);
    }
    return builder.CreateCall(func, {value}, "int_to_str");
  }

  // 4. Long Integer (i64) -> fg_lltos(long long)
  if (type->isIntegerTy(64)) {
    auto *func = module->getFunction("fg_lltos");
    if (!func) {
      auto *charPtrTy = llvm::Type::getInt8PtrTy(*ctx);
      auto *i64Ty = llvm::Type::getInt64Ty(*ctx);
      func = llvm::Function::Create(
          llvm::FunctionType::get(charPtrTy, {i64Ty}, false),
          llvm::Function::ExternalLinkage, "fg_lltos", module);
    }
    return builder.CreateCall(func, {value}, "long_to_str");
  }

  // 5. Float (float) -> Cast to Double -> fg_dtos(double)
  if (type->isFloatTy()) {
    auto *doubleVal = builder.CreateFPExt(value, llvm::Type::getDoubleTy(*ctx),
                                          "float_to_double");
    auto *func = module->getFunction("fg_dtos");
    if (!func) {
      auto *charPtrTy = llvm::Type::getInt8PtrTy(*ctx);
      auto *dblTy = llvm::Type::getDoubleTy(*ctx);
      func = llvm::Function::Create(
          llvm::FunctionType::get(charPtrTy, {dblTy}, false),
          llvm::Function::ExternalLinkage, "fg_dtos", module);
    }
    return builder.CreateCall(func, {doubleVal}, "float_to_str");
  }

  // 6. Double (double) -> fg_dtos(double)
  if (type->isDoubleTy()) {
    auto *func = module->getFunction("fg_dtos");
    if (!func) {
      auto *charPtrTy = llvm::Type::getInt8PtrTy(*ctx);
      auto *dblTy = llvm::Type::getDoubleTy(*ctx);
      func = llvm::Function::Create(
          llvm::FunctionType::get(charPtrTy, {dblTy}, false),
          llvm::Function::ExternalLinkage, "fg_dtos", module);
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

llvm::Value *IRGenerator::getDefaultValue(types::Type *type) {

  if (type == analysis::Builtins::m_int32_type_instance.get()) {
    return m_ir_gen_context.getLLVMBuilder()->getInt32(0);
  }
  if (type == analysis::Builtins::m_int64_type_instance.get()) {
    return m_ir_gen_context.getLLVMBuilder()->getInt64(0);
  }

  if (type == analysis::Builtins::m_int8_type_instance.get()) {
    return m_ir_gen_context.getLLVMBuilder()->getInt8(0);
  }

  if (type == analysis::Builtins::m_deci_type_instance.get()) {
    return llvm::ConstantFP::get(*m_ir_gen_context.getLLVMContext(),
                                 llvm::APFloat(0.0));
  }
  if (type == analysis::Builtins::m_deci32_type_instance.get()) {
    return llvm::ConstantFP::get(*m_ir_gen_context.getLLVMContext(),
                                 llvm::APFloat(static_cast<float>(0.0)));
  }
  if (type == analysis::Builtins::m_bool_type_instance.get()) {
    return m_ir_gen_context.getLLVMBuilder()->getInt1(false);
  }

  if (type == analysis::Builtins::m_int8_type_instance.get()) {
    return m_ir_gen_context.getLLVMBuilder()->CreateGlobalStringPtr("");
  }
  if (type == analysis::Builtins::m_str_type_instance.get()) {
    return m_ir_gen_context.getLLVMBuilder()->CreateGlobalStringPtr("");
  }
  if (type == analysis::Builtins::m_nthg_type_instance.get()) {
    return nullptr;
  }
  if (type == analysis::Builtins::m_nirast_type_instance.get()) {
    return llvm::ConstantPointerNull::get(
        llvm::Type::getInt8PtrTy(*m_ir_gen_context.getLLVMContext()));
  }

  assert(false && "Unsupported type [getDefaultValue]");
  return nullptr;
}

} // namespace ir_gen
} // namespace flow_wing