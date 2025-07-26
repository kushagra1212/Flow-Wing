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


#ifndef __FLOWWING_INDEX_EXPRESSION_STRATEGY_H__
#define __FLOWWING_INDEX_EXPRESSION_STRATEGY_H__

#include "src/IR/context/utils/DynamicValueHandler/DynamicValueHandler.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundIndexExpression/BoundIndexExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundVariableExpression/BoundVariableExpression.h"
#include "src/IR/irGen/expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

class IndexExpressionGenerationStrategy : public ExpressionGenerationStrategy {
public:
  IndexExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  llvm::Value *handleGlobalVariable(llvm::GlobalVariable *variable,
                                    std::string variableName);

  llvm::Value *handleStringIndexing();

  llvm::Value *handleArrayTypeIndexing();

  void verifyBounds(llvm::Value *index, llvm::ConstantInt *actualSize);

  const bool canGenerateExpression(const std::string &variableName);

  inline auto setIndexExpression(BoundIndexExpression *indexExpression) {
    _indexExpression = indexExpression;
  }
  int8_t populateIndices();
  int8_t populateVariableName();
  inline auto setArrayType(llvm::Type *arrayType) -> void {
    _arrayType = llvm::cast<llvm::ArrayType>(arrayType);
  }
  inline auto populateArraySize() -> void {
    _arrayElementType = _arrayType;
    std::vector<uint64_t> sizes;
    _codeGenerationContext->createArraySizesAndArrayElementType(
        sizes, _arrayElementType);
    for (int i = 0; i < sizes.size(); i++) {
      _actualSizes.push_back(Builder->getInt32(sizes[i]));
    }
  }

  inline auto setVariable(llvm::Value *variable) { _variable = variable; }

private:
  std::vector<llvm::Value *> _indices;
  std::vector<llvm::ConstantInt *> _actualSizes;
  std::string _variableName;
  llvm::Type *_arrayElementType = nullptr;
  llvm::Value *_variable = nullptr;
  llvm::ArrayType *_arrayType = nullptr;
  BoundIndexExpression *_indexExpression = nullptr;
};

#endif // __FLOWWING_INDEX_EXPRESSION_STRATEGY_H__
