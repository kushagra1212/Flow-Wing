/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 */
#include "NodeKind.h"
#include <cassert>
#include <unordered_map>

namespace flow_wing {
namespace binding {

const std::string &toString(NodeKind kind) {
  static const std::unordered_map<NodeKind, std::string> kKindStrings = {

      // --- Statements ---
      {NodeKind::kCompilationUnit, "CompilationUnit"},
      {NodeKind::kBlockStatement, "BlockStatement"},
      {NodeKind::kExposeStatement, "ExposeStatement"},

      // ---- Bound If Statements ----
      {NodeKind::kIfStatement, "IfStatement"},

      // ---- Bound While Statements ----
      {NodeKind::kWhileStatement, "WhileStatement"},

      // ---- Bound For Statements ----
      {NodeKind::kForStatement, "ForStatement"},

      // ---- Bound Break Statements ----
      {NodeKind::kBreakStatement, "BreakStatement"},

      // ---- Bound Continue Statements ----
      {NodeKind::kContinueStatement, "ContinueStatement"},

      // ---- Bound Return Statements ----
      {NodeKind::kReturnStatement, "ReturnStatement"},

      // ---- Bound Switch Statements ----
      {NodeKind::kSwitchStatement, "SwitchStatement"},

      // ---- Bound Class Statements ----
      {NodeKind::kClassStatement, "ClassStatement"},
      {NodeKind::kModuleStatement, "ModuleStatement"},
      {NodeKind::kExpressionStatement, "ExpressionStatement"},

      // ---- Bound Declaration Statements ----
      {NodeKind::kCustomTypeStatement, "CustomTypeStatement"},
      {NodeKind::kFunctionStatement, "FunctionStatement"},
      {NodeKind::kVariableDeclaration, "VariableDeclaration"},

      // -- Bound Expressions --
      {NodeKind::kIdentifierExpression, "IdentifierExpression"},
      {NodeKind::kIndexExpression, "IndexExpression"},

      // ---- Bound Parenthesized Expressions ----
      {NodeKind::kParenthesizedExpression, "ParenthesizedExpression"},

      // --- Bound Literal Expressions ---
      {NodeKind::kNumberLiteralExpression, "NumberLiteralExpression"},
      {NodeKind::kDoubleLiteralExpression, "DoubleLiteralExpression"},
      {NodeKind::kFloatLiteralExpression, "FloatLiteralExpression"},
      {NodeKind::kCharacterLiteralExpression, "CharacterLiteralExpression"},
      {NodeKind::kStringLiteralExpression, "StringLiteralExpression"},
      {NodeKind::kBooleanLiteralExpression, "BooleanLiteralExpression"},
      {NodeKind::kTemplateStringLiteralExpression,
       "TemplateStringLiteralExpression"},
      {NodeKind::kNirastLiteralExpression, "NirastLiteralExpression"},

      // ---- Error ----
      {NodeKind::kErrorStatement, "ErrorStatement"},
      {NodeKind::kErrorExpression, "ErrorExpression"},

      // ---- Bound Module Access Expressions ----
      {NodeKind::kModuleAccessExpression, "ModuleAccessExpression"},

      // ---- Bound Call Expressions ----
      {NodeKind::kCallExpression, "CallExpression"},

      // ---- Bound Member Access Expressions ----
      {NodeKind::kMemberAccessExpression, "MemberAccessExpression"},

      // ---- Bound Ternary Expressions ----
      {NodeKind::kTernaryExpression, "TernaryExpression"},

      // ---- Bound New Expressions ----
      {NodeKind::kNewExpression, "NewExpression"},

      // ---- Bound Unary Expressions ----
      {NodeKind::kUnaryExpression, "UnaryExpression"},

      // ---- Bound Binary Expressions ----
      {NodeKind::kBinaryExpression, "BinaryExpression"},

      // ---- Bound Assignment Expressions ----
      {NodeKind::kAssignmentExpression, "AssignmentExpression"},

      // ---- Bound Object Expressions ----
      {NodeKind::kObjectExpression, "ObjectExpression"},

      // ---- Bound Colon Expressions ----
      {NodeKind::kColonExpression, "ColonExpression"},

      // ---- Bound Container Expressions ----
      {NodeKind::kContainerExpression, "ContainerExpression"},

      // ---- Bound Dimension Clause Expressions ----
      {NodeKind::kDimensionClauseExpression, "DimensionClauseExpression"},

  };

  static const std::string kNotDefined = "";
  auto it = kKindStrings.find(kind);
  if (it != kKindStrings.end()) {
    return it->second;
  }

  assert(false && "toString: Binding::NodeKind not found");
  return kNotDefined;
}

} // namespace binding
} // namespace flow_wing
