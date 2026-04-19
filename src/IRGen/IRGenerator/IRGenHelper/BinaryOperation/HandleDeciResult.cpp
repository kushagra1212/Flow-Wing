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



#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"

namespace flow_wing::ir_gen {

llvm::Value *IRGenerator::getDecimalResult(llvm::Value *left_value,
                                           llvm::Value *right_value,
                                           lexer::TokenKind operator_kind) {

  auto decimal_left_value = convertToDouble(left_value, left_value->getType());
  auto decimal_right_value =
      convertToDouble(right_value, right_value->getType());

  switch (operator_kind) {
  case lexer::TokenKind::kPlusToken:
    return m_ir_gen_context.getLLVMBuilder()->CreateFAdd(
        decimal_left_value, decimal_right_value, "addition_result");

  case lexer::TokenKind::kMinusToken:
    return m_ir_gen_context.getLLVMBuilder()->CreateFSub(
        decimal_left_value, decimal_right_value, "subtraction_result");

  case lexer::TokenKind::kStarToken:
    return m_ir_gen_context.getLLVMBuilder()->CreateFMul(
        decimal_left_value, decimal_right_value, "multiplication_result");

  case lexer::TokenKind::kSlashToken:
    return m_ir_gen_context.getLLVMBuilder()->CreateFDiv(
        decimal_left_value, decimal_right_value, "division_result");

  default:
    assert(false && "Unsupported decimal operator");
    return nullptr;
  }
}
} // namespace flow_wing::ir_gen