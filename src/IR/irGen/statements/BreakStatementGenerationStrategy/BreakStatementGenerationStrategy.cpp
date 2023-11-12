#include "BreakStatementGenerationStrategy.h"

BreakStatementGenerationStrategy::BreakStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *BreakStatementGenerationStrategy::generateStatement(
    BoundStatement *expression) {

  BoundBreakStatement *boundBreakStatement =
      static_cast<BoundBreakStatement *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundBreakStatement->getLocation());

  _codeGenerationContext->incrementCount(
      _codeGenerationContext->getPrefixedName(FLOWWING_BREAK_COUNT));

  return nullptr;
}

llvm::Value *BreakStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *expression) {

  BoundBreakStatement *boundBreakStatement =
      static_cast<BoundBreakStatement *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundBreakStatement->getLocation());

  _codeGenerationContext->getLogger()->LogError(
      "Break statement cannot be used outside of a loop");

  return nullptr;
}