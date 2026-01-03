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
  if (target_type->getKind() == types::TypeKind::kObject &&
      source_type->getKind() == types::TypeKind::kObject &&
      target_type != source_type) {

    emitStructuralCopy(
        target_addr, static_cast<types::CustomObjectType *>(target_type),
        source_raw_value, static_cast<types::CustomObjectType *>(source_type));
    return;
  }

  if (target_type->isDynamic()) {
    if (source_type->isDynamic()) {
      // Dynamic -> Dynamic: Direct struct copy
      llvm::Value *val_to_store = resolveValue(source_raw_value, source_type);
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

  if (target_type != source_type) {
    // Handles implicit casts (e.g., int -> float, or Derived* -> Base*)
    val_to_store = convertToTargetType(val_to_store, target_type, source_type);
  }

  builder->CreateStore(val_to_store, target_addr);
}

void IRGenerator::emitStructuralCopy(llvm::Value *dest_ptr,
                                     types::CustomObjectType *dest_type,
                                     [[maybe_unused]] llvm::Value *src_ptr,
                                     types::CustomObjectType *src_type) {
  auto &builder = m_ir_gen_context.getLLVMBuilder();
  auto *llvm_dest_type = static_cast<llvm::StructType *>(
      m_ir_gen_context.getTypeBuilder()->getLLVMType(dest_type));
  [[maybe_unused]] auto *llvm_src_type = static_cast<llvm::StructType *>(
      m_ir_gen_context.getTypeBuilder()->getLLVMType(src_type));

  size_t field_index = 0;

  for (const auto &[field_name, field_type] : dest_type->getFieldTypesMap()) {

    auto it = src_type->getFieldTypesMap().find(field_name);

    llvm::Value *dest_field_ptr = builder->CreateStructGEP(
        llvm_dest_type, dest_ptr, static_cast<unsigned int>(field_index),
        field_name + "_ptr");

    if (it != src_type->getFieldTypesMap().end()) {
      CODEGEN_DEBUG_LOG("Structural copy", "IR GENERATION", field_name,
                        field_type->getName(), it->second->getName());

      size_t src_index = static_cast<size_t>(
          std::distance(src_type->getFieldTypesMap().begin(), it));

      llvm::Value *src_field_ptr = builder->CreateStructGEP(
          llvm_src_type, src_ptr, static_cast<unsigned int>(src_index),
          field_name + "_src_ptr");

      llvm::Value *val = builder->CreateLoad(
          m_ir_gen_context.getTypeBuilder()->getLLVMType(field_type.get()),
          src_field_ptr, field_name + "_val");

      emitTypedStore(dest_field_ptr, field_type.get(), val, field_type.get());
    } else {
      auto *default_value = m_ir_gen_context.getDefaultValue(field_type.get());
      m_ir_gen_context.getLLVMBuilder()->CreateStore(default_value,
                                                     dest_field_ptr);
    }

    field_index++;
  }
}
} // namespace ir_gen
} // namespace flow_wing