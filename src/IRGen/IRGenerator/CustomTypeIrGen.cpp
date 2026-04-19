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
#include "src/SemanticAnalyzer/BoundStatements/BoundCustomTypeStatement/BoundCustomTypeStatement.h"
#include "src/utils/LogConfig.h"

namespace flow_wing::ir_gen {
void IRGenerator::visit(
    binding::BoundCustomTypeStatement *custom_type_statement) {
  CODEGEN_DEBUG_LOG("Visiting Bound Custom Type Statement", "IR GENERATION");

  auto custom_type_symbol = custom_type_statement->getSymbols().front();
  assert(custom_type_symbol && "Custom type symbol is null");

  CODEGEN_DEBUG_LOG("Custom Type Symbol", custom_type_symbol->getName());

  auto symbol_type = custom_type_symbol->getType();
  assert(symbol_type && "Symbol type is null");

  CODEGEN_DEBUG_LOG("Symbol Type", symbol_type->getName());

  auto llvm_type =
      m_ir_gen_context.getTypeBuilder()->getLLVMType(symbol_type.get());

  CODEGEN_DEBUG_LOG("LLVM Type", llvm_type->getStructName().str());
  m_last_llvm_type = llvm_type;
  m_last_type = symbol_type.get();
}
} // namespace flow_wing::ir_gen