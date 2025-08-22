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


#pragma once

#include "src/SemanticAnalyzer/BoundExpressions/BoundFillExpression/BoundFillExpression.h"
#include "src/IR/irGen/expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

class FillExpressionGenerationStrategy : public ExpressionGenerationStrategy {
public:
  FillExpressionGenerationStrategy(CodeGenerationContext *context,
                                   std::vector<uint64_t> actualSizes,
                                   llvm::Type *elementType,
                                   const std::string &containerName);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  llvm::Value *createGlobalExpression(llvm::Type *arrayType,
                                      llvm::GlobalVariable *_globalVariable);

  llvm::Value *createLocalExpression(llvm::Type *arrayType,
                                     llvm::AllocaInst *arrayAlloca);

  llvm::Value *createExpression(llvm::Type *arrayType, llvm::Value *v,
                                llvm::Value *elementToFill,
                                uint64_t sizeToFillVal);

  bool canGenerateExpression(BoundExpression *expression);
  llvm::Value *createExpressionAtom(llvm::Type *arrayType, llvm::Value *v,
                                    llvm::Value *elementToFill,
                                    uint64_t &sizeToFillVal,
                                    std::vector<llvm::Value *> &indices,
                                    uint64_t index);

  llvm::Value *createExpressionLoop(llvm::Type *arrayType, llvm::Value *v,
                                    llvm::Value *elementToFill,
                                    uint64_t &sizeToFillVal);

  llvm::Value *createExpressionLoopWithTotalSize(llvm::Type *arrayType,
                                                 llvm::Value *v,
                                                 llvm::Value *elementToFill);

  llvm::Value *createExpressionLoopWrapper(llvm::Type *arrayType,
                                           llvm::Value *val);

  inline auto setAllocaInst(llvm::Value *allocaInst) {
    _allocaInst = allocaInst;
  }

private:
  std::vector<uint64_t> _actualSizes;

  uint64_t _totalSize;

  llvm::Type *_elementType;
  std::string _containerName;

  //  Variables for the fill expression

  llvm::Value *_elementToFill;
  uint64_t _sizeToFillInt;
  llvm::Value *_allocaInst;
  BoundExpression *_objectExpression = nullptr;
  BoundExpression *_variableExpression = nullptr;
  bool _isGlobal = false;
  llvm::Type *_elementToFillType;
  BoundFillExpression *_fillExpression = nullptr;
  int8_t _isElementToFillDynamicValue = 0;
};
