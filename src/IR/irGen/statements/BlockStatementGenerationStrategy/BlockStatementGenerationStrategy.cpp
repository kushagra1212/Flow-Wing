#include "BlockStatementGenerationStrategy.h"

BlockStatementGenerationStrategy::BlockStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *BlockStatementGenerationStrategy::generateStatement(
    BoundStatement *expression) {
  BoundBlockStatement *blockStatement =
      static_cast<BoundBlockStatement *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      blockStatement->getLocation());

  _codeGenerationContext->getNamedValueChain()->addHandler(
      new NamedValueTable());
  _codeGenerationContext->getAllocaChain()->addHandler(
      std::make_unique<AllocaTable>());
  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
  // create and load variable

  llvm::BasicBlock *afterNestedBlock = llvm::BasicBlock::Create(
      *TheContext, "afterNestedBlock", currentBlock->getParent());

  std::vector<llvm::BasicBlock *> nestedBlocks, checkContinueBlocks,
      checkReturnBlocks;
  int statementSize = blockStatement->getStatements().size();
  int indexForStatements = 0;

  while (indexForStatements < statementSize) {
    llvm::BasicBlock *nestedBlock = llvm::BasicBlock::Create(
        *TheContext, "nestedBlock", currentBlock->getParent());
    nestedBlocks.push_back(nestedBlock);

    llvm::BasicBlock *checkContinueBlock = llvm::BasicBlock::Create(
        *TheContext, "checkContinueBlock", currentBlock->getParent());

    checkContinueBlocks.push_back(checkContinueBlock);

    indexForStatements++;
  }

  // Nested Block

  if (blockStatement->getStatements().size() == 0) {
    Builder->CreateBr(afterNestedBlock);
  } else {
    Builder->CreateBr(nestedBlocks[0]);
  }

  for (int i = 0; i < statementSize; i++) {
    // i th nested block

    Builder->SetInsertPoint(nestedBlocks[i]);

    llvm::Value *res =
        _statementGenerationFactory
            ->createStrategy(
                blockStatement->getStatements()[i].get()->getKind())
            ->generateStatement(blockStatement->getStatements()[i].get());

    Builder->CreateCondBr(
        _codeGenerationContext->isCountZero(
            _codeGenerationContext->getPrefixedName(FLOWWING_BREAK_COUNT),
            llvm::Type::getInt32Ty(*TheContext)),
        checkContinueBlocks[i], afterNestedBlock);

    //  i th Check continue Block

    Builder->SetInsertPoint(checkContinueBlocks[i]);

    if (i == blockStatement->getStatements().size() - 1)
      Builder->CreateBr(afterNestedBlock);
    else {
      Builder->CreateCondBr(
          _codeGenerationContext->isCountZero(
              _codeGenerationContext->getPrefixedName(FLOWWING_CONTINUE_COUNT),
              llvm::Type::getInt32Ty(*TheContext)),
          nestedBlocks[i + 1], afterNestedBlock);
    }
  }

  Builder->SetInsertPoint(afterNestedBlock);

  // this->_NamedValuesStack.pop();
  _codeGenerationContext->getNamedValueChain()->removeHandler();
  _codeGenerationContext->getAllocaChain()->removeHandler();
  return nullptr;
}

llvm::Value *BlockStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *expression) {
  return this->generateStatement(expression);
}