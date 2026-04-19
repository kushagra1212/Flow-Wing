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

#include "AstJson.hpp"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/compiler/diagnostics/Diagnostic.h"
#include "src/compiler/diagnostics/DiagnosticMessageDatabase/DiagnosticMessageDatabase.h"
#include "src/compiler/diagnostics/DiagnosticUtils/DiagnosticUtils.h"
#include "src/syntax/CompilationUnitSyntax.h"
#include "src/syntax/NodeKind/NodeKind.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/AssignmentExpressionSyntax/AssignmentExpressionSyntax.h"
#include "src/syntax/expression/BinaryExpressionSyntax/BinaryExpressionSyntax.h"
#include "src/syntax/expression/BooleanLiteralExpressionSyntax/BooleanLiteralExpressionSyntax.h"
#include "src/syntax/expression/BracketedExpressionSyntax/BracketedExpressionSyntax.h"
#include "src/syntax/expression/CallExpressionSyntax/CallExpressionSyntax.h"
#include "src/syntax/expression/CharacterLiteralExpressionSyntax/CharacterLiteralExpressionSyntax.h"
#include "src/syntax/expression/ColonExpressionSyntax/ColonExpressionSyntax.h"
#include "src/syntax/expression/ContainerExpressionSyntax/ContainerExpressionSyntax.h"
#include "src/syntax/expression/DeclaratorExpressionSyntax/DeclaratorExpressionSyntax.h"
#include "src/syntax/expression/DimensionClauseExpressionSyntax/DimensionClauseExpressionSyntax.h"
#include "src/syntax/expression/DoubleLiteralExpressionSyntax/DoubleLiteralExpressionSyntax.h"
#include "src/syntax/expression/ErrorExpressionSyntax/ErrorExpressionSyntax.hpp"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/expression/FieldDeclarationSyntax/FieldDeclarationSyntax.h"
#include "src/syntax/expression/FillExpressionSyntax/FillExpressionSyntax.h"
#include "src/syntax/expression/FloatLiteralExpressionSyntax/FloatLiteralExpressionSyntax.h"
#include "src/syntax/expression/FunctionReturnTypeExpressionSyntax/FunctionReturnTypeExpressionSyntax.h"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/expression/IndexExpressionSyntax/IndexExpressionSyntax.h"
#include "src/syntax/expression/Int64LiteralExpressionSyntax/Int64LiteralExpressionSyntax.h"
#include "src/syntax/expression/IntegerLiteralExpressionSyntax/IntegerLiteralExpressionSyntax.h"
#include "src/syntax/expression/MemberAccessExpressionSyntax/MemberAccessExpressionSyntax.h"
#include "src/syntax/expression/ModuleAccessExpressionSyntax/ModuleAccessExpressionSyntax.h"
#include "src/syntax/expression/NewExpressionSyntax/NewExpressionSyntax.h"
#include "src/syntax/expression/NirastExpressionSyntax/NirastExpressionSyntax.h"
#include "src/syntax/expression/SuperExpressionSyntax/SuperExpressionSyntax.h"
#include "src/syntax/expression/ObjectExpressionSyntax/ObjectExpressionSyntax.h"
#include "src/syntax/expression/ParenthesizedExpressionSyntax/ParenthesizedExpressionSyntax.h"
#include "src/syntax/expression/StringLiteralExpressionSyntax/StringLiteralExpressionSyntax.h"
#include "src/syntax/expression/TemplateStringLiteralExpressionSyntax/TemplateStringLiteralExpressionSyntax.h"
#include "src/syntax/expression/TernaryExpressionSyntax/TernaryExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/ArrayTypeExpressionSyntax/ArrayTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/BoolTypeExpressionSyntax/BoolTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/CharTypeExpressionSyntax/CharTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/Deci32TypeExpressionSyntax/Deci32TypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/DeciTypeExpressionSyntax/DeciTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/DynTypeExpressionSyntax/DynTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/FunctionTypeExpressionSyntax/FunctionTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/Int32TypeExpressionSyntax/Int32TypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/Int64TypeExpressionSyntax/Int64TypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/Int8TypeExpressionSyntax/Int8TypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/ModuleAccessTypeExpressionSyntax/ModuleAccessTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/NthgTypeExpressionSyntax/NthgTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/ObjectTypeExpressionSyntax/ObjectTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/StrTypeExpressionSyntax/StrTypeExpressionSyntax.h"
#include "src/syntax/expression/UnaryExpressionSyntax/UnaryExpressionSyntax.h"
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "src/syntax/statements/BreakStatementSyntax/BreakStatementSyntax.h"
#include "src/syntax/statements/BringStatementSyntax/BringStatementSyntax.h"
#include "src/syntax/statements/CaseStatementSyntax/CaseStatementSyntax.h"
#include "src/syntax/statements/ClassStatementSyntax/ClassStatementSyntax.h"
#include "src/syntax/statements/ContinueStatementSyntax/ContinueStatementSyntax.h"
#include "src/syntax/statements/CustomTypeStatementSyntax/CustomTypeStatementSyntax.h"
#include "src/syntax/statements/DefaultCaseStatementSyntax/DefaultCaseStatementSyntax.h"
#include "src/syntax/statements/ElseClauseSyntax/ElseClauseSyntax.h"
#include "src/syntax/statements/ExposeStatementSyntax/ExposeStatementSyntax.h"
#include "src/syntax/statements/ExpressionStatementSyntax/ExpressionStatementSyntax.hpp"
#include "src/syntax/statements/ForStatementSyntax/ForStatementSyntax.h"
#include "src/syntax/statements/FunctionStatementSyntax/FunctionStatementSyntax.h"
#include "src/syntax/statements/IfStatementSyntax/IfStatementSyntax.h"
#include "src/syntax/statements/ModuleStatementSyntax/ModuleStatementSyntax.h"
#include "src/syntax/statements/OrIfStatementSyntax/OrIfStatementSyntax.h"
#include "src/syntax/statements/ParameterExpressionSyntax/ParameterExpressionSyntax.h"
#include "src/syntax/statements/ReturnStatementSyntax/ReturnStatementSyntax.h"
#include "src/syntax/statements/SwitchStatementSyntax/SwitchStatementSyntax.h"
#include "src/syntax/statements/VariableDeclarationSyntax/VariableDeclarationSyntax.h"
#include "src/syntax/statements/WhileStatementSyntax/WhileStatementSyntax.h"
#include "src/utils/LogConfig.h"
namespace flow_wing::compiler::serializer {
template <typename T>
void AstJson::serializeChild(const std::unique_ptr<T> &node,
                             nlohmann::json &parent, const std::string &key) {
  if (node) {
    node->accept(this);
    parent[key] = std::move(m_last_node_json);
  } else {
    parent[key] = nullptr;
  }
}

// Helper to serialize a vector of children (Fixes the loop bug)
template <typename T>
void AstJson::serializeArray(const std::vector<std::unique_ptr<T>> &nodes,
                             nlohmann::json &parent, const std::string &key) {
  nlohmann::json array = nlohmann::json::array();
  for (const auto &node : nodes) {
    if (node) {
      node->accept(this);
      array.push_back(std::move(m_last_node_json));
    }
  }
  parent[key] = std::move(array);
}

nlohmann::json AstJson::toJson(
     const std::unique_ptr<syntax::CompilationUnitSyntax> &ast)
    const {
  PARSER_DEBUG_LOG("Serializing AST to JSON", "AST");
  ast->accept(const_cast<AstJson *>(this));
  return m_ast_json;
}

nlohmann::json
AstJson::toJsonSourcePoint(const flow_wing::diagnostic::SourcePoint &point) {
  return {point.line_number, point.column_number};
}

nlohmann::json
AstJson::toJsonRange(const flow_wing::diagnostic::SourceLocation &location) {
  return {{"start", toJsonSourcePoint(location.m_start)},
          {"end", toJsonSourcePoint(location.m_end)}};
}

void AstJson::visit( syntax::SyntaxToken *node) {
  PARSER_DEBUG_LOG("Visiting SyntaxToken", "AST");
  m_last_node_json = {{"kind", syntax::toString(node->getKind())},
                      {"value", node->getText()},
                      {"range", toJsonRange(node->getSourceLocation())}};
}

void AstJson::visit( syntax::ErrorExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting ErrorExpressionSyntax", "AST");
  nlohmann::json error_expression_json;
  error_expression_json["kind"] = syntax::toString(node->getKind());
  std::vector<std::string> skipped;
  for (auto *token : node->getSkippedTokens()) {
    std::string text = token->getText();
    if (text.empty()) {
      text = "<" + lexer::toString(token->getTokenKind()) + ">";
    }
    skipped.push_back(text);
  }
  error_expression_json["skipped_tokens"] = skipped;
  error_expression_json["message"] = node->getDiagnostic().getMessage();
  error_expression_json["help"] = node->getDiagnostic().getHelp();
  error_expression_json["note"] = node->getDiagnostic().getNote();
  error_expression_json["code"] =
      diagnostic::DiagnosticMessageDatabase::toString(
          node->getDiagnostic().getCode());
  error_expression_json["type"] =
      diagnostic::utils::toString(node->getDiagnostic().getType());
  error_expression_json["level"] =
      diagnostic::utils::toString(node->getDiagnostic().getLevel());
  error_expression_json["location"] =
      toJsonRange(node->getDiagnostic().getLocation());

  error_expression_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(error_expression_json);
}

void AstJson::visit( syntax::CompilationUnitSyntax *node) {
  PARSER_DEBUG_LOG("Visiting CompilationUnitSyntax", "AST");

  nlohmann::json json;
  json["kind"] = syntax::toString(node->getKind());
  serializeArray(node->getStatements(), json, "statements");
  json["range"] = toJsonRange(node->getSourceLocation());
  m_ast_json = std::move(json);
}
void AstJson::visit( syntax::IdentifierExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting IdentifierExpressionSyntax", "AST");

  m_last_node_json = {{"kind", syntax::toString(node->getKind())},
                      {"value", node->getValue()},
                      {"range", toJsonRange(node->getSourceLocation())}};
}
void AstJson::visit( syntax::ParameterExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting ParameterExpressionSyntax", "AST");
  nlohmann::json parameter_json;

  parameter_json["kind"] = syntax::toString(node->getKind());

  if (node->hasInoutKeyword()) {
    parameter_json["is_inout"] = true;
  }

  if (node->hasConstKeyword()) {
    parameter_json["is_const"] = true;
  }

  serializeChild(node->getIdentifierExpression(), parameter_json,
                 "identifier_expression");

  if (node->hasAsKeyword()) {
    parameter_json["is_as"] = true;
  }
  serializeChild(node->getTypeExpression(), parameter_json, "type_expression");
  serializeChild(node->getDefaultValueExpression(), parameter_json,
                 "default_value_expression");
  parameter_json["range"] = toJsonRange(node->getSourceLocation());

  m_last_node_json = std::move(parameter_json);
}
void AstJson::visit(
     syntax::DimensionClauseExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting DimensionClauseExpressionSyntax", "AST");
  nlohmann::json dimension_clause_json;

  dimension_clause_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getSizeLiteral(), dimension_clause_json, "size_literal");
  dimension_clause_json["range"] = toJsonRange(node->getSourceLocation());

