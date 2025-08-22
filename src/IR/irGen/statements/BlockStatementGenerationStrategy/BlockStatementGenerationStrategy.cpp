/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

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

  _codeGenerationContext->getAllocaChain()->addHandler(
      std::make_unique<AllocaTable>());

  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
  // create and load variable

  llvm::BasicBlock *afterNestedBlock = llvm::BasicBlock::Create(
      *TheContext, "afterNestedBlock", currentBlock->getParent());

  std::vector<llvm::BasicBlock *> nestedBlocks, checkContinueBlocks,
      checkReturnBlocks;
  size_t statementSize = blockStatement->getStatements().size();
  size_t indexForStatements = 0;

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

  for (size_t i = 0; i < statementSize; i++) {
    // i th nested block

    Builder->SetInsertPoint(nestedBlocks[i]);

    _statementGenerationFactory
        ->createStrategy(blockStatement->getStatements()[i].get()->getKind())
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

  _codeGenerationContext->getAllocaChain()->removeHandler();
  return nullptr;
}

llvm::Value *BlockStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *expression) {
  return this->generateStatement(expression);
}