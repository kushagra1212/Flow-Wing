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

#include "src/IR/irGen/expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundContainerExpression/BoundContainerExpression.h"

class ContainerExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  ContainerExpressionGenerationStrategy(CodeGenerationContext *context,
                                        std::vector<uint64_t> actualSizes,
                                        llvm::Type *elementType,
                                        const std::string &containerName);

  llvm::Value *generateExpression(BoundExpression *expression) override;

  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  // Specialized for BoundContainerExpression
  llvm::Value *
  createGlobalExpression(llvm::Type *arrayType,
                         llvm::GlobalVariable *_globalVariable,
                         BoundContainerExpression *containerExpression);

  llvm::Value *
  createLocalExpression(llvm::Type *arrayType, llvm::AllocaInst *v,
                        BoundContainerExpression *containerExpression);

  llvm::Value *createExpression(llvm::Type *arrayType, llvm::Value *v,
                                BoundContainerExpression *containerExpression);

  bool canGenerateExpression(BoundContainerExpression *containerExpression);

  llvm::Value *
  createExpressionAtom(llvm::Type *&arrayType, llvm::Value *&v,
                       BoundContainerExpression *containerExpression,
                       std::vector<llvm::Value *> &indices, uint64_t index);

  inline auto setAllocaInst(llvm::Value *allocaInst) {
    _allocaInst = allocaInst;
  }

private:
  uint64_t _totalSize;
  std::vector<uint64_t> _actualSizes;
  llvm::Type *_elementType = nullptr;
  std::string _containerName;
  uint64_t _sizeToFill;
  bool _isGlobal;
  llvm::Value *_allocaInst = nullptr;
};
