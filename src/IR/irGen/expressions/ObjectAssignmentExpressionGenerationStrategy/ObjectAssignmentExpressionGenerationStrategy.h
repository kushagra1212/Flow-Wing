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


#ifndef __FLOWWING_OBJECT_ASSIGNMENT_EXPRESSION_STRATEGY_H__
#define __FLOWWING_OBJECT_ASSIGNMENT_EXPRESSION_STRATEGY_H__

#include "../../../../SemanticAnalyzer/BoundExpressions/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "../../../../SemanticAnalyzer/BoundExpressions/BoundObjectExpression/BoundObjectExpression.h"
#include "../../../../SemanticAnalyzer/BoundExpressions/BoundVariableExpression/BoundVariableExpression.h"
#include "../../statements/CustomTypeStatementGenerationStrategy/CustomTypeStatementGenerationStrategy.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

class ObjectAssignmentExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  ObjectAssignmentExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  llvm::Value *_deprecated_assignObject(llvm::Value *variableElementPtr,
                                        size_t listIndex,
                                        const std::string &parPropertyKey,
                                        bool reachedEnd);

  bool canGenerateAssignmentExpressionAssignment(
      BoundAssignmentExpression *assignmentExpression);

  llvm::Value *copyObject(llvm::StructType *parStructType, llvm::Value *lshPtr,
                          llvm::Value *rhsPtr);

  llvm::Value *assignObject(BoundObjectExpression *parObjectExpression,
                            llvm::Value *variable,
                            llvm::StructType *parStructType,
                            std::string lhsVarName);

private:
  BoundAssignmentExpression *_assignmentExp = nullptr;
  llvm::Value *_lhsVar;
  BoundVariableExpression *_lhsVarExpr = nullptr;
  bool _isGlobal = false;
};

#endif // __FLOWWING_OBJECT_ASSIGNMENT_EXPRESSION_STRATEGY_H__
