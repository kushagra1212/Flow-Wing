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

    auto *var_type = variable_symbol->getType().get();
    auto *llvm_type = m_ir_gen_context.getTypeBuilder()->getLLVMType(var_type);
    llvm::Value *storage_ptr = nullptr;

    if (m_ir_gen_context.isGlobalScope()) {
      llvm::Value *existing_global_variable =
          m_ir_gen_context.getSymbol(variable_symbol->getName());
      if (existing_global_variable &&
          llvm::isa<llvm::GlobalVariable>(existing_global_variable)) {
        storage_ptr = existing_global_variable;
      }
    }

    // Fallback for locals or new globals
    if (!storage_ptr) {
      storage_ptr =
          m_ir_gen_context.createAlloca(llvm_type, variable_symbol->getName());
      m_ir_gen_context.setSymbol(variable_symbol->getName(), storage_ptr);
    }

    // Handle Initialization
    if (auto *init_expression =
            variable_symbol->getInitializerExpression().get()) {
      init_expression->accept(this);

      emitTypedStore(storage_ptr, var_type, m_last_value, m_last_type);
    } else {
      // Default Initialization
      auto *default_value = m_ir_gen_context.getDefaultValue(var_type);
      m_ir_gen_context.getLLVMBuilder()->CreateStore(default_value,
                                                     storage_ptr);
    }

    clearLast();
  }
}
} // namespace flow_wing::ir_gen
