
#ifndef __BIND_BINDER_H__
#define __BIND_BINDER_H__

#include <stack>

#include "../../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../../interpreter/InterpreterUtils/InterpreterConversions/InterpreterConversion.h"
#include "../../syntax/CompilationUnitSyntax.h"
#include "../../syntax/SyntaxKindUtils.h"
#include "../../syntax/expression/AssignmentExpressionSyntax.h"
#include "../../syntax/expression/BinaryExpressionSyntax.h"
#include "../../syntax/expression/BracketedExpressionSyntax/BracketedExpressionSyntax.h"
#include "../../syntax/expression/CallExpressionSyntax/CallExpressionSyntax.h"
#include "../../syntax/expression/ExpressionSyntax.h"
#include "../../syntax/expression/FillExpressionSyntax/FillExpressionSyntax.h"
#include "../../syntax/expression/LiteralExpressionSyntax.h"
#include "../../syntax/expression/ObjectExpressionSyntax/ObjectExpressionSyntax.h"
#include "../../syntax/expression/ParenthesizedExpressionSyntax.h"
#include "../../syntax/expression/TypeExpressionSyntax/ArrayTypeExpressionSyntax/ArrayTypeExpressionSyntax.h"
#include "../../syntax/expression/TypeExpressionSyntax/TypeExpressionSyntax.h"
#include "../../syntax/expression/UnaryExpressionSyntax.h"
#include "../../syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "../../syntax/statements/BreakStatementSyntax/BreakStatementSyntax.h"
#include "../../syntax/statements/BringStatementSyntax/BringStatementSyntax.h"
#include "../../syntax/statements/ClassStatementSyntax/ClassStatementSyntax.h"
#include "../../syntax/statements/ContainerStatementSyntax/ContainerStatementSyntax.h"
#include "../../syntax/statements/ContinueStatementSyntax/ContinueStatementSyntax.h"
#include "../../syntax/statements/CustomTypeStatementSyntax/CustomTypeStatementSyntax.h"
#include "../../syntax/statements/ExpressionStatementSyntax/ExpressionStatementSyntax.h"
#include "../../syntax/statements/ForStatementSyntax/ForStatementSyntax.h"
#include "../../syntax/statements/FunctionDeclarationSyntax/FunctionDeclarationSyntax.h"
#include "../../syntax/statements/GlobalStatementSyntax/GlobalStatementSyntax.h"
#include "../../syntax/statements/IfStatementSyntax/IfStatementSyntax.h"
#include "../../syntax/statements/ReturnStatementSyntax/ReturnStatementSyntax.h"
#include "../../syntax/statements/StatementSyntax.h"
#include "../../syntax/statements/VariableDeclarationSyntax/VariableDeclarationSyntax.h"
#include "../../syntax/statements/WhileStatementSyntax/WhileStatementSyntax.h"
#include "../../utils/BuiltInFunction/BuiltInFunction.h"
#include "../../utils/Utils.h"
#include "../BinderKindUtils.h"
#include "../BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "../BoundBinaryExpression/BoundBinaryExpression.h"
#include "../BoundBlockStatement/BoundBlockStatement.h"
#include "../BoundBracketedExpression/BoundBracketedExpression.h"
#include "../BoundBreakStatement/BoundBreakStatement.h"
#include "../BoundBringStatement/BoundBringStatement.h"
#include "../BoundCallExpression/BoundCallExpression.h"
#include "../BoundClassStatement/BoundClassStatement.h"
#include "../BoundContainerExpression/BoundContainerExpression.h"
#include "../BoundContainerStatement/BoundContainerStatement.h"
#include "../BoundContinueStatement/BoundContinueStatement.h"
#include "../BoundCustomTypeStatement/BoundCustomTypeStatement.h"
#include "../BoundExpression.h"
#include "../BoundExpressionStatement/BoundExpressionStatement.h"
#include "../BoundFillExpression/BoundFillExpression.h"
#include "../BoundForStatement/BoundForStatement.h"
#include "../BoundFunctionDeclaration/BoundFunctionDeclaration.h"
#include "../BoundIfStatement/BoundIfStatement.h"
#include "../BoundIndexExpression/BoundIndexExpression.h"
#include "../BoundLiteralExpression/BoundLiteralExpression.h"
#include "../BoundObjectExpression/BoundObjectExpression.h"
#include "../BoundOrIfStatement/BoundOrIfStatement.h"
#include "../BoundReturnStatement/BoundReturnStatement.h"
#include "../BoundStatement/BoundStatement.h"
#include "../BoundTypeExpression/BoundArrayTypeExpression/BoundArrayTypeExpression.h"
#include "../BoundTypeExpression/BoundObjectTypeExpression/BoundObjectTypeExpression.h"
#include "../BoundTypeExpression/BoundTypeExpression.h"
#include "../BoundUnaryExpression/BoundUnaryExpression.h"
#include "../BoundVariableDeclaration/BoundVariableDeclaration.h"
#include "../BoundVariableExpression/BoundArrayVariableExpression/BoundArrayVariableExpression.h"
#include "../BoundVariableExpression/BoundVariableExpression.h"
#include "../BoundWhileStatement/BoundWhileStatement.h"
#include "BoundScope/BoundScope.h"
#include "BoundScopeGlobal/BoundScopeGlobal.h"

