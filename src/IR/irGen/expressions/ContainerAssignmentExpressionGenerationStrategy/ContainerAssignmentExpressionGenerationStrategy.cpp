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

#include "ContainerAssignmentExpressionGenerationStrategy.h"

ContainerAssignmentExpressionGenerationStrategy::
    ContainerAssignmentExpressionGenerationStrategy(
        CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

void ContainerAssignmentExpressionGenerationStrategy::setVariable(
    llvm::Value *var) {
  _variable = var;
}

void ContainerAssignmentExpressionGenerationStrategy::setContainerName(
    const std::string &containerName) {
  _containerName = containerName;
}

bool ContainerAssignmentExpressionGenerationStrategy::
    canGenerateExpressionAssignment(BoundExpression *expr) {
  if (!_arrayType) {
    _codeGenerationContext->getLogger()->LogError(
        "Variable " + _containerName + " not found in assignment expression ");
    return false;
  }

  if (_arrayType->getElementType()->isIntegerTy(8)) {
    _codeGenerationContext->getLogger()->LogError(
        "Variable " + _containerName + " not found in assignment expression ");
    return false;
  }

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      expr->getLocation());

  _rhsVariable = _expressionGenerationFactory->createStrategy(expr->getKind())
                     ->generateExpression(expr);
  _codeGenerationContext->getValueStackHandler()->popAll();
  _rhsArrayType = nullptr;

  bool hasError = false;

  if (llvm::isa<llvm::AllocaInst>(_rhsVariable)) {
    llvm::AllocaInst *allocaInst = llvm::cast<llvm::AllocaInst>(_rhsVariable);

    if (llvm::isa<llvm::ArrayType>(allocaInst->getAllocatedType())) {
      _rhsArrayType =
          llvm::cast<llvm::ArrayType>(allocaInst->getAllocatedType());
    }

  } else if (llvm::isa<llvm::GlobalVariable>(_rhsVariable)) {
    llvm::GlobalVariable *rhsGlobalVariable =
        llvm::cast<llvm::GlobalVariable>(_rhsVariable);

    if (llvm::isa<llvm::ArrayType>(rhsGlobalVariable->getValueType())) {
      _rhsArrayType =
          llvm::cast<llvm::ArrayType>(rhsGlobalVariable->getValueType());
    }

  } else if (llvm::isa<llvm::CallInst>(_rhsVariable)) {
    llvm::CallInst *calledInst = llvm::cast<llvm::CallInst>(_rhsVariable);
    auto *calledFunction = calledInst->getCalledFunction();
    _codeGenerationContext->getRetrunedArrayType(
        calledFunction, _rhsArrayType, _rhsArrayElementType, _rhsSizes);

    if (_rhsArrayType == nullptr) {
      hasError = true;
    }

    if (hasError) {
      _codeGenerationContext->getLogger()->LogError(
          "Function Call " + calledFunction->getName().str() +
          " is not returning an array in assignment expression ");
      return false;
    }
  } else {
    hasError = true;
  }

  if (!_rhsArrayType) {
    hasError = true;
  }

  if (_lhsSizes.size() == 0)
    _codeGenerationContext->getArraySizeMetadata(_variable, _lhsSizes);

  if (!_lhsArrayElementType)
    _lhsArrayElementType =
        _codeGenerationContext->getArrayElementTypeMetadata(_variable);

  if (_rhsSizes.size() == 0) {
    _codeGenerationContext->getArraySizeMetadata(_rhsVariable, _rhsSizes);

    _rhsArrayElementType =
        _codeGenerationContext->getArrayElementTypeMetadata(_rhsVariable);
  }

  if (_rhsArrayType->getElementType()->isIntegerTy(8)) {
    hasError = true;
  }
  if (hasError) {
    _codeGenerationContext->getLogger()->LogError(
        "Variable " + _containerName + " not found in assignment expression ");
    return false;
  }

  if (_rhsArrayElementType != _lhsArrayElementType) {
    _codeGenerationContext->getLogger()->LogError(
        "Element type mismatch in assignment expression in " + _containerName +
        " Expected " + _lhsArrayElementType->getStructName().str() +
        " but got " + _rhsArrayElementType->getStructName().str());

    return false;
  }

  if (_lhsSizes.size() != _rhsSizes.size()) {
    _codeGenerationContext->getLogger()->LogError(
        "Dimension mismatch in assignment expression in " + _containerName +
        " Expected " + std::to_string(_lhsSizes.size()) + " but got " +
        std::to_string(_rhsSizes.size()));

    return false;
  }

  for (size_t i = 0; i < _lhsSizes.size(); i++) {
    if (_rhsSizes[i] > _lhsSizes[i]) {
      _codeGenerationContext->getLogger()->LogError(
          "You can't assign an array of size " + std::to_string(_rhsSizes[i]) +
          " to an array of size " + std::to_string(_lhsSizes[i]));
      return false;
    }
  }

  return true;
}

