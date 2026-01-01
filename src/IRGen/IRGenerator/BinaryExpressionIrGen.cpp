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
#include "src/SemanticAnalyzer/BoundExpressions/BoundBinaryExpression/BoundBinaryExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundBinaryOperator/BoundBinaryOperator.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/common/types/Type.hpp"
#include "src/utils/LogConfig.h"

namespace flow_wing::ir_gen {

llvm::Value *IRGenerator::getBinaryResult(llvm::Value *left_value,
                                          llvm::Value *right_value,
                                          lexer::TokenKind operator_kind,
                                          types::Type *left_type,
                                          types::Type *right_type,
                                          types::Type *result_type) {

  // Handle dynamic type result
  if (result_type->isDynamic()) {
    return getDynamicBinaryResult(left_value, right_value, operator_kind,
                                  left_type, right_type);
  }

  if (result_type == analysis::Builtins::m_bool_type_instance.get()) {

    return getBooleanResult(left_value, right_value, operator_kind, left_type,
                            right_type);
  }

  if (result_type == analysis::Builtins::m_int32_type_instance.get()) {
    return getInt32Result(left_value, right_value, operator_kind, left_type,
                          right_type);
  } else if (result_type == analysis::Builtins::m_int64_type_instance.get()) {
    return getInt64Result(left_value, right_value, operator_kind, left_type,
                          right_type);
  } else if (result_type == analysis::Builtins::m_int8_type_instance.get()) {
    return getInt8Result(left_value, right_value, operator_kind, left_type,
                         right_type);
  }

  if (result_type == analysis::Builtins::m_char_type_instance.get()) {
    return getCharResult(left_value, right_value, operator_kind);
  }

  if (result_type == analysis::Builtins::m_deci32_type_instance.get()) {
    return getDecimal32Result(left_value, right_value, operator_kind);
  }

  if (result_type == analysis::Builtins::m_deci_type_instance.get()) {
    return getDecimalResult(left_value, right_value, operator_kind);
  }

  if (result_type == analysis::Builtins::m_str_type_instance.get()) {
    return getStringResult(left_value, right_value, operator_kind, left_type,
                           right_type);
  }

  assert(false && "Unsupported binary operator");
  return nullptr;
}

void IRGenerator::visit(binding::BoundBinaryExpression *binary_expression) {
  CODEGEN_DEBUG_LOG("Visiting Bound Binary Expression", "IR GENERATION");

  binary_expression->getLeft()->accept(this);
  assert(m_last_value && "m_last_value is null");
  llvm::Value *left_value = m_last_value;
  types::Type *left_type = m_last_type;
  clearLast();
  binary_expression->getRight()->accept(this);
  assert(m_last_value && "m_last_value is null");
  llvm::Value *right_value = m_last_value;
  types::Type *right_type = m_last_type;
  clearLast();

  auto binary_operator = binary_expression->getBinaryOperator();
  auto binary_operator_kind = binary_operator->getSyntaxKind();
  auto result_type = binary_operator->getResultType().get();

  // For dynamic types, keep pointers; for primitives, resolve values
  if (!left_type->isDynamic()) {
    left_value = resolveValue(left_value, left_type);
  }
  if (!right_type->isDynamic()) {
    right_value = resolveValue(right_value, right_type);
  }

  auto binary_operator_result =
      getBinaryResult(left_value, right_value, binary_operator_kind,
                      binary_operator->getLeftType().get(),
                      binary_operator->getRightType().get(), result_type);
  m_last_type = result_type;
  m_last_value = binary_operator_result;
}
} // namespace flow_wing::ir_gen