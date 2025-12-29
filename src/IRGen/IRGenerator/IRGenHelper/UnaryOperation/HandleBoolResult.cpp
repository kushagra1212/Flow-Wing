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
#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/utils/LogConfig.h"
namespace flow_wing::ir_gen {

llvm::Value *IRGenerator::getBoolResult(llvm::Value *value,
                                        lexer::TokenKind operator_kind,
                                        types::Type *expression_type) {
  switch (operator_kind) {
  case lexer::TokenKind::kBangToken: {
    if (expression_type == analysis::Builtins::m_bool_type_instance.get()) {
      return m_ir_gen_context.getLLVMBuilder()->CreateNot(
          value, "logical_negation_result");
    }

    if (expression_type == analysis::Builtins::m_int32_type_instance.get() ||
        expression_type == analysis::Builtins::m_char_type_instance.get()) {
      return m_ir_gen_context.getLLVMBuilder()->CreateICmpEQ(
          value,
          llvm::ConstantInt::get(
              m_ir_gen_context.getLLVMBuilder()->getInt32Ty(), 0),
          "is_zero_result");
    }

    if (expression_type == analysis::Builtins::m_int8_type_instance.get()) {
      return m_ir_gen_context.getLLVMBuilder()->CreateICmpEQ(
          value,
          llvm::ConstantInt::get(m_ir_gen_context.getLLVMBuilder()->getInt8Ty(),
                                 0),
          "is_zero_result");
    }

    if (expression_type == analysis::Builtins::m_int64_type_instance.get()) {
      return m_ir_gen_context.getLLVMBuilder()->CreateICmpEQ(
          value,
          llvm::ConstantInt::get(
              m_ir_gen_context.getLLVMBuilder()->getInt64Ty(), 0),
          "is_zero_result");
    }

    if (expression_type == analysis::Builtins::m_deci_type_instance.get()) {
      return m_ir_gen_context.getLLVMBuilder()->CreateFCmpOEQ(
          value,
          llvm::ConstantFP::get(
              m_ir_gen_context.getLLVMBuilder()->getDoubleTy(), 0.0),
          "is_zero_result");
    }

    if (expression_type == analysis::Builtins::m_deci32_type_instance.get()) {
      return m_ir_gen_context.getLLVMBuilder()->CreateFCmpOEQ(
          value,
          llvm::ConstantFP::get(m_ir_gen_context.getLLVMBuilder()->getFloatTy(),
                                0.0),
          "is_zero_result");
    }

    if (expression_type == analysis::Builtins::m_nirast_type_instance.get()) {
      return m_ir_gen_context.getLLVMBuilder()->getTrue();
    }

    if (expression_type == analysis::Builtins::m_str_type_instance.get()) {
      auto *string_length_function =
          m_ir_gen_context.getLLVMModule()->getFunction(
              flow_wing::ir_gen::constants::functions::kString_length_fn);
      assert(string_length_function && "Function string_length not found");
      return m_ir_gen_context.getLLVMBuilder()->CreateICmpEQ(
          m_ir_gen_context.getLLVMBuilder()->CreateCall(string_length_function,
                                                        {value}),
          m_ir_gen_context.getLLVMBuilder()->getInt32(0), "is_zero_result");
    }
  }
  default: {
    assert(false && "Unsupported unary operator for bool result type");
  }
  }
}
} // namespace flow_wing::ir_gen