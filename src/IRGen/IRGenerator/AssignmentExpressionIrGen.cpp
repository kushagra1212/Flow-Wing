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
#include "src/SemanticAnalyzer/BoundExpressions/BoundIndexExpression/BoundIndexExpression.h"
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
  auto *module = m_ir_gen_context.getLLVMModule();

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

      if (left_expression->getKind() == binding::NodeKind::kIndexExpression) {
        auto *index_expression =
            static_cast<binding::BoundIndexExpression *>(left_expression);
        auto *base_expression = index_expression->getLeftExpression().get();

        base_expression->accept(this);
        llvm::Value *base_value = m_last_value;
        types::Type *base_type = m_last_type;
        assert(base_value && "string index base value is null");
        assert(base_type && "string index base type is null");
        clearLast();

        if (base_type == analysis::Builtins::m_str_type_instance.get() ||
            base_type->isDynamic()) {
          const auto &dimension_expressions =
              index_expression->getDimensionClauseExpressions();
          assert(dimension_expressions.size() == 1 &&
                 "string indexing must have exactly 1 index");
          dimension_expressions[0]->accept(this);

          llvm::Value *index_value = nullptr;
          if (m_last_type->isDynamic()) {
            llvm::Type *index_dynamic_type =
                m_ir_gen_context.getTypeBuilder()->getLLVMType(m_last_type);
            auto [index_storage, _tag] =
                DynamicValueHandler::extractDynamicValue(
                    m_last_value, index_dynamic_type, builder.get());
            index_value = index_storage;
          } else {
            index_value = resolveValue(m_last_value, m_last_type);
          }
          clearLast();

          index_value =
              builder->CreateIntCast(index_value, builder->getInt64Ty(), true,
                                     "str_idx_i64");

          right_expression->accept(this);
          llvm::Value *source_value = m_last_value;
          auto *source_type = m_last_type;
          assert(source_value && "string index source value is null");
          assert(source_type && "string index source type is null");
          clearLast();

          llvm::Value *source_char = nullptr;
          if (source_type->isDynamic()) {
            auto *unbox_char_fn = module->getFunction(
                std::string(constants::functions::kUnbox_char_fn));
            assert(unbox_char_fn && "fg_unbox_char function not found");
            llvm::Value *source_ptr =
                ensurePointer(source_value, source_type, "str_idx_rhs");
            source_char = builder->CreateCall(unbox_char_fn, {source_ptr},
                                              "str_idx_rhs_char");
          } else {
            llvm::Value *resolved_source =
                resolveValue(source_value, source_type);
            source_char =
                convertToChar(resolved_source, resolved_source->getType());
          }

          auto emit_string_index_set = [&](llvm::Value *string_ptr,
                                           llvm::Value *char_value) {
            llvm::FunctionType *fn_type = llvm::FunctionType::get(
                builder->getVoidTy(),
                {builder->getInt8PtrTy(), builder->getInt64Ty(),
                 builder->getInt32Ty()},
                false);
            auto callee = module->getOrInsertFunction(
                std::string(constants::functions::kString_set_fn), fn_type);
            builder->CreateCall(callee, {string_ptr, index_value, char_value});
          };

          auto emit_dynamic_string_index_set =
              [&](llvm::Value *value_storage, llvm::Value *type_tag,
                  llvm::Value *char_value) {
                llvm::FunctionType *fn_type = llvm::FunctionType::get(
                    builder->getVoidTy(),
                    {builder->getInt64Ty(), builder->getInt64Ty(),
                     builder->getInt64Ty(), builder->getInt32Ty()},
                    false);
                auto callee = module->getOrInsertFunction(
                    std::string(constants::functions::kDynamic_string_set_fn),
                    fn_type);
                auto *type_tag_i64 =
                    builder->CreateIntCast(type_tag, builder->getInt64Ty(),
                                           false, "dyn_tag_i64");
                builder->CreateCall(callee,
                                    {value_storage, type_tag_i64, index_value,
                                     char_value});
              };

          if (base_type == analysis::Builtins::m_str_type_instance.get()) {
            llvm::Value *string_ptr = resolveValue(base_value, base_type);
            emit_string_index_set(string_ptr, source_char);
          } else {
            llvm::Type *dynamic_struct_type =
                m_ir_gen_context.getTypeBuilder()->getLLVMType(base_type);
            auto [value_storage, type_tag] =
                DynamicValueHandler::extractDynamicValue(
                    base_value, dynamic_struct_type, builder.get());
            emit_dynamic_string_index_set(value_storage, type_tag, source_char);
          }

          var_idx++;
          expr_idx++;
          clearLast();
          continue;
        }
      }

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