  m_last_node_json = std::move(dimension_clause_json);
}
void AstJson::visit(
     syntax::IntegerLiteralExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting IntegerLiteralExpressionSyntax", "AST");
  nlohmann::json integer_literal_json;

  integer_literal_json["kind"] = syntax::toString(node->getKind());
  integer_literal_json["value"] = node->getValue();
  integer_literal_json["range"] = toJsonRange(node->getSourceLocation());

  m_last_node_json = std::move(integer_literal_json);
}
void AstJson::visit(
     syntax::Int64LiteralExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting Int64LiteralExpressionSyntax", "AST");
  nlohmann::json int64_literal_json;

  int64_literal_json["kind"] = syntax::toString(node->getKind());
  int64_literal_json["value"] = node->getValue();
  int64_literal_json["range"] = toJsonRange(node->getSourceLocation());

  m_last_node_json = std::move(int64_literal_json);
}
void AstJson::visit( syntax::AssignmentExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting AssignmentExpressionSyntax", "AST");
  nlohmann::json assignment_json;

  assignment_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getLeft(), assignment_json, "left");
  assignment_json["operator"] = node->getOperatorToken()->getText();
  serializeChild(node->getRight(), assignment_json, "right");
  assignment_json["range"] = toJsonRange(node->getSourceLocation());

  m_last_node_json = std::move(assignment_json);
}
void AstJson::visit(
     syntax::BooleanLiteralExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting BooleanLiteralExpressionSyntax", "AST");
  nlohmann::json boolean_literal_json;

  boolean_literal_json["kind"] = syntax::toString(node->getKind());
  boolean_literal_json["value"] = node->getValue();
  boolean_literal_json["range"] = toJsonRange(node->getSourceLocation());

  m_last_node_json = std::move(boolean_literal_json);
}
void AstJson::visit( syntax::BracketedExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting BracketedExpressionSyntax", "AST");
  nlohmann::json bracketed_expression_json;

  bracketed_expression_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getExpression(), bracketed_expression_json,
                 "expression");
  bracketed_expression_json["range"] = toJsonRange(node->getSourceLocation());

  m_last_node_json = std::move(bracketed_expression_json);
}
void AstJson::visit( syntax::CallExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting CallExpressionSyntax", "AST");
  nlohmann::json call_json;

  call_json["kind"] = syntax::toString(node->getKind());

  std::vector<syntax::ExpressionSyntax *> argument_expressions = {};

  if (node->getArgumentExpression() != nullptr) {

    argument_expressions = getListOfExpressions(
        node->getArgumentExpression().get(), lexer::TokenKind::kCommaToken);
    for (const auto &argument_expression : argument_expressions) {
      argument_expression->accept(this);
      call_json["argument_expressions"].push_back(std::move(m_last_node_json));
    }
  }

  serializeChild(node->getIdentifier(), call_json, "identifier");
  call_json["range"] = toJsonRange(node->getSourceLocation());

  m_last_node_json = std::move(call_json);
}
void AstJson::visit(
     syntax::CharacterLiteralExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting CharacterLiteralExpressionSyntax", "AST");
  nlohmann::json character_literal_json;

  character_literal_json["kind"] = syntax::toString(node->getKind());
  character_literal_json["value"] = node->getValue();
  character_literal_json["range"] = toJsonRange(node->getSourceLocation());

  m_last_node_json = std::move(character_literal_json);
}
void AstJson::visit( syntax::ContainerExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting ContainerExpressionSyntax", "AST");

  nlohmann::json container_expression_json;

  container_expression_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getValueExpression(), container_expression_json,
                 "value_expression");
  container_expression_json["range"] = toJsonRange(node->getSourceLocation());

  m_last_node_json = std::move(container_expression_json);
}
void AstJson::visit( syntax::DeclaratorExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting DeclaratorExpressionSyntax", "AST");
  nlohmann::json declarator_expression_json;

  declarator_expression_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getIdentifierExpression(), declarator_expression_json,
                 "identifier_expression");
  serializeChild(node->getTypeExpression(), declarator_expression_json,
                 "type_expression");
  declarator_expression_json["range"] = toJsonRange(node->getSourceLocation());

  m_last_node_json = std::move(declarator_expression_json);
}
void AstJson::visit(
     syntax::DoubleLiteralExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting DoubleLiteralExpressionSyntax", "AST");

  nlohmann::json double_literal_json;

  double_literal_json["kind"] = syntax::toString(node->getKind());
  double_literal_json["value"] = node->getValue();
  double_literal_json["range"] = toJsonRange(node->getSourceLocation());

  m_last_node_json = std::move(double_literal_json);
}
void AstJson::visit( syntax::FieldDeclarationSyntax *node) {
  PARSER_DEBUG_LOG("Visiting FieldDeclarationSyntax", "AST");

  nlohmann::json field_declaration_json;

  field_declaration_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getKey(), field_declaration_json, "key_expression");
  serializeChild(node->getValue(), field_declaration_json, "value_expression");
  field_declaration_json["range"] = toJsonRange(node->getSourceLocation());

  m_last_node_json = std::move(field_declaration_json);
}
void AstJson::visit( syntax::FillExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting FillExpressionSyntax", "AST");
  nlohmann::json fill_expression_json;

  fill_expression_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getSizeToFillExpression(), fill_expression_json, "size");
  serializeChild(node->getElementExpression(), fill_expression_json,
                 "element_expression");
  fill_expression_json["range"] = toJsonRange(node->getSourceLocation());

  m_last_node_json = std::move(fill_expression_json);
}
void AstJson::visit(
     syntax::FloatLiteralExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting FloatLiteralExpressionSyntax", "AST");

  nlohmann::json float_literal_json;
  float_literal_json["kind"] = syntax::toString(node->getKind());
  float_literal_json["value"] = node->getValue();
  float_literal_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(float_literal_json);
}
void AstJson::visit(
     syntax::FunctionReturnTypeExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting FunctionReturnTypeExpressionSyntax", "AST");

  nlohmann::json function_return_type_expression_json;

  function_return_type_expression_json["kind"] =
      syntax::toString(node->getKind());

  if (node->hasAsKeyword()) {
    function_return_type_expression_json["is_as"] = true;
  }

  serializeArray(node->getTypeExpressions(),
                 function_return_type_expression_json, "type_expressions");
  function_return_type_expression_json["range"] =
      toJsonRange(node->getSourceLocation());

  m_last_node_json = std::move(function_return_type_expression_json);
}
void AstJson::visit( syntax::IndexExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting IndexExpressionSyntax", "AST");

  nlohmann::json index_expression_json;

  index_expression_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getLeftExpression(), index_expression_json,
                 "left_expression");
  serializeArray(node->getDimensionClauseExpressions(), index_expression_json,
                 "dimension_clause_expressions");
  index_expression_json["range"] = toJsonRange(node->getSourceLocation());

  m_last_node_json = std::move(index_expression_json);
}
void AstJson::visit(
     syntax::MemberAccessExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting MemberAccessExpressionSyntax", "AST");

  nlohmann::json member_access_expression_json;

  member_access_expression_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getLeftExpression(), member_access_expression_json,
                 "left_expression");
  serializeChild(node->getRightExpression(), member_access_expression_json,
                 "right_expression");
  member_access_expression_json["range"] =
      toJsonRange(node->getSourceLocation());

  m_last_node_json = std::move(member_access_expression_json);
}
void AstJson::visit(
     syntax::ModuleAccessExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting ModuleAccessExpressionSyntax", "AST");

  nlohmann::json module_access_expression_json;
  module_access_expression_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getModuleNameExpression(), module_access_expression_json,
                 "module_name_expression");
  serializeChild(node->getMemberAccessExpression(),
                 module_access_expression_json, "member_access_expression");
  module_access_expression_json["range"] =
      toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(module_access_expression_json);
}
void AstJson::visit( syntax::NewExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting NewExpressionSyntax", "AST");

  nlohmann::json new_expression_json;
  new_expression_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getExpression(), new_expression_json, "expression");
  new_expression_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(new_expression_json);
}
void AstJson::visit( syntax::NirastExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting NirastExpressionSyntax", "AST");

  nlohmann::json nirast_expression_json;
  nirast_expression_json["kind"] = syntax::toString(node->getKind());
  nirast_expression_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(nirast_expression_json);
}
void AstJson::visit( syntax::SuperExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting SuperExpressionSyntax", "AST");

  nlohmann::json super_expression_json;
  super_expression_json["kind"] = syntax::toString(node->getKind());
  super_expression_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(super_expression_json);
}
void AstJson::visit( syntax::ObjectExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting ObjectExpressionSyntax", "AST");

  nlohmann::json object_expression_json;
  object_expression_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getColonExpression(), object_expression_json,
                 "expression");
  object_expression_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(object_expression_json);
}
void AstJson::visit( syntax::ColonExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting ObjectMemberSyntax", "AST");

  nlohmann::json object_member_json;
  object_member_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getLeftExpression(), object_member_json,
                 "key_expression");
  serializeChild(node->getRightExpression(), object_member_json,
                 "value_expression");
  object_member_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(object_member_json);
}

