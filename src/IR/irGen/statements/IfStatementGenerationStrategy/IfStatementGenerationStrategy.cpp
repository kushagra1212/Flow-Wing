#include "IfStatementGenerationStrategy.h"

#include "../../expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

IfStatementGenerationStrategy::IfStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *
IfStatementGenerationStrategy::generateStatement(BoundStatement *statement) {

  BoundIfStatement *ifStatement = static_cast<BoundIfStatement *>(statement);
  llvm::Value *exitValue = nullptr;

  llvm::Value *conditionValue =
      _expressionGenerationFactory
          ->createStrategy(ifStatement->getConditionPtr().get()->getKind())
          ->generateExpression(ifStatement->getConditionPtr().get());

  if (_codeGenerationContext->getValueStackHandler()->isPrimaryType()) {
    conditionValue = Builder->CreateLoad(
        _codeGenerationContext->getValueStackHandler()->getLLVMType(),
        _codeGenerationContext->getValueStackHandler()->getValue());
    _codeGenerationContext->getValueStackHandler()->popAll();
  }

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      ifStatement->getLocation());

  if (conditionValue == nullptr) {

    _codeGenerationContext->getLogger()->LogError(
        "Condition value is not found in if statement");

    return nullptr;
  }

  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();

  llvm::Function *function = currentBlock->getParent();

  llvm::BasicBlock *thenBlock =
      llvm::BasicBlock::Create(*TheContext, "then", function);

  std::vector<llvm::BasicBlock *> orIfBlock;

  for (int i = 0; i < ifStatement->getOrIfStatementsPtr().size(); i++) {
    orIfBlock.push_back(llvm::BasicBlock::Create(
        *TheContext, "orIf" + std::to_string(i), function));
  }

  std::vector<llvm::BasicBlock *> orIfThenBlocks;

  for (int i = 0; i < ifStatement->getOrIfStatementsPtr().size(); i++) {
    orIfThenBlocks.push_back(llvm::BasicBlock::Create(
        *TheContext, "orIfThen" + std::to_string(i), function));
  }

  llvm::BasicBlock *elseBlock =
      llvm::BasicBlock::Create(*TheContext, "else", function);

  llvm::BasicBlock *afterIfElse =
      llvm::BasicBlock::Create(*TheContext, "afterIfElse", function);

  if (ifStatement->getOrIfStatementsPtr().size()) {
    Builder->CreateCondBr(conditionValue, thenBlock, orIfBlock[0]);
  } else {
    Builder->CreateCondBr(conditionValue, thenBlock, elseBlock);
  }

  for (int i = 0; i < orIfBlock.size(); i++) {
    Builder->SetInsertPoint(orIfBlock[i]);

    BoundExpression *conditionExp =
        ifStatement->getOrIfStatementsPtr()[i]->getConditionPtr().get();

    llvm::Value *orIfConditionValue =
        _expressionGenerationFactory->createStrategy(conditionExp->getKind())
            ->generateExpression(conditionExp);

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        ifStatement->getOrIfStatementsPtr()[i]->getLocation());

    if (orIfConditionValue == nullptr) {

      _codeGenerationContext->getLogger()->LogError(
          "Condition value is not found in or if statement");

      return nullptr;
    }

    if (i == orIfBlock.size() - 1) {
      Builder->CreateCondBr(orIfConditionValue, orIfThenBlocks[i], elseBlock);
    } else {
      Builder->CreateCondBr(orIfConditionValue, orIfThenBlocks[i],
                            orIfBlock[i + 1]);
    }
  }

  // Then Block

  Builder->SetInsertPoint(thenBlock);

  BoundStatement *thenStat = ifStatement->getThenStatementPtr().get();
  llvm::Value *thenValue =
      _statementGenerationFactory->createStrategy(thenStat->getKind())
          ->generateStatement(thenStat);

  if (_codeGenerationContext->getValueStackHandler()->isPrimaryType()) {
    thenValue = Builder->CreateLoad(
        _codeGenerationContext->getValueStackHandler()->getLLVMType(),
        _codeGenerationContext->getValueStackHandler()->getValue());
    _codeGenerationContext->getValueStackHandler()->popAll();
  }

  Builder->CreateBr(afterIfElse);

  // Or If Then Block

  for (int i = 0; i < orIfThenBlocks.size(); i++) {
    Builder->SetInsertPoint(orIfThenBlocks[i]);

    BoundStatement *ofIfThenStat =
        ifStatement->getOrIfStatementsPtr()[i]->getThenStatementPtr().get();
    llvm::Value *orIfThenValue =
        _statementGenerationFactory->createStrategy(ofIfThenStat->getKind())
            ->generateStatement(ofIfThenStat);

    Builder->CreateBr(afterIfElse);
  }

  // Else Block

  Builder->SetInsertPoint(elseBlock);
  BoundStatement *elseStat = ifStatement->getElseStatementPtr().get();

  if (elseStat) {
    llvm::Value *elseValue =
        _statementGenerationFactory->createStrategy(elseStat->getKind())
            ->generateStatement(elseStat);

    if (_codeGenerationContext->getValueStackHandler()->isPrimaryType()) {
      elseValue = Builder->CreateLoad(
          _codeGenerationContext->getValueStackHandler()->getLLVMType(),
          _codeGenerationContext->getValueStackHandler()->getValue());
      _codeGenerationContext->getValueStackHandler()->popAll();
    }
  }

  Builder->CreateBr(afterIfElse);

  Builder->SetInsertPoint(afterIfElse);

  return exitValue;
}

llvm::Value *IfStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  return this->generateStatement(statement);
}