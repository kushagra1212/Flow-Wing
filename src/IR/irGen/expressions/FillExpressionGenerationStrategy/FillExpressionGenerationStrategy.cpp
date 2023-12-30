#include "FillExpressionGenerationStrategy.h"

FillExpressionGenerationStrategy::FillExpressionGenerationStrategy(
    CodeGenerationContext *context, std::vector<uint64_t> actualSizes,
    llvm::Type *elementType, const std::string &containerName)
    : ExpressionGenerationStrategy(context), _actualSizes(actualSizes),
      _elementType(elementType), _containerName(containerName) {

  _totalSize = std::accumulate(_actualSizes.begin(), _actualSizes.end(), 1,
                               std::multiplies<uint64_t>());
}

llvm::Value *FillExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {

  if (!canGenerateExpression(expression))
    return nullptr;

  // Allocate memory on the stack for the array
  llvm::ArrayType *arrayType = nullptr;

  llvm::Constant *_defaultVal = llvm::cast<llvm::Constant>(
      _codeGenerationContext->getMapper()->getDefaultValue(_elementType));

  _codeGenerationContext->getMultiArrayType(arrayType, _defaultVal,
                                            _actualSizes, _elementType);

  llvm::AllocaInst *arrayAlloca =
      Builder->CreateAlloca(arrayType, nullptr, _containerName);

  // Fill the array with default values

  _codeGenerationContext->setArraySizeMetadata(arrayAlloca, _actualSizes);
  _codeGenerationContext->setArrayElementTypeMetadata(arrayAlloca,
                                                      _elementType);

  _codeGenerationContext->getAllocaChain()->setAllocaInst(_containerName,
                                                          arrayAlloca);
  createExpression(
      arrayType, arrayAlloca,
      llvm::cast<llvm::Constant>(
          _codeGenerationContext->getMapper()->getDefaultValue(_elementType)),
      _totalSize);

  return createExpression(arrayType, arrayAlloca, _elementToFill,
                          _sizeToFillInt);
}

llvm::Value *FillExpressionGenerationStrategy::createLocalExpression(
    llvm::Type *arrayType, llvm::AllocaInst *arrayAlloca) {
  // Get And Set Default Value

  this->createExpression(arrayType, arrayAlloca, _elementToFill,
                         _sizeToFillInt);

  _codeGenerationContext->getAllocaChain()->setAllocaInst(_containerName,
                                                          arrayAlloca);

  return arrayAlloca;
}

llvm::Value *FillExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {

  if (!canGenerateExpression(expression))
    return nullptr;

  // Load and Store the items in the allocated memory

  llvm::ArrayType *arrayType = nullptr;

  // Create a default value for the array

  llvm::Constant *_defaultVal = llvm::cast<llvm::Constant>(
      _codeGenerationContext->getMapper()->getDefaultValue(_elementType));

  _codeGenerationContext->getMultiArrayType(arrayType, _defaultVal,
                                            _actualSizes, _elementType);
  llvm::GlobalVariable *_globalVariable = new llvm::GlobalVariable(
      *TheModule, arrayType, false, llvm::GlobalValue::ExternalLinkage,
      _defaultVal, _containerName);

  _codeGenerationContext->setArraySizeMetadata(_globalVariable, _actualSizes);
  _codeGenerationContext->setArrayElementTypeMetadata(_globalVariable,
                                                      _elementType);
  return createGlobalExpression(arrayType, _globalVariable);
}

llvm::Value *FillExpressionGenerationStrategy::createExpressionAtom(
    llvm::Type *arrayType, llvm::Value *v, llvm::Value *elementToFill,
    uint64_t &sizeToFillVal, std::vector<llvm::Value *> &indices,
    uint64_t index) {

  if (sizeToFillVal == 0)
    return nullptr;

  if (index < (_actualSizes.size())) {
    for (int64_t i = 0; i < _actualSizes[index]; i++) {
      indices.push_back(Builder->getInt32(i));
      createExpressionAtom(arrayType, v, elementToFill, sizeToFillVal, indices,
                           index + 1);
      indices.pop_back();
      if (sizeToFillVal == 0)
        return nullptr;
    }
    return nullptr;
  }

  llvm::Value *elementPtr = Builder->CreateGEP(arrayType, v, indices);

  Builder->CreateStore(elementToFill, elementPtr);
  sizeToFillVal--;
  // llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
  // // Create blocks
  // llvm::BasicBlock *loopStart = llvm::BasicBlock::Create(
  //     *TheContext, "FillExpr::loopStart", currentBlock->getParent());
  // llvm::BasicBlock *loopBody = llvm::BasicBlock::Create(
  //     *TheContext, "FillExpr::loopBody", currentBlock->getParent());
  // llvm::BasicBlock *loopEnd = llvm::BasicBlock::Create(
  //     *TheContext, "FillExpr::loopEnd", currentBlock->getParent());

  // // Initialize counter
  // llvm::AllocaInst *i = Builder->CreateAlloca(Builder->getInt32Ty());
  // Builder->CreateStore(Builder->getInt32(0), i);

  // // Jump to the loop start block
  // Builder->CreateBr(loopStart);

  // // Loop start block
  // Builder->SetInsertPoint(loopStart);
  // llvm::Value *iVal =
  //     Builder->CreateLoad(llvm::Type::getInt32Ty(*TheContext), i);
  // llvm::Value *cond = Builder->CreateICmpSLT(iVal, sizeToFillVal);
  // Builder->CreateCondBr(cond, loopBody, loopEnd);

  // // Loop body block
  // Builder->SetInsertPoint(loopBody);
  // llvm::Value *elementPtr = Builder->CreateGEP(arrayType, v, indices);

  // Builder->CreateStore(elementToFill, elementPtr);
  // llvm::Value *iNext = Builder->CreateAdd(iVal, Builder->getInt32(1));
  // Builder->CreateStore(iNext, i);
  // Builder->CreateBr(loopStart);

  // // Loop end block
  // Builder->SetInsertPoint(loopEnd);

  return nullptr;
}

