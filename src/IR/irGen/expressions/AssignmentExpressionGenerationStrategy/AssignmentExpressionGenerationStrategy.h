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


#ifndef __FLOWWING_ASSIGNMENT_EXPRESSION_STRATEGY_H__
#define __FLOWWING_ASSIGNMENT_EXPRESSION_STRATEGY_H__

#include "src/SemanticAnalyzer/BoundExpressions/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundBracketedExpression/BoundBracketedExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundIndexExpression/BoundIndexExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundNirastExpression/BoundNirastExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundObjectExpression/BoundObjectExpression.h"
#include "src/IR/context/utils/DynamicValueHandler/DynamicValueHandler.h"
#include "src/IR/irGen/expressions/CallExpressionGenerationStrategy/CallExpressionGenerationStrategy.h"
#include "src/IR/irGen/expressions/ContainerAssignmentExpressionGenerationStrategy/ContainerAssignmentExpressionGenerationStrategy.h"
#include "src/IR/irGen/expressions/ContainerExpressionGenerationStrategy/ContainerExpressionGenerationStrategy.h"
#include "src/IR/irGen/expressions/NirastExpressionGenerationStrategy/NirastExpressionGenerationStrategy.h"
#include "src/IR/irGen/expressions/ObjectAssignmentExpressionGenerationStrategy/ObjectAssignmentExpressionGenerationStrategy.h"

class AssignmentExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  AssignmentExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  void declare(BoundExpression *expression);

  llvm::Value *handleDynamicPrimitiveVariableAssignment(
      llvm::Value *variable, const std::string &variableName,
      llvm::Value *rhsValue, const bool IS_RHS_VALUE_A_DYNAMIC_VALUE);

  llvm::Value *
  handleAssignmentExpression(BoundAssignmentExpression *assignmentExpression);
  llvm::Value *handleRHSExpression(BoundExpression *expression);
  llvm::Value *handleAssignExpression(llvm::Value *lshPtr, llvm::Type *lhsType,
                                      std::string lhsVarName,
                                      BoundExpression *expression);
  llvm::Value *handleAssignmentByVariable(BoundExpression *exp);

  int8_t populateLHS(BoundAssignmentExpression *&assignmentExpression);

  int8_t handleWhenRHSIsPrimitive(BoundExpression *expression);

  llvm::Value *handleAssignmentByBracketedExpression(
      BoundBracketedExpression *bracketedExpression);
  llvm::Value *
  handleAssignmentByObjectExpression(BoundObjectExpression *boundObjExp);

  // Default Initialize
  void initObjectWithDefaultValue(llvm::StructType *type, llvm::Value *alloca,
                                  llvm::IRBuilder<> &Builder);
  void initArrayWithDefaultValue(llvm::ArrayType *arrayType,
                                 llvm::Value *alloca,
                                 llvm::IRBuilder<> &Builder);
  void initDefaultValue(llvm::Type *type, llvm::Value *alloca,
                        llvm::IRBuilder<> &Builder);

private:
  std::string _variableName;
  llvm::Value *_allocaInst = nullptr;
  llvm::GlobalVariable *_previousGlobalVariable = nullptr;
  SyntaxKindUtils::SyntaxKind _variableType;
  std::vector<llvm::Value *> _indices;
  BoundVariableExpression *_variableExpression = nullptr;
  BoundExpression *_rhsExpression = nullptr;

  // Complete Assignment
  std::string _lhsVariableName;
  llvm::Type *_lhsType = nullptr, *_rhsType = nullptr;
  llvm::Value *_lhsPtr = nullptr, *_rhsPtr = nullptr;
  SyntaxKindUtils::SyntaxKind _lhsTypeKind;

  int8_t m_isLHSDynamicValue = 0;
};

#endif // __FLOWWING_ASSIGNMENT_EXPRESSION_STRATEGY_H__
