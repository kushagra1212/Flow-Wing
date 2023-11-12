#include "ContinueStatementGenerationStrategy.h"

ContinueStatementGenerationStrategy::ContinueStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *ContinueStatementGenerationStrategy::generateStatement(
    BoundStatement *expression) {
  BoundContinueStatement *boundContinueStatement =
      static_cast<BoundContinueStatement *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundContinueStatement->getLocation());

  _codeGenerationContext->incrementCount(
      _codeGenerationContext->getPrefixedName(FLOWWING_CONTINUE_COUNT));

  return nullptr;
}

llvm::Value *ContinueStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *expression) {
  BoundContinueStatement *boundContinueStatement =
      static_cast<BoundContinueStatement *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundContinueStatement->getLocation());

  _codeGenerationContext->getLogger()->LogError(
      "Continue statement cannot be used outside of a loop");

  return nullptr;
}