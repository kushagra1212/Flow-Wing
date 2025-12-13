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


#include "BoundTreeJson.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundExposeStatement/BoundExposeStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundVariableDeclaration/BoundVariableDeclaration.h"
#include "src/SemanticAnalyzer/SyntaxBinder/BoundCompilationUnit.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/Symbol/ParameterSymbol.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/common/types/Type.hpp"
#include "src/common/utils/stringUtils/StringUtils.hpp"
#include "src/utils/LogConfig.h"
#include <memory>
#include <vector>

namespace flow_wing::compiler::serializer {

nlohmann::json BoundTreeJson::toJson(
    const std::unique_ptr<binding::BoundCompilationUnit> &bound_tree) const {
  PARSER_DEBUG_LOG("Serializing Bound Tree to JSON", "BOUND TREE");
  bound_tree->accept(const_cast<BoundTreeJson *>(this));
  return m_bound_tree_json;
}

template <typename T>
void BoundTreeJson::serializeChild(const std::unique_ptr<T> &node,
                                   nlohmann::json &parent,
                                   const std::string &key) {
  if (node) {
    node->accept(this);
    parent[key] = std::move(m_last_node_json);
  } else {
    parent[key] = nullptr;
  }
}

template <typename T>
void BoundTreeJson::serializeArray(const std::vector<std::unique_ptr<T>> &nodes,
                                   nlohmann::json &parent,
                                   const std::string &key) {
  nlohmann::json array = nlohmann::json::array();
  for (const auto &node : nodes) {
    if (node) {
      node->accept(this);
      array.push_back(std::move(m_last_node_json));
    }
  }
  parent[key] = std::move(array);
}

nlohmann::json BoundTreeJson::toJsonSourcePoint(
    const flow_wing::diagnostic::SourcePoint &point) {
  return {point.line_number, point.column_number};
}

nlohmann::json BoundTreeJson::toJsonRange(
    const flow_wing::diagnostic::SourceLocation &location) {
  return {{"start", toJsonSourcePoint(location.m_start)},
          {"end", toJsonSourcePoint(location.m_end)}};
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundCompilationUnit *compilation_unit) {
  PARSER_DEBUG_LOG("Visiting Bound Compilation Unit", "BOUND TREE");
  nlohmann::json compilation_unit_json;
  compilation_unit_json["kind"] = toString(compilation_unit->getKind());
  compilation_unit_json["range"] =
      toJsonRange(compilation_unit->getSourceLocation());
  serializeArray(compilation_unit->getStatements(), compilation_unit_json,
                 "statements");

  m_bound_tree_json = {{"tree", compilation_unit_json},
                       {"symbols", m_symbols_json},
                       {"types", m_types_json}};
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundBlockStatement *block_statement) {
  PARSER_DEBUG_LOG("Visiting Bound Block Statement", "BOUND TREE");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundExposeStatement *expose_statement) {
  PARSER_DEBUG_LOG("Visiting Bound Expose Statement", "BOUND TREE");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundCustomTypeStatement *custom_type_statement) {
  PARSER_DEBUG_LOG("Visiting Bound Custom Type Statement", "BOUND TREE");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundVariableDeclaration *variable_declaration) {
  PARSER_DEBUG_LOG("Visiting Bound Variable Declaration", "BOUND TREE");

  // nlohmann::json variable_declaration_json;
  // variable_declaration_json["kind"] =
  // toString(variable_declaration->getKind());
  // serializeChild(variable_declaration->getIdentifierExpression(),
  //                variable_declaration_json, "identifier_expression");
  // serializeChild(variable_declaration->getTypeExpression(),
  //                variable_declaration_json, "type_expression");
  // variable_declaration_json["range"] =
  //     toJsonRange(variable_declaration->getSourceLocation());
  // m_last_node_json = std::move(variable_declaration_json);
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundFunctionStatement *function_statement) {
  PARSER_DEBUG_LOG("Visiting Bound Function Statement", "BOUND TREE");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundIfStatement *if_statement) {
  PARSER_DEBUG_LOG("Visiting Bound If Statement", "BOUND TREE");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundWhileStatement *while_statement) {
  PARSER_DEBUG_LOG("Visiting Bound While Statement", "BOUND TREE");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundForStatement *for_statement) {
  PARSER_DEBUG_LOG("Visiting Bound For Statement", "BOUND TREE");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundBreakStatement *break_statement) {
  PARSER_DEBUG_LOG("Visiting Bound Break Statement", "BOUND TREE");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundContinueStatement *continue_statement) {
  PARSER_DEBUG_LOG("Visiting Bound Continue Statement", "BOUND TREE");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundReturnStatement *return_statement) {
  PARSER_DEBUG_LOG("Visiting Bound Return Statement", "BOUND TREE");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundSwitchStatement *switch_statement) {
  PARSER_DEBUG_LOG("Visiting Bound Switch Statement", "BOUND TREE");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundClassStatement *class_statement) {
  PARSER_DEBUG_LOG("Visiting Bound Class Statement", "BOUND TREE");
}

void BoundTreeJson::visit([[maybe_unused]] binding::BoundIdentifierExpression
                              *identifier_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Identifier Expression", "BOUND TREE");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundIndexExpression *index_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Index Expression", "BOUND TREE");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundExpressionStatement *expression_statement) {
  PARSER_DEBUG_LOG("Visiting Bound Expression Statement", "BOUND TREE");

  nlohmann::json expression_statement_json;
  expression_statement_json["kind"] = toString(expression_statement->getKind());
  serializeChild(expression_statement->getExpression(),
                 expression_statement_json, "expression");
  expression_statement_json["range"] =
      toJsonRange(expression_statement->getSourceLocation());

  m_last_node_json = std::move(expression_statement_json);
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundIntegerLiteralExpression
        *integer_literal_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Integer Literal Expression", "BOUND TREE");
}

