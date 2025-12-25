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

#include "src/IRGen/IRGenContext/IRGenContext.hpp"
#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"

// clang-format off
 #include "llvm/IR/Constants.h"
 #include "llvm/IR/IRBuilder.h"
 #include "llvm/IR/Type.h"
 #include "llvm/IR/Value.h"
// clang-format on

namespace flow_wing {
namespace ir_gen {

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