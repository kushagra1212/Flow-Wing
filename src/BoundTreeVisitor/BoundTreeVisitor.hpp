#pragma once

#include "src/SemanticAnalyzer/BoundExpressions/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundBinaryExpression/BoundBinaryExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundColonExpression/BoundColonExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundContainerExpression/BoundContainerExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundIdentifierExpression/BoundIdentifierExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundIndexExpression/BoundIndexExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundBooleanLiteralExpression/BoundBooleanLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundCharacterLiteralExpression/BoundCharacterLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundDoubleLiteralExpression/BoundDoubleLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundFloatLiteralExpression/BoundFloatLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundIntegerLiteralExpression/BoundIntegerLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundNirastLiteralExpression/BoundNirastLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundStringLiteralExpression/BoundStringLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundTemplateStringLiteralExpression/BoundTemplateStringLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundMemberAccessExpression/BoundMemberAccessExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundModuleAccessExpression/BoundModuleAccessExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundNewExpression/BoundNewExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundObjectExpression/BoundObjectExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundParenthesizedExpression/BoundParenthesizedExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundTernaryExpression/BoundTernaryExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundUnaryExpression/BoundUnaryExpression.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundBlockStatement/BoundBlockStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundBreakStatement/BoundBreakStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundClassStatement/BoundClassStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundContinueStatement/BoundContinueStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundCustomTypeStatement/BoundCustomTypeStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundErrorStatement/BoundErrorStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundExposeStatement/BoundExposeStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundExpressionStatement/BoundExpressionStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundForStatement/BoundForStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundFunctionStatement/BoundFunctionStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundIfStatement/BoundIfStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundReturnStatement/BoundReturnStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundSwitchStatement/BoundSwitchStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundVariableDeclaration/BoundVariableDeclaration.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundWhileStatement/BoundWhileStatement.hpp"
#include "src/syntax/expression/ExpressionSyntax.h"

namespace flow_wing {

namespace binding {
class BoundCompilationUnit;
} // namespace binding

namespace visitor {

class BoundTreeVisitor {
public:
  virtual ~BoundTreeVisitor() = default;

  virtual void visit(binding::BoundCompilationUnit *compilation_unit) = 0;
  virtual void visit(binding::BoundBlockStatement *block_statement) = 0;
  virtual void visit(binding::BoundExposeStatement *expose_statement) = 0;
  virtual void
  visit(binding::BoundCustomTypeStatement *custom_type_statement) = 0;
  virtual void
  visit(binding::BoundVariableDeclaration *variable_declaration) = 0;
  virtual void visit(binding::BoundFunctionStatement *function_statement) = 0;
  virtual void visit(binding::BoundIfStatement *if_statement) = 0;
  virtual void visit(binding::BoundWhileStatement *while_statement) = 0;
  virtual void visit(binding::BoundForStatement *for_statement) = 0;
  virtual void visit(binding::BoundBreakStatement *break_statement) = 0;
  virtual void visit(binding::BoundContinueStatement *continue_statement) = 0;
  virtual void visit(binding::BoundReturnStatement *return_statement) = 0;
  virtual void visit(binding::BoundSwitchStatement *switch_statement) = 0;
  virtual void visit(binding::BoundClassStatement *class_statement) = 0;
  virtual void
  visit(binding::BoundIdentifierExpression *identifier_expression) = 0;
  virtual void visit(binding::BoundIndexExpression *index_expression) = 0;
  virtual void
  visit(binding::BoundIntegerLiteralExpression *integer_literal_expression) = 0;
  virtual void
  visit(binding::BoundDoubleLiteralExpression *double_literal_expression) = 0;
  virtual void
  visit(binding::BoundFloatLiteralExpression *float_literal_expression) = 0;
  virtual void visit(binding::BoundCharacterLiteralExpression
                         *character_literal_expression) = 0;
  virtual void
  visit(binding::BoundStringLiteralExpression *string_literal_expression) = 0;
  virtual void
  visit(binding::BoundBooleanLiteralExpression *boolean_literal_expression) = 0;
  virtual void visit(binding::BoundTemplateStringLiteralExpression
                         *template_string_literal_expression) = 0;
  virtual void
  visit(binding::BoundNirastLiteralExpression *nirast_literal_expression) = 0;
  virtual void visit(binding::BoundErrorStatement *error_statement) = 0;
  virtual void
  visit(binding::BoundExpressionStatement *expression_statement) = 0;
  virtual void visit(binding::BoundErrorExpression *error_expression) = 0;

  virtual void
  visit(binding::BoundModuleAccessExpression *module_access_expression) = 0;

  virtual void visit(binding::BoundCallExpression *call_expression) = 0;
  virtual void
  visit(binding::BoundMemberAccessExpression *member_access_expression) = 0;
  virtual void visit(binding::BoundTernaryExpression *ternary_expression) = 0;
  virtual void visit(binding::BoundNewExpression *new_expression) = 0;
  virtual void visit(binding::BoundUnaryExpression *unary_expression) = 0;
  virtual void visit(binding::BoundBinaryExpression *binary_expression) = 0;
  virtual void
  visit(binding::BoundParenthesizedExpression *parenthesized_expression) = 0;
  virtual void visit(binding::BoundObjectExpression *object_expression) = 0;
  virtual void
  visit(binding::BoundAssignmentExpression *assignment_expression) = 0;
  virtual void visit(binding::BoundColonExpression *colon_expression) = 0;
  virtual void
  visit(binding::BoundContainerExpression *container_expression) = 0;
};

} // namespace visitor
} // namespace flow_wing