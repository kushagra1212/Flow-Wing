#pragma once

#include "src/SemanticAnalyzer/BoundExpressions/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundBinaryExpression/BoundBinaryExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundCallExpression/BoundCallExpression.h"
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
  virtual void visit(binding::BoundFunctionStatement *variable_declaration) = 0;
  virtual void visit(binding::BoundIfStatement *variable_declaration) = 0;
  virtual void visit(binding::BoundWhileStatement *variable_declaration) = 0;
  virtual void visit(binding::BoundForStatement *variable_declaration) = 0;
  virtual void visit(binding::BoundBreakStatement *variable_declaration) = 0;
  virtual void visit(binding::BoundContinueStatement *variable_declaration) = 0;
  virtual void visit(binding::BoundReturnStatement *variable_declaration) = 0;
  virtual void visit(binding::BoundSwitchStatement *variable_declaration) = 0;
  virtual void visit(binding::BoundClassStatement *variable_declaration) = 0;
  virtual void
  visit(binding::BoundIdentifierExpression *variable_declaration) = 0;
  virtual void visit(binding::BoundIndexExpression *variable_declaration) = 0;
  virtual void
  visit(binding::BoundIntegerLiteralExpression *variable_declaration) = 0;
  virtual void
  visit(binding::BoundDoubleLiteralExpression *variable_declaration) = 0;
  virtual void
  visit(binding::BoundFloatLiteralExpression *variable_declaration) = 0;
  virtual void
  visit(binding::BoundCharacterLiteralExpression *variable_declaration) = 0;
  virtual void
  visit(binding::BoundStringLiteralExpression *variable_declaration) = 0;
  virtual void
  visit(binding::BoundBooleanLiteralExpression *variable_declaration) = 0;
  virtual void visit(
      binding::BoundTemplateStringLiteralExpression *variable_declaration) = 0;
  virtual void
  visit(binding::BoundNirastLiteralExpression *variable_declaration) = 0;
  virtual void visit(binding::BoundErrorStatement *variable_declaration) = 0;
  virtual void
  visit(binding::BoundExpressionStatement *variable_declaration) = 0;
  virtual void visit(binding::BoundErrorExpression *variable_declaration) = 0;

  virtual void
  visit(binding::BoundModuleAccessExpression *variable_declaration) = 0;

  virtual void visit(binding::BoundCallExpression *variable_declaration) = 0;
  virtual void
  visit(binding::BoundMemberAccessExpression *variable_declaration) = 0;
  virtual void visit(binding::BoundTernaryExpression *variable_declaration) = 0;
  virtual void visit(binding::BoundNewExpression *variable_declaration) = 0;
  virtual void visit(binding::BoundUnaryExpression *variable_declaration) = 0;
  virtual void visit(binding::BoundBinaryExpression *variable_declaration) = 0;
  virtual void
  visit(binding::BoundAssignmentExpression *variable_declaration) = 0;
};

} // namespace visitor
} // namespace flow_wing