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

      llvm::Value *value_to_store = resolveValue(m_last_value, m_last_type);
      if (value_to_store->getType() != llvm_type) {
        value_to_store =
            convertToTargetType(value_to_store, variable_type, m_last_type);
      }

      m_ir_gen_context.getLLVMBuilder()->CreateStore(value_to_store,
                                                     storage_ptr);
    } else {
      m_ir_gen_context.getLLVMBuilder()->CreateStore(
          m_ir_gen_context.getDefaultValue(variable_type), storage_ptr);
    }

    clearLast();
  }
}
} // namespace flow_wing::ir_gen
