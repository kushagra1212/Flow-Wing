
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
  std::shared_ptr<BoundScope> root;
  std::vector<std::shared_ptr<BoundCallExpression>> _callExpressions;

public:
  Binder(std::shared_ptr<BoundScope> root);

  std::vector<std::string> logs;

public:
  std::shared_ptr<BoundExpression>
  bindExpression(std::shared_ptr<ExpressionSyntax> syntax);

  std::shared_ptr<BoundStatement>
  bindGlobalStatement(std::shared_ptr<GlobalStatementSyntax> syntax);

  std::shared_ptr<BoundStatement>
  bindFunctionDeclaration(std::shared_ptr<FunctionDeclarationSyntax> syntax);

public:
  static void verifyAllCallsAreValid(std::shared_ptr<Binder> binder);

  static std::shared_ptr<BoundScopeGlobal>
  bindGlobalScope(std::unique_ptr<BoundScopeGlobal> previous,
                  std::shared_ptr<CompilationUnitSyntax> syntax);

public:
  static std::shared_ptr<BoundScope>
  CreateParentScope(std::shared_ptr<BoundScopeGlobal> parent);

public:
  std::shared_ptr<BoundStatement>
  bindStatement(std::shared_ptr<StatementSyntax> syntax);
};