void AstJson::visit(
     syntax::ParenthesizedExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting ParenthesizedExpressionSyntax", "AST");

  nlohmann::json parenthesized_expression_json;
  parenthesized_expression_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getExpression(), parenthesized_expression_json,
                 "expression");
  parenthesized_expression_json["range"] =
      toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(parenthesized_expression_json);
}
void AstJson::visit(
     syntax::StringLiteralExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting StringLiteralExpressionSyntax", "AST");
  nlohmann::json string_json;
  string_json["kind"] = syntax::toString(node->getKind());
  string_json["value"] = node->getValue();
  string_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(string_json);
}
void AstJson::visit(
     syntax::TemplateStringLiteralExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting TemplateStringLiteralExpressionSyntax", "AST");

  nlohmann::json template_string_literal_expression_json;
  template_string_literal_expression_json["kind"] =
      syntax::toString(node->getKind());
  template_string_literal_expression_json["value"] = node->getValue();
  template_string_literal_expression_json["range"] =
      toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(template_string_literal_expression_json);
}
void AstJson::visit( syntax::TernaryExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting TernaryExpressionSyntax", "AST");

  nlohmann::json ternary_expression_json;
  ternary_expression_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getConditionExpression(), ternary_expression_json,
                 "condition_expression");
  serializeChild(node->getTrueExpression(), ternary_expression_json,
                 "true_expression");
  serializeChild(node->getFalseExpression(), ternary_expression_json,
                 "false_expression");
  ternary_expression_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(ternary_expression_json);
}
void AstJson::visit( syntax::BinaryExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting BinaryExpressionSyntax", "AST");

  nlohmann::json binary_expression_json;
  binary_expression_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getLeft(), binary_expression_json, "left");
  binary_expression_json["operator"] = node->getOperatorToken()->getText();
  serializeChild(node->getRight(), binary_expression_json, "right");
  binary_expression_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(binary_expression_json);
}

