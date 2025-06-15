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
      llvm::BasicBlock::Create(*TheContext, "while:conditon", function);
  llvm::BasicBlock *loopBody =
      llvm::BasicBlock::Create(*TheContext, "while:body", function);
  llvm::BasicBlock *endLoop =
      llvm::BasicBlock::Create(*TheContext, "while.end", function);

  Builder->CreateBr(loopCondition);

  // Loop Condition

  Builder->SetInsertPoint(loopCondition);

  _codeGenerationContext->decrementCountIfNotZero(
      _codeGenerationContext->getPrefixedName(FLOWWING_CONTINUE_COUNT));

  llvm::Value *conditionValue =
      _expressionGenerationFactory
          ->createStrategy(whileStatement->getConditionPtr().get()->getKind())
          ->generateExpression(whileStatement->getConditionPtr().get());
  if (_codeGenerationContext->getValueStackHandler()->isPrimaryType()) {
    conditionValue = Builder->CreateLoad(
        _codeGenerationContext->getValueStackHandler()->getLLVMType(),
        _codeGenerationContext->getValueStackHandler()->getValue());
  } else if (_codeGenerationContext->getValueStackHandler()
                 ->isDynamicValueType()) {
    auto [valueStorage, typeTag] =
        DYNAMIC_VALUE_HANDLER::getDynamicStoredValueAndType(
            conditionValue, _codeGenerationContext, Builder);

    conditionValue = DYNAMIC_VALUE_HANDLER::VALUE_CASTER::castToType(
        valueStorage, DYNAMIC_VALUE::TYPE::VALUE_TYPE::BOOLEAN,
        _codeGenerationContext, Builder);
  }

  _codeGenerationContext->getValueStackHandler()->popAll();
  // Load the condition

  if (conditionValue == nullptr) {
    _codeGenerationContext->getLogger()->LogError(
        "Condition value is not found in while statement");

    return nullptr;
  }

  Builder->CreateCondBr(conditionValue, loopBody, endLoop);

  // Loop Body

  Builder->SetInsertPoint(loopBody);
  llvm::Value *result =
      _statementGenerationFactory
          ->createStrategy(whileStatement->getBodyPtr().get()->getKind())
          ->generateStatement(whileStatement->getBodyPtr().get());
  if (_codeGenerationContext->getValueStackHandler()->isPrimaryType()) {
    result = Builder->CreateLoad(
        _codeGenerationContext->getValueStackHandler()->getLLVMType(),
        _codeGenerationContext->getValueStackHandler()->getValue());
    _codeGenerationContext->getValueStackHandler()->popAll();
  }
  Builder->CreateCondBr(
      _codeGenerationContext->isCountZero(
          _codeGenerationContext->getPrefixedName(FLOWWING_BREAK_COUNT),
          llvm::Type::getInt32Ty(*TheContext)),
      loopCondition, endLoop);

  // After Loop

  Builder->SetInsertPoint(endLoop);

  _codeGenerationContext->decrementCountIfNotZero(
      _codeGenerationContext->getPrefixedName(FLOWWING_BREAK_COUNT));

  return exitValue;
}

llvm::Value *WhileStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  return this->generateStatement(statement);
}