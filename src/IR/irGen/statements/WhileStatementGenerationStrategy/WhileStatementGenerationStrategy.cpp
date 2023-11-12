#include "WhileStatementGenerationStrategy.h"

#include "../../expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

WhileStatementGenerationStrategy::WhileStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *WhileStatementGenerationStrategy::generateStatement(
    BoundStatement *expression) {
  BoundWhileStatement *whileStatement =
      static_cast<BoundWhileStatement *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      whileStatement->getLocation());

  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
  llvm::Function *function = currentBlock->getParent();
  llvm::Value *exitValue = nullptr;
  llvm::BasicBlock *loopCondition =
      llvm::BasicBlock::Create(*TheContext, "loopCondition", function);
  llvm::BasicBlock *loopBody =
      llvm::BasicBlock::Create(*TheContext, "loopBody", function);
  llvm::BasicBlock *afterLoop =
      llvm::BasicBlock::Create(*TheContext, "afterLoop", function);

  llvm::BasicBlock *breakLoop =
      llvm::BasicBlock::Create(*TheContext, "breakLoop", function);

  Builder->CreateBr(loopCondition);

  // Loop Condition

  Builder->SetInsertPoint(loopCondition);

  _codeGenerationContext->decrementCountIfNotZero(
      _codeGenerationContext->getPrefixedName(FLOWWING_CONTINUE_COUNT));

  BoundExpression *condExp = whileStatement->getConditionPtr().get();
  llvm::Value *conditionValue =
      _expressionGenerationFactory->createStrategy(condExp->getKind())
          ->generateExpression(condExp);

  // Load the condition

  if (conditionValue == nullptr) {

    _codeGenerationContext->getLogger()->LogError(
        "Condition value is not found in while statement");

    return nullptr;
  }

  Builder->CreateCondBr(conditionValue, breakLoop, afterLoop);

  Builder->SetInsertPoint(breakLoop);

  Builder->CreateCondBr(
      _codeGenerationContext->isCountZero(
          _codeGenerationContext->getPrefixedName(FLOWWING_BREAK_COUNT),
          llvm::Type::getInt32Ty(*TheContext)),
      loopBody, afterLoop);

  // Loop Body

  Builder->SetInsertPoint(loopBody);
  BoundStatement *loopBodyStat = whileStatement->getBodyPtr().get();
  llvm::Value *result =
      _statementGenerationFactory->createStrategy(loopBodyStat->getKind())
          ->generateStatement(loopBodyStat);

  Builder->CreateBr(loopCondition);

  // After Loop

  Builder->SetInsertPoint(afterLoop);

  _codeGenerationContext->decrementCountIfNotZero(
      _codeGenerationContext->getPrefixedName(FLOWWING_BREAK_COUNT));

  return exitValue;
}

llvm::Value *WhileStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  return this->generateStatement(statement);
}