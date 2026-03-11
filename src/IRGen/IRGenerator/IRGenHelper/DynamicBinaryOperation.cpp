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

#include "src/IRGen/IRGenerator/IRGenHelper/DynamicValueHandler.h"
#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundBinaryOperator/BoundBinaryOperator.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"

namespace flow_wing::ir_gen {

uint32_t IRGenerator::getRuntimeOpCode(lexer::TokenKind kind) {
  using namespace lexer;
  switch (kind) {
  // Binary / Unary shared
  case TokenKind::kPlusToken:
    return 1; // OP_ADD
  case TokenKind::kMinusToken:
    return 2; // OP_SUB

  // Binary
  case TokenKind::kStarToken:
    return 3;
  case TokenKind::kSlashToken:
    return 4;
  case TokenKind::kPercentToken:
    return 5;
  case TokenKind::kEqualsEqualsToken:
    return 6;
  case TokenKind::kBangEqualsToken:
    return 7;
  case TokenKind::kLessToken:
    return 8;
  case TokenKind::kLessOrEqualsToken:
    return 9;
  case TokenKind::kGreaterToken:
    return 10;
  case TokenKind::kGreaterOrEqualsToken:
    return 11;
  case TokenKind::kAmpersandAmpersandToken:
    return 12;
  case TokenKind::kPipePipeToken:
    return 13;
  case TokenKind::kSlashSlashToken:
    return 14;

  // Bitwise (&, |, ^) - NEW MAPPINGS
  case TokenKind::kAmpersandToken:
    return 15; // OP_BITWISE_AND
  case TokenKind::kPipeToken:
    return 16; // OP_BITWISE_OR
  case TokenKind::kCaretToken:
    return 17; // OP_BITWISE_XOR

  // Unary Specific
  case TokenKind::kBangToken:
    return 20; // OP_BANG
  case TokenKind::kTildeToken:
    return 21; // OP_TILDE

  default:
    return 0;
  }
}

// 2. Helper to wrap primitives into a Dynamic struct alloca
llvm::Value *IRGenerator::ensureDynamic(llvm::Value *value, types::Type *type) {
  if (type->isDynamic()) {
    return value;
  }

  llvm::Type *dynType = m_ir_gen_context.getTypeBuilder()->getLLVMType(
      analysis::Builtins::m_dynamic_type_instance.get());

  // Create temp storage
  llvm::Value *alloca =
      m_ir_gen_context.createAlloca(dynType, "dyn_wrapper_temp");

  llvm::IRBuilder<> *builder = m_ir_gen_context.getLLVMBuilder().get();

  llvm::Value *stored = DynamicValueHandler::storePrimitiveToDynamic(
      value, value->getType(), dynType, builder, type);

  builder->CreateStore(stored, alloca);
  return alloca;
}

llvm::Value *IRGenerator::getDynamicBinaryResult(llvm::Value *left_value,
                                                 llvm::Value *right_value,
                                                 lexer::TokenKind operator_kind,
                                                 types::Type *left_type,
                                                 types::Type *right_type) {

  llvm::Value *left_dyn_ptr = ensureDynamic(left_value, left_type);
  llvm::Value *right_dyn_ptr = ensureDynamic(right_value, right_type);

  llvm::Type *dynStructType = m_ir_gen_context.getTypeBuilder()->getLLVMType(
      analysis::Builtins::m_dynamic_type_instance.get());

  llvm::FunctionCallee func =
      m_ir_gen_context.getLLVMModule()->getFunction("fg_perform_dynamic_op");

  assert(func && "fg_perform_dynamic_op function not found");

  uint32_t opCode = getRuntimeOpCode(operator_kind);
  llvm::Value *opCodeVal = llvm::ConstantInt::get(
      llvm::Type::getInt32Ty(*m_ir_gen_context.getLLVMContext()), opCode);

  // Allocate result struct on stack and pass as first argument (sret pattern)
  llvm::Value *resultAlloca =
      m_ir_gen_context.createAlloca(dynStructType, "dyn_op_res_ptr");
  m_ir_gen_context.getLLVMBuilder()->CreateCall(
      func, {resultAlloca, left_dyn_ptr, right_dyn_ptr, opCodeVal});

  return resultAlloca;
}

} // namespace flow_wing::ir_gen
