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

#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundBooleanLiteralExpression/BoundBooleanLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundCharacterLiteralExpression/BoundCharacterLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundDoubleLiteralExpression/BoundDoubleLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundFloatLiteralExpression/BoundFloatLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundIntegerLiteralExpression/BoundIntegerLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundNirastLiteralExpression/BoundNirastLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundStringLiteralExpression/BoundStringLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundTemplateStringLiteralExpression/BoundTemplateStringLiteralExpression.hpp"
#include "src/compiler/Serialization/BoundTree/BoundTreeJson.hpp"

namespace flow_wing::compiler::serializer {
void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundIntegerLiteralExpression
        *integer_literal_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Integer Literal Expression", "BOUND TREE");

  nlohmann::json integer_literal_expression_json;
  integer_literal_expression_json["kind"] =
      toString(integer_literal_expression->getKind());
  integer_literal_expression_json["value"] =
      integer_literal_expression->getValue();
  integer_literal_expression_json["range"] =
      toJsonRange(integer_literal_expression->getSourceLocation());
  integer_literal_expression_json["typeId"] =
      getTypeId(integer_literal_expression->getType().get());

  m_last_node_json = std::move(integer_literal_expression_json);
}

void BoundTreeJson::visit([[maybe_unused]] binding::BoundDoubleLiteralExpression
                              *double_literal_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Double Literal Expression", "BOUND TREE");
  nlohmann::json double_literal_expression_json;
  double_literal_expression_json["kind"] =
      toString(double_literal_expression->getKind());
  double_literal_expression_json["value"] =
      double_literal_expression->getValue();
  double_literal_expression_json["range"] =
      toJsonRange(double_literal_expression->getSourceLocation());
  double_literal_expression_json["typeId"] =
      getTypeId(double_literal_expression->getType().get());

  m_last_node_json = std::move(double_literal_expression_json);
}

void BoundTreeJson::visit([[maybe_unused]] binding::BoundFloatLiteralExpression
                              *float_literal_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Float Literal Expression", "BOUND TREE");

  nlohmann::json float_literal_expression_json;
  float_literal_expression_json["kind"] =
      toString(float_literal_expression->getKind());
  float_literal_expression_json["value"] = float_literal_expression->getValue();
  float_literal_expression_json["range"] =
      toJsonRange(float_literal_expression->getSourceLocation());
  float_literal_expression_json["typeId"] =
      getTypeId(float_literal_expression->getType().get());

  m_last_node_json = std::move(float_literal_expression_json);
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundCharacterLiteralExpression
        *character_literal_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Character Literal Expression", "BOUND TREE");

  nlohmann::json character_literal_expression_json;
  character_literal_expression_json["kind"] =
      toString(character_literal_expression->getKind());
  character_literal_expression_json["value"] =
      character_literal_expression->getValue();
  character_literal_expression_json["range"] =
      toJsonRange(character_literal_expression->getSourceLocation());
  character_literal_expression_json["typeId"] =
      getTypeId(character_literal_expression->getType().get());

  m_last_node_json = std::move(character_literal_expression_json);
}

void BoundTreeJson::visit([[maybe_unused]] binding::BoundStringLiteralExpression
                              *string_literal_expression) {
  PARSER_DEBUG_LOG("Visiting Bound String Literal Expression", "BOUND TREE");

  nlohmann::json string_literal_expression_json;
  string_literal_expression_json["kind"] =
      toString(string_literal_expression->getKind());
  string_literal_expression_json["value"] =
      string_literal_expression->getValue();
  string_literal_expression_json["range"] =
      toJsonRange(string_literal_expression->getSourceLocation());
  string_literal_expression_json["typeId"] =
      getTypeId(string_literal_expression->getType().get());

  m_last_node_json = std::move(string_literal_expression_json);
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundBooleanLiteralExpression
        *boolean_literal_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Boolean Literal Expression", "BOUND TREE");

  nlohmann::json boolean_literal_expression_json;
  boolean_literal_expression_json["kind"] =
      toString(boolean_literal_expression->getKind());
  boolean_literal_expression_json["value"] =
      boolean_literal_expression->getValue();
  boolean_literal_expression_json["range"] =
      toJsonRange(boolean_literal_expression->getSourceLocation());
  boolean_literal_expression_json["typeId"] =
      getTypeId(boolean_literal_expression->getType().get());

  m_last_node_json = std::move(boolean_literal_expression_json);
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundTemplateStringLiteralExpression
        *template_string_literal_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Template String Literal Expression",
                   "BOUND TREE");

  nlohmann::json template_string_literal_expression_json;
  template_string_literal_expression_json["kind"] =
      toString(template_string_literal_expression->getKind());
  template_string_literal_expression_json["value"] =
      template_string_literal_expression->getValue();
  template_string_literal_expression_json["range"] =
      toJsonRange(template_string_literal_expression->getSourceLocation());
  template_string_literal_expression_json["typeId"] =
      getTypeId(template_string_literal_expression->getType().get());

  m_last_node_json = std::move(template_string_literal_expression_json);
}

void BoundTreeJson::visit([[maybe_unused]] binding::BoundNirastLiteralExpression
                              *nirast_literal_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Nirast Literal Expression", "BOUND TREE");

  nlohmann::json nirast_literal_expression_json;
  nirast_literal_expression_json["kind"] =
      toString(nirast_literal_expression->getKind());
  nirast_literal_expression_json["range"] =
      toJsonRange(nirast_literal_expression->getSourceLocation());
  nirast_literal_expression_json["typeId"] =
      getTypeId(nirast_literal_expression->getType().get());

  m_last_node_json = std::move(nirast_literal_expression_json);
}
} // namespace flow_wing::compiler::serializer