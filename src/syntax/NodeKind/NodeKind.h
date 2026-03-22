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

#pragma once
#include <string>

namespace flow_wing {
namespace syntax {

enum class NodeKind : int {

  kTokenNode,

  // --- Expressions ---

  // --- Literals ---
  kNumberLiteralExpression,
  kInt64LiteralExpression,
  kFloatLiteralExpression,
  kDoubleLiteralExpression,
  kStringLiteralExpression,
  kTemplateStringLiteralExpression,
  kCharacterLiteralExpression,
  kBooleanLiteralExpression,

  kUnaryExpression,
  kBinaryExpression,
  kParenthesizedExpression,
  kAssignmentExpression,
  kCallExpression,
  kIndexExpression,
  kContainerExpression,
  kNirastExpression,
  kSuperExpression,
  kFillExpression,
  kBracketedExpression,
  kNewExpression,
  kTernaryExpression,
  kColonExpression,
  kInt32TypeExpression,
  kInt64TypeExpression,
  kDeci32TypeExpression,
  kInt8TypeExpression,
  kCharTypeExpression,
  kDeciTypeExpression,
  kStrTypeExpression,
  kArrayTypeExpression,
  kNthgTypeExpression,
  kBoolTypeExpression,
  kObjectTypeExpression,
  kFunctionTypeExpression,
  kModuleAccessTypeExpression,
  kObjectExpression,
  kIdentifierExpression,
  kDimensionClauseExpression,
  kModuleAccessExpression,
  kMemberAccessExpression,
  kDeclaratorExpression,
  kFieldDeclarationExpression,
  kParameterExpression,
  kFunctionReturnTypeExpression,
  kErrorExpression,

  // --- Statements ---
  kCompilationUnit,
  kGlobalStatement,
  kExpressionStatement,
  kCustomTypeStatement,
  kBlockStatement,
  kVariableDeclaration,
  kClassStatement,
  kIfStatement,
  kOrIfStatement,
  kElseClause,
  kWhileStatement,
  kForStatement,
  kReturnStatement,
  kParameter,
  kArrayParameter,
  kBringStatement,
  kContainerStatement,
  kCaseStatement,
  kSwitchStatement,
  kBreakStatement,
  kModuleStatement,
  kContinueStatement,
  kDefaultCaseStatement,
  kExposeStatement,
  kFunctionStatement,

};

const std::string &toString(NodeKind kind);
bool isType(NodeKind kind);

} // namespace syntax
} // namespace flow_wing
