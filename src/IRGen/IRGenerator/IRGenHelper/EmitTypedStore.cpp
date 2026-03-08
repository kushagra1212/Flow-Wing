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
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/common/types/ArrayType/ArrayType.hpp"
#include "src/common/types/CustomObjectType/CustomObjectType.hpp"
#include "src/utils/LogConfig.h"
#include "llvm/IR/Value.h"

namespace flow_wing {
namespace ir_gen {
void IRGenerator::emitTypedStore(llvm::Value *target_addr,
                                 types::Type *target_type,
                                 llvm::Value *source_raw_value,
                                 types::Type *source_type) {

  auto &builder = m_ir_gen_context.getLLVMBuilder();
  auto *llvm_target_type =
      m_ir_gen_context.getTypeBuilder()->getLLVMType(target_type);

  bool is_source_null =
      llvm::isa<llvm::ConstantPointerNull>(source_raw_value) ||
      source_type == analysis::Builtins::m_nirast_type_instance.get();

  if (is_source_null) {

    builder->CreateStore(
        llvm::ConstantPointerNull::get(m_ir_gen_context.getTypeBuilder()
                                           ->getLLVMType(target_type)
                                           ->getPointerTo()),
        target_addr);

    return;
  }

  // CASE: Struct to Struct Assignment (with different types)
  if (target_type->getKind() == types::TypeKind::kObject) {
    auto *dest_obj_type = static_cast<types::CustomObjectType *>(target_type);
    auto *src_obj_type = static_cast<types::CustomObjectType *>(source_type);

    llvm::Value *source_value = source_raw_value;

    bool is_source_inline = false;
    if (auto *gep = llvm::dyn_cast<llvm::GEPOperator>(source_raw_value)) {
      if (gep->getSourceElementType()->isArrayTy()) {
        is_source_inline = true;
      }
    }

    if (llvm::isa<llvm::AllocaInst>(source_raw_value) ||
        llvm::isa<llvm::GlobalVariable>(source_raw_value) ||
        (llvm::isa<llvm::GEPOperator>(source_raw_value) && !is_source_inline)) {
      // Variables and Struct Fields hold heap pointers. MUST load.
      auto expected_llvm_type =
          m_ir_gen_context.getTypeBuilder()->getLLVMType(source_type);
      source_value = m_ir_gen_context.getLLVMBuilder()->CreateLoad(
          expected_llvm_type->getPointerTo(), source_raw_value, "load_var");

    } else if (is_source_inline ||
               llvm::isa<llvm::LoadInst>(source_raw_value) ||
               llvm::isa<llvm::CallInst>(source_raw_value)) {
      // Array slices hold inline memory.
      source_value = source_raw_value;

    } else {
      // Literals: Materialize as NATIVE type to prevent double-conversion!
      source_value = getTempObject(source_type, source_type, source_raw_value);
    }

    bool is_target_inline = false;
    if (auto *gep = llvm::dyn_cast<llvm::GEPOperator>(target_addr)) {
      if (gep->getSourceElementType()->isArrayTy()) {
        is_target_inline = true;
      }
    }

    if (is_target_inline) {
      // Target is inline memory. Deep copy fields directly.
      emitStructuralCopy(target_addr, dest_obj_type, source_value,
                         src_obj_type);
    } else {
      if (*source_type != *target_type) {
        source_value =
            convertToTargetType(source_value, target_type, source_type);
      }
      builder->CreateStore(source_value, target_addr);
    }

    return;
  }

  if (target_type->getKind() == types::TypeKind::kArray) {
    auto *dest_array_type = static_cast<types::ArrayType *>(target_type);
    auto *src_array_type = static_cast<types::ArrayType *>(source_type);
    const auto source_underlying_type = src_array_type->getUnderlyingType();
    const auto target_underlying_type = dest_array_type->getUnderlyingType();

    bool is_target_slice = llvm::isa<llvm::GEPOperator>(target_addr);

    if (is_target_slice) {
      llvm::Value *src_ptr_for_copy = source_raw_value;

      if (llvm::isa<llvm::AllocaInst>(source_raw_value) ||
          llvm::isa<llvm::GlobalVariable>(source_raw_value)) {
        auto expected_llvm_type =
            m_ir_gen_context.getTypeBuilder()->getLLVMType(source_type);
        if (auto *src_alloca =
                llvm::dyn_cast<llvm::AllocaInst>(source_raw_value)) {
          if (!src_alloca->getAllocatedType()->isPointerTy()) {
            src_ptr_for_copy = source_raw_value;
          } else {
            src_ptr_for_copy =
                builder->CreateLoad(expected_llvm_type->getPointerTo(),
                                    source_raw_value, "load_var");
          }
        } else {
          src_ptr_for_copy = builder->CreateLoad(
              expected_llvm_type->getPointerTo(), source_raw_value, "load_var");
        }
      }

      emitArrayCopy(target_addr, dest_array_type, src_ptr_for_copy,
                    src_array_type);

    } else {
      // --- TARGET IS A VARIABLE (e.g., x = ...) ---
      llvm::Value *final_heap_ptr = source_raw_value;

      if (llvm::isa<llvm::AllocaInst>(source_raw_value) ||
          llvm::isa<llvm::GlobalVariable>(source_raw_value)) {
        // Loading variable
        auto expected_llvm_type =
            m_ir_gen_context.getTypeBuilder()->getLLVMType(source_type);
        final_heap_ptr = builder->CreateLoad(expected_llvm_type->getPointerTo(),
                                             source_raw_value, "load_var");

      } else if (llvm::isa<llvm::GEPOperator>(source_raw_value)) {

        final_heap_ptr = source_raw_value;

      } else {
        // Literal
        final_heap_ptr =
            getTempArray(target_type, source_type, source_raw_value);

        bool target_wants_inline = false;
        if (auto *alloca = llvm::dyn_cast<llvm::AllocaInst>(target_addr)) {
          target_wants_inline = !alloca->getAllocatedType()->isPointerTy();
        } else if (llvm::isa<llvm::Argument>(target_addr)) {
          target_wants_inline = true;
        }

        if (target_wants_inline) {
          const llvm::DataLayout &dl =
              m_ir_gen_context.getLLVMModule()->getDataLayout();
          llvm::Align align = dl.getABITypeAlign(llvm_target_type);
          uint64_t size = dl.getTypeAllocSize(llvm_target_type);
          builder->CreateMemCpy(target_addr, llvm::MaybeAlign(align),
                                final_heap_ptr, llvm::MaybeAlign(align), size);
        } else {
          builder->CreateStore(final_heap_ptr, target_addr);
        }
        return;
      }

      if ((*source_type != *target_type) ||
          (source_underlying_type != target_underlying_type)) {
        final_heap_ptr =
            convertToTargetType(final_heap_ptr, target_type, source_type);
      }
      bool target_wants_inline = false;
      if (auto *alloca = llvm::dyn_cast<llvm::AllocaInst>(target_addr)) {
        target_wants_inline = !alloca->getAllocatedType()->isPointerTy();
      } else if (llvm::isa<llvm::Argument>(target_addr)) {
        target_wants_inline = true;
      }

      if (target_wants_inline) {
        const llvm::DataLayout &dl =
            m_ir_gen_context.getLLVMModule()->getDataLayout();
        llvm::Align align = dl.getABITypeAlign(llvm_target_type);
        uint64_t size = dl.getTypeAllocSize(llvm_target_type);
        builder->CreateMemCpy(target_addr, llvm::MaybeAlign(align),
                              final_heap_ptr, llvm::MaybeAlign(align), size);
      } else {
        builder->CreateStore(final_heap_ptr, target_addr);
      }
    }

    return;
  }

  if (target_type->getKind() == types::TypeKind::kArray) {
    auto *dest_array_type = static_cast<types::ArrayType *>(target_type);
    auto *src_array_type = static_cast<types::ArrayType *>(source_type);
    const auto source_underlying_type = src_array_type->getUnderlyingType();
    const auto target_underlying_type = dest_array_type->getUnderlyingType();

    bool is_target_slice = llvm::isa<llvm::GEPOperator>(target_addr);

    if (is_target_slice) {
      // --- TARGET IS A SLICE (e.g., x[1] = ...) ---
      llvm::Value *src_ptr_for_copy = source_raw_value;

      if (llvm::isa<llvm::AllocaInst>(source_raw_value) ||
          llvm::isa<llvm::GlobalVariable>(source_raw_value)) {
        auto expected_llvm_type =
            m_ir_gen_context.getTypeBuilder()->getLLVMType(source_type);
        if (auto *src_alloca =
                llvm::dyn_cast<llvm::AllocaInst>(source_raw_value)) {
          if (!src_alloca->getAllocatedType()->isPointerTy()) {
            src_ptr_for_copy = source_raw_value; // inline — addr IS the data
          } else {
            src_ptr_for_copy =
                builder->CreateLoad(expected_llvm_type->getPointerTo(),
                                    source_raw_value, "load_var");
          }
        } else {
          // GlobalVariable — always a pointer slot
          src_ptr_for_copy = builder->CreateLoad(
              expected_llvm_type->getPointerTo(), source_raw_value, "load_var");
        }
      }

      emitArrayCopy(target_addr, dest_array_type, src_ptr_for_copy,
                    src_array_type);

    } else {
      // --- TARGET IS A VARIABLE (e.g., x = ...) ---
      llvm::Value *final_heap_ptr = source_raw_value;

      if (llvm::isa<llvm::AllocaInst>(source_raw_value) ||
          llvm::isa<llvm::GlobalVariable>(source_raw_value)) {
        // Loading variable
        auto expected_llvm_type =
            m_ir_gen_context.getTypeBuilder()->getLLVMType(source_type);
        final_heap_ptr = builder->CreateLoad(expected_llvm_type->getPointerTo(),
                                             source_raw_value, "load_var");

      } else if (llvm::isa<llvm::GEPOperator>(source_raw_value)) {

        final_heap_ptr = source_raw_value;

      } else {
        // Literal
        final_heap_ptr =
            getTempArray(target_type, source_type, source_raw_value);

        builder->CreateStore(final_heap_ptr, target_addr);
        return;
      }

      if ((*source_type != *target_type) ||
          (source_underlying_type != target_underlying_type)) {
        final_heap_ptr =
            convertToTargetType(final_heap_ptr, target_type, source_type);
      }

      builder->CreateStore(final_heap_ptr, target_addr);
    }

    return;
  }

  if (target_type->isDynamic()) {
    if (source_type->isDynamic()) {
      // Dynamic -> Dynamic: Direct struct copy
      llvm::Value *val_to_store = resolveValue(source_raw_value, source_type);

      if (val_to_store->getType()->isPointerTy()) {
        val_to_store = builder->CreateLoad(
            m_ir_gen_context.getTypeBuilder()->getLLVMType(source_type),
            val_to_store, "load_val");
      }

      builder->CreateStore(val_to_store, target_addr);
    } else if (source_type->isPrimitive() ||
               source_type->getKind() == types::TypeKind::kObject ||
               source_type->getKind() == types::TypeKind::kArray) {
      llvm::Value *val_to_store = nullptr;

      if (source_type->getKind() == types::TypeKind::kObject ||
          source_type->getKind() == types::TypeKind::kArray) {

        if (llvm::isa<llvm::AllocaInst>(source_raw_value) ||
            llvm::isa<llvm::GEPOperator>(source_raw_value) ||
            llvm::isa<llvm::GlobalVariable>(source_raw_value)) {

          // It's a variable (L-Value). Load the pointer stored in it.
          auto *llvm_type =
              m_ir_gen_context.getTypeBuilder()->getLLVMType(source_type);
          val_to_store = builder->CreateLoad(llvm_type->getPointerTo(),
                                             source_raw_value, "load_obj_ptr");

        } else {
          // It's a temporary (R-Value). It is ALREADY the pointer we need.
          val_to_store = source_raw_value;
        }

      } else {
        // For Primitives (Int, Float, Bool, String), resolveValue works
        // correctly.
        val_to_store = resolveValue(source_raw_value, source_type);
      }

      llvm::Value *boxed_struct = DynamicValueHandler::storePrimitiveToDynamic(
          val_to_store, val_to_store->getType(), llvm_target_type,
          builder.get(), source_type);

      builder->CreateStore(boxed_struct, target_addr);
    } else {
      // TODO: Future Object/Array Support
      assert(false && "Unsupported type assignment to Dynamic variable");
    }
    return;
  }

  if (source_type->isDynamic()) {
    // Dynamic -> Static Type: Unbox
    auto unboxing_func_name =
        analysis::Builtins::getUnboxingFunctionName(target_type);

    assert(!unboxing_func_name.empty() &&
           "No unboxing function found for this type");

    auto *func =
        m_ir_gen_context.getLLVMModule()->getFunction(unboxing_func_name);
    assert(func && "Unboxing runtime function not found in module");

    llvm::Value *unbox_arg =
        ensurePointer(source_raw_value, source_type, "unbox_arg");

    auto *unboxed_val = builder->CreateCall(func, {unbox_arg});
    builder->CreateStore(unboxed_val, target_addr);
    return;
  }

  // Primitive->Primitive, Object->Object
  llvm::Value *val_to_store = resolveValue(source_raw_value, source_type);

  CODEGEN_DEBUG_LOG("Implicit cast", "IR GENERATION", source_type->getName(),
                    target_type->getName());
  if (*target_type != *source_type) {

    val_to_store = convertToTargetType(val_to_store, target_type, source_type);
  }

  builder->CreateStore(val_to_store, target_addr);
}

void IRGenerator::emitStructuralCopy(llvm::Value *dest_ptr,
                                     types::CustomObjectType *dest_type,
                                     [[maybe_unused]] llvm::Value *src_raw,
                                     types::CustomObjectType *src_type) {
  llvm::Value *src_ptr = ensurePointer(src_raw, src_type, "struct_copy");
  auto &builder = m_ir_gen_context.getLLVMBuilder();

  if (*dest_type == *src_type) {
    auto *llvm_dest_type =
        m_ir_gen_context.getTypeBuilder()->getLLVMType(dest_type);
    const llvm::DataLayout &dl =
        m_ir_gen_context.getLLVMModule()->getDataLayout();

    uint64_t type_size_bytes = dl.getTypeAllocSize(llvm_dest_type);

    builder->CreateMemCpy(dest_ptr, llvm::MaybeAlign(0), src_ptr,
                          llvm::MaybeAlign(0), type_size_bytes);
    return;
  }

  auto *llvm_dest_type = static_cast<llvm::StructType *>(
      m_ir_gen_context.getTypeBuilder()->getLLVMType(dest_type));
  auto *llvm_src_type = static_cast<llvm::StructType *>(
      m_ir_gen_context.getTypeBuilder()->getLLVMType(src_type));

  size_t dest_index = 0;
  for (const auto &[field_name, dest_field_type] :
       dest_type->getFieldTypesMap()) {

    // 1. Calculate Destination Address
    llvm::Value *dest_field_ptr = builder->CreateStructGEP(
        llvm_dest_type, dest_ptr, static_cast<unsigned int>(dest_index),
        field_name + "_dest_ptr");

    auto it = src_type->getFieldTypesMap().find(field_name);

    if (it != src_type->getFieldTypesMap().end()) {

      auto src_field_type = it->second;

      size_t src_index = static_cast<size_t>(
          std::distance(src_type->getFieldTypesMap().begin(), it));

      // C. Calculate Source Address
      llvm::Value *src_field_ptr = builder->CreateStructGEP(
          llvm_src_type, src_ptr, static_cast<unsigned int>(src_index),
          field_name + "_src_ptr");

      emitTypedStore(dest_field_ptr, dest_field_type.get(), src_field_ptr,
                     src_field_type.get());
    } else {

      auto *default_value =
          m_ir_gen_context.getDefaultValue(dest_field_type.get());
      builder->CreateStore(default_value, dest_field_ptr);
    }

    dest_index++;
  }
}

void IRGenerator::emitArrayCopy(llvm::Value *dest_ptr,
                                types::ArrayType *dest_type,
                                llvm::Value *src_ptr,
                                types::ArrayType *src_type) {
  auto &builder = m_ir_gen_context.getLLVMBuilder();

  dest_ptr = ensurePointer(dest_ptr, dest_type, "dest_arr_ptr");
  src_ptr = ensurePointer(src_ptr, src_type, "src_arr_ptr");

  CODEGEN_DEBUG_LOG("Dest Type", dest_type->getName());
  CODEGEN_DEBUG_LOG("Src Type", src_type->getName());
  const llvm::DataLayout &dl =
      m_ir_gen_context.getLLVMModule()->getDataLayout();

  bool types_match = (*dest_type == *src_type);

  // Explicit double-check to prevent Dynamic <-> Static memcpy
  if (dest_type->getUnderlyingType()->isDynamic() !=
      src_type->getUnderlyingType()->isDynamic()) {
    types_match = false;
  }

  if (types_match) {
    llvm::Type *llvm_dest_type =
        m_ir_gen_context.getTypeBuilder()->getLLVMType(dest_type);
    uint64_t type_size_bytes = dl.getTypeAllocSize(llvm_dest_type);

    builder->CreateMemCpy(dest_ptr, llvm::MaybeAlign(0), src_ptr,
                          llvm::MaybeAlign(0), type_size_bytes);
    return;
  }

  uint64_t src_count = src_type->getDimensions()[0];
  uint64_t dest_count = dest_type->getDimensions()[0];
  uint64_t copy_limit = std::min(src_count, dest_count);

  llvm::Function *func = builder->GetInsertBlock()->getParent();
  llvm::BasicBlock *loop_cond = llvm::BasicBlock::Create(
      *m_ir_gen_context.getLLVMContext(), "copy.cond", func);
  llvm::BasicBlock *loop_body = llvm::BasicBlock::Create(
      *m_ir_gen_context.getLLVMContext(), "copy.body", func);
  llvm::BasicBlock *loop_exit = llvm::BasicBlock::Create(
      *m_ir_gen_context.getLLVMContext(), "copy.exit", func);

  llvm::BasicBlock *predecessor_block = builder->GetInsertBlock();
  builder->CreateBr(loop_cond);

  builder->SetInsertPoint(loop_cond);

  llvm::PHINode *idx = builder->CreatePHI(builder->getInt64Ty(), 2, "i");
  idx->addIncoming(builder->getInt64(0), predecessor_block);

  llvm::Value *cmp = builder->CreateICmpULT(idx, builder->getInt64(copy_limit));
  builder->CreateCondBr(cmp, loop_body, loop_exit);

  builder->SetInsertPoint(loop_body);

  std::shared_ptr<types::Type> src_elem_type;
  if (src_type->getDimensions().size() > 1) {
    std::vector<size_t> sub_dims(src_type->getDimensions().begin() + 1,
                                 src_type->getDimensions().end());
    src_elem_type = std::make_shared<types::ArrayType>(
        src_type->getUnderlyingType(), sub_dims);
  } else {
    src_elem_type = src_type->getUnderlyingType();
  }

  std::shared_ptr<types::Type> dest_elem_type;
  if (dest_type->getDimensions().size() > 1) {
    std::vector<size_t> sub_dims(dest_type->getDimensions().begin() + 1,
                                 dest_type->getDimensions().end());
    dest_elem_type = std::make_shared<types::ArrayType>(
        dest_type->getUnderlyingType(), sub_dims);
  } else {
    dest_elem_type = dest_type->getUnderlyingType();
  }

  llvm::Type *dest_llvm_type =
      m_ir_gen_context.getTypeBuilder()->getLLVMType(dest_type);
  llvm::Type *src_llvm_type =
      m_ir_gen_context.getTypeBuilder()->getLLVMType(src_type);

  std::vector<llvm::Value *> indices = {builder->getInt64(0), idx};

  llvm::Value *dest_elem_ptr =
      builder->CreateInBoundsGEP(dest_llvm_type, dest_ptr, indices, "dest_ptr");
  llvm::Value *src_elem_ptr =
      builder->CreateInBoundsGEP(src_llvm_type, src_ptr, indices, "src_ptr");
  ;

  if (dest_elem_type->getKind() == types::TypeKind::kArray) {
    emitArrayCopy(
        dest_elem_ptr, static_cast<types::ArrayType *>(dest_elem_type.get()),
        src_elem_ptr, static_cast<types::ArrayType *>(src_elem_type.get()));
  } else {

    llvm::Value *src_val = builder->CreateLoad(
        m_ir_gen_context.getTypeBuilder()->getLLVMType(src_elem_type.get()),
        src_elem_ptr, "src_val");

    emitTypedStore(dest_elem_ptr, dest_elem_type.get(), src_val,
                   src_elem_type.get());
  }

  llvm::BasicBlock *current_body_block = builder->GetInsertBlock();
  llvm::Value *next_idx = builder->CreateAdd(idx, builder->getInt64(1));
  idx->addIncoming(next_idx, current_body_block);
  builder->CreateBr(loop_cond);

  builder->SetInsertPoint(loop_exit);
}

llvm::Value *IRGenerator::getTempObject(types::Type *dest_type,
                                        types::Type *src_type,
                                        llvm::Value *src_val) {
  auto &builder = m_ir_gen_context.getLLVMBuilder();
  llvm::Type *dest_llvm_type =
      m_ir_gen_context.getTypeBuilder()->getLLVMType(dest_type);

  auto fun = m_ir_gen_context.getLLVMModule()->getFunction(
      std::string(constants::functions::kGC_malloc_fn));

  assert(fun && "GC_malloc function not found");

  const llvm::DataLayout &dl =
      m_ir_gen_context.getLLVMModule()->getDataLayout();

  uint64_t type_size_bytes = dl.getTypeAllocSize(dest_llvm_type);

  llvm::CallInst *malloc_call = builder->CreateCall(
      fun, llvm::ConstantInt::get(
               llvm::Type::getInt64Ty(*m_ir_gen_context.getLLVMContext()),
               type_size_bytes));
  malloc_call->setTailCall(false);

  // Cast the result of 'malloc' to a pointer to int
  auto new_struct_alloc =
      builder->CreateBitCast(malloc_call, dest_llvm_type->getPointerTo());

  llvm::Value *default_val = m_ir_gen_context.getDefaultValue(dest_type);
  builder->CreateStore(default_val, new_struct_alloc);

  if (src_val != nullptr) {

    emitStructuralCopy(new_struct_alloc,
                       static_cast<types::CustomObjectType *>(dest_type),
                       src_val,

                       static_cast<types::CustomObjectType *>(src_type));
  }

  return new_struct_alloc;
}

llvm::Value *IRGenerator::getTempArray(types::Type *dest_type,
                                       types::Type *src_type,
                                       llvm::Value *src_val) {

  CODEGEN_DEBUG_LOG("getTempArray", "dest_type", dest_type->getName(),
                    "src_type", src_type->getName());

  auto &builder = m_ir_gen_context.getLLVMBuilder();
  auto *dest_array_type = static_cast<types::ArrayType *>(dest_type);

  llvm::Type *dest_llvm_type =
      m_ir_gen_context.getTypeBuilder()->getLLVMType(dest_type);

  auto fun = m_ir_gen_context.getLLVMModule()->getFunction(
      std::string(constants::functions::kGC_malloc_fn));
  assert(fun && "GC_malloc function not found");

  const llvm::DataLayout &dl =
      m_ir_gen_context.getLLVMModule()->getDataLayout();
  uint64_t type_size_bytes = dl.getTypeAllocSize(dest_llvm_type);

  llvm::CallInst *malloc_call = builder->CreateCall(
      fun, llvm::ConstantInt::get(
               llvm::Type::getInt64Ty(*m_ir_gen_context.getLLVMContext()),
               type_size_bytes));
  malloc_call->setTailCall(false);

  auto new_array_ptr = builder->CreateBitCast(
      malloc_call, dest_llvm_type->getPointerTo(), "new_array");

  llvm::Value *default_val = m_ir_gen_context.getDefaultValue(dest_type);
  builder->CreateStore(default_val, new_array_ptr);

  if (src_val != nullptr) {
    auto *src_array_type = static_cast<types::ArrayType *>(src_type);
    emitArrayCopy(new_array_ptr, dest_array_type, src_val, src_array_type);
  }

  return new_array_ptr;
}

llvm::Function *
IRGenerator::getOrCreateStructCopier(types::CustomObjectType *type) {
  auto &builder = m_ir_gen_context.getLLVMBuilder();
  auto *mod = m_ir_gen_context.getLLVMModule();

  // 1. Check Cache (e.g., "fg_copy_struct_Node")
  std::string func_name = "fg_copy_struct_" + type->getCustomTypeName();
  if (auto *existing_fn = mod->getFunction(func_name)) {
    return existing_fn;
  }

  // 2. Define Function Signature: void copy(StructType* dest, StructType* src)
  llvm::Type *llvm_struct_type =
      m_ir_gen_context.getTypeBuilder()->getLLVMType(type);
  llvm::Type *struct_ptr_type = llvm_struct_type->getPointerTo();

  llvm::FunctionType *fn_type = llvm::FunctionType::get(
      builder->getVoidTy(), {struct_ptr_type, struct_ptr_type}, false);

  llvm::Function *copier_fn = llvm::Function::Create(
      fn_type, llvm::Function::ExternalLinkage, func_name, mod);

  // 3. Save Insert Point (So we don't break the main code generation)
  auto prev_block = builder->GetInsertBlock();
  auto prev_insert_point = builder->GetInsertPoint();

  // 4. Generate Body
  llvm::BasicBlock *entry_block = llvm::BasicBlock::Create(
      *m_ir_gen_context.getLLVMContext(), "entry", copier_fn);
  builder->SetInsertPoint(entry_block);

  llvm::Value *dest_ptr = copier_fn->getArg(0);
  llvm::Value *src_ptr = copier_fn->getArg(1);

  // Iterate Fields
  size_t field_index = 0;
  for (const auto &[field_name, field_type] : type->getFieldTypesMap()) {

    // GEP for Source and Dest
    llvm::Value *src_field_gep = builder->CreateStructGEP(
        llvm_struct_type, src_ptr, static_cast<unsigned int>(field_index));

    llvm::Value *dest_field_gep = builder->CreateStructGEP(
        llvm_struct_type, dest_ptr, static_cast<unsigned int>(field_index));

    // Determine the LLVM type for the load
    llvm::Type *field_llvm_type = nullptr;

    if (field_type->getKind() == types::TypeKind::kObject) {
      // If field is an Object, it's stored as a pointer (Node*).
      // We copy the pointer itself (Shallow Copy of Reference).
      field_llvm_type = m_ir_gen_context.getTypeBuilder()
                            ->getLLVMType(field_type.get())
                            ->getPointerTo();
    } else {
      // Primitives (int, float, etc.)
      field_llvm_type =
          m_ir_gen_context.getTypeBuilder()->getLLVMType(field_type.get());
    }

    // Perform the Copy: Load from Src -> Store to Dest
    llvm::Value *val = builder->CreateLoad(field_llvm_type, src_field_gep,
                                           field_name + "_val");
    builder->CreateStore(val, dest_field_gep);

    field_index++;
  }

  builder->CreateRetVoid();

  // 5. Restore Insert Point
  if (prev_block) {
    builder->SetInsertPoint(prev_block, prev_insert_point);
  }

  return copier_fn;
}

} // namespace ir_gen
} // namespace flow_wing