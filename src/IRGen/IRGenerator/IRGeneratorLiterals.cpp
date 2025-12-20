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



#include "IRGenerator.hpp"
#include "src/IRGen/IRGenContext/IRGenContext.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundBooleanLiteralExpression/BoundBooleanLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundDoubleLiteralExpression/BoundDoubleLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundIntegerLiteralExpression/BoundIntegerLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundStringLiteralExpression/BoundStringLiteralExpression.hpp"

// clang-format off
#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"
// clang-format on

namespace flow_wing {
namespace ir_gen {

void IRGenerator::visit([[maybe_unused]] binding::BoundIntegerLiteralExpression
                            *integer_literal_expression) {
  m_last_value = llvm::ConstantInt::get(
      *m_ir_gen_context.getLLVMContext(),
      llvm::APInt(32,
                  static_cast<uint32_t>(integer_literal_expression->getValue()),
                  true));
}

void IRGenerator::visit([[maybe_unused]] binding::BoundDoubleLiteralExpression
                            *double_literal_expression) {
  m_last_value = llvm::ConstantFP::get(
      *m_ir_gen_context.getLLVMContext(),
      llvm::APFloat(double_literal_expression->getValue()));
}

void IRGenerator::visit([[maybe_unused]] binding::BoundStringLiteralExpression
                            *string_literal_expression) {
  m_last_value = m_ir_gen_context.getLLVMBuilder()->CreateGlobalStringPtr(
      string_literal_expression->getValue());
}

void IRGenerator::visit([[maybe_unused]] binding::BoundBooleanLiteralExpression
                            *boolean_literal_expression) {
  m_last_value = llvm::ConstantInt::get(
      *m_ir_gen_context.getLLVMContext(),
      llvm::APInt(1, boolean_literal_expression->getValue() ? 1 : 0, false));
}

void IRGenerator::visit(
    [[maybe_unused]] binding::BoundTemplateStringLiteralExpression
        *template_string_literal_expression) {

  m_last_value = m_ir_gen_context.getLLVMBuilder()->CreateGlobalStringPtr(
      template_string_literal_expression->getValue());
}

void IRGenerator::visit(
    [[maybe_unused]] binding::BoundCharacterLiteralExpression
        *character_literal_expression) {

  m_last_value = llvm::ConstantInt::get(
      *m_ir_gen_context.getLLVMContext(),
      llvm::APInt(
          8, static_cast<uint8_t>(character_literal_expression->getValue()),
          true));
}

} // namespace ir_gen
} // namespace flow_wing