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
    canGenerateExpressionAssignment(
        BoundVariableExpression *variableExpression) {

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
      variableExpression->getLocation());

  _rhsVariable = _expressionGenerationFactory
                     ->createStrategy(variableExpression->getKind())
                     ->generateExpression(variableExpression);

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
  } else {
    hasError = true;
  }

  if (!_rhsArrayType) {
    hasError = true;
  }

  if (_rhsArrayType->getElementType()->isIntegerTy(8)) {
    hasError = true;
  }
  if (hasError) {
    _codeGenerationContext->getLogger()->LogError(
        "Variable " + _containerName + " not found in assignment expression ");
    return false;
  }

  if (_arrayType->getElementType() !=
      (llvm::Type *)_rhsArrayType->getElementType()) {
    _codeGenerationContext->getLogger()->LogError(
        "Type mismatch in assignment expression : " + _containerName);

    return false;
  }

  _rhsSize = _codeGenerationContext->getBuilder()->getInt32(
      _rhsArrayType->getNumElements());

  _size = _codeGenerationContext->getBuilder()->getInt32(
      _arrayType->getNumElements());

  llvm::BasicBlock *currentBlock =
      _codeGenerationContext->getBuilder()->GetInsertBlock();

  llvm::BasicBlock *outOfBoundBlock = llvm::BasicBlock::Create(
      *_codeGenerationContext->getContext(),
      "ContainerAssignmentExpr::outOfBound", currentBlock->getParent());

  llvm::BasicBlock *mergeBlock = llvm::BasicBlock::Create(
      *_codeGenerationContext->getContext(), "ContainerAssignmentExpr::merge",
      currentBlock->getParent());

  llvm::Value *isGreaterThanEqual =
      _codeGenerationContext->getBuilder()->CreateICmpSGE(_size, _rhsSize);

  _codeGenerationContext->getBuilder()->CreateCondBr(
      isGreaterThanEqual, mergeBlock, outOfBoundBlock);

  _codeGenerationContext->getBuilder()->SetInsertPoint(outOfBoundBlock);

  _codeGenerationContext->callREF(
      "Index out of bound in assignment expression : " + _containerName);

  _codeGenerationContext->getBuilder()->CreateBr(mergeBlock);

  _codeGenerationContext->getBuilder()->SetInsertPoint(mergeBlock);

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

  auto variableExpression = dynamic_cast<BoundVariableExpression *>(expression);

  if (!canGenerateExpressionAssignment(variableExpression)) {
    return nullptr;
  }

  return createExpression(_arrayType, _variable, _size, _rhsSize, _rhsVariable,
                          _rhsArrayType);
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

  auto variableExpression = dynamic_cast<BoundVariableExpression *>(expression);

  if (!canGenerateExpressionAssignment(variableExpression)) {
    return nullptr;
  }

  return createExpression(_arrayType, _variable, _size, _rhsSize, _rhsVariable,
                          _rhsArrayType);
}

llvm::Value *ContainerAssignmentExpressionGenerationStrategy::createExpression(
    llvm::ArrayType *arrayType, llvm::Value *variable, llvm::Value *size,
    llvm::Value *rhsSize, llvm::Value *rhsVariable,
    llvm::ArrayType *rhsArrayType) {
  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
  // Create blocks
  llvm::BasicBlock *loopStart = llvm::BasicBlock::Create(
      *TheContext, "Assignment::loopStart", currentBlock->getParent());
  llvm::BasicBlock *loopBody = llvm::BasicBlock::Create(
      *TheContext, "Assignment::loopBody", currentBlock->getParent());
  llvm::BasicBlock *loopEnd = llvm::BasicBlock::Create(
      *TheContext, "Assignment::loopEnd", currentBlock->getParent());

  // Initialize counter
  llvm::AllocaInst *i = Builder->CreateAlloca(Builder->getInt32Ty());
  Builder->CreateStore(Builder->getInt32(0), i);

  // Jump to the loop start block
  Builder->CreateBr(loopStart);

  // Loop start block
  Builder->SetInsertPoint(loopStart);
  llvm::Value *iVal =
      Builder->CreateLoad(llvm::Type::getInt32Ty(*TheContext), i);
  llvm::Value *cond = Builder->CreateICmpSLT(iVal, rhsSize);
  Builder->CreateCondBr(cond, loopBody, loopEnd);

  // Loop body block
  Builder->SetInsertPoint(loopBody);
  llvm::Value *elementPtr =
      Builder->CreateGEP(arrayType, variable, {Builder->getInt32(0), iVal});

  // Load element to fill from rhs array
  llvm::Value *rhsElementPtr = Builder->CreateGEP(rhsArrayType, rhsVariable,
                                                  {Builder->getInt32(0), iVal});

  llvm::Value *elementToFill =
      Builder->CreateLoad(rhsArrayType->getElementType(), rhsElementPtr);

  Builder->CreateStore(elementToFill, elementPtr);

  llvm::Value *iNext = Builder->CreateAdd(iVal, Builder->getInt32(1));
  Builder->CreateStore(iNext, i);
  Builder->CreateBr(loopStart);

  // Loop end block
  Builder->SetInsertPoint(loopEnd);

  return nullptr;
}