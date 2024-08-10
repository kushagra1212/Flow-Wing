#include "MultipleAssignmentExpressionGenerationStrategy.h"

MultipleAssignmentExpressionGenerationStrategy::
    MultipleAssignmentExpressionGenerationStrategy(
        CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *MultipleAssignmentExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {

  BoundMultipleAssignmentExpression *boundMultipleAssignmentExpression =
      static_cast<BoundMultipleAssignmentExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundMultipleAssignmentExpression->getLocation());
  std::unique_ptr<AssignmentExpressionGenerationStrategy> assignmentStrategy =
      std::make_unique<AssignmentExpressionGenerationStrategy>(
          _codeGenerationContext);

  for (auto &expr : boundMultipleAssignmentExpression->getAssignmentListRef()) {
    assignmentStrategy->generateExpression(expr.get());
  }

  return nullptr;
}
llvm::Value *
MultipleAssignmentExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {

  BoundMultipleAssignmentExpression *boundMultipleAssignmentExpression =
      static_cast<BoundMultipleAssignmentExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundMultipleAssignmentExpression->getLocation());
  std::unique_ptr<AssignmentExpressionGenerationStrategy> assignmentStrategy =
      std::make_unique<AssignmentExpressionGenerationStrategy>(
          _codeGenerationContext);

  for (auto &expr : boundMultipleAssignmentExpression->getAssignmentListRef()) {
    assignmentStrategy->generateGlobalExpression(expr.get());
  }

  return nullptr;
}

void MultipleAssignmentExpressionGenerationStrategy::declare(
    BoundExpression *expression) {

  BoundMultipleAssignmentExpression *boundMultipleAssignmentExpression =
      static_cast<BoundMultipleAssignmentExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundMultipleAssignmentExpression->getLocation());

  std::unique_ptr<AssignmentExpressionGenerationStrategy> assignmentStrategy =
      std::make_unique<AssignmentExpressionGenerationStrategy>(
          _codeGenerationContext);

  for (auto &expr : boundMultipleAssignmentExpression->getAssignmentListRef()) {
    assignmentStrategy->declare(expr.get());
  }
}