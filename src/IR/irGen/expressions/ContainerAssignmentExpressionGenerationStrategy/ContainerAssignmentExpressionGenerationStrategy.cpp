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

const bool ContainerAssignmentExpressionGenerationStrategy::
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
  } else {
    hasError = true;
  }

  if (!_rhsArrayType) {
    hasError = true;
  }

  _codeGenerationContext->getArraySizeMetadata(_variable, _lhsSizes);
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

llvm::Value *
ContainerAssignmentExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  _arrayType = nullptr;

  if (llvm::isa<llvm::GlobalVariable>(_variable)) {

    llvm::GlobalVariable *globalVariable =
        llvm::cast<llvm::GlobalVariable>(_variable);

    if (llvm::isa<llvm::ArrayType>(globalVariable->getValueType())) {

      _arrayType = llvm::cast<llvm::ArrayType>(globalVariable->getValueType());
    }
  }

  if (!canGenerateExpressionAssignment(expression)) {
    return nullptr;
  }

  return createExpression(_arrayType, _variable, _rhsVariable, _rhsArrayType,
                          _rhsArrayElementType, _lhsSizes, _rhsSizes);
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
    const std::vector<size_t> &rhsSizes, uint64_t index) {

  if (index < rhsSizes.size()) {
    for (int64_t i = 0; i < rhsSizes[index]; i++) {
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
    llvm::ArrayType *&arrayType, llvm::Value *&variable,
    llvm::Value *&rhsVariable, llvm::ArrayType *&rhsArrayType,
    llvm::Type *arrayElementType, const std::vector<size_t> &lhsSizes,
    const std::vector<size_t> &rhsSizes) {

  std::vector<llvm::Value *> indices = {Builder->getInt32(0)};

  llvm::LoadInst *loaded = Builder->CreateLoad(rhsArrayType, rhsVariable);

  Builder->CreateStore(loaded, variable);

  return nullptr;
}