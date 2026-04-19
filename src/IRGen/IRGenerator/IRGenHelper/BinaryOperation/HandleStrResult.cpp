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

llvm::Value *IRGenerator::getStringResult(llvm::Value *left_value,
                                          llvm::Value *right_value,
                                          lexer::TokenKind operator_kind,
                                          types::Type *left_type,
                                          types::Type *right_type) {

  auto is_left_type_char =
      left_type == analysis::Builtins::m_char_type_instance.get();
  auto is_right_type_char =
      right_type == analysis::Builtins::m_char_type_instance.get();

  auto string_left_value =
      convertToString(left_value, left_value->getType(), is_left_type_char);
  auto string_right_value =
      convertToString(right_value, right_value->getType(), is_right_type_char);

  switch (operator_kind) {
  case lexer::TokenKind::kPlusToken: {
    auto string_concatenate_func =
        m_ir_gen_context.getLLVMModule()->getFunction(
            constants::functions::kConcat_strings_fn);

    return m_ir_gen_context.getLLVMBuilder()->CreateCall(
        string_concatenate_func, {string_left_value, string_right_value},
        "string_concatenate_result");
  }
  default:
    assert(false && "Unsupported string operator");
    return nullptr;
  }
}
} // namespace flow_wing::ir_gen