// other
#include "../../parser/Parser.h"

class Binder {
private:
  std::unique_ptr<BoundScope> root;
  FLowWing::DiagnosticHandler *_diagnosticHandler;

public:
  Binder(std::unique_ptr<BoundScope> root,
         FLowWing::DiagnosticHandler *diagnosticHandler);

  static void verifyAllCallsAreValid(Binder *binder);

  static std::unique_ptr<BoundScopeGlobal>
  bindGlobalScope(std::unique_ptr<BoundScopeGlobal> previous,
                  CompilationUnitSyntax *syntax,
                  FLowWing::DiagnosticHandler *diagnosticHandler);

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

  std::unique_ptr<BoundVariableDeclaration>
  bindVariableDeclaration(VariableDeclarationSyntax *variableDeclaration);
  std::unique_ptr<BoundStatement>
  bindIfStatement(IfStatementSyntax *ifStatement);

  std::unique_ptr<BoundOrIfStatement>
  bindOrIfStatement(OrIfStatementSyntax *orIfStatement);

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

  std::unique_ptr<BoundStatement>
  bindBringStatement(BringStatementSyntax *bringStatement);

  std::unique_ptr<BoundStatement>
  bindClassStatement(ClassStatementSyntax *bringStatement);

  std::unique_ptr<BoundStatement>
  bindCustomTypeStatement(CustomTypeStatementSyntax *customTypeStatement);

  // BoundExpressions

  std::unique_ptr<BoundExpression> bindExpression(ExpressionSyntax *syntax);

  std::unique_ptr<BoundLiteralExpression<std::any>>
  bindLiteralExpression(ExpressionSyntax *syntax);

  std::unique_ptr<BoundExpression>
  bindunaryExpression(UnaryExpressionSyntax *unaryExpression);

  std::unique_ptr<BoundExpression>
  bindBinaryExpression(BinaryExpressionSyntax *binaryExpression);

  std::unique_ptr<BoundExpression>
  bindAssignmentExpression(AssignmentExpressionSyntax *assignmentExpression);

  std::unique_ptr<BoundExpression>
  bindCallExpression(CallExpressionSyntax *callExpression);

  std::unique_ptr<BoundExpression>
  bindIndexExpression(IndexExpressionSyntax *indexExpression);

  std::unique_ptr<BoundExpression>
  bindContainerExpression(ContainerExpressionSyntax *containerExpression);

  std::unique_ptr<BoundExpression>
  bindFillExpression(FillExpressionSyntax *fillExpression);

  std::unique_ptr<BoundExpression>
  bindBracketedExpression(BracketedExpressionSyntax *bracketedExpression);

  std::unique_ptr<BoundVariableExpression>
  bindVariableExpression(VariableExpressionSyntax *variableExpressionSyntax);

  std::unique_ptr<BoundTypeExpression>
  bindTypeExpression(TypeExpressionSyntax *typeExpressionSyntax);

  std::unique_ptr<BoundExpression>
  bindObjectExpression(ObjectExpressionSyntax *objectExpressionSyntax);

  // Utils
  auto getMemberMap(const std::vector<std::unique_ptr<MemberSyntax>> &members,
                    CompilationUnitSyntax *nestedCompilationUnit)
      -> std::unordered_map<std::string, int>;

  void handleFunctionDefAndDec(FunctionDeclarationSyntax *syntax,
                               BoundFunctionDeclaration *fd);
};

#endif // __BIND_BINDER_H__