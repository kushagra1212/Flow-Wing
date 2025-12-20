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
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundIdentifierExpression/BoundIdentifierExpression.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundExposeStatement/BoundExposeStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundVariableDeclaration/BoundVariableDeclaration.h"
#include "src/SemanticAnalyzer/SyntaxBinder/BoundCompilationUnit.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/Symbol/ParameterSymbol.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/common/Symbol/VariableSymbol.hpp"
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

void BoundTreeJson::visit(binding::BoundBlockStatement *block_statement) {
  PARSER_DEBUG_LOG("Visiting Bound Block Statement", "BOUND TREE");

  nlohmann::json block_statement_json;
  block_statement_json["kind"] = toString(block_statement->getKind());
  serializeArray(block_statement->getStatements(), block_statement_json,
                 "statements");
  block_statement_json["range"] =
      toJsonRange(block_statement->getSourceLocation());

  m_last_node_json = std::move(block_statement_json);
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

  nlohmann::json identifier_expression_json;
  identifier_expression_json["kind"] =
      toString(identifier_expression->getKind());
  identifier_expression_json["name"] =
      identifier_expression->getSymbol()->getName();

  identifier_expression_json["symbolId"] =
      visit(identifier_expression->getSymbol());

  identifier_expression_json["range"] =
      toJsonRange(identifier_expression->getSourceLocation());

  m_last_node_json = std::move(identifier_expression_json);
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