llvm::Value *FillExpressionGenerationStrategy::createExpression(
    llvm::Type *arrayType, llvm::Value *v, llvm::Value *elementToFill,
    uint64_t sizeToFillVal) {

  std::vector<llvm::Value *> indices = {Builder->getInt32(0)};

  createExpressionAtom(arrayType, v, elementToFill, sizeToFillVal, indices, 0);

  return nullptr;
}

llvm::Value *FillExpressionGenerationStrategy::createGlobalExpression(
    llvm::Type *arrayType, llvm::GlobalVariable *_globalVariable) {
  return this->createExpression(arrayType, _globalVariable, _elementToFill,
                                _sizeToFillInt);
}

bool FillExpressionGenerationStrategy::canGenerateExpression(
    BoundExpression *expression) {

  BoundFillExpression *fillExpression =
      static_cast<BoundFillExpression *>(expression);

  llvm::Value *sizeToFillVal = nullptr;

  if (fillExpression->getSizeToFillRef().get())
    sizeToFillVal =
        _expressionGenerationFactory
            ->createStrategy(fillExpression->getSizeToFillRef()->getKind())
            ->generateExpression(fillExpression->getSizeToFillRef().get());

  if (llvm::isa<llvm::ConstantInt>(sizeToFillVal)) {
    llvm::ConstantInt *c = llvm::cast<llvm::ConstantInt>(sizeToFillVal);

    _sizeToFillInt = c->getSExtValue();
    llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();

    llvm::BasicBlock *outOfBoundBlock = llvm::BasicBlock::Create(
        *TheContext, "FillExpr::CHECK::outOfBound", currentBlock->getParent());

    llvm::BasicBlock *mergeBlock = llvm::BasicBlock::Create(
        *TheContext, "FillExpr::CHECK::merge", currentBlock->getParent());
    llvm::Value *isGreaterThanEqual =
        Builder->CreateICmpSGT(sizeToFillVal, Builder->getInt32(_totalSize));

    llvm::Value *isLessThan =
        Builder->CreateICmpSLE(sizeToFillVal, Builder->getInt32(0));

    llvm::Value *isOutOfBound =
        Builder->CreateOr(isGreaterThanEqual, isLessThan);

    Builder->CreateCondBr(isOutOfBound, outOfBoundBlock, mergeBlock);

    Builder->SetInsertPoint(outOfBoundBlock);

    _codeGenerationContext->callREF("Element to fill is out of bound.  Size to "
                                    "fill must be less than to the "
                                    "actual size of the container and greater "
                                    "than or equal to zero:" +
                                    _containerName);

    Builder->CreateBr(mergeBlock);

    Builder->SetInsertPoint(mergeBlock);

  } else {
    sizeToFillVal = Builder->getInt32(_totalSize);
    _sizeToFillInt = _totalSize;
  }

  _elementToFill =
      _expressionGenerationFactory
          ->createStrategy(fillExpression->getElementToFillRef()->getKind())
          ->generateExpression(fillExpression->getElementToFillRef().get());

  if (!_elementToFill) {
    _codeGenerationContext->getLogger()->LogError(
        "Element to fill must be a Value.");
    return false;
  }

  if (_elementType && _elementType != _elementToFill->getType()) {
    std::string elementTypeName =
        _codeGenerationContext->getMapper()->getLLVMTypeName(_elementType);

    std::string itemValueTypeName =
        _codeGenerationContext->getMapper()->getLLVMTypeName(
            _elementToFill->getType());

    _codeGenerationContext->getLogger()->LogError(
        _containerName + " Container item type mismatch. Expected " +
        elementTypeName + " but got " + itemValueTypeName);

    return false;
  }

  return true;
}