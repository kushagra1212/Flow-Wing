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



#include "StringBinaryOperationStrategy.h"

StringBinaryOperationStrategy::StringBinaryOperationStrategy(
    CodeGenerationContext *context)
    : BinaryOperationStrategy(context){};

llvm::Value *StringBinaryOperationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BoundBinaryExpression *binaryExpression) {

  return performOperation(lhsValue, rhsValue, binaryExpression->getOperator());
}

llvm::Value *StringBinaryOperationStrategy::createStringComparison(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    const std::string functionName, std::string operand) {

  llvm::Function *stringComparison = TheModule->getFunction(functionName);

  if (!stringComparison) {

    this->_codeGenerationContext->getLogger()->LogError(
        "Function " + functionName + " not found");

    return nullptr;
  }

  llvm::GlobalVariable *globalTrueStr = TheModule->getGlobalVariable(
      this->_codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_TRUE));

  if (!globalTrueStr) {

    this->_codeGenerationContext->getLogger()->LogError(
        this->_codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_TRUE) +
        " variable not found");

    return nullptr;
  }

  llvm::GlobalVariable *globalFalseStr = TheModule->getGlobalVariable(
      this->_codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_FALSE));

  if (!globalFalseStr) {

    this->_codeGenerationContext->getLogger()->LogError(
        this->_codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_FALSE) +
        " variable not found");

    return nullptr;
  }

  llvm::Value *args[] = {lhsValue, rhsValue};
  llvm::CallInst *stringsCall = Builder->CreateCall(stringComparison, args);
  llvm::Value *resultStr =
      operand == "!=" ? Builder->CreateSelect(stringsCall, Builder->getFalse(),
                                              Builder->getTrue())
                      : Builder->CreateSelect(stringsCall, Builder->getTrue(),
                                              Builder->getFalse());

  return resultStr;
}

llvm::Value *
StringBinaryOperationStrategy::concatenateStrings(llvm::Value *lhs,
                                                  llvm::Value *rhs) {

  llvm::Function *stringConcatenateFunc =
      TheModule->getFunction(INNERS::FUNCTIONS::CONCAT_STRINGS);

  if (!stringConcatenateFunc) {
    // Function not found, handle error
    return nullptr;
  } else {

    llvm::Value *args[] = {_stringTypeConverter->convertExplicit(lhs),
                           _stringTypeConverter->convertExplicit(rhs)};

    llvm::Value *res = Builder->CreateCall(stringConcatenateFunc, args);
    return res;
  }
}

llvm::Value *StringBinaryOperationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BinderKindUtils::BoundBinaryOperatorKind binaryOperator) {

  if (!OperationSupport::isSupported(OperationSupport::StringStrategyTag{},
                                     binaryOperator)) {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported binary operator " +
        BinderKindUtils::to_string(binaryOperator) + " for string type");
    return nullptr;
  }

  switch (binaryOperator) {

  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    return concatenateStrings(lhsValue, rhsValue);

  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return createStringComparison(lhsValue, rhsValue,
                                  INNERS::FUNCTIONS::EQUAL_STRINGS);

  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return createStringComparison(lhsValue, rhsValue,
                                  INNERS::FUNCTIONS::EQUAL_STRINGS, "!=");

  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    return createStringComparison(lhsValue, rhsValue,
                                  INNERS::FUNCTIONS::LESS_THAN_STRINGS);

  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
    return createStringComparison(
        lhsValue, rhsValue, INNERS::FUNCTIONS::LESS_THAN_OR_EQUAL_STRINGS);

  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    return createStringComparison(lhsValue, rhsValue,
                                  INNERS::FUNCTIONS::GREATER_THAN_STRINGS);

  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    return createStringComparison(
        lhsValue, rhsValue, INNERS::FUNCTIONS::GREATER_THAN_OR_EQUAL_STRINGS);

  default: {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported binary operator " +
        BinderKindUtils::to_string(binaryOperator) + " for string type");
    break;
  }
  }

  return nullptr;
}