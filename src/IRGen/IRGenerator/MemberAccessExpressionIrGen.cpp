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
#include "src/SemanticAnalyzer/BoundExpressions/BoundMemberAccessExpression/BoundMemberAccessExpression.hpp"
#include "src/common/types/CustomObjectType/CustomObjectType.hpp"
#include "src/utils/LogConfig.h"

namespace flow_wing::ir_gen {

void IRGenerator::visit(
    binding::BoundMemberAccessExpression *member_access_expression) {
  CODEGEN_DEBUG_LOG("Visiting Bound Member Access Expression", "IR GENERATION");

  member_access_expression->getLeftExpression()->accept(this);

  auto left_expression = member_access_expression->getLeftExpression().get();

  llvm::Value *object_value = m_last_value;
  types::Type *object_type = m_last_type;

  bool is_nested_access = (left_expression->getKind() ==
                           binding::NodeKind::kMemberAccessExpression);

  if (is_nested_access && object_type->getKind() == types::TypeKind::kObject) {
    // Dereference: Node** -> Node*
    object_value = m_ir_gen_context.getLLVMBuilder()->CreateLoad(
        m_ir_gen_context.getTypeBuilder()
            ->getLLVMType(object_type)
            ->getPointerTo(),
        object_value, "chain_load");
  }

  if (object_type->getKind() == types::TypeKind::kObject) {
    auto &builder = m_ir_gen_context.getLLVMBuilder();

    // A. Check if Pointer is Null
    llvm::Value *is_null = builder->CreateIsNull(object_value, "is_null_check");

    llvm::BasicBlock *error_block =
        m_ir_gen_context.createBlock("null_access_error");
    llvm::BasicBlock *continue_block =
        m_ir_gen_context.createBlock("null_access_ok");

    // Branch: If null -> Error, Else -> Continue
    builder->CreateCondBr(is_null, error_block, continue_block);

    // B. Generate Error Block
    m_ir_gen_context.setInsertPoint(error_block);

    auto *runtime_err_fn =
        m_ir_gen_context.getLLVMModule()->getFunction("fg_re");
    if (runtime_err_fn) {
      // Pass a specific error message
      llvm::Value *msg = builder->CreateGlobalStringPtr(
          "Runtime Error: Cannot access member '" +
          member_access_expression->getMemberName() + "' of null object.");
      builder->CreateCall(runtime_err_fn, {msg});
    }
    builder->CreateUnreachable(); // Stop execution here

    // C. Continue Normal Execution
    m_ir_gen_context.setInsertPoint(continue_block);
  }

  auto *custom_object_type =
      static_cast<types::CustomObjectType *>(object_type);
  const std::string &member_name = member_access_expression->getMemberName();

  size_t field_index = 0;
  for (const auto &[field_name, field_type] :
       custom_object_type->getFieldTypesMap()) {
    if (field_name == member_name) {
      break;
    }
    field_index++;
  }

  auto *llvm_obj_type = static_cast<llvm::StructType *>(
      m_ir_gen_context.getTypeBuilder()->getLLVMType(object_type));

  auto &builder = m_ir_gen_context.getLLVMBuilder();
  llvm::Value *field_ptr = builder->CreateStructGEP(
      llvm_obj_type, object_value, static_cast<unsigned int>(field_index),
      member_name + "_ptr");

  types::Type *field_type = member_access_expression->getType().get();

  // Always return the pointer (like IdentifierExpression does)
  // This allows it to work both as an lvalue (assignment) and rvalue (reading)
  // When used as an rvalue, resolveValue will load it if needed
  m_last_value = field_ptr;
  m_last_llvm_type = field_ptr->getType();
  m_last_type = field_type;

  CODEGEN_DEBUG_LOG("Member Access Expression IR Generated", "Field Pointer",
                    field_type->getName());
}

} // namespace flow_wing::ir_gen