#include "AssignmentExpressionBinder.h"

#include "../ExpressionBinderFactory.h"

std::unique_ptr<BoundExpression>
AssignmentExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                           ExpressionSyntax *expression) {
  std::string variable_str = "";

  AssignmentExpressionSyntax *assignmentExpression =
      static_cast<AssignmentExpressionSyntax *>(expression);

  if (auto variableExpression = dynamic_cast<VariableExpressionSyntax *>(
          assignmentExpression->getLeftRef().get())) {
    variable_str = variableExpression->getVariableName();
  } else if (auto indexExpression = dynamic_cast<IndexExpressionSyntax *>(
                 assignmentExpression->getLeftRef().get())) {
    variable_str = std::any_cast<std::string>(
        indexExpression->getIndexIdentifierExpressionRef()->getValue());
  } else {

    ctx->getDiagnosticHandler()->addDiagnostic(
        Diagnostic("Invalid Assignment Expression",
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic,
                   assignmentExpression->getLeftRef()->getSourceLocation()));

    return std::move(
        ExpressionBinderFactory::create(
            assignmentExpression->getLeftRef()->getKind())
            ->bindExpression(ctx, assignmentExpression->getLeftRef().get()));
  }

  std::unique_ptr<BoundExpression> boundIdentifierExpression(
      ExpressionBinderFactory::create(
          assignmentExpression->getLeftRef()->getKind())
          ->bindExpression(ctx, assignmentExpression->getLeftRef().get()));

  BinderKindUtils::BoundBinaryOperatorKind op =
      BinderKindUtils::getBinaryOperatorKind(
          assignmentExpression->getOperatorTokenKind());

  if (!ctx->getRootRef()->tryLookupVariable(variable_str)) {
    ctx->getDiagnosticHandler()->addDiagnostic(
        Diagnostic("Can Not Assign To Undeclared Variable " + variable_str,
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic,
                   assignmentExpression->getLeftRef()->getSourceLocation()));

    return std::move(boundIdentifierExpression);
  }

  if (ctx->getRootRef()->tryGetVariable(variable_str)->isConst()) {
    ctx->getDiagnosticHandler()->addDiagnostic(
        Diagnostic("Can Not Assign To Constant Variable " + variable_str,
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic,
                   assignmentExpression->getLeftRef()->getSourceLocation()));

    return std::move(boundIdentifierExpression);
  }

  if (assignmentExpression->getRightRef()) {
    std::unique_ptr<BoundExpression> boundRight = std::move(
        ExpressionBinderFactory::create(
            assignmentExpression->getRightRef()->getKind())
            ->bindExpression(ctx, assignmentExpression->getRightRef().get()));

    return std::make_unique<BoundAssignmentExpression>(
        assignmentExpression->getSourceLocation(),
        ctx->getRootRef()->tryGetVariable(variable_str),
        std::move(boundIdentifierExpression), op, std::move(boundRight),
        assignmentExpression->getNeedDefaulInitilization());
  } else {
    return std::make_unique<BoundAssignmentExpression>(
        assignmentExpression->getSourceLocation(),
        ctx->getRootRef()->tryGetVariable(variable_str),
        std::move(boundIdentifierExpression), op, nullptr,
        assignmentExpression->getNeedDefaulInitilization());
  }
}