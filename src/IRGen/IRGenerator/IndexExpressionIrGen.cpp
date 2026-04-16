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
#include "src/IRGen/IRGenerator/IRGenHelper/DynamicValueHandler.h"
#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundIndexExpression/BoundIndexExpression.h"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/common/types/ArrayType/ArrayType.hpp"
#include "src/common/types/Type.hpp"
#include "src/utils/LogConfig.h"

// clang-format off
#include "src/compiler/diagnostics/DiagnosticPush.hpp"
#include "llvm/IR/IRBuilder.h"
#include "src/compiler/diagnostics/DiagnosticPop.hpp"
// clang-format on

namespace flow_wing {
namespace ir_gen {

namespace {

llvm::Function *getOrDeclareStrIdx(llvm::Module *mod, llvm::LLVMContext &ctx) {
  const std::string name(ir_gen::constants::functions::kString_index_fn);
  if (auto *fn = mod->getFunction(name))
    return fn;
  auto *fn_ty = llvm::FunctionType::get(
      llvm::Type::getInt32Ty(ctx),
      {llvm::Type::getInt8PtrTy(ctx), llvm::Type::getInt64Ty(ctx)}, false);
  return llvm::Function::Create(fn_ty, llvm::Function::ExternalLinkage, name,
                                mod);
}

llvm::Function *getOrDeclareDynStrIdx(llvm::Module *mod,
                                      llvm::LLVMContext &ctx) {
  const std::string name(
      ir_gen::constants::functions::kDynamic_string_index_fn);
  if (auto *fn = mod->getFunction(name))
    return fn;
  auto *i64 = llvm::Type::getInt64Ty(ctx);
  auto *fn_ty = llvm::FunctionType::get(llvm::Type::getInt32Ty(ctx),
                                        {i64, i64, i64}, false);
  return llvm::Function::Create(fn_ty, llvm::Function::ExternalLinkage, name,
                                mod);
}

} // namespace

void IRGenerator::visit(
    [[maybe_unused]] binding::BoundIndexExpression *statement) {
  CODEGEN_DEBUG_LOG("Visiting Bound Index Expression", "IR GENERATION");
  statement->getLeftExpression()->accept(this);

  llvm::Value *left_value = m_last_value;
  types::Type *left_type = m_last_type;
  clearLast();

  auto *builder = m_ir_gen_context.getLLVMBuilder().get();
  auto *mod = m_ir_gen_context.getLLVMModule();
  auto &ctx = *m_ir_gen_context.getLLVMContext();

  const bool is_str =
      (left_type == analysis::Builtins::m_str_type_instance.get());

  const bool is_dynamic = left_type->isDynamic();

  if (is_dynamic) {
    llvm::Type *dynamic_struct_type =
        m_ir_gen_context.getTypeBuilder()->getLLVMType(left_type);

    auto [value_storage, type_tag] = DynamicValueHandler::extractDynamicValue(
        left_value, dynamic_struct_type, builder);

    llvm::Value *type_tag_i64 = builder->CreateIntCast(
        type_tag, builder->getInt64Ty(), false, "dyn_tag_i64");

    const auto &dim_exprs = statement->getDimensionClauseExpressions();
    assert(dim_exprs.size() == 1 &&
           "dynamic indexing must have exactly 1 index");
    dim_exprs[0]->accept(this);

    llvm::Value *idx_val = nullptr;
    if (m_last_type->isDynamic()) {
      llvm::Type *idx_dyn_type =
          m_ir_gen_context.getTypeBuilder()->getLLVMType(m_last_type);
      auto [idx_storage, _tag] = DynamicValueHandler::extractDynamicValue(
          m_last_value, idx_dyn_type, builder);
      idx_val = idx_storage;
    } else {
      idx_val = resolveValue(m_last_value, m_last_type);
    }
    clearLast();

    idx_val = builder->CreateIntCast(idx_val, builder->getInt64Ty(), true,
                                     "dyn_idx_i64");

    llvm::Function *dyn_str_idx_fn = getOrDeclareDynStrIdx(mod, ctx);
    llvm::Value *result = builder->CreateCall(
        dyn_str_idx_fn, {value_storage, type_tag_i64, idx_val},
        "dyn_str_idx_result");

    m_last_value = result;
    m_last_type = analysis::Builtins::m_char_type_instance.get();
    return;
  }

  if (is_str) {
    llvm::Value *str_ptr = resolveValue(left_value, left_type);

    const auto &dim_exprs = statement->getDimensionClauseExpressions();
    assert(dim_exprs.size() == 1 && "str indexing must have exactly 1 index");
    dim_exprs[0]->accept(this);
    llvm::Value *idx_val = nullptr;
    if (m_last_type->isDynamic()) {
      llvm::Type *idx_dyn_type =
          m_ir_gen_context.getTypeBuilder()->getLLVMType(m_last_type);
      auto [idx_storage, _tag] = DynamicValueHandler::extractDynamicValue(
          m_last_value, idx_dyn_type, builder);
      idx_val = idx_storage;
    } else {
      idx_val = resolveValue(m_last_value, m_last_type);
    }
    clearLast();

    idx_val = builder->CreateIntCast(idx_val, builder->getInt64Ty(), true,
                                     "str_idx_i64");

    llvm::Function *str_idx_fn = getOrDeclareStrIdx(mod, ctx);
    llvm::Value *result =
        builder->CreateCall(str_idx_fn, {str_ptr, idx_val}, "str_idx_result");

    m_last_value = result;
    m_last_type = analysis::Builtins::m_char_type_instance.get();
    return;
  }

  auto *array_type = static_cast<types::ArrayType *>(left_type);
  auto *left_llvm_type =
      m_ir_gen_context.getTypeBuilder()->getLLVMType(left_type);

  llvm::Value *left_ptr = nullptr;
  if (auto *gep = llvm::dyn_cast<llvm::GEPOperator>(left_value)) {
    if (gep->getSourceElementType()->isStructTy() ||
        gep->getSourceElementType()->isArrayTy()) {
      left_ptr = left_value;
    }
  }

  if (!left_ptr) {
    if (auto *load = llvm::dyn_cast<llvm::LoadInst>(left_value)) {
      if (load->getType()->isArrayTy()) {
        auto *spill =
            m_ir_gen_context.createAlloca(load->getType(), "arr_spill");
        m_ir_gen_context.getLLVMBuilder()->CreateStore(load, spill);
        left_ptr = spill;
      }
    }
  }

  if (!left_ptr) {
    left_ptr = resolvePtr(left_value, left_type);
  }

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
    types::Type *index_expr_type = m_last_type;
    llvm::Value *index_val = nullptr;
    if (index_expr_type->isDynamic()) {
      llvm::Type *dynamic_struct_type =
          m_ir_gen_context.getTypeBuilder()->getLLVMType(index_expr_type);
      auto [value_storage, _type_tag] =
          DynamicValueHandler::extractDynamicValue(
              m_last_value, dynamic_struct_type,
              m_ir_gen_context.getLLVMBuilder().get());
      index_val = value_storage; // already i64
    } else {
      index_val = resolveValue(m_last_value, m_last_type);
    }
    clearLast();

    {

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