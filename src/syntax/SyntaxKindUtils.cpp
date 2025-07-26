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

#include "SyntaxKindUtils.h"
#include <cctype>    // Required for isdigit
#include <stdexcept> // Required for std::exception, std::out_of_range
#include <string>

bool SyntaxKindUtils::isInt32(const std::string &str) {
  try {
    size_t pos;
    int32_t number = std::stoi(str, &pos);
    return pos == str.size() && number >= std::numeric_limits<int32_t>::min() &&
           number <= std::numeric_limits<int32_t>::max();
  } catch (const std::exception &) {
    return false;
  }
}

bool SyntaxKindUtils::isInt64(const std::string &str) {
  try {
    size_t pos;
    int64_t number = std::stoll(str, &pos);
    return pos == str.size() && number >= std::numeric_limits<int64_t>::min() &&
           number <= std::numeric_limits<int64_t>::max();
  } catch (const std::exception &) {
    return false;
  }
}

bool SyntaxKindUtils::isDouble(const std::string &str) {
  try {
    size_t pos;
    double number = std::stod(str, &pos);
    return pos == str.size() && number >= std::numeric_limits<double>::min() &&
           number <= std::numeric_limits<double>::max();
  } catch (const std::exception &) {
    return false;
  }
}

bool SyntaxKindUtils::isValidInteger(const std::string &str) {
  // An empty string is not a valid integer.
  if (str.empty()) {
    return false;
  }

  try {
    size_t pos;
    std::stoll(str, &pos);

    // To be a valid integer, the stoll function must consume the entire string.
    // If pos is not equal to str.size(), it means there were trailing
    // characters that are not part of the number (e.g., "123a" or "123.45").
    return pos == str.size();
  } catch (const std::exception &) {
    // This will catch two main cases:
    // 1. std::invalid_argument: The string is not a number (e.g., "abc").
    // 2. std::out_of_range: The number is outside the range of long long.
    return false;
  }
}

bool SyntaxKindUtils::isNumberTooLarge(const std::string &str) {
  if (str.empty()) {
    return false;
  }

  // Step 1: Manually check if the string has a valid integer format.
  // This prevents misinterpreting floats ("1.23") or other text ("--123") as
  // "too large".
  size_t start = 0;
  if (str[0] == '+' || str[0] == '-') {
    // If the string is just a sign, it's not a valid number.
    if (str.length() == 1) {
      return false;
    }
    start = 1;
  }

  for (size_t i = start; i < str.length(); ++i) {
    if (!isdigit(str[i])) {
      // The string contains non-digit characters, so it's not a pure integer.
      return false;
    }
  }

  // Step 2: Now that we know it's a well-formatted integer string,
  // try to parse it and see if it's out of range.
  try {
    std::stoll(str);
  } catch (const std::out_of_range &) {
    // The string represents a number, but it's too big or too small
    // to fit in a long long. This is the exact case we want to catch.
    return true;
  } catch (...) {
    // Catch any other unexpected exception (like std::invalid_argument, though
    // our manual check should prevent this).
    return false;
  }

  // If stoll succeeded without throwing an exception, the number fits.
  return false;
}