void AstJson::visit( syntax::ArrayTypeExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting ArrayTypeExpressionSyntax", "AST");

  nlohmann::json array_type_expression_json;
  array_type_expression_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getUnderlyingType(), array_type_expression_json,
                 "underlying_type");
  serializeArray(node->getDimensions(), array_type_expression_json,
                 "dimensions");
  array_type_expression_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(array_type_expression_json);
}

void AstJson::visit( syntax::BoolTypeExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting BoolTypeExpressionSyntax", "AST");

  nlohmann::json bool_type_expression_json;
  bool_type_expression_json["kind"] = syntax::toString(node->getKind());
  bool_type_expression_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(bool_type_expression_json);
}
void AstJson::visit( syntax::Deci32TypeExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting Deci32TypeExpressionSyntax", "AST");

  nlohmann::json deci32_type_expression_json;
  deci32_type_expression_json["kind"] = syntax::toString(node->getKind());
  deci32_type_expression_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(deci32_type_expression_json);
}
void AstJson::visit( syntax::DeciTypeExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting DeciTypeExpressionSyntax", "AST");

  nlohmann::json deci_type_expression_json;
  deci_type_expression_json["kind"] = syntax::toString(node->getKind());
  deci_type_expression_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(deci_type_expression_json);
}
void AstJson::visit(
     syntax::FunctionTypeExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting FunctionTypeExpressionSyntax", "AST");

  nlohmann::json function_type_expression_json;
  const auto &as_parameter_keywords_table = node->getAsParameterKeywordsTable();
  const auto &constant_keyword_table = node->getConstantKeywordTable();
  const auto &inout_keyword_table = node->getInoutKeywordTable();
  const auto &parameter_types = node->getParameterTypes();
  const auto &return_types = node->getReturnTypes();
  const auto has_as_return_keyword = node->hasAsReturnType();

  const size_t parameter_count = parameter_types.size();

  for (size_t i = 0; i < parameter_count; i++) {
    nlohmann::json parameter_json;

    if (as_parameter_keywords_table.count(i) > 0) {
      parameter_json["is_as"] = true;
    }
    if (constant_keyword_table.count(i) > 0) {
      parameter_json["is_const"] = true;
    }
    if (inout_keyword_table.count(i) > 0) {
      parameter_json["is_inout"] = true;
    }

    serializeChild(parameter_types[i], parameter_json, "type_expression");

    function_type_expression_json["parameters"].push_back(
        std::move(parameter_json));
  }

  for (size_t i = 0; i < return_types.size(); i++) {
    nlohmann::json return_json;
    serializeChild(return_types[i], return_json, "type_expression");

    if (has_as_return_keyword) {
      return_json["is_as"] = true;
    }

    function_type_expression_json["return_types"].push_back(
        std::move(return_json));
  }

  function_type_expression_json["range"] =
      toJsonRange(node->getSourceLocation());

      function_type_expression_json["kind"] = syntax::toString(node->getKind());

  m_last_node_json = std::move(function_type_expression_json);
}
void AstJson::visit( syntax::Int8TypeExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting Int8TypeExpressionSyntax", "AST");

  nlohmann::json int8_type_expression_json;
  int8_type_expression_json["kind"] = syntax::toString(node->getKind());
  int8_type_expression_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(int8_type_expression_json);
}

