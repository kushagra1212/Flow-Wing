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

  const auto &symbols = variable_declaration->getSymbols();
  const auto &multi_exprs = variable_declaration->getInitializerExpressions();
  auto &builder = m_ir_gen_context.getLLVMBuilder();

  size_t var_idx = 0;
  size_t expr_idx = 0;

  while (var_idx < symbols.size()) {
    if (expr_idx < multi_exprs.size() && multi_exprs[expr_idx] != nullptr &&
        multi_exprs[expr_idx]->isMultipleType()) {
      auto &expr = multi_exprs[expr_idx];
      expr->accept(this);

      assert(m_last_value &&
             "m_last_value is null after initializer expression");
      llvm::Value *struct_ptr = m_last_value;
      llvm::Type *struct_type = m_last_llvm_type;

      size_t num_returns = expr->getMultipleTypes().size();
      for (size_t i = 0; i < num_returns; ++i) {
        if (var_idx >= symbols.size())
          break;

        const auto &variable_symbol =
            static_cast<const analysis::VariableSymbol *>(
                symbols[var_idx].get());

        CODEGEN_DEBUG_LOG("Variable Symbol (Multi)",
                          variable_symbol->getName());

        auto *var_type = variable_symbol->getType().get();
        auto *llvm_type =
            m_ir_gen_context.getTypeBuilder()->getLLVMType(var_type);
        llvm::Value *storage_ptr = nullptr;

        if (m_ir_gen_context.isGlobalScope()) {
          llvm::Value *existing_global_variable =
              m_ir_gen_context.getSymbol(variable_symbol->getName());
          if (existing_global_variable &&
              llvm::isa<llvm::GlobalVariable>(existing_global_variable)) {
            storage_ptr = existing_global_variable;
          }
        }

        if (!storage_ptr) {
          storage_ptr = m_ir_gen_context.createAlloca(
              llvm_type, variable_symbol->getName());
          m_ir_gen_context.setSymbol(variable_symbol->getName(), storage_ptr);
        }

        llvm::Value *gep = builder->CreateStructGEP(
            struct_type, struct_ptr, static_cast<unsigned>(i),
            "extract_" + variable_symbol->getName());
        llvm::Value *extracted_val = builder->CreateLoad(
            llvm_type, gep, "load_" + variable_symbol->getName());

        emitTypedStore(storage_ptr, var_type, extracted_val, var_type);
        var_idx++;
      }
    } else {
      const auto &variable_symbol =
          static_cast<const analysis::VariableSymbol *>(symbols[var_idx].get());

      CODEGEN_DEBUG_LOG("Variable Symbol (Single)", variable_symbol->getName());

      auto *var_type = variable_symbol->getType().get();
      auto *llvm_type =
          m_ir_gen_context.getTypeBuilder()->getLLVMType(var_type);
      llvm::Value *storage_ptr = nullptr;

      if (m_ir_gen_context.isGlobalScope()) {
        llvm::Value *existing_global_variable =
            m_ir_gen_context.getSymbol(variable_symbol->getName());
        if (existing_global_variable &&
            llvm::isa<llvm::GlobalVariable>(existing_global_variable)) {
          storage_ptr = existing_global_variable;
        }
      }

      if (!storage_ptr) {
        storage_ptr = m_ir_gen_context.createAlloca(llvm_type,
                                                    variable_symbol->getName());
        m_ir_gen_context.setSymbol(variable_symbol->getName(), storage_ptr);
      }

      auto *init_expression = variable_symbol->getInitializerExpression().get();
      if (init_expression) {
        init_expression->accept(this);
        assert(m_last_value &&
               "m_last_value is null after initializer expression");
        emitTypedStore(storage_ptr, var_type, m_last_value, m_last_type);
      }
      var_idx++;
    }

    expr_idx++;
    clearLast();
  }
}
} // namespace flow_wing::ir_gen
