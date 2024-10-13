#include "MultipleAssignmentExpressionBinder.h"
#include <memory>

std::unique_ptr<BoundExpression>
MultipleAssignmentExpressionBinder::bindExpression(
    SyntaxBinderContext *ctx, ExpressionSyntax *expression) {
  MultipleAssignmentExpressionSyntax *multipleAssignmentExpressionSyntax =
      static_cast<MultipleAssignmentExpressionSyntax *>(expression);

  std::unique_ptr<BoundMultipleAssignmentExpression>
      boundMultipleAssignmentExpression =
          std::make_unique<BoundMultipleAssignmentExpression>(
              multipleAssignmentExpressionSyntax->getSourceLocation());

  for (const auto &assignment :
       multipleAssignmentExpressionSyntax->getAssignmentExprListRef()) {
    boundMultipleAssignmentExpression->addAssignment(
        std::unique_ptr<BoundAssignmentExpression>(
            (BoundAssignmentExpression *)ExpressionBinderFactory::create(
                assignment->getKind())
                ->bindExpression(ctx, assignment.get())
                .release()));
  }

  return std::move(boundMultipleAssignmentExpression);
}