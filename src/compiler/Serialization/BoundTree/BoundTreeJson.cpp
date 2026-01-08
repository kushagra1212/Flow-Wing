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

#include "BoundTreeJson.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundColonExpression/BoundColonExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundIdentifierExpression/BoundIdentifierExpression.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundErrorStatement/BoundErrorStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundExposeStatement/BoundExposeStatement.hpp"
#include "src/SemanticAnalyzer/SyntaxBinder/BoundCompilationUnit.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/utils/LogConfig.h"
#include <memory>

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
  assert(false && "Expose statement not supported");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundFunctionStatement *function_statement) {
  PARSER_DEBUG_LOG("Visiting Bound Function Statement", "BOUND TREE");
  assert(false && "Function statement not supported");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundIfStatement *if_statement) {
  PARSER_DEBUG_LOG("Visiting Bound If Statement", "BOUND TREE");
  assert(false && "If statement not supported");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundWhileStatement *while_statement) {
  PARSER_DEBUG_LOG("Visiting Bound While Statement", "BOUND TREE");
  assert(false && "While statement not supported");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundForStatement *for_statement) {
  PARSER_DEBUG_LOG("Visiting Bound For Statement", "BOUND TREE");
  assert(false && "For statement not supported");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundBreakStatement *break_statement) {
  PARSER_DEBUG_LOG("Visiting Bound Break Statement", "BOUND TREE");
  assert(false && "Break statement not supported");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundContinueStatement *continue_statement) {
  PARSER_DEBUG_LOG("Visiting Bound Continue Statement", "BOUND TREE");
  assert(false && "Continue statement not supported");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundReturnStatement *return_statement) {
  PARSER_DEBUG_LOG("Visiting Bound Return Statement", "BOUND TREE");
  assert(false && "Return statement not supported");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundSwitchStatement *switch_statement) {
  PARSER_DEBUG_LOG("Visiting Bound Switch Statement", "BOUND TREE");
  assert(false && "Switch statement not supported");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundClassStatement *class_statement) {
  PARSER_DEBUG_LOG("Visiting Bound Class Statement", "BOUND TREE");
  assert(false && "Class statement not supported");
}

void BoundTreeJson::visit([[maybe_unused]] binding::BoundIdentifierExpression
                              *identifier_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Identifier Expression", "BOUND TREE");

  nlohmann::json identifier_expression_json;
  identifier_expression_json["kind"] =
      toString(identifier_expression->getKind());
  identifier_expression_json["name"] =
      identifier_expression->getSymbol()->getName();

  identifier_expression_json["symbol_id"] =
      getSymbolId(identifier_expression->getSymbol());

  identifier_expression_json["range"] =
      toJsonRange(identifier_expression->getSourceLocation());

  m_last_node_json = std::move(identifier_expression_json);
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundIndexExpression *index_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Index Expression", "BOUND TREE");
  assert(false && "Index expression not supported");
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

  assert(false && "Error statement not supported");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundErrorExpression *error_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Error Expression", "BOUND TREE");
  assert(false && "Error expression not supported");
}

void BoundTreeJson::visit([[maybe_unused]] binding::BoundModuleAccessExpression
                              *module_access_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Module Access Expression", "BOUND TREE");
  assert(false && "Module access expression not supported");
}

void BoundTreeJson::visit([[maybe_unused]] binding::BoundParenthesizedExpression
                              *parenthesized_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Parenthesized Expression", "BOUND TREE");
  nlohmann::json parenthesized_expression_json;
  parenthesized_expression_json["kind"] =
      toString(parenthesized_expression->getKind());
  serializeChild(parenthesized_expression->getExpression(),
                 parenthesized_expression_json, "expression");
  parenthesized_expression_json["range"] =
      toJsonRange(parenthesized_expression->getSourceLocation());
  m_last_node_json = std::move(parenthesized_expression_json);
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundTernaryExpression *ternary_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Ternary Expression", "BOUND TREE");
  assert(false && "Ternary expression not supported");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundNewExpression *new_expression) {
  PARSER_DEBUG_LOG("Visiting Bound New Expression", "BOUND TREE");
  assert(false && "New expression not supported");
}

void BoundTreeJson::visit(
    [[maybe_unused]] binding::BoundColonExpression *colon_expression) {
  PARSER_DEBUG_LOG("Visiting Bound Colon Expression", "BOUND TREE");
  nlohmann::json colon_expression_json;
  colon_expression_json["kind"] = toString(colon_expression->getKind());
  colon_expression_json["field_name"] = colon_expression->getFieldName();
  serializeChild(colon_expression->getRightExpression(), colon_expression_json,
                 "right");
  colon_expression_json["range"] =
      toJsonRange(colon_expression->getSourceLocation());
  m_last_node_json = std::move(colon_expression_json);
}
} // namespace flow_wing::compiler::serializer
