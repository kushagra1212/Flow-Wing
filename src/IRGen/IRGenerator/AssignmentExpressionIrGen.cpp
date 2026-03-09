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

#include "src/IRGen/FlowWingConstants/FlowWingConstants.hpp"
#include "src/IRGen/IRGenerator/IRGenHelper/DynamicValueHandler.h"
#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/common/types/Type.hpp"
#include "src/utils/LogConfig.h"
#include <cassert>

namespace flow_wing::ir_gen {
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundAssignmentExpression *statement) {
  CODEGEN_DEBUG_LOG("Visiting Bound Assignment Expression", "IR GENERATION");

  const auto &left_expressions = statement->getLeft();
  const auto &right_expressions = statement->getRight();
  auto &builder = m_ir_gen_context.getLLVMBuilder();

  size_t var_idx = 0;
  size_t expr_idx = 0;

  while (var_idx < left_expressions.size()) {
    if (expr_idx < right_expressions.size() &&
        right_expressions[expr_idx]->isMultipleType()) {
      auto *expr = right_expressions[expr_idx].get();
      expr->accept(this);

      assert(m_last_value &&
             "m_last_value is null after multi-return expression");
      llvm::Value *struct_ptr = m_last_value;
      llvm::Type *struct_type = m_last_llvm_type;

      size_t num_returns = expr->getMultipleTypes().size();
      for (size_t i = 0; i < num_returns; ++i) {
        if (var_idx >= left_expressions.size())
          break;

        auto *left_expression = left_expressions[var_idx].get();
        left_expression->accept(this);
        llvm::Value *target_ptr = m_last_value;
        types::Type *target_type = m_last_type;

        assert(target_ptr && "target pointer is null");
        assert(target_type && "target type is null");
        clearLast();

        llvm::Value *gep = builder->CreateStructGEP(
            struct_type, struct_ptr, static_cast<unsigned>(i),
            "assign_extract_" + std::to_string(var_idx));
        types::Type *field_type = expr->getMultipleTypes()[i].get();
        llvm::Type *field_llvm_type =
            m_ir_gen_context.getTypeBuilder()->getLLVMType(field_type);
        llvm::Value *extracted_val =
            builder->CreateLoad(field_llvm_type, gep, "assign_load");

        emitTypedStore(target_ptr, target_type, extracted_val, field_type);
        var_idx++;
      }
      expr_idx++;
    } else {
      auto *left_expression = left_expressions[var_idx].get();
      auto *right_expression = right_expressions[expr_idx].get();

      left_expression->accept(this);
      auto *target_ptr = m_last_value;
      auto *target_type = m_last_type;

      assert(target_ptr && "target pointer is null");
      assert(target_type && "target type is null");
      clearLast();

      right_expression->accept(this);
      auto *source_val = m_last_value;
      auto *source_type = m_last_type;

      assert(source_val && "Assignment source value is null");

      CODEGEN_DEBUG_LOG("Target Type", target_type->getName());
      CODEGEN_DEBUG_LOG("Source Type", source_type->getName());

      emitTypedStore(target_ptr, target_type, source_val, source_type);

      var_idx++;
      expr_idx++;
    }
    clearLast();
  }
}
}; // namespace flow_wing::ir_gen