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


#ifndef __FLOWWING_CONTAINER_ASSIGNMENT_EXPRESSION_STRATEGY_H__
#define __FLOWWING_CONTAINER_ASSIGNMENT_EXPRESSION_STRATEGY_H__

#include "src/SemanticAnalyzer/BoundExpressions/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundVariableExpression/BoundVariableExpression.h"
#include "src/IR/irGen/expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

class ContainerAssignmentExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  ContainerAssignmentExpressionGenerationStrategy(
      CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  const bool canGenerateExpressionAssignment(BoundExpression *expr);

  void setVariable(llvm::Value *var);
  void setContainerName(const std::string &containerName);

  llvm::Value *createExpression(llvm::ArrayType *&arrayType,
                                llvm::Value *&variable,
                                llvm::Value *&rhsVariable,
                                llvm::ArrayType *&rhsArrayType,
                                llvm::Type *arrayElementType,
                                const std::vector<uint64_t> &lhsSizes,
                                const std::vector<uint64_t> &rhsSizes);

  void assignArray(llvm::ArrayType *&arrayType, llvm::Value *&variable,
                   llvm::Value *&rhsVariable, llvm::ArrayType *&rhsArrayType,
                   llvm::Type *rhsArrayElementType,
                   std::vector<llvm::Value *> &indices,
                   const std::vector<uint64_t> &rhsSizes, uint64_t index);

  llvm::Value *createExpressionForObject(BoundExpression *expression,
                                         llvm::ArrayType *&arrayType,
                                         llvm::Value *&variable,
                                         const std::vector<uint64_t> &sizes,
                                         llvm::Type *&elementType);

  llvm::Value *assignVariable(BoundAssignmentExpression *assignmentExpression);

private:
  // LHS
  std::string _containerName;
  llvm::Value *_variable = nullptr;
  llvm::ArrayType *_arrayType = nullptr;
  llvm::Value *_size = nullptr;

  // RHS
  llvm::Value *_rhsVariable = nullptr;
  llvm::ArrayType *_rhsArrayType = nullptr;
  llvm::Value *_rhsSize = nullptr;

  std::vector<uint64_t> _lhsSizes, _rhsSizes;
  llvm::Type *_rhsArrayElementType = nullptr, *_lhsArrayElementType = nullptr;
};

#endif // __FLOWWING_CONTAINER_ASSIGNMENT_EXPRESSION_STRATEGY_H__
