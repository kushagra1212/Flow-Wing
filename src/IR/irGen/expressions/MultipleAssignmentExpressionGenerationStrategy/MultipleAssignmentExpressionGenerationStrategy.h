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


#ifndef __FLOWWING_MULTIPLE_ASSIGNMENT_EXPRESSION_GENERATION_STRATEGY_H__
#define __FLOWWING_MULTIPLE_ASSIGNMENT_EXPRESSION_GENERATION_STRATEGY_H__

#include "src/SemanticAnalyzer/BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundMultipleAssignmentExpression/BoundMultipleAssignmentExpression.h"
#include "src/SemanticAnalyzer/BoundUtils.h"
#include "src/IR/irGen/expressions/AssignmentExpressionGenerationStrategy/AssignmentExpressionGenerationStrategy.h"
class MultipleAssignmentExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  MultipleAssignmentExpressionGenerationStrategy(
      CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  void declare(BoundExpression *expression);

  void handleMultipleVarAssignCallExprGen(
      BoundMultipleAssignmentExpression *boundMultipleAssignmentExpression);

  bool hasSingleCallExpr(
      BoundMultipleAssignmentExpression *boundMultipleAssignmentExpression);
};

#endif