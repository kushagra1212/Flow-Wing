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

namespace flow_wing::ir_gen {

llvm::Value *IRGenerator::getIntResult(llvm::Value *left_value,
                                       llvm::Value *right_value,
                                       lexer::TokenKind operator_kind) {

  switch (operator_kind) {
  case lexer::TokenKind::kPlusToken:
    return m_ir_gen_context.getLLVMBuilder()->CreateAdd(left_value, right_value,
                                                        "addition_result");
  case lexer::TokenKind::kMinusToken:
    return m_ir_gen_context.getLLVMBuilder()->CreateSub(left_value, right_value,
                                                        "subtraction_result");
  case lexer::TokenKind::kStarToken:
    return m_ir_gen_context.getLLVMBuilder()->CreateMul(
        left_value, right_value, "multiplication_result");
  case lexer::TokenKind::kSlashSlashToken:
    return m_ir_gen_context.getLLVMBuilder()->CreateSDiv(
        left_value, right_value, "integer_division_result");
  case lexer::TokenKind::kPercentToken:
    return m_ir_gen_context.getLLVMBuilder()->CreateSRem(
        left_value, right_value, "modulus_result");
  case lexer::TokenKind::kAmpersandToken:
    return m_ir_gen_context.getLLVMBuilder()->CreateAnd(left_value, right_value,
                                                        "bitwise_and_result");
  case lexer::TokenKind::kPipeToken:
    return m_ir_gen_context.getLLVMBuilder()->CreateOr(left_value, right_value,
                                                       "bitwise_or_result");
  case lexer::TokenKind::kCaretToken:
    return m_ir_gen_context.getLLVMBuilder()->CreateXor(left_value, right_value,
                                                        "bitwise_xor_result");
  default:
    assert(false && "Unsupported integer operator");
    return nullptr;
  }
}
} // namespace flow_wing::ir_gen