llvm::Value *ContainerAssignmentExpressionGenerationStrategy::assignVariable(
    BoundAssignmentExpression *assignmentExpression) {
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      assignmentExpression->getLocation());
  _expressionGenerationFactory
      ->createStrategy(assignmentExpression->getLeftPtr().get()->getKind())
      ->generateExpression(assignmentExpression->getLeftPtr().get());
  llvm::Value *lhsPtr =
      _codeGenerationContext->getValueStackHandler()->getValue();
  llvm::Type *lhsType =
      _codeGenerationContext->getValueStackHandler()->getLLVMType();
  if (_codeGenerationContext->getValueStackHandler()->isLLVMConstant()) {
    _codeGenerationContext->getLogger()->LogError(
        "Assignment to constant  is not supported");
    return nullptr;
  }
  llvm::Value *lhsValue = Builder->CreateLoad(lhsType, lhsPtr);
  _codeGenerationContext->getValueStackHandler()->popAll();

  _expressionGenerationFactory
      ->createStrategy(assignmentExpression->getRightPtr().get()->getKind())
      ->generateExpression(assignmentExpression->getRightPtr().get());

  llvm::Value *rhsPtr =
      _codeGenerationContext->getValueStackHandler()->getValue();
  llvm::Type *rhsType =
      _codeGenerationContext->getValueStackHandler()->getLLVMType();
  llvm::Value *rhsValue = nullptr;

  if (_codeGenerationContext->getValueStackHandler()->isLLVMConstant()) {
    rhsValue = _codeGenerationContext->getValueStackHandler()->getValue();
  } else {
    rhsValue = Builder->CreateLoad(rhsType, rhsPtr);
  }

  _codeGenerationContext->getValueStackHandler()->popAll();

  if (!rhsValue) {
    _codeGenerationContext->getLogger()->LogError(
        "Right hand side value not found in assignment expression ");
    return nullptr;
  }

  if (!lhsValue) {
    _codeGenerationContext->getLogger()->LogError(
        "Left hand side value not found in assignment expression ");
    return nullptr;
  }

  if (llvm::isa<llvm::ArrayType>(lhsType) &&
      llvm::isa<llvm::ArrayType>(rhsType)) {

    if (_codeGenerationContext->verifyArrayType(
            llvm::cast<llvm::ArrayType>(lhsType),
            llvm::cast<llvm::ArrayType>(rhsType)) == EXIT_FAILURE)
      return nullptr;
  } else {

    if (lhsType != rhsType) {
      _codeGenerationContext->getLogger()->LogError(
          "Type mismatch in assignment expression, expected " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(lhsType) +
          " but found " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(rhsType) + " ");
      return nullptr;
    }
  }
  Builder->CreateStore(rhsValue, lhsPtr);

  return rhsValue;
}

