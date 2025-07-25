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


#ifndef __FLOWWING_OBJECT_EXPRESSION_STRATEGY_H__
#define __FLOWWING_OBJECT_EXPRESSION_STRATEGY_H__

#include "../../../../SemanticAnalyzer/BoundExpressions/BoundObjectExpression/BoundObjectExpression.h"
#include "../../../../SemanticAnalyzer/BoundExpressions/BoundTypeExpression/BoundObjectTypeExpression/BoundObjectTypeExpression.h"
#include "../../statements/ContainerDeclarationStatementGenerationStrategy/ContainerDeclarationStatementGenerationStrategy.h"
#include "../ContainerAssignmentExpressionGenerationStrategy/ContainerAssignmentExpressionGenerationStrategy.h"
#include "../ContainerExpressionGenerationStrategy/ContainerExpressionGenerationStrategy.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"
#include "../FillExpressionGenerationStrategy/FillExpressionGenerationStrategy.h"
#include "../LiteralExpressionGenerationStrategy/LiteralExpressionGenerationStrategy.h"
#include "../ObjectAssignmentExpressionGenerationStrategy/ObjectAssignmentExpressionGenerationStrategy.h"

class ObjectExpressionGenerationStrategy : public ExpressionGenerationStrategy {
public:
  ObjectExpressionGenerationStrategy(CodeGenerationContext *context);
  llvm::Value *generateExpression(BoundExpression *expression) override;

  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;
  llvm::Value *generateCallExp(BoundExpression *expression);
  llvm::Value *generateVariableExp(BoundExpression *expression);
  // llvm::Value *createExpression(BoundExpression *expression,
  //                               llvm::Value *variable,
  //                               const std::string &typeName);

  llvm::Value *createExpressionNP(BoundExpression *expression,
                                  llvm::Value *variable,
                                  const std::string &typeName);

  llvm::Value *generateVariable(llvm::Value *variable,
                                const std::string &typeName,
                                llvm::Value *fromVar, const bool isGlobal);

  // llvm::Value *generateVariableAccessThroughPtr(llvm::Value *variable,
  //                                               const std::string &typeName,
  //                                               llvm::Value *fromVar);

  llvm::Value *createExpressionNPDefault(llvm::Value *variable,
                                         const std::string &typeName);

  void handleCreateDef(BoundLiteralExpression<std::any> *bLitExpr,
                       llvm::StructType *parStructType, llvm::Value *variable,
                       uint64_t indexValue, BoundTypeExpression *bExpr);

  inline auto setVariable(llvm::Value *variable) { _variable = variable; }

  inline auto setTypeName(std::string typeName) { _typeName = typeName; }
  llvm::AllocaInst *findAllocaInstFromPtr(llvm::Value *ptr);

private:
  llvm::Value *_variable = nullptr;
  std::string _typeName;
  bool _variableIsGlobal = false;
};

#endif // __FLOWWING_OBJECT_EXPRESSION_STRATEGY_H__