const std::string SyntaxKindUtils::to_string(SyntaxKind kind) {
  switch (kind) {
  case SyntaxKind::NumberToken:
    return "NumberToken";
  case SyntaxKind::TrueKeyword:
    return "TrueKeyword";
  case SyntaxKind::FalseKeyword:
    return "FalseKeyword";
  case SyntaxKind::WhitespaceToken:
    return "WhitespaceToken";
  case SyntaxKind::PlusToken:
    return "PlusToken";
  case SyntaxKind::MinusToken:
    return "MinusToken";
  case SyntaxKind::StarToken:
    return "StarToken";
  case SyntaxKind::SlashToken:
    return "SlashToken";
  case SyntaxKind::OpenParenthesisToken:
    return "OpenParenthesisToken";
  case SyntaxKind::CloseParenthesisToken:
    return "CloseParenthesisToken";
  case SyntaxKind::BadToken:
    return "BadToken";
  case SyntaxKind::EndOfFileToken:
    return "EndOfFileToken";
  case SyntaxKind::LiteralExpression:
    return "LiteralExpression";
  case SyntaxKind::UnaryExpression:
    return "UnaryExpression";
  case SyntaxKind::BinaryExpression:
    return "BinaryExpression";
  case SyntaxKind::ParenthesizedExpression:
    return "ParenthesizedExpression";
  case SyntaxKind::CompilationUnit:
    return "CompilationUnit";
  case SyntaxKind::AmpersandAmpersandToken:
    return "AmpersandAmpersandToken";
  case SyntaxKind::PipePipeToken:
    return "PipePipeToken";
  case SyntaxKind::EqualsEqualsToken:
    return "EqualsEqualsToken";
  case SyntaxKind::EqualsToken:
    return "EqualsToken";
  case SyntaxKind::BangToken:
    return "BangToken";
  case SyntaxKind::BangEqualsToken:
    return "BangEqualsToken";
  case SyntaxKind::LessOrEqualsToken:
    return "LessOrEqualsToken";
  case SyntaxKind::LessToken:
    return "LessToken";
  case SyntaxKind::GreaterOrEqualsToken:
    return "GreaterOrEqualsToken";
  case SyntaxKind::GreaterToken:
    return "GreaterToken";
  case SyntaxKind::SemiColonToken:
    return "SemiColonToken";
  case SyntaxKind::CommaToken:
    return "CommaToken";
  case SyntaxKind::OpenBraceToken:
    return "OpenBraceToken";
  case SyntaxKind::QuestionToken:
    return "QuestionToken";
  case SyntaxKind::CloseBraceToken:
    return "CloseBraceToken";
  case SyntaxKind::StringToken:
    return "StringToken";
  case SyntaxKind::CharacterToken:
    return "CharacterToken";
  case SyntaxKind::IdentifierToken:
    return "IdentifierToken";
  case SyntaxKind::SemicolonToken:
    return "SemicolonToken";
  case SyntaxKind::AmpersandToken:
    return "AmpersandToken";
  case SyntaxKind::PipeToken:
    return "PipeToken";
  case SyntaxKind::CaretToken:
    return "CaretToken";
  case SyntaxKind::TildeToken:
    return "TildeToken";
  case SyntaxKind::PercentToken:
    return "PercentToken";

  case SyntaxKind::AssignmentExpression:
    return "AssignmentExpression";
  case SyntaxKind::EndOfLineToken:
    return "EndOfLineToken";
  case SyntaxKind::VarKeyword:
    return "VarKeyword";
  case SyntaxKind::ConstKeyword:
    return "ConstKeyword";
  case SyntaxKind::VariableDeclaration:
    return "VariableDeclaration";
  case SyntaxKind::IfKeyword:
    return "IfKeyword";
  case SyntaxKind::ElseKeyword:
    return "ElseKeyword";
  case SyntaxKind::ElseClause:
    return "ElseClause";
  case SyntaxKind::IfStatement:
    return "IfStatement";
  case SyntaxKind::WhileKeyword:
    return "WhileKeyword";
  case SyntaxKind::WhileStatement:
    return "WhileStatement";
  case SyntaxKind::ForKeyword:
    return "ForKeyword";
  case SyntaxKind::ToKeyword:
    return "ToKeyword";
  case SyntaxKind::ForStatement:
    return "ForStatement";
  case SyntaxKind::BlockStatement:
    return "BlockStatement";
  case SyntaxKind::ExpressionStatement:
    return "ExpressionStatement";
  case SyntaxKind::CallExpression:
    return "CallExpression";
  case SyntaxKind::GlobalStatement:
    return "GlobalStatement";
  case SyntaxKind::ParameterSyntax:
    return "ParameterSyntax";
  case SyntaxKind::FunctionDeclarationSyntax:
    return "FunctionDeclarationSyntax";
  case SyntaxKind::FunctionKeyword:
    return "FunctionKeyword";
  case SyntaxKind::ContinueKeyword:
    return "ContinueKeyword";
  case SyntaxKind::BreakKeyword:
    return "BreakKeyword";

  case SyntaxKind::AsKeyword:
    return "AsKeyword";

  case SyntaxKind::InOutKeyword:
    return "InOutKeyword";

  case SyntaxKind::ReturnKeyword:
    return "ReturnKeyword";

  case SyntaxKind::ReturnStatement:
    return "ReturnStatement";

  case SyntaxKind::CaseStatementSyntax:
    return "CaseStatementSyntax";

  case SyntaxKindUtils::SwitchStatementSyntax:
    return "SwitchStatementSyntax";

  case SyntaxKind::OrKeyword:
    return "OrKeyword";

  case SyntaxKind::OrIfStatement:
    return "OrIfStatement";

  case SyntaxKind::ColonToken:
    return "ColonToken";

  case SyntaxKind::SlashHashToken:
    return "SlashHashToken";

  case SyntaxKind::HashToken:
    return "HashToken";

  case SyntaxKind::HashSlashToken:
    return "HashSlashToken";

  case SyntaxKind::DotToken: {
    return "DotToken";
  }

  case SyntaxKind::CommentStatement:
    return "CommentStatement";

  case SyntaxKind::ModuleStatement:
    return "ModuleStatement";

  case SyntaxKind::NthgKeyword:
    return "NthgKeyword";

  case SyntaxKind::BoolKeyword:
    return "BoolKeyword";

  case SyntaxKind::Int32Keyword:
    return "Int32Keyword";
  case SyntaxKind::Int8Keyword:
    return "Int8Keyword";
  case SyntaxKindUtils::SwitchKeyword:
    return "SwitchKeyword";

  case SyntaxKind::CaseKeyword:
    return "CaseKeyword";

  case SyntaxKind::DefaultKeyword:
    return "DefaultKeyword";

  case SyntaxKind::DeciKeyword:
    return "DeciKeyword";

  case SyntaxKind::NirastKeyword:
    return "NirastKeyword";

  case SyntaxKind::StrKeyword:
    return "StrKeyword";

  case SyntaxKind::BringKeyword:
    return "BringKeyword";

  case SyntaxKind::EmptyStatement:
    return "EmptyStatement";
  case SyntaxKind::ExposeKeyword: {
    return "ExposeKeyword";
  }
  case SyntaxKind::FromKeyword: {
    return "FromKeyword";
  }

  case SyntaxKind::NirastExpression: {
    return "NirastExpression";
  }

  case SyntaxKind::BringStatementSyntax:
    return "BringStatementSyntax";

  case SyntaxKind::OpenBracketToken:
    return "OpenBracketToken";

  case SyntaxKind::CloseBracketToken:
    return "CloseBracketToken";

  case SyntaxKind::IndexExpression:
    return "IndexExpression";
  case SyntaxKind::SlashSlashToken:
    return "SlashSlashToken";

  case SyntaxKind::ContainerExpression:
    return "ContainerExpression";

  case SyntaxKind::FillExpression:
    return "FillExpression";

  case SyntaxKind::BracketedExpression:
    return "BracketedExpression";

  case SyntaxKind::FillKeyword:
    return "FillKeyword";
  case SyntaxKind::MultipleAssignmentExpression:
    return "MultipleAssignmentExpression";
  case SyntaxKind::ContainerStatement:
    return "ContainerStatement";
  case SyntaxKind::VariableExpressionSyntax:
    return "VariableExpressionSyntax";

  case SyntaxKind::ArrayVariableExpressionSyntax:
    return "ArrayVariableExpressionSyntax";

  case SyntaxKind::PrimitiveTypeExpression:
    return "PrimitiveTypeExpression";

  case SyntaxKind::ArrayTypeExpression:
    return "ArrayTypeExpression";

  case SyntaxKind::TypeKeyword:
    return "TypeKeyword";

  case SyntaxKind::ModuleKeyword:
    return "ModuleKeyword";

  case SyntaxKind::ObjectTypeExpression:
    return "ObjectTypeExpression";

  case SyntaxKind::FunctionTypeExpression:
    return "FunctionTypeExpression";

  case SyntaxKind::CustomTypeStatement:
    return "CustomTypeStatement";

  case SyntaxKind::ObjectExpression:
    return "ObjectExpression";

  case SyntaxKind::NBU_ARRAY_TYPE:
    return "NBU_ARRAY_TYPE";

  case SyntaxKind::NBU_OBJECT_TYPE:
    return "NBU_OBJECT_TYPE";

  case SyntaxKind::NBU_UNKNOWN_TYPE:
    return "NBU_UNKNOWN_TYPE";

  case SyntaxKind::NBU_FUNCTION_TYPE:
    return "NBU_FUNCTION_TYPE";

  case SyntaxKind::BreakStatement:
    return "BreakStatement";

  case SyntaxKind::ContinueStatement:
    return "ContinueStatement";

  case SyntaxKind::DeclKeyword:
    return "DeclKeyword";
  case SyntaxKind::Deci32Keyword:
    return "Deci32Keyword";
  case SyntaxKind::Int64Keyword:
    return "Int64Keyword";
  case SyntaxKind::AssignmentToken:
    return "AssignmentToken";
  case SyntaxKind::NewKeyword:
    return "NewKeyword";
  case SyntaxKind::ClassKeyword:
    return "ClassKeyword";
  case SyntaxKind::ClassStatement:
    return "ClassStatement";
  case SyntaxKind::ExtendsKeyword:
    return "ExtendsKeyword";
  case SyntaxKindUtils::TernaryExpression:
    return "TernaryExpression";
  default:
    return "NotDefined";
  }
}

bool SyntaxKindUtils::isType(SyntaxKind kind) {
  switch (kind) {
  case SyntaxKind::BoolKeyword:
  case SyntaxKind::Int8Keyword:
  case SyntaxKind::Int32Keyword:
  case SyntaxKind::Int64Keyword:
  case SyntaxKind::DeciKeyword:
  case SyntaxKind::Deci32Keyword:
  case SyntaxKind::StrKeyword:
    return true;
  default:
    return false;
  }
}