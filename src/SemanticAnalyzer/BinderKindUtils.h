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

#include "src/syntax/SyntaxKindUtils.h"

namespace BinderKindUtils {
enum BoundNodeKind : int {
  UnaryExpression,
  BinaryExpression,
  LiteralExpression,
  ParenthesizedExpression,
  AssignmentExpression,
  VariableExpression,
  CallExpression,
  IndexExpression,
  BoundContainerExpression,
  BoundFillExpression,
  BoundBracketedExpression,
  ArrayVariableExpression,
  BoundTypeExpression,
  BoundArrayTypeExpression,
  BoundObjectTypeExpression,
  BoundFunctionTypeExpression,
  BoundObjectExpression,
  BoundNirastExpression,
  BoundTernaryExpression,
  BoundMultipleAssignmentExpression,

  // Statements
  BoundStatementKind,
  ExpressionStatement,
  BlockStatement,
  IfStatement,
  OrIfStatement,
  WhileStatement,
  ForStatement,
  BreakStatement,
  ContinueStatement,
  ReturnStatement,
  BringStatement,
  ContainerStatement,
  CustomTypeStatement,
  BoundCaseStatement,
  BoundSwitchStatement,
  ClassStatement,
  BoundModuleStatement,
  BoundMultipleVariableDeclarationStatement,

  // declarations

  VariableDeclaration,
  FunctionDeclaration,

  // Symbols
  BoundFunctionSymbol,
};

enum BoundUnaryOperatorKind : int {
  Identity,
  Negation,
  LogicalNegation,
  BitwiseNegation,
};

enum BoundBinaryOperatorKind : int {
  Addition,
  Subtraction,
  Multiplication,
  Division,
  LogicalAnd,
  LogicalOr,
  Equals,
  NotEquals,
  Less,
  LessOrEquals,
  Greater,
  GreaterOrEquals,
  Assignment,
  BitwiseAnd,
  BitwiseOr,
  BitwiseXor,
  Modulus,
  IntegerDivision,
  AssignmentToken
};

enum MemoryKind : int { Stack, Heap, Global, None };

std::string to_string(MemoryKind kind);

std::string to_string(BoundNodeKind kind);

std::string to_string(BoundUnaryOperatorKind kind);

std::string to_string(BoundBinaryOperatorKind kind);

BoundUnaryOperatorKind getUnaryOperatorKind(SyntaxKindUtils::SyntaxKind kind);

BoundBinaryOperatorKind getBinaryOperatorKind(SyntaxKindUtils::SyntaxKind kind);

} // namespace BinderKindUtils
