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


#include "ExpressionBinder.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundBooleanLiteralExpression/BoundBooleanLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundCharacterLiteralExpression/BoundCharacterLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundDoubleLiteralExpression/BoundDoubleLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundFloatLiteralExpression/BoundFloatLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundIntegerLiteralExpression/BoundIntegerLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundNirastLiteralExpression/BoundNirastLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundStringLiteralExpression/BoundStringLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundTemplateStringLiteralExpression/BoundTemplateStringLiteralExpression.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/syntax/expression/BooleanLiteralExpressionSyntax/BooleanLiteralExpressionSyntax.h"
#include "src/syntax/expression/CharacterLiteralExpressionSyntax/CharacterLiteralExpressionSyntax.h"
#include "src/syntax/expression/DoubleLiteralExpressionSyntax/DoubleLiteralExpressionSyntax.h"
#include "src/syntax/expression/FloatLiteralExpressionSyntax/FloatLiteralExpressionSyntax.h"
#include "src/syntax/expression/IntegerLiteralExpressionSyntax/IntegerLiteralExpressionSyntax.h"
#include "src/syntax/expression/StringLiteralExpressionSyntax/StringLiteralExpressionSyntax.h"
#include "src/syntax/expression/TemplateStringLiteralExpressionSyntax/TemplateStringLiteralExpressionSyntax.h"
#include <cassert>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundExpression> ExpressionBinder::bindLiteralExpression(
    syntax::IntegerLiteralExpressionSyntax *expression) {
  assert(expression != nullptr &&
         "LiteralExpressionBinder::bind: NumberLiteralExpressionSyntax "
         "expression is null");

  auto value = expression->getValue();

  std::shared_ptr<types::Type> type =
      (value >= std::numeric_limits<int32_t>::min() &&
       value <= std::numeric_limits<int32_t>::max())
          ? analysis::Builtins::m_int32_type_instance
          : analysis::Builtins::m_int64_type_instance;

  return std::make_unique<BoundIntegerLiteralExpression>(value, type);
}

std::unique_ptr<BoundExpression> ExpressionBinder::bindLiteralExpression(
    syntax::DoubleLiteralExpressionSyntax *expression) {
  assert(expression != nullptr &&
         "LiteralExpressionBinder::bind: DoubleLiteralExpressionSyntax "
         "expression is null");

  return std::make_unique<BoundDoubleLiteralExpression>(
      expression->getValue(), analysis::Builtins::m_deci_type_instance);
}

std::unique_ptr<BoundExpression> ExpressionBinder::bindLiteralExpression(
    syntax::FloatLiteralExpressionSyntax *expression) {
  assert(expression != nullptr &&
         "LiteralExpressionBinder::bind: FloatLiteralExpressionSyntax "
         "expression is null");

  return std::make_unique<BoundFloatLiteralExpression>(
      expression->getValue(), analysis::Builtins::m_deci32_type_instance);
}

std::unique_ptr<BoundExpression> ExpressionBinder::bindLiteralExpression(
    syntax::CharacterLiteralExpressionSyntax *expression) {
  assert(expression != nullptr &&
         "LiteralExpressionBinder::bind: expression is null");

  return std::make_unique<BoundCharacterLiteralExpression>(
      expression->getValue(), analysis::Builtins::m_int8_type_instance);
}

std::unique_ptr<BoundExpression> ExpressionBinder::bindLiteralExpression(
    syntax::StringLiteralExpressionSyntax *expression) {
  assert(expression != nullptr &&
         "LiteralExpressionBinder::bind: StringLiteralExpressionSyntax "
         "expression is null");

  return std::make_unique<BoundStringLiteralExpression>(
      expression->getValue(), analysis::Builtins::m_str_type_instance);
}

std::unique_ptr<BoundExpression> ExpressionBinder::bindLiteralExpression(
    syntax::TemplateStringLiteralExpressionSyntax *expression) {
  assert(expression != nullptr &&
         "LiteralExpressionBinder::bind: expression is null");

  return std::make_unique<BoundTemplateStringLiteralExpression>(
      expression->getValue(), analysis::Builtins::m_str_type_instance);
}

std::unique_ptr<BoundExpression> ExpressionBinder::bindLiteralExpression(
    syntax::BooleanLiteralExpressionSyntax *expression) {
  assert(expression != nullptr &&
         "LiteralExpressionBinder::bind: expression is null");

  return std::make_unique<BoundBooleanLiteralExpression>(
      expression->getValue(), analysis::Builtins::m_bool_type_instance);
}

std::unique_ptr<BoundExpression> ExpressionBinder::bindLiteralExpression(
    syntax::NirastExpressionSyntax *expression) {
  assert(expression != nullptr &&
         "LiteralExpressionBinder::bind: expression is null");

  return std::make_unique<BoundNirastLiteralExpression>(
      analysis::Builtins::m_nirast_type_instance);
}
} // namespace binding
} // namespace flow_wing