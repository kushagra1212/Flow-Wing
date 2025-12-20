/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
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

    auto llvm_type = m_ir_gen_context.getTypeBuilder()->getLLVMType(
        variable_symbol->getType().get());

    auto alloca =
        m_ir_gen_context.createAlloca(llvm_type, variable_symbol->getName());

    if (variable_symbol->getInitializerExpression()) {
      variable_symbol->getInitializerExpression()->accept(this);
      m_ir_gen_context.getLLVMBuilder()->CreateStore(m_last_value, alloca);
    } else {
      m_ir_gen_context.getLLVMBuilder()->CreateStore(
          getDefaultValue(variable_symbol->getType().get()), alloca);
    }

    m_ir_gen_context.setSymbol(variable_symbol->getName(), alloca);

    clearLastValue();
  }
}
} // namespace flow_wing::ir_gen
