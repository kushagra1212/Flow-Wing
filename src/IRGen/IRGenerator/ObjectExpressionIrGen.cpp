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

    for (const auto &[field_name, field_type] :
         fg_custom_type->getFieldTypesMap()) {
      if (field_name == colon_expression->getFieldName()) {
        break;
      }
      field_index++;
    }

    auto *field_ptr = builder->CreateStructGEP(
        llvm_obj_type, object_alloc, static_cast<unsigned int>(field_index));

    emitTypedStore(field_ptr, colon_expression->getType().get(), val_to_store,
                   val_type);

    field_index++;
  }

  m_last_value = object_alloc;
  m_last_llvm_type = llvm_obj_type;
  m_last_type = flow_type.get();
}
} // namespace flow_wing::ir_gen