void BoundTreeJson::visit([[maybe_unused]] binding::BoundDoubleLiteralExpression
                              *double_literal_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Double Literal Expression", "BOUND TREE");
}

void BoundTreeJson::visit([[maybe_unused]] binding::BoundFloatLiteralExpression
                              *float_literal_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Float Literal Expression", "BOUND TREE");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundCharacterLiteralExpression
        *character_literal_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Character Literal Expression", "BOUND TREE");
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
      visit(string_literal_expression->getType().get());

  m_last_node_json = std::move(string_literal_expression_json);
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundBooleanLiteralExpression
        *boolean_literal_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Boolean Literal Expression", "BOUND TREE");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundTemplateStringLiteralExpression
        *template_string_literal_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Template String Literal Expression",
                   "BOUND TREE");
}

void BoundTreeJson::visit([[maybe_unused]] binding::BoundNirastLiteralExpression
                              *nirast_literal_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Nirast Literal Expression", "BOUND TREE");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundErrorStatement *error_statement) {
  PARSER_DEBUG_LOG("Visiting Bound Error Statement", "BOUND TREE");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundErrorExpression *error_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Error Expression", "BOUND TREE");
}

void BoundTreeJson::visit([[maybe_unused]] binding::BoundModuleAccessExpression
                              *module_access_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Module Access Expression", "BOUND TREE");
}

std::string BoundTreeJson::getShortId(const void *ptr) {
  if (m_ptr_to_id_map.find(ptr) == m_ptr_to_id_map.end()) {
    m_ptr_to_id_map[ptr] = m_next_id++;
  }

  size_t id = m_ptr_to_id_map[ptr];

  std::stringstream ss;
  ss << "0x" << std::uppercase << std::hex << id;
  return ss.str();
}

std::string
BoundTreeJson::visit(const analysis::FunctionSymbol *function_symbol) {
  PARSER_DEBUG_LOG("Visiting Function Symbol", "BOUND TREE");
  nlohmann::json function_symbol_json;
  function_symbol_json["kind"] =
      analysis::Symbol::toString(function_symbol->getKind());
  function_symbol_json["name"] = function_symbol->getName();
  function_symbol_json["typeId"] =
      visit(static_cast<const types::FunctionType *>(
          function_symbol->getType().get()));
  const auto &symbol_id = getShortId(function_symbol);
  function_symbol_json["is_declaration"] =
      function_symbol->getBody() == nullptr;

  for (const auto &parameter : function_symbol->getParameters()) {
    function_symbol_json["parameters"].push_back(visit(parameter.get()));
  }

  // TODO(kushagra): Add Ranges for Symbols

  m_symbols_json[symbol_id] = function_symbol_json;

  return symbol_id;
};

