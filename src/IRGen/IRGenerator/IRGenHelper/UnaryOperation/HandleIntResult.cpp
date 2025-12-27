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

llvm::Value *IRGenerator::getIntResult(llvm::Value *value,
                                       lexer::TokenKind operator_kind) {
  switch (operator_kind) {
  case lexer::TokenKind::kPlusToken: {
    return value;
  }
  case lexer::TokenKind::kMinusToken: {
    return m_ir_gen_context.getLLVMBuilder()->CreateNeg(value,
                                                        "negation_result");
  }
  case lexer::TokenKind::kTildeToken: {
    return m_ir_gen_context.getLLVMBuilder()->CreateNot(
        value, "bitwise_negation_result");
  }
  default: {
    assert(false && "Unsupported unary operator for int32 result type");
  }
  }
}
} // namespace flow_wing::ir_gen