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

#include "src/IRGen/FlowWingConstants/FlowWingConstants.hpp"
#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundIndexExpression/BoundIndexExpression.h"
#include "src/common/types/ArrayType/ArrayType.hpp"
#include "src/common/types/Type.hpp"
#include "src/utils/LogConfig.h"
namespace flow_wing {
namespace ir_gen {

void IRGenerator::visit(
    [[maybe_unused]] binding::BoundIndexExpression *statement) {
  CODEGEN_DEBUG_LOG("Visiting Bound Index Expression", "IR GENERATION");
  statement->getLeftExpression()->accept(this);

  auto *array_type = static_cast<types::ArrayType *>(m_last_type);
  auto *left_llvm_type =
      m_ir_gen_context.getTypeBuilder()->getLLVMType(m_last_type);

  llvm::Value *left_ptr = nullptr;
  if (auto *gep = llvm::dyn_cast<llvm::GEPOperator>(m_last_value)) {
    if (gep->getSourceElementType()->isStructTy() ||
        gep->getSourceElementType()->isArrayTy()) {
      left_ptr = m_last_value;
    }
  }
  if (!left_ptr) {
    left_ptr = resolvePtr(m_last_value, m_last_type);
  }

  clearLast();

  std::vector<llvm::Value *> indices = {
      m_ir_gen_context.getLLVMBuilder()->getInt64(0)};

  types::Type *final_index_type = nullptr;
  size_t dimension_index = 0;

  llvm::Function *panic_func = m_ir_gen_context.getLLVMModule()->getFunction(
      std::string(ir_gen::constants::functions::kIndex_out_of_bounds_fn));

  assert(panic_func && "panic_func is null in index expression ir gen");

  final_index_type = statement->getType().get();
  for (const auto &dimension_clause_expression :
       statement->getDimensionClauseExpressions()) {
    CODEGEN_DEBUG_LOG("Final Index Expression Type",
                      final_index_type->getName());
    dimension_clause_expression->accept(this);
    llvm::Value *index_val = resolveValue(m_last_value, m_last_type);
    clearLast();

    {

      auto builder = m_ir_gen_context.getLLVMBuilder().get();

      index_val = builder->CreateIntCast(index_val, builder->getInt64Ty(), true,
                                         "idx_promoted");

      llvm::Value *size_val = m_ir_gen_context.getLLVMBuilder()->getInt64(
          array_type->getDimensions()[dimension_index]);

      CODEGEN_DEBUG_LOG("Dimension Index", dimension_index,
                        "array_type->getDimensions()",
                        array_type->getDimensions(), index_val, size_val);

      llvm::Function *parent_func = builder->GetInsertBlock()->getParent();
      llvm::BasicBlock *block_ok = llvm::BasicBlock::Create(
          *m_ir_gen_context.getLLVMContext(), "idx_ok", parent_func);
      llvm::BasicBlock *block_fail = llvm::BasicBlock::Create(
          *m_ir_gen_context.getLLVMContext(), "idx_fail", parent_func);

      llvm::Value *cmp =
          builder->CreateICmpUGE(index_val, size_val, "bounds_check");
      builder->CreateCondBr(cmp, block_fail, block_ok);

      builder->SetInsertPoint(block_fail);
      builder->CreateCall(panic_func, {index_val, size_val});
      builder->CreateUnreachable(); // Runtime will exit, but LLVM needs to know
                                    // control stops.

      builder->SetInsertPoint(block_ok);
    }

    indices.push_back(index_val);
    dimension_index++;
  }

  m_last_value = m_ir_gen_context.getLLVMBuilder()->CreateInBoundsGEP(
      left_llvm_type, left_ptr, indices, "index_expression");

  m_last_type = final_index_type;
}
} // namespace ir_gen
} // namespace flow_wing