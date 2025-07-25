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


#ifndef __FLOWWING__BRACKETED_EXPRESSION_GENERATION_STRATEGY_H__
#define __FLOWWING__BRACKETED_EXPRESSION_GENERATION_STRATEGY_H__

#include "../../../../SemanticAnalyzer/BoundExpressions/BoundBracketedExpression/BoundBracketedExpression.h"
#include "../../../../SemanticAnalyzer/BoundExpressions/BoundContainerExpression/BoundContainerExpression.h"
#include "../../../../SemanticAnalyzer/BoundExpressions/BoundFillExpression/BoundFillExpression.h"
#include "../ContainerExpressionGenerationStrategy/ContainerExpressionGenerationStrategy.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"
#include "../FillExpressionGenerationStrategy/FillExpressionGenerationStrategy.h"

class BracketedExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  BracketedExpressionGenerationStrategy(CodeGenerationContext *context);

  void setPreviousGlobalVariable(llvm::GlobalVariable *previousGlobalVariable);
  void setAllocatedVariable(llvm::AllocaInst *allocaInst);
  void setContainerName(const std::string &containerName);

  llvm::Value *
  assignBracketExpression(BoundBracketedExpression *&bracketedExpression,
                          llvm::Value *&lhsPtr, llvm::ArrayType *lhsType,
                          std::string &containerName);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  // Specialized for BoundBracketedExpression

private:
  llvm::GlobalVariable *_previousGlobalVariable = nullptr;
  std::string _containerName;
  llvm::AllocaInst *_allocaInst = nullptr;
};

#endif // __FLOWWING__BRACKETED_EXPRESSION_GENERATION_STRATEGY_H__
