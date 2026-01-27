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
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/utils/LogConfig.h"

namespace flow_wing::ir_gen {

void IRGenerator::visit(binding::BoundObjectExpression *object_expression) {
  CODEGEN_DEBUG_LOG("Visiting Bound Object Expression", "IR GENERATION");

  auto &builder = m_ir_gen_context.getLLVMBuilder();
  auto flow_type = object_expression->getType();
  auto llvm_type =
      m_ir_gen_context.getTypeBuilder()->getLLVMType(flow_type.get());

  auto fg_custom_type = static_cast<types::CustomObjectType *>(flow_type.get());

  llvm::Value *tmp_obj = getTempObject(fg_custom_type, fg_custom_type, nullptr);

  CODEGEN_DEBUG_LOG("Temp Object", fg_custom_type->getName());
  CODEGEN_DEBUG_LOG("Object Expression Name",
                    fg_custom_type->getCustomTypeName());

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
        llvm_type, tmp_obj, static_cast<unsigned int>(field_index));

    auto is_object = (field_type->getKind() == types::TypeKind::kObject);

    if (is_object) {

      auto custom_object_type =
          static_cast<types::CustomObjectType *>(val_type);

      CODEGEN_DEBUG_LOG("Custom Object Name",
                        custom_object_type->getCustomTypeName());

      if (!custom_object_type->isObjectExpression()) {

        val_to_store = builder->CreateLoad(m_ir_gen_context.getTypeBuilder()
                                               ->getLLVMType(custom_object_type)
                                               ->getPointerTo(),
                                           val_to_store,
                                           "load_val_" + val_type->getName());
      }

      builder->CreateStore(val_to_store, field_ptr);

    } else {
      CODEGEN_DEBUG_LOG("Primitives (Value Copy)", "IR GENERATION",
                        field_type->getName(), val_type->getName());
      // Primitives (Value Copy)
      emitTypedStore(field_ptr, field_type, val_to_store, val_type);
    }

    field_index++;
  }

  m_last_value = tmp_obj;
  m_last_llvm_type = llvm_type;
  m_last_type = object_expression->getType().get();
}
} // namespace flow_wing::ir_gen
