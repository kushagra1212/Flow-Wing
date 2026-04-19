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

#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/common/types/CustomObjectType/CustomObjectType.hpp"
#include "src/utils/LogConfig.h"
#include "llvm/Support/Casting.h"
#include <cstdint>

namespace flow_wing::ir_gen {

llvm::Value *IRGenerator::emitStructuralComparison(
    llvm::Value *lhs_ptr, llvm::Value *rhs_ptr, types::CustomObjectType *type) {
  auto &builder = m_ir_gen_context.getLLVMBuilder();

  lhs_ptr = ensurePointer(lhs_ptr, type, "cmp_lhs");
  rhs_ptr = ensurePointer(rhs_ptr, type, "cmp_rhs");

  llvm::Function *comparator = getOrCreateStructComparator(type);

  if ((llvm::isa<llvm::AllocaInst>(lhs_ptr) ||
       llvm::isa<llvm::GEPOperator>(lhs_ptr) ||
       llvm::isa<llvm::GlobalVariable>(lhs_ptr))) {
    auto expected_llvm_type =
        m_ir_gen_context.getTypeBuilder()->getLLVMType(type);
    lhs_ptr = m_ir_gen_context.getLLVMBuilder()->CreateLoad(
        expected_llvm_type->getPointerTo(), lhs_ptr, "load_var");
  }

  if ((llvm::isa<llvm::AllocaInst>(rhs_ptr) ||
       llvm::isa<llvm::GEPOperator>(rhs_ptr) ||
       llvm::isa<llvm::GlobalVariable>(rhs_ptr))) {
    auto expected_llvm_type =
        m_ir_gen_context.getTypeBuilder()->getLLVMType(type);
    rhs_ptr = m_ir_gen_context.getLLVMBuilder()->CreateLoad(
        expected_llvm_type->getPointerTo(), rhs_ptr, "load_var");
  }

  llvm::Value *result =
      builder->CreateCall(comparator, {lhs_ptr, rhs_ptr}, "struct_cmp_res");
  return result;
}

llvm::Function *
IRGenerator::getOrCreateStructComparator(types::CustomObjectType *type) {
  auto &builder = m_ir_gen_context.getLLVMBuilder();
  auto *mod = m_ir_gen_context.getLLVMModule();
  auto *ctx = m_ir_gen_context.getLLVMContext();

  std::string func_name = "fg_eq_struct_" + type->getCustomTypeName();
  if (auto *existing_fn = mod->getFunction(func_name)) {
    return existing_fn;
  }

  llvm::Type *struct_ptr_ty =
      m_ir_gen_context.getTypeBuilder()->getLLVMType(type)->getPointerTo();
  llvm::FunctionType *fn_type = llvm::FunctionType::get(
      llvm::Type::getInt1Ty(*ctx), {struct_ptr_ty, struct_ptr_ty}, false);

  llvm::Function *cmp_fn = llvm::Function::Create(
      fn_type, llvm::Function::ExternalLinkage, func_name, mod);

  auto prev_block = builder->GetInsertBlock();
  auto prev_point = builder->GetInsertPoint();

  llvm::BasicBlock *entry_bb = llvm::BasicBlock::Create(*ctx, "entry", cmp_fn);
  llvm::BasicBlock *return_true_bb =
      llvm::BasicBlock::Create(*ctx, "return_true", cmp_fn);
  llvm::BasicBlock *return_false_bb =
      llvm::BasicBlock::Create(*ctx, "return_false", cmp_fn);
  llvm::BasicBlock *check_null_bb =
      llvm::BasicBlock::Create(*ctx, "check_null", cmp_fn);

  builder->SetInsertPoint(entry_bb);
  llvm::Value *lhs = cmp_fn->getArg(0);
  llvm::Value *rhs = cmp_fn->getArg(1);

  llvm::Value *ptr_eq = builder->CreateICmpEQ(lhs, rhs, "ptrs_same");
  builder->CreateCondBr(ptr_eq, return_true_bb, check_null_bb);

  builder->SetInsertPoint(check_null_bb);
  llvm::Value *lhs_is_null =
      builder->CreateICmpEQ(lhs,
                            llvm::ConstantPointerNull::get(
                                llvm::cast<llvm::PointerType>(lhs->getType())),
                            "lhs_null");
  llvm::Value *rhs_is_null =
      builder->CreateICmpEQ(rhs,
                            llvm::ConstantPointerNull::get(
                                llvm::cast<llvm::PointerType>(rhs->getType())),
                            "rhs_null");
  llvm::Value *either_null =
      builder->CreateOr(lhs_is_null, rhs_is_null, "either_null");

  llvm::BasicBlock *check_fields_bb =
      llvm::BasicBlock::Create(*ctx, "check_fields", cmp_fn);
  builder->CreateCondBr(either_null, return_false_bb,
                        check_fields_bb); // If either is null (and they aren't
                                          // both null), return false

  builder->SetInsertPoint(check_fields_bb);
  llvm::Type *llvm_struct_type =
      m_ir_gen_context.getTypeBuilder()->getLLVMType(type);

  uint32_t field_idx = 0;
  for (const auto &[field_name, field_type] : type->getFieldTypesMap()) {

    // Calculate GEPs
    llvm::Value *lhs_field_ptr =
        builder->CreateStructGEP(llvm_struct_type, lhs, field_idx);
    llvm::Value *rhs_field_ptr =
        builder->CreateStructGEP(llvm_struct_type, rhs, field_idx);

    llvm::Value *is_field_equal = nullptr;

    if (field_type->getKind() == types::TypeKind::kObject) {
      llvm::Value *lhs_sub =
          builder->CreateLoad(lhs_field_ptr->getType(), lhs_field_ptr);
      llvm::Value *rhs_sub =
          builder->CreateLoad(rhs_field_ptr->getType(), rhs_field_ptr);

      auto *sub_custom =
          static_cast<types::CustomObjectType *>(field_type.get());
      llvm::Function *sub_cmp = getOrCreateStructComparator(sub_custom);
      is_field_equal = builder->CreateCall(sub_cmp, {lhs_sub, rhs_sub});

    } else {
      llvm::Type *prim_ty =
          m_ir_gen_context.getTypeBuilder()->getLLVMType(field_type.get());
      llvm::Value *lhs_val = builder->CreateLoad(prim_ty, lhs_field_ptr);
      llvm::Value *rhs_val = builder->CreateLoad(prim_ty, rhs_field_ptr);

      is_field_equal = getBooleanResult(lhs_val, rhs_val,
                                        lexer::TokenKind::kEqualsEqualsToken,
                                        field_type.get(), field_type.get());
    }

    llvm::BasicBlock *next_field_bb =
        llvm::BasicBlock::Create(*ctx, "field_" + field_name + "_next", cmp_fn);
    builder->CreateCondBr(is_field_equal, next_field_bb, return_false_bb);

    builder->SetInsertPoint(next_field_bb);
    field_idx++;
  }

  builder->CreateBr(return_true_bb);

  builder->SetInsertPoint(return_true_bb);
  builder->CreateRet(builder->getInt1(true));

  builder->SetInsertPoint(return_false_bb);
  builder->CreateRet(builder->getInt1(false));

  if (prev_block)
    builder->SetInsertPoint(prev_block, prev_point);

  return cmp_fn;
}

} // namespace flow_wing::ir_gen
