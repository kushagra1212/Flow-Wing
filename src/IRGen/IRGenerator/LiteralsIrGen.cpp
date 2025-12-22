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

void IRGenerator::visit(
    binding::BoundIntegerLiteralExpression *integer_literal_expression) {
  m_last_value = llvm::ConstantInt::get(
      *m_ir_gen_context.getLLVMContext(),
      llvm::APInt(32,
                  static_cast<uint32_t>(integer_literal_expression->getValue()),
                  true));
}

void IRGenerator::visit(
    binding::BoundDoubleLiteralExpression *double_literal_expression) {
  m_last_value = llvm::ConstantFP::get(
      *m_ir_gen_context.getLLVMContext(),
      llvm::APFloat(double_literal_expression->getValue()));
}

std::string IRGenerator::unescapeString(const std::string &value) {
  std::string string_value = "";
  size_t pos = 0, len = value.size();
  while (pos < len) {
    if (value[pos] == '\\' && pos + 1 < len) {
      switch (value[++pos]) {
      case 'n': {
        string_value += '\n';
        pos++;
        continue;
      }
      case 'r': {
        string_value += '\r';
        pos++;
        continue;
      }
      case 't': {
        string_value += '\t';
        pos++;
        continue;
      }
      case '0': {
        string_value += '\0';
        pos++;
        continue;
      }
      default: {
        string_value += value[pos];
        pos++;
        continue;
      }
      }
    } else {
      string_value += value[pos++];
    }
  }

  return string_value;
}
void IRGenerator::visit(
    binding::BoundStringLiteralExpression *string_literal_expression) {

  m_last_value = m_ir_gen_context.getLLVMBuilder()->CreateGlobalStringPtr(
      unescapeString(string_literal_expression->getValue()));
}

void IRGenerator::visit(
    binding::BoundBooleanLiteralExpression *boolean_literal_expression) {
  m_last_value = llvm::ConstantInt::get(
      *m_ir_gen_context.getLLVMContext(),
      llvm::APInt(1, boolean_literal_expression->getValue() ? 1 : 0, false));
}

void IRGenerator::visit(binding::BoundTemplateStringLiteralExpression
                            *template_string_literal_expression) {

  m_last_value = m_ir_gen_context.getLLVMBuilder()->CreateGlobalStringPtr(
      template_string_literal_expression->getValue());
}

void IRGenerator::visit(
    binding::BoundCharacterLiteralExpression *character_literal_expression) {

  m_last_value = llvm::ConstantInt::get(
      *m_ir_gen_context.getLLVMContext(),
      llvm::APInt(
          8, static_cast<uint8_t>(character_literal_expression->getValue()),
          true));
}

} // namespace ir_gen
} // namespace flow_wing