/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 */
#include "NodeKind.h"
#include <unordered_map>

namespace flow_wing {
namespace syntax {

const std::string &toString(NodeKind kind) {
  static const std::unordered_map<NodeKind, std::string> kKindStrings = {

      // Syntax Node
      {NodeKind::kTokenNode, "TokenNode"},

      // Expressions
      {NodeKind::kCharacterLiteralExpression, "CharacterLiteralExpression"},
      {NodeKind::kNumberLiteralExpression, "NumberLiteralExpression"},
      {NodeKind::kInt64LiteralExpression, "Int64LiteralExpression"},
      {NodeKind::kFloatLiteralExpression, "FloatLiteralExpression"},
      {NodeKind::kDoubleLiteralExpression, "DoubleLiteralExpression"},
      {NodeKind::kStringLiteralExpression, "StringLiteralExpression"},
      {NodeKind::kTemplateStringLiteralExpression,
       "TemplateStringLiteralExpression"},
      {NodeKind::kBooleanLiteralExpression, "BooleanLiteralExpression"},
      {NodeKind::kUnaryExpression, "UnaryExpression"},
      {NodeKind::kBinaryExpression, "BinaryExpression"},
      {NodeKind::kParenthesizedExpression, "ParenthesizedExpression"},
      {NodeKind::kAssignmentExpression, "AssignmentExpression"},
      {NodeKind::kCallExpression, "CallExpression"},
      {NodeKind::kIndexExpression, "IndexExpression"},
      {NodeKind::kContainerExpression, "ContainerExpression"},
      {NodeKind::kNirastExpression, "NirastExpression"},
      {NodeKind::kFillExpression, "FillExpression"},
      {NodeKind::kBracketedExpression, "BracketedExpression"},
      {NodeKind::kTernaryExpression, "TernaryExpression"},
      {NodeKind::kInt32TypeExpression, "Int32TypeExpression"},
      {NodeKind::kInt64TypeExpression, "Int64TypeExpression"},
      {NodeKind::kDeci32TypeExpression, "Deci32TypeExpression"},
      {NodeKind::kInt8TypeExpression, "Int8TypeExpression"},
      {NodeKind::kCharTypeExpression, "CharTypeExpression"},
      {NodeKind::kDeciTypeExpression, "DeciTypeExpression"},
      {NodeKind::kStrTypeExpression, "StrTypeExpression"},
      {NodeKind::kBoolTypeExpression, "BoolTypeExpression"},
      {NodeKind::kNthgTypeExpression, "NthgTypeExpression"},
      {NodeKind::kArrayTypeExpression, "ArrayTypeExpression"},
      {NodeKind::kObjectTypeExpression, "ObjectTypeExpression"},
      {NodeKind::kFunctionTypeExpression, "FunctionTypeExpression"},
      {NodeKind::kObjectExpression, "ObjectExpression"},
      {NodeKind::kIdentifierExpression, "IdentifierExpression"},
      {NodeKind::kDimensionClauseExpression, "DimensionClauseExpression"},
      {NodeKind::kModuleAccessExpression, "ModuleAccessExpression"},
      {NodeKind::kModuleAccessTypeExpression, "ModuleAccessTypeExpression"},
      {NodeKind::kNewExpression, "NewExpression"},
      {NodeKind::kObjectMemberExpression, "ObjectMemberExpression"},
      {NodeKind::kMemberAccessExpression, "MemberAccessExpression"},
      {NodeKind::kDeclaratorExpression, "DeclaratorExpression"},
      {NodeKind::kFieldDeclarationExpression, "FieldDeclarationExpression"},
      {NodeKind::kParameterExpression, "ParameterExpression"},
      {NodeKind::kFunctionReturnTypeExpression, "FunctionReturnTypeExpression"},
      {NodeKind::kErrorExpression, "ErrorExpression"},

      // Statements
      {NodeKind::kCompilationUnit, "CompilationUnit"},
      {NodeKind::kGlobalStatement, "GlobalStatement"},
      {NodeKind::kExpressionStatement, "ExpressionStatement"},
      {NodeKind::kCustomTypeStatement, "CustomTypeStatement"},
      {NodeKind::kBlockStatement, "BlockStatement"},
      {NodeKind::kVariableDeclaration, "VariableDeclaration"},
      {NodeKind::kClassStatement, "ClassStatement"},
      {NodeKind::kIfStatement, "IfStatement"},
      {NodeKind::kOrIfStatement, "OrIfStatement"},
      {NodeKind::kElseClause, "ElseClause"},
      {NodeKind::kWhileStatement, "WhileStatement"},
      {NodeKind::kForStatement, "ForStatement"},
      {NodeKind::kReturnStatement, "ReturnStatement"},
      {NodeKind::kParameter, "Parameter"},
      {NodeKind::kArrayParameter, "ArrayParameter"},
      {NodeKind::kBringStatement, "BringStatement"},
      {NodeKind::kContainerStatement, "ContainerStatement"},
      {NodeKind::kCaseStatement, "CaseStatement"},
      {NodeKind::kSwitchStatement, "SwitchStatement"},
      {NodeKind::kBreakStatement, "BreakStatement"},
      {NodeKind::kModuleStatement, "ModuleStatement"},
      {NodeKind::kContinueStatement, "ContinueStatement"},
      {NodeKind::kDefaultCaseStatement, "DefaultCaseStatement"},
      {NodeKind::kExposeStatement, "ExposeStatement"},
      {NodeKind::kFunctionStatement, "FunctionStatement"},

  };

  static const std::string kNotDefined = "NotDefined";
  auto it = kKindStrings.find(kind);
  if (it != kKindStrings.end()) {
    return it->second;
  }
  return kNotDefined;
}

} // namespace syntax
} // namespace flow_wing
