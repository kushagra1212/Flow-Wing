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
#include "src/SemanticAnalyzer/BoundExpressions/BoundObjectExpression/BoundObjectExpression.hpp"
#include "src/utils/LogConfig.h"

namespace flow_wing::ir_gen {

void IRGenerator::visit(binding::BoundObjectExpression *object_expression) {
  CODEGEN_DEBUG_LOG("Visiting Bound Object Expression", "IR GENERATION");

  auto &builder = m_ir_gen_context.getLLVMBuilder();
  auto flow_type = object_expression->getType();
  auto llvm_obj_type =
      m_ir_gen_context.getTypeBuilder()->getLLVMType(flow_type.get());

  auto fg_custom_type = static_cast<types::CustomObjectType *>(flow_type.get());

  llvm::Value *object_alloc =
      m_ir_gen_context.createAlloca(llvm_obj_type, "obj_lit_tmp");

  auto *default_value = m_ir_gen_context.getDefaultValue(flow_type.get());
  m_ir_gen_context.getLLVMBuilder()->CreateStore(default_value, object_alloc);

  for (const auto &prop : object_expression->getColonExpressions()) {
    auto colon_expression =
        static_cast<binding::BoundColonExpression *>(prop.get());

    colon_expression->getRightExpression()->accept(this);

    llvm::Value *val_to_store = m_last_value;
    types::Type *val_type = m_last_type;

    size_t field_index = 0;
    types::Type *field_type = nullptr;

    for (const auto &[field_name, src_field_type] :
         fg_custom_type->getFieldTypesMap()) {
      if (field_name == colon_expression->getFieldName()) {
        field_type = src_field_type.get();
        break;
      }
      field_index++;
    }

    auto *field_ptr = builder->CreateStructGEP(
        llvm_obj_type, object_alloc, static_cast<unsigned int>(field_index));

    // --- FIX START ---
    // If the field is an Object, it is stored as a Pointer (Node*).
    // We must LINK the pointer, not COPY the content.
    if (field_type->getKind() == types::TypeKind::kObject) {

      // Ensure we have the pointer value (Node*)
      llvm::Value *ptr_val = resolveValue(val_to_store, val_type);

      // Store Node* into Node** (the field slot)
      builder->CreateStore(ptr_val, field_ptr);
    } else {
      CODEGEN_DEBUG_LOG("Primitives (Value Copy)", "IR GENERATION",
                        field_type->getName(), val_type->getName());
      // Primitives (Value Copy)
      emitTypedStore(field_ptr, field_type, val_to_store, val_type);
    }

    field_index++;
  }

  m_last_value = object_alloc;
  m_last_llvm_type = llvm_obj_type;
  m_last_type = object_expression->getType().get();
}
} // namespace flow_wing::ir_gen
