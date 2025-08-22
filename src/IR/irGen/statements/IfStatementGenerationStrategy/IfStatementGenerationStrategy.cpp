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

#include "IfStatementGenerationStrategy.h"

#include "src/IR/irGen/expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

IfStatementGenerationStrategy::IfStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *
IfStatementGenerationStrategy::generateStatement(BoundStatement *statement) {

  BoundIfStatement *ifStatement = static_cast<BoundIfStatement *>(statement);
  llvm::Value *exitValue = nullptr;

  _codeGenerationContext->getValueStackHandler()->popAll();

  llvm::Value *conditionValue =
      _expressionGenerationFactory
          ->createStrategy(ifStatement->getConditionPtr().get()->getKind())
          ->generateExpression(ifStatement->getConditionPtr().get());

  if (_codeGenerationContext->getValueStackHandler()->isDynamicValueType()) {

    auto [valueStorage, typeTag] =
        DYNAMIC_VALUE_HANDLER::getDynamicStoredValueAndType(
            conditionValue, _codeGenerationContext, Builder);

    conditionValue = DYNAMIC_VALUE_HANDLER::VALUE_CASTER::toBoolean(
        valueStorage, _codeGenerationContext, Builder);

  } else if (_codeGenerationContext->getValueStackHandler()->isStructType()) {
    if (!_codeGenerationContext->isValidClassType(llvm::cast<llvm::StructType>(
            _codeGenerationContext->getValueStackHandler()->getLLVMType()))) {
      _codeGenerationContext->getLogger()->LogError(
          "Using Objects in If Statement is not allowed");
      return nullptr;
    }

    conditionValue = Builder->CreateIsNotNull(Builder->CreateLoad(
        llvm::Type::getInt8PtrTy(*TheContext), conditionValue));
  } else if (_codeGenerationContext->getValueStackHandler()->isPrimaryType()) {
    conditionValue = Builder->CreateLoad(
        _codeGenerationContext->getValueStackHandler()->getLLVMType(),
        _codeGenerationContext->getValueStackHandler()->getValue());
  }
  _codeGenerationContext->getValueStackHandler()->popAll();

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

  for (size_t i = 0; i < ifStatement->getOrIfStatementsPtr().size(); i++) {
    orIfBlock.push_back(llvm::BasicBlock::Create(
        *TheContext, "orIf" + std::to_string(i), function));
  }

  std::vector<llvm::BasicBlock *> orIfThenBlocks;

  for (size_t i = 0; i < ifStatement->getOrIfStatementsPtr().size(); i++) {
    orIfThenBlocks.push_back(llvm::BasicBlock::Create(
        *TheContext, "orIfThen" + std::to_string(i), function));
  }

  llvm::BasicBlock *elseBlock =
      llvm::BasicBlock::Create(*TheContext, "else", function);

  llvm::BasicBlock *afterIfElse =
      llvm::BasicBlock::Create(*TheContext, "afterIfElse", function);

  if (ifStatement->getOrIfStatementsPtr().size()) {
    Builder->CreateCondBr(_boolTypeConverter->convertExplicit(conditionValue),
                          thenBlock, orIfBlock[0]);
  } else {
    Builder->CreateCondBr(_boolTypeConverter->convertExplicit(conditionValue),
                          thenBlock, elseBlock);
  }

  for (size_t i = 0; i < orIfBlock.size(); i++) {
    Builder->SetInsertPoint(orIfBlock[i]);

    BoundExpression *conditionExp =
        ifStatement->getOrIfStatementsPtr()[i]->getConditionPtr().get();

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        ifStatement->getOrIfStatementsPtr()[i]->getLocation());

    _codeGenerationContext->getValueStackHandler()->popAll();

    llvm::Value *orIfConditionValue =
        _expressionGenerationFactory->createStrategy(conditionExp->getKind())
            ->generateExpression(conditionExp);
    if (_codeGenerationContext->getValueStackHandler()->isDynamicValueType()) {

      auto [valueStorage, typeTag] =
          DYNAMIC_VALUE_HANDLER::getDynamicStoredValueAndType(
              orIfConditionValue, _codeGenerationContext, Builder);

      orIfConditionValue = DYNAMIC_VALUE_HANDLER::VALUE_CASTER::toBoolean(
          valueStorage, _codeGenerationContext, Builder);
    } else if (_codeGenerationContext->getValueStackHandler()->isStructType()) {
      if (!_codeGenerationContext->isValidClassType(
              llvm::cast<llvm::StructType>(
                  _codeGenerationContext->getValueStackHandler()
                      ->getLLVMType()))) {
        _codeGenerationContext->getLogger()->LogError(
            "Using Objects in Or If Statement is not allowed");
        return nullptr;
      }
      orIfConditionValue = Builder->CreateIsNotNull(Builder->CreateLoad(
          llvm::Type::getInt8PtrTy(*TheContext), orIfConditionValue));
    } else if (_codeGenerationContext->getValueStackHandler()
                   ->isPrimaryType()) {
      orIfConditionValue = Builder->CreateLoad(
          _codeGenerationContext->getValueStackHandler()->getLLVMType(),
          _codeGenerationContext->getValueStackHandler()->getValue());
    }

    _codeGenerationContext->getValueStackHandler()->popAll();
    if (orIfConditionValue == nullptr) {

      _codeGenerationContext->getLogger()->LogError(
          "Condition value is not found in or if statement");

      return nullptr;
    }

    if (i == orIfBlock.size() - 1) {
      Builder->CreateCondBr(
          _boolTypeConverter->convertExplicit(orIfConditionValue),
          orIfThenBlocks[i], elseBlock);
    } else {
      Builder->CreateCondBr(
          _boolTypeConverter->convertExplicit(orIfConditionValue),
          orIfThenBlocks[i], orIfBlock[i + 1]);
    }
  }

  // Then Block

  Builder->SetInsertPoint(thenBlock);

  BoundStatement *thenStat = ifStatement->getThenStatementPtr().get();

  _statementGenerationFactory->createStrategy(thenStat->getKind())
      ->generateStatement(thenStat);

  _codeGenerationContext->getValueStackHandler()->popAll();

  Builder->CreateBr(afterIfElse);

  // Or If Then Block

  for (size_t i = 0; i < orIfThenBlocks.size(); i++) {
    Builder->SetInsertPoint(orIfThenBlocks[i]);

    BoundStatement *ofIfThenStat =
        ifStatement->getOrIfStatementsPtr()[i]->getThenStatementPtr().get();

    _statementGenerationFactory->createStrategy(ofIfThenStat->getKind())
        ->generateStatement(ofIfThenStat);
    _codeGenerationContext->getValueStackHandler()->popAll();

    Builder->CreateBr(afterIfElse);
  }

  // Else Block

  Builder->SetInsertPoint(elseBlock);
  BoundStatement *elseStat = ifStatement->getElseStatementPtr().get();

  if (elseStat) {
    _statementGenerationFactory->createStrategy(elseStat->getKind())
        ->generateStatement(elseStat);

    _codeGenerationContext->getValueStackHandler()->popAll();
  }

  Builder->CreateBr(afterIfElse);

  Builder->SetInsertPoint(afterIfElse);

  return exitValue;
}

llvm::Value *IfStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  return this->generateStatement(statement);
}