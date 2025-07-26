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


#ifndef __FLOWWING_VARIABLE_EXPRESSION_STRATEGY_H__
#define __FLOWWING_VARIABLE_EXPRESSION_STRATEGY_H__

#include "src/SemanticAnalyzer/BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundTypeExpression/BoundObjectTypeExpression/BoundObjectTypeExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundVariableExpression/BoundVariableExpression.h"
#include "src/IR/irGen/expressions/CallExpressionGenerationStrategy/CallExpressionGenerationStrategy.h"
#include "src/IR/irGen/expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"
#include "src/IR/irGen/expressions/IndexExpressionGenerationStrategy/IndexExpressionGenerationStrategy.h"

class VariableExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  VariableExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  llvm::Value *getVariableValue(const std::string &variableName);

  llvm::Value *getGlobalVariableValue(const std::string &variableName,
                                      llvm::GlobalVariable *variable);

  // Get Primitive Local Variable Value

  llvm::Value *getUnTypedLocalVariableValue(llvm::Value *variableValue,
                                            llvm::Value *v,
                                            const std::string &variableName);

  llvm::Value *getObjectValueNF(llvm::Value *variableElementPtr,
                                size_t listIndex,
                                const std::string &parPropertyKey,
                                llvm::StructType *type, bool itsClass = false);

  llvm::Value *handleVariableGet(llvm::StructType *parObjType, bool itsClass,
                                 std::string &dotPropertyName, size_t listIndex,
                                 const std::string &parPropertyName,
                                 bool isNested, llvm::Value *outerElementPtr);

  llvm::Value *handleIndexExpression(size_t listIndex,
                                     llvm::Value *innerElementPtr,
                                     llvm::ArrayType *arrayType);

  std::string getPropertyName(size_t listIndex);

  llvm::Value *getVariable(llvm::Value *v, llvm::Type *variableType,
                           const std::string &variableName, int64_t pos = 0);

  llvm::Value *handleSingleVariable(llvm::Type *&variableType, llvm::Value *v,
                                    const std::string &variableName);

  llvm::Value *getClassPtr(llvm::StructType *parObjType, int64_t pos,
                           llvm::Value *v, int64_t finalPosition);

  llvm::Value *getClassMemberFunctionValue(std::string className,
                                           std::string memberName,
                                           llvm::Value *classPtr);
  llvm::StructType *getStructType();
  inline auto
  setVariableExpression(BoundVariableExpression *variableExpression) {
    _variableExpression = variableExpression;
  }

private:
  BoundVariableExpression *_variableExpression = nullptr;
  BoundTypeExpression *_typeExpression = nullptr;
  llvm::StructType *parObjTypeType = nullptr;
  std::string _variableName;
  bool _isGlobal = false;
};

#endif // __FLOWWING_VARIABLE_EXPRESSION_STRATEGY_H__