void AstJson::visit( syntax::DynTypeExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting DynTypeExpressionSyntax", "AST");
  nlohmann::json dyn_type_expression_json;
  dyn_type_expression_json["kind"] = syntax::toString(node->getKind());
  dyn_type_expression_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(dyn_type_expression_json);
}

void AstJson::visit( syntax::Int32TypeExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting Int32TypeExpressionSyntax", "AST");

  nlohmann::json int32_type_expression_json;
  int32_type_expression_json["kind"] = syntax::toString(node->getKind());
  int32_type_expression_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(int32_type_expression_json);
}
void AstJson::visit( syntax::Int64TypeExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting Int64TypeExpressionSyntax", "AST");

  nlohmann::json int64_type_expression_json;
  int64_type_expression_json["kind"] = syntax::toString(node->getKind());
  int64_type_expression_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(int64_type_expression_json);
}
void AstJson::visit(
     syntax::ModuleAccessTypeExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting ModuleAccessTypeExpressionSyntax", "AST");

  nlohmann::json module_access_type_expression_json;
  module_access_type_expression_json["kind"] =
      syntax::toString(node->getKind());
  serializeChild(node->getModuleIdentifier(),
                 module_access_type_expression_json,
                 "module_identifier_expression");
  serializeChild(node->getTypeExpression(), module_access_type_expression_json,
                 "type_expression");
  module_access_type_expression_json["range"] =
      toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(module_access_type_expression_json);
}
void AstJson::visit( syntax::NthgTypeExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting NthgTypeExpressionSyntax", "AST");

  nlohmann::json nthg_type_expression_json;
  nthg_type_expression_json["kind"] = syntax::toString(node->getKind());
  nthg_type_expression_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(nthg_type_expression_json);
}
void AstJson::visit( syntax::ObjectTypeExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting ObjectTypeExpressionSyntax", "AST");

  nlohmann::json object_type_expression_json;
  object_type_expression_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getObjectIdentifier(), object_type_expression_json,
                 "object_identifier_expression");
  object_type_expression_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(object_type_expression_json);
}
void AstJson::visit( syntax::StrTypeExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting StrTypeExpressionSyntax", "AST");

  nlohmann::json str_type_expression_json;
  str_type_expression_json["kind"] = syntax::toString(node->getKind());
  str_type_expression_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(str_type_expression_json);
}
void AstJson::visit( syntax::UnaryExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting UnaryExpressionSyntax", "AST");

  nlohmann::json unary_expression_json;
  unary_expression_json["kind"] = syntax::toString(node->getKind());
  unary_expression_json["operator"] = node->getOperatorToken()->getText();
  serializeChild(node->getExpression(), unary_expression_json, "expression");
  unary_expression_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(unary_expression_json);
}
void AstJson::visit( syntax::ExposeStatementSyntax *node) {
  PARSER_DEBUG_LOG("Visiting ExposeStatementSyntax", "AST");

  nlohmann::json expose_statement_json;
  expose_statement_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getStatement(), expose_statement_json, "statement");
  expose_statement_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(expose_statement_json);
}
void AstJson::visit( syntax::BlockStatementSyntax *node) {
  PARSER_DEBUG_LOG("Visiting BlockStatementSyntax", "AST");

  nlohmann::json block_statement_json;
  block_statement_json["kind"] = syntax::toString(node->getKind());
  serializeArray(node->getStatements(), block_statement_json, "statements");
  block_statement_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(block_statement_json);
}
void AstJson::visit( syntax::FunctionStatementSyntax *node) {
  PARSER_DEBUG_LOG("Visiting FunctionStatementSyntax", "AST");

  nlohmann::json function_statement_json;
  function_statement_json["kind"] = syntax::toString(node->getKind());

  if (!node->hasBody()) {
    function_statement_json["is_declaration"] = true;
  }

  serializeChild(node->getIdentifier(), function_statement_json, "identifier");
  serializeArray(node->getParameters(), function_statement_json, "parameters");

  serializeChild(node->getReturnType(), function_statement_json, "returnType");
  serializeChild(node->getBody(), function_statement_json, "body");
  function_statement_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(function_statement_json);
}
void AstJson::visit(syntax::BreakStatementSyntax *node) {
  PARSER_DEBUG_LOG("Visiting BreakStatementSyntax", "AST");

  nlohmann::json break_statement_json;
  break_statement_json["kind"] = syntax::toString(node->getKind());
  break_statement_json["keyword"] = "break";
  break_statement_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(break_statement_json);
}
void AstJson::visit( syntax::BringStatementSyntax *node) {
  PARSER_DEBUG_LOG("Visiting BringStatementSyntax", "AST");

  nlohmann::json bring_statement_json;
  bring_statement_json["kind"] = syntax::toString(node->getKind());
  serializeArray(node->getIdentifierExpressions(), bring_statement_json,
                 "identifier_expressions");
  serializeChild(node->getStringLiteralExpression(), bring_statement_json,
                 "file_path");
  bring_statement_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(bring_statement_json);
}
void AstJson::visit( syntax::CaseStatementSyntax *node) {
  PARSER_DEBUG_LOG("Visiting CaseStatementSyntax", "AST");

  nlohmann::json case_statement_json;
  case_statement_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getCaseExpression(), case_statement_json,
                 "case_expression");
  serializeChild(node->getStatement(), case_statement_json, "statement");
  case_statement_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(case_statement_json);
}
void AstJson::visit( syntax::ClassStatementSyntax *node) {
  PARSER_DEBUG_LOG("Visiting ClassStatementSyntax", "AST");

  nlohmann::json class_statement_json;
  class_statement_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getClassNameIdentifierExpr(), class_statement_json,
                 "class_name_identifier_expr");
  serializeChild(node->getParentClassIdentifierExpr(), class_statement_json,
                 "parent_class_identifier_expr");
  serializeArray(node->getClassMemberStatements(), class_statement_json,
                 "class_member_statements");
  class_statement_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(class_statement_json);
}
void AstJson::visit(syntax::ContinueStatementSyntax *node) {
  PARSER_DEBUG_LOG("Visiting ContinueStatementSyntax", "AST");

  nlohmann::json continue_statement_json;
  continue_statement_json["kind"] = syntax::toString(node->getKind());
  continue_statement_json["keyword"] = "continue";
  continue_statement_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(continue_statement_json);
}
void AstJson::visit( syntax::CustomTypeStatementSyntax *node) {
  PARSER_DEBUG_LOG("Visiting CustomTypeStatementSyntax", "AST");

  nlohmann::json custom_type_statement_json;
  custom_type_statement_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getTypeName(), custom_type_statement_json,
                 "custom_type_identifier_expr");
  serializeArray(node->getFieldDeclarations(), custom_type_statement_json,
                 "field_declarations");
  custom_type_statement_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(custom_type_statement_json);
}
void AstJson::visit( syntax::DefaultCaseStatementSyntax *node) {
  PARSER_DEBUG_LOG("Visiting DefaultCaseStatementSyntax", "AST");

  nlohmann::json default_case_statement_json;
  default_case_statement_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getStatement(), default_case_statement_json,
                 "statement");
  default_case_statement_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(default_case_statement_json);
}
void AstJson::visit( syntax::ElseClauseSyntax *node) {
  PARSER_DEBUG_LOG("Visiting ElseClauseSyntax", "AST");
  nlohmann::json else_clause_json;
  else_clause_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getStatement(), else_clause_json, "statement");
  else_clause_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(else_clause_json);
}
void AstJson::visit( syntax::ForStatementSyntax *node) {
  PARSER_DEBUG_LOG("Visiting ForStatementSyntax", "AST");

  nlohmann::json for_statement_json;
  for_statement_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getVariableDeclaration(), for_statement_json,
                 "variable_declaration");
  serializeChild(node->getAssignmentExpression(), for_statement_json,
                 "assignment_expression");
  serializeChild(node->getUpperBound(), for_statement_json, "upper_bound");
  serializeChild(node->getStep(), for_statement_json, "step");
  serializeChild(node->getBody(), for_statement_json, "loop_body");
  for_statement_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(for_statement_json);
}
void AstJson::visit( syntax::IfStatementSyntax *node) {
  PARSER_DEBUG_LOG("Visiting IfStatementSyntax", "AST");
  nlohmann::json if_statement_json;
  if_statement_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getConditionExpression(), if_statement_json,
                 "condition_expression");
  serializeChild(node->getStatement(), if_statement_json, "statement");
  serializeArray(node->getOrIfStatements(), if_statement_json,
                 "or_if_statements");
  serializeChild(node->getElseClause(), if_statement_json, "else_clause");
  if_statement_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(if_statement_json);
}
void AstJson::visit( syntax::ModuleStatementSyntax *node) {
  PARSER_DEBUG_LOG("Visiting ModuleStatementSyntax", "AST");

  nlohmann::json module_statement_json;
  module_statement_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getModuleNameExpression(), module_statement_json,
                 "module_name_expression");
  serializeArray(node->getModuleMemberStatements(), module_statement_json,
                 "module_member_statements");
  module_statement_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(module_statement_json);
}
void AstJson::visit( syntax::OrIfStatementSyntax *node) {
  PARSER_DEBUG_LOG("Visiting OrIfStatementSyntax", "AST");

  nlohmann::json or_if_statement_json;
  or_if_statement_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getConditionExpression(), or_if_statement_json,
                 "condition_expression");
  serializeChild(node->getStatement(), or_if_statement_json, "statement");
  or_if_statement_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(or_if_statement_json);
}
void AstJson::visit( syntax::ReturnStatementSyntax *node) {
  PARSER_DEBUG_LOG("Visiting ReturnStatementSyntax", "AST");
  nlohmann::json return_statement_json;
  return_statement_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getReturnExpression(), return_statement_json,
                 "returnExpression");
  return_statement_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(return_statement_json);
}
void AstJson::visit( syntax::SwitchStatementSyntax *node) {
  PARSER_DEBUG_LOG("Visiting SwitchStatementSyntax", "AST");
  nlohmann::json switch_statement_json;
  switch_statement_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getSwitchConditionExpression(), switch_statement_json,
                 "switch_condition_expression");
  serializeArray(node->getCaseStatements(), switch_statement_json,
                 "case_statements");
  switch_statement_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(switch_statement_json);
}
void AstJson::visit( syntax::VariableDeclarationSyntax *node) {

  PARSER_DEBUG_LOG("Visiting VariableDeclarationSyntax", "AST");
  nlohmann::json variable_declaration_json;
  variable_declaration_json["kind"] = syntax::toString(node->getKind());
  if (node->hasConstKeyword()) {
    variable_declaration_json["is_const"] = true;
  }
  serializeArray(node->getDeclarators(), variable_declaration_json,
                 "declarators");
  if (node->getInitializerExpression())
    serializeChild(node->getInitializerExpression(), variable_declaration_json,
                   "initializer_expression");
  variable_declaration_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(variable_declaration_json);
}
void AstJson::visit( syntax::WhileStatementSyntax *node) {
  PARSER_DEBUG_LOG("Visiting WhileStatementSyntax", "AST");
  nlohmann::json while_statement_json;
  while_statement_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getCondition(), while_statement_json,
                 "condition_expression");
  serializeChild(node->getStatement(), while_statement_json, "loop_body");
  while_statement_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(while_statement_json);
}
void AstJson::visit( syntax::ExpressionStatementSyntax *node) {
  PARSER_DEBUG_LOG("Visiting ExpressionStatementSyntax", "AST");
  nlohmann::json expression_statement_json;
  expression_statement_json["kind"] = syntax::toString(node->getKind());
  serializeChild(node->getExpression(), expression_statement_json,
                 "expression");
  expression_statement_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(expression_statement_json);
}

void AstJson::visit( syntax::CharTypeExpressionSyntax *node) {
  PARSER_DEBUG_LOG("Visiting CharTypeExpressionSyntax", "AST");
  nlohmann::json char_type_expression_json;
  char_type_expression_json["kind"] = syntax::toString(node->getKind());
  char_type_expression_json["range"] = toJsonRange(node->getSourceLocation());
  m_last_node_json = std::move(char_type_expression_json);
}

std::vector<syntax::ExpressionSyntax *>
AstJson::getListOfExpressions(syntax::ExpressionSyntax *expression,
                              lexer::TokenKind operator_token_kind) {
  std::vector<syntax::ExpressionSyntax *> expressions;
  while (expression->getKind() == syntax::NodeKind::kBinaryExpression) {
    auto binary_expr =
        static_cast<syntax::BinaryExpressionSyntax *>(expression);
    if (binary_expr->getOperatorToken()->getTokenKind() ==
        operator_token_kind) {
      expressions.insert(expressions.begin(), (binary_expr->getRight().get()));
      expression = binary_expr->getLeft().get();
    } else {
      break;
    }
  }
  expressions.insert(expressions.begin(), expression);
  return expressions;
}

} // namespace flow_wing::compiler::serializer