std::string BoundTreeJson::visit(const types::ParameterType *parameter_type) {
  PARSER_DEBUG_LOG("Visiting Parameter Type", "BOUND TREE");
  nlohmann::json parameter_type_json;

  parameter_type_json["kind"] = "ParameterType";
  parameter_type_json["baseTypeId"] = visit(parameter_type->type.get());
  parameter_type_json["valueKind"] =
      types::toString(parameter_type->value_kind);
  parameter_type_json["typeConvention"] =
      types::toString(parameter_type->type_convention);
  parameter_type_json["constness"] = types::toString(parameter_type->constness);

  const auto &parameter_type_id = getShortId(parameter_type);
  m_types_json[parameter_type_id] = parameter_type_json;

  return parameter_type_id;
}
std::string BoundTreeJson::visit(const types::ReturnType *return_type) {
  PARSER_DEBUG_LOG("Visiting Return Type", "BOUND TREE");
  nlohmann::json return_type_json;
  return_type_json["kind"] = "ReturnType";
  return_type_json["baseTypeId"] = visit(return_type->type.get());
  return_type_json["typeConvention"] =
      types::toString(return_type->type_convention);

  const auto &return_type_id = getShortId(return_type);
  m_types_json[return_type_id] = return_type_json;

  return return_type_id;
}

std::string BoundTreeJson::visit(const types::Type *type) {
  PARSER_DEBUG_LOG("Visiting Type", "BOUND TREE");
  nlohmann::json type_json;
  type_json["kind"] = types::Type::toString(type->getKind());
  type_json["name"] = type->getName();

  const auto &type_id = getShortId(type);

  m_types_json[type_id] = type_json;

  return type_id;
}

std::string BoundTreeJson::visit(const types::FunctionType *function_type) {
  PARSER_DEBUG_LOG("Visiting Function Type", "BOUND TREE");
  nlohmann::json function_type_json;
  function_type_json["kind"] = types::Type::toString(function_type->getKind());
  function_type_json["name"] = function_type->getName();

  for (const auto &parameter : function_type->getParameterTypes()) {
    function_type_json["parameter_types"].push_back(visit(parameter.get()));
  }

  for (const auto &return_type : function_type->getReturnTypes()) {
    function_type_json["return_types"].push_back(visit(return_type.get()));
  }

  const auto &type_id = getShortId(function_type);
  m_types_json[type_id] = function_type_json;

  return type_id;
}

std::string
BoundTreeJson::visit(const analysis::ParameterSymbol *parameter_symbol) {
  PARSER_DEBUG_LOG("Visiting Parameter Symbol", "BOUND TREE");
  nlohmann::json parameter_symbol_json;
  parameter_symbol_json["kind"] =
      analysis::Symbol::toString(parameter_symbol->getKind());
  parameter_symbol_json["name"] = parameter_symbol->getName();
  parameter_symbol_json["typeId"] = visit(parameter_symbol->getType().get());

  const auto &parameter_symbol_id = getShortId(parameter_symbol);

  m_symbols_json[parameter_symbol_id] = parameter_symbol_json;

  return parameter_symbol_id;
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundCallExpression *call_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Call Expression", "BOUND TREE");
  nlohmann::json call_expression_json;
  call_expression_json["kind"] = toString(call_expression->getKind());

  call_expression_json["symbolId"] = visit(call_expression->getSymbol());

  serializeArray(call_expression->getArguments(), call_expression_json,
                 "arguments");

  call_expression_json["range"] =
      toJsonRange(call_expression->getSourceLocation());
  m_last_node_json = std::move(call_expression_json);
}

void BoundTreeJson::visit([[maybe_unused]] binding::BoundMemberAccessExpression
                              *member_access_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Member Access Expression", "BOUND TREE");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundTernaryExpression *ternary_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Ternary Expression", "BOUND TREE");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundNewExpression *new_expression) {
  PARSER_DEBUG_LOG("Visiting Bound New Expression", "BOUND TREE");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundUnaryExpression *unary_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Unary Expression", "BOUND TREE");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundBinaryExpression *binary_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Binary Expression", "BOUND TREE");
}

void BoundTreeJson::visit([[maybe_unused]] binding::BoundAssignmentExpression
                              *assignment_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Assignment Expression", "BOUND TREE");
}

} // namespace flow_wing::compiler::serializer
