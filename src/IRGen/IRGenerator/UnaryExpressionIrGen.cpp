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
#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundBinaryExpression/BoundBinaryExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundBinaryOperator/BoundBinaryOperator.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundUnaryExpression/BoundUnaryExpression.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/common/types/Type.hpp"
#include "src/utils/LogConfig.h"

namespace flow_wing::ir_gen {

llvm::Value *IRGenerator::getUnaryOperationResult(
    llvm::Value *value, lexer::TokenKind operator_kind,
    types::Type *result_type, types::Type *expression_type) {

  if (result_type == analysis::Builtins::m_int32_type_instance.get() ||
      result_type == analysis::Builtins::m_int8_type_instance.get() ||
      result_type == analysis::Builtins::m_int64_type_instance.get()) {
    return getIntResult(value, operator_kind);
  }

  if (result_type == analysis::Builtins::m_deci32_type_instance.get()) {
    return getDecimal32Result(value, operator_kind);
  }

  if (result_type == analysis::Builtins::m_deci_type_instance.get()) {
    return getDecimalResult(value, operator_kind);
  }

  if (result_type == analysis::Builtins::m_bool_type_instance.get()) {
    return getBoolResult(value, operator_kind, expression_type);
  }

  assert(false && "Unsupported unary operator");
  return nullptr;
}

void IRGenerator::visit(binding::BoundUnaryExpression *unary_expression) {
  CODEGEN_DEBUG_LOG("Visiting Bound Unary Expression", "IR GENERATION");

  unary_expression->getExpression()->accept(this);
  llvm::Value *expression_value = resolveValue(m_last_value, m_last_type);
  clearLast();

  auto unary_operator_kind = unary_expression->getOperatorTokenKind();
  const auto result_type = unary_expression->getType().get();
  const auto expression_type =
      unary_expression->getExpression()->getType().get();
  auto unary_operator_result = getUnaryOperationResult(
      expression_value, unary_operator_kind, result_type, expression_type);
  m_last_value = unary_operator_result;
  m_last_type = result_type;
}
} // namespace flow_wing::ir_gen