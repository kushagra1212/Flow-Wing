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
#include "src/common/Symbol/VariableSymbol.hpp"
#include "src/utils/LogConfig.h"

namespace flow_wing::ir_gen {
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundVariableDeclaration *variable_declaration) {
  CODEGEN_DEBUG_LOG("Visiting Bound Variable Declaration", "IR GENERATION");

  for (const auto &symbol : variable_declaration->getSymbols()) {
    const auto &variable_symbol =
        static_cast<const analysis::VariableSymbol *>(symbol.get());

    auto variable_type = variable_symbol->getType().get();
    auto llvm_type =
        m_ir_gen_context.getTypeBuilder()->getLLVMType(variable_type);
    llvm::Value *storage_ptr = nullptr;

    bool is_global_scope = m_ir_gen_context.isGlobalScope();

    llvm::Value *existing_global_variable =
        m_ir_gen_context.getSymbol(variable_symbol->getName());

    if (is_global_scope && existing_global_variable &&
        llvm::isa<llvm::GlobalVariable>(existing_global_variable)) {
      storage_ptr = existing_global_variable;
    } else {
      storage_ptr =
          m_ir_gen_context.createAlloca(llvm_type, variable_symbol->getName());
      m_ir_gen_context.setSymbol(variable_symbol->getName(), storage_ptr);
    }

    if (variable_symbol->getInitializerExpression()) {
      variable_symbol->getInitializerExpression()->accept(this);

      // Handle dynamic type initialization
      if (variable_type == analysis::Builtins::m_dynamic_type_instance.get()) {
        if (m_last_type->isDynamic()) {
          // Dynamic to dynamic: just copy the struct
          // m_last_value is already the pointer to the dynamic value
          llvm::Value *dynamic_value = resolveValue(m_last_value, m_last_type);
          m_ir_gen_context.getLLVMBuilder()->CreateStore(dynamic_value,
                                                         storage_ptr);
        } else if (m_last_type->isPrimitive()) {
          // Primitive to dynamic: store primitive into dynamic struct
          llvm::Value *value_to_store = resolveValue(m_last_value, m_last_type);
          llvm::Value *dynamic_struct =
              DynamicValueHandler::storePrimitiveToDynamic(
                  value_to_store, value_to_store->getType(), llvm_type,
                  m_ir_gen_context.getLLVMBuilder().get(), m_last_type);
          m_ir_gen_context.getLLVMBuilder()->CreateStore(dynamic_struct,
                                                         storage_ptr);
        } else {
          // Non-primitive to dynamic: should have been caught by semantic
          // analyzer
          assert(false &&
                 "Non-primitive type cannot be assigned to dynamic variable");
        }
      } else if (m_last_type->isDynamic()) {
        llvm::Value *dynamic_ptr = m_last_value; // Keep pointer, don't resolve

        auto unboxing_function_name =
            analysis::Builtins::getUnboxingFunctionName(variable_type);

        llvm::FunctionCallee func =
            m_ir_gen_context.getLLVMModule()->getFunction(
                unboxing_function_name);

        llvm::Value *unboxed_val =
            m_ir_gen_context.getLLVMBuilder()->CreateCall(func, {dynamic_ptr});

        m_ir_gen_context.getLLVMBuilder()->CreateStore(unboxed_val,
                                                       storage_ptr);

      } else {
        // Primitive to primitive: normal conversion
        llvm::Value *value_to_store = resolveValue(m_last_value, m_last_type);
        if (value_to_store->getType() != llvm_type) {
          value_to_store =
              convertToTargetType(value_to_store, variable_type, m_last_type);
        }
        m_ir_gen_context.getLLVMBuilder()->CreateStore(value_to_store,
                                                       storage_ptr);
      }
    } else {
      m_ir_gen_context.getLLVMBuilder()->CreateStore(
          m_ir_gen_context.getDefaultValue(variable_type), storage_ptr);
    }

    clearLast();
  }
}
} // namespace flow_wing::ir_gen
