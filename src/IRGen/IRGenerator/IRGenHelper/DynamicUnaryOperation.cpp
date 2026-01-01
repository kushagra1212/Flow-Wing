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
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"

namespace flow_wing::ir_gen {
llvm::Value *IRGenerator::getDynamicUnaryResult(llvm::Value *value,
                                                lexer::TokenKind operator_kind,
                                                types::Type *expression_type) {

  llvm::Value *dyn_ptr = ensureDynamic(value, expression_type);

  // DynamicValue fg_perform_dynamic_unary_op(DynamicValue*, int)
  llvm::Type *dynStructType = m_ir_gen_context.getTypeBuilder()->getLLVMType(
      analysis::Builtins::m_dynamic_type_instance.get());

  llvm::FunctionCallee func = m_ir_gen_context.getLLVMModule()->getFunction(
      "fg_perform_dynamic_unary_op");

  assert(func && "fg_perform_dynamic_unary_op function not found");

  uint32_t opCode = getRuntimeOpCode(operator_kind);
  llvm::Value *opCodeVal = llvm::ConstantInt::get(
      llvm::Type::getInt32Ty(*m_ir_gen_context.getLLVMContext()), opCode);

  llvm::Value *resultStruct = m_ir_gen_context.getLLVMBuilder()->CreateCall(
      func, {dyn_ptr, opCodeVal}, "dyn_unary_res");

  llvm::Value *resultAlloca =
      m_ir_gen_context.createAlloca(dynStructType, "dyn_unary_res_ptr");
  m_ir_gen_context.getLLVMBuilder()->CreateStore(resultStruct, resultAlloca);

  return resultAlloca;
}

} // namespace flow_wing::ir_gen
