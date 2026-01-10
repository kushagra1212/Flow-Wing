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
#include "src/common/types/CustomObjectType/CustomObjectType.hpp"
#include "src/utils/LogConfig.h"

namespace flow_wing {
namespace ir_gen {
void IRGenerator::emitTypedStore(llvm::Value *target_addr,
                                 types::Type *target_type,
                                 llvm::Value *source_raw_value,
                                 types::Type *source_type) {
  auto &builder = m_ir_gen_context.getLLVMBuilder();
  auto *llvm_target_type =
      m_ir_gen_context.getTypeBuilder()->getLLVMType(target_type);

  // CASE: Struct to Struct Assignment (with different types)
  if (target_type->getKind() == types::TypeKind::kObject) {

    bool is_source_null =
        llvm::isa<llvm::ConstantPointerNull>(source_raw_value) ||
        source_type == analysis::Builtins::m_nirast_type_instance.get();

    if (is_source_null) {
      auto *default_value = m_ir_gen_context.getDefaultValue(target_type);
      builder->CreateStore(default_value, target_addr);
      return;
    }

    emitStructuralCopy(
        target_addr, static_cast<types::CustomObjectType *>(target_type),
        source_raw_value, static_cast<types::CustomObjectType *>(source_type));
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
    } else if (source_type->isPrimitive()) {
      // Primitive -> Dynamic: Box the primitive
      llvm::Value *val_to_store = resolveValue(source_raw_value, source_type);

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

    auto *unboxed_val = builder->CreateCall(func, {source_raw_value});
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

  if (*dest_type == *src_type) {
    llvm::Function *copier = getOrCreateStructCopier(dest_type);
    m_ir_gen_context.getLLVMBuilder()->CreateCall(copier, {dest_ptr, src_ptr});
    return;
  }

  auto &builder = m_ir_gen_context.getLLVMBuilder();
  auto *llvm_dest_type = static_cast<llvm::StructType *>(
      m_ir_gen_context.getTypeBuilder()->getLLVMType(dest_type));
  auto *llvm_src_type = static_cast<llvm::StructType *>(
      m_ir_gen_context.getTypeBuilder()->getLLVMType(src_type));

  CODEGEN_DEBUG_LOG("Destination type", llvm_dest_type->getName().str());

  CODEGEN_DEBUG_LOG("Source type", llvm_src_type->getName().str());

  size_t dest_index = 0;
  for (const auto &[field_name, dest_field_type] :
       dest_type->getFieldTypesMap()) {

    // 1. Calculate Destination Address
    llvm::Value *dest_field_ptr = builder->CreateStructGEP(
        llvm_dest_type, dest_ptr, static_cast<unsigned int>(dest_index),
        field_name + "_dest_ptr");

    auto it = src_type->getFieldTypesMap().find(field_name);

    if (it != src_type->getFieldTypesMap().end()) {
      // Field Found: Copy it
      auto src_field_type = it->second;

      size_t src_index = static_cast<size_t>(
          std::distance(src_type->getFieldTypesMap().begin(), it));

      llvm::Value *src_field_ptr = builder->CreateStructGEP(
          llvm_src_type, src_ptr, static_cast<unsigned int>(src_index),
          field_name + "_src_ptr");

      llvm::Value *val = builder->CreateLoad(
          m_ir_gen_context.getTypeBuilder()->getLLVMType(src_field_type.get()),
          src_field_ptr, field_name + "_val");

      CODEGEN_DEBUG_LOG("Src Field Type", src_field_type->getName());
      CODEGEN_DEBUG_LOG("Dest Field Type", dest_field_type->getName());

      if (dest_field_type->getKind() == types::TypeKind::kObject) {

        bool needs_conversion = *src_field_type.get() != *dest_field_type.get();

        CODEGEN_DEBUG_LOG("Needs Conversion", needs_conversion ? "Yes" : "No");
        CODEGEN_DEBUG_LOG("Src Field Type", src_field_type->getName());
        CODEGEN_DEBUG_LOG("Dest Field Type", dest_field_type->getName());

        val = builder->CreateLoad(m_ir_gen_context.getTypeBuilder()
                                      ->getLLVMType(src_field_type.get())
                                      ->getPointerTo(),
                                  src_field_ptr, field_name + "_val");

        // Object Value Semantics
        if (needs_conversion) {
          val = getTempObject(dest_field_type.get(), src_field_type.get(), val);
        }

        builder->CreateStore(val, dest_field_ptr);
      } else {

        bool is_source_null =
            llvm::isa<llvm::ConstantPointerNull>(val) ||
            src_field_type.get() ==
                analysis::Builtins::m_nirast_type_instance.get();

        if (is_source_null) {
          auto *default_value =
              m_ir_gen_context.getDefaultValue(dest_field_type.get());
          builder->CreateStore(default_value, dest_field_ptr);
          continue;
        }

        CODEGEN_DEBUG_LOG("Destination Field Type", dest_field_type->getName());

        // Value Semantics: Handle implicit casts (e.g. i8 -> i32)
        emitTypedStore(dest_field_ptr, dest_field_type.get(), val,
                       src_field_type.get());
      }
    } else {

      auto *default_value =
          m_ir_gen_context.getDefaultValue(dest_field_type.get());
      builder->CreateStore(default_value, dest_field_ptr);
    }

    dest_index++;
  }
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

  emitStructuralCopy(new_struct_alloc,
                     static_cast<types::CustomObjectType *>(dest_type), src_val,

                     static_cast<types::CustomObjectType *>(src_type));

  return new_struct_alloc;
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