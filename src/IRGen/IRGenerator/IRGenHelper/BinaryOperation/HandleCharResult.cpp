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

llvm::Value *IRGenerator::getCharResult(llvm::Value *left_value,
                                        llvm::Value *right_value,
                                        lexer::TokenKind operator_kind) {
  auto char_left_value = convertToInt32(left_value, left_value->getType());
  auto char_right_value = convertToInt32(right_value, right_value->getType());

  switch (operator_kind) {
  case lexer::TokenKind::kPlusToken:
    return m_ir_gen_context.getLLVMBuilder()->CreateAdd(
        char_left_value, char_right_value, "addition_result");
  default:
    assert(false && "Unsupported char operator");
    return nullptr;
  }
}
} // namespace flow_wing::ir_gen