llvm::Value *
ContainerAssignmentExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  // 1 RHS is variableExpression (array,array), (struct,struct)(useCopy Function
  // 2 if direct does not works) from ObjectAssignment), (primitive,primitive)

  // 2 RHS Expression (array,BracketExp), (struct,structExp)

  // 3 RHS CallExpression (can be handled using first)
  BoundAssignmentExpression *assignmentExpression =
      static_cast<BoundAssignmentExpression *>(expression);

  BinderKindUtils::BoundNodeKind rhsKind =
      assignmentExpression->getRightPtr()->getKind();

  switch (rhsKind) {
  case BinderKindUtils::VariableExpression:
    return assignVariable(assignmentExpression);
  default:
    break;
  }

  _codeGenerationContext->getLogger()->LogError(
      "Right hand side value not found in assignment expression " +
      assignmentExpression->getVariable()->getVariableName());
  return nullptr;
}

llvm::Value *
ContainerAssignmentExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  _arrayType = nullptr;

  if (llvm::isa<llvm::AllocaInst>(_variable)) {
    llvm::AllocaInst *allocaInst = llvm::cast<llvm::AllocaInst>(_variable);

    if (llvm::isa<llvm::ArrayType>(allocaInst->getAllocatedType())) {
      _arrayType = llvm::cast<llvm::ArrayType>(allocaInst->getAllocatedType());
    }
  }

  if (!canGenerateExpressionAssignment(expression)) {
    return nullptr;
  }

  return createExpression(_arrayType, _variable, _rhsVariable, _rhsArrayType,
                          _rhsArrayElementType, _lhsSizes, _rhsSizes);
}
void ContainerAssignmentExpressionGenerationStrategy::assignArray(
    llvm::ArrayType *&arrayType, llvm::Value *&variable,
    llvm::Value *&rhsVariable, llvm::ArrayType *&rhsArrayType,
    llvm::Type *rhsArrayElementType, std::vector<llvm::Value *> &indices,
    const std::vector<uint64_t> &rhsSizes, uint64_t index) {
  if (index < rhsSizes.size()) {
    for (size_t i = 0; i < rhsSizes[index]; i++) {
      indices.push_back(Builder->getInt32(i));
      assignArray(arrayType, variable, rhsVariable, rhsArrayType,
                  rhsArrayElementType, indices, rhsSizes, index + 1);
      indices.pop_back();
    }

    return;
  }

  llvm::Value *elementPtr = Builder->CreateGEP(arrayType, variable, indices);

  // Load element to fill from rhs array
  llvm::Value *rhsElementPtr =
      Builder->CreateGEP(rhsArrayType, rhsVariable, indices);

  llvm::Value *elementToFill =
      Builder->CreateLoad(rhsArrayElementType, rhsElementPtr);

  Builder->CreateStore(elementToFill, elementPtr);
}

llvm::Value *ContainerAssignmentExpressionGenerationStrategy::createExpression(
    [[maybe_unused]] llvm::ArrayType *&arrayType, llvm::Value *&variable,
    llvm::Value *&rhsVariable, llvm::ArrayType *&rhsArrayType,
    [[maybe_unused]] llvm::Type *arrayElementType,
    [[maybe_unused]] const std::vector<uint64_t> &lhsSizes,
    [[maybe_unused]] const std::vector<uint64_t> &rhsSizes) {
  std::vector<llvm::Value *> indices = {Builder->getInt32(0)};

  llvm::LoadInst *loaded = Builder->CreateLoad(rhsArrayType, rhsVariable);

  Builder->CreateStore(loaded, variable);

  return nullptr;
}
llvm::Value *
ContainerAssignmentExpressionGenerationStrategy::createExpressionForObject(
    BoundExpression *expression, llvm::ArrayType *&arrayType,
    llvm::Value *&variable, const std::vector<uint64_t> &sizes,
    llvm::Type *&elementType) {
  _arrayType = arrayType;
  _variable = variable;
  _lhsSizes = sizes;
  _lhsArrayElementType = elementType;
  if (!canGenerateExpressionAssignment(expression)) {
    return nullptr;
  }

  return createExpression(_arrayType, _variable, _rhsVariable, _rhsArrayType,
                          _rhsArrayElementType, _lhsSizes, _rhsSizes);
}