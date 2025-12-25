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

#pragma once
#include <string>

namespace flow_wing {
namespace binding {

enum class NodeKind : int {

  // ---------- Statements ----------
  kCompilationUnit,
  kBlockStatement,
  kExposeStatement,

  // ---- Bound Declaration Statements ----
  kCustomTypeStatement,
  kVariableDeclaration,
  kFunctionStatement,

  // ---- Bound If Statements ----
  kIfStatement,

  // ---- Bound While Statements ----
  kWhileStatement,

  // ---- Bound For Statements ----
  kForStatement,

  // ---- Bound Break Statements ----
  kBreakStatement,

  // ---- Bound Continue Statements ----
  kContinueStatement,

  // ---- Bound Return Statements ----
  kReturnStatement,

  // ---- Bound Switch Statements ----
  kSwitchStatement,

  // ---- Bound Class Statements ----
  kClassStatement,

  // ---- Bound Expression Statements ----
  kExpressionStatement,

  // ---------- Expressions ----------

  // -- Bound Expressions --
  kIdentifierExpression,
  kIndexExpression,

  // ---- Bound Parenthesized Expressions ----
  kParenthesizedExpression,

  // --- Bound Literal Expressions ---
  kNumberLiteralExpression,
  kDoubleLiteralExpression,
  kFloatLiteralExpression,
  kCharacterLiteralExpression,
  kStringLiteralExpression,
  kBooleanLiteralExpression,
  kTemplateStringLiteralExpression,
  kNirastLiteralExpression,

  // ---- Error ----
  kErrorStatement,
  kErrorExpression,

  // ---- Bound Module Access Expressions ----
  kModuleAccessExpression,

  // ---- Bound Call Expressions ----
  kCallExpression,

  // ---- Bound Member Access Expressions ----
  kMemberAccessExpression,

  // ---- Bound Ternary Expressions ----
  kTernaryExpression,

  // ---- Bound New Expressions ----
  kNewExpression,

  // ---- Bound Unary Expressions ----
  kUnaryExpression,

  // ---- Bound Binary Expressions ----
  kBinaryExpression,

  // ---- Bound Assignment Expressions ----
  kAssignmentExpression,

};

const std::string &toString(NodeKind kind);
bool isType(NodeKind kind);

} // namespace binding
} // namespace flow_wing
