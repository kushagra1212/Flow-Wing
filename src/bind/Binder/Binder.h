
#pragma once
#include "../../syntax/CompilationUnitSyntax.h"
#include "../../syntax/SyntaxKindUtils.h"
#include "../../syntax/expression/AssignmentExpressionSyntax.h"
#include "../../syntax/expression/BinaryExpressionSyntax.h"
#include "../../syntax/expression/CallExpressionSyntax/CallExpressionSyntax.h"
#include "../../syntax/expression/ExpressionSyntax.h"
#include "../../syntax/expression/LiteralExpressionSyntax.h"
#include "../../syntax/expression/ParenthesizedExpressionSyntax.h"
#include "../../syntax/expression/UnaryExpressionSyntax.h"
#include "../../syntax/expression/VariableExpressionSyntax.h"
#include "../../syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "../../syntax/statements/BreakStatementSyntax/BreakStatementSyntax.h"
#include "../../syntax/statements/ContinueStatementSyntax/ContinueStatementSyntax.h"
#include "../../syntax/statements/ExpressionStatementSyntax/ExpressionStatementSyntax.h"
#include "../../syntax/statements/ForStatementSyntax/ForStatementSyntax.h"
#include "../../syntax/statements/FunctionDeclarationSyntax/FunctionDeclarationSyntax.h"
#include "../../syntax/statements/GlobalStatementSyntax/GlobalStatementSyntax.h"
#include "../../syntax/statements/IfStatementSyntax/IfStatementSyntax.h"
#include "../../syntax/statements/ReturnStatementSyntax/ReturnStatementSyntax.h"
#include "../../syntax/statements/StatementSyntax.h"
#include "../../syntax/statements/VariableDeclarationSyntax/VariableDeclarationSyntax.h"
#include "../../syntax/statements/WhileStatementSyntax/WhileStatementSyntax.h"

#include "../../utils/Utils.h"
#include "../BinderKindUtils.h"
#include "../BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "../BoundBinaryExpression/BoundBinaryExpression.h"
#include "../BoundBlockStatement/BoundBlockStatement.h"
#include "../BoundBreakStatement/BoundBreakStatement.h"
#include "../BoundCallExpression/BoundCallExpression.h"
#include "../BoundContinueStatement/BoundContinueStatement.h"
#include "../BoundExpression.h"
#include "../BoundExpressionStatement/BoundExpressionStatement.h"
#include "../BoundForStatement/BoundForStatement.h"
#include "../BoundFunctionDeclaration/BoundFunctionDeclaration.h"
#include "../BoundIfStatement/BoundIfStatement.h"
#include "../BoundLiteralExpression/BoundLiteralExpression.h"
#include "../BoundReturnStatement/BoundReturnStatement.h"
#include "../BoundStatement/BoundStatement.h"
#include "../BoundUnaryExpression/BoundUnaryExpression.h"
#include "../BoundVariableDeclaration/BoundVariableDeclaration.h"
#include "../BoundVariableExpression/BoundVariableExpression.h"
#include "../BoundWhileStatement/BoundWhileStatement.h"
#include "BoundScope/BoundScope.h"
#include "BoundScopeGlobal/BoundScopeGlobal.h"
#include <stack>
class Binder {
private:
private:
  std::unique_ptr<BoundScope> root;
  std::vector<BoundCallExpression *> _callExpressions;

public:
  Binder(std::unique_ptr<BoundScope> root);

  std::vector<std::string> logs;

  static void verifyAllCallsAreValid(Binder *binder);

  static std::unique_ptr<BoundScopeGlobal>
  bindGlobalScope(std::unique_ptr<BoundScopeGlobal> previous,
                  CompilationUnitSyntax *syntax);

  // BoundStatements

  std::unique_ptr<BoundStatement>
  bindGlobalStatement(GlobalStatementSyntax *syntax);

  std::unique_ptr<BoundStatement>
  bindFunctionDeclaration(FunctionDeclarationSyntax *syntax);

  std::unique_ptr<BoundStatement> bindStatement(StatementSyntax *syntax);

  std::unique_ptr<BoundStatement>
  bindExpressionStatement(ExpressionStatementSyntax *syntax);

  std::unique_ptr<BoundStatement>
  bindBlockStatement(BlockStatementSyntax *blockStatement);

  std::unique_ptr<BoundStatement>
  bindVariableDeclaration(VariableDeclarationSyntax *variableDeclaration);
  std::unique_ptr<BoundStatement>
  bindIfStatement(IfStatementSyntax *ifStatement);

  std::unique_ptr<BoundStatement>
  bindWhileStatement(WhileStatementSyntax *whileStatement);

  std::unique_ptr<BoundStatement>
  bindForStatement(ForStatementSyntax *forStatement);

  std::unique_ptr<BoundStatement>
  bindBreakStatement(BreakStatementSyntax *breakStatement);

  std::unique_ptr<BoundStatement>
  bindContinueStatement(ContinueStatementSyntax *continueStatement);
  std::unique_ptr<BoundStatement>
  bindReturnStatement(ReturnStatementSyntax *returnStatement);

  // BoundExpressions

  std::unique_ptr<BoundExpression> bindExpression(ExpressionSyntax *syntax);

  std::unique_ptr<BoundExpression>
  bindLiteralExpression(LiteralExpressionSyntax<std::any> *literalSyntax);

  std::unique_ptr<BoundExpression>
  bindunaryExpression(UnaryExpressionSyntax *unaryExpression);

  std::unique_ptr<BoundExpression>
  bindBinaryExpression(BinaryExpressionSyntax *binaryExpression);

  std::unique_ptr<BoundExpression>
  bindAssignmentExpression(AssignmentExpressionSyntax *assignmentExpression);

  std::unique_ptr<BoundExpression>
  bindVariableExpression(VariableExpressionSyntax *variableExpression);

  std::unique_ptr<BoundExpression>
  bindCallExpression(CallExpressionSyntax *callExpression);
};
