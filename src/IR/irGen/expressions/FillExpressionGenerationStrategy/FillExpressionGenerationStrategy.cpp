#include "FillExpressionGenerationStrategy.h"

FillExpressionGenerationStrategy::FillExpressionGenerationStrategy(
    CodeGenerationContext *context, uint64_t actualSize,
    llvm::Type *elementType, const std::string &containerName)
    : ExpressionGenerationStrategy(context), _actualSize(actualSize),
      _elementType(elementType), _containerName(containerName) {}

llvm::Value *FillExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {

  if (!canGenerateExpression(expression))
    return nullptr;

  // Allocate memory on the stack for the array
  llvm::Type *arrayType = llvm::ArrayType::get(_elementType, _actualSize);
  llvm::AllocaInst *arrayAlloca =
      Builder->CreateAlloca(arrayType, nullptr, _containerName);

  // Fill the array with default values
  llvm::Constant *_defaultVal = llvm::cast<llvm::Constant>(
      _codeGenerationContext->getMapper()->getDefaultValue(_elementType));

  _codeGenerationContext->getAllocaChain()->setAllocaInst(_containerName,
                                                          arrayAlloca);
  createExpression(
      arrayType, arrayAlloca, _defaultVal,
      llvm::ConstantInt::get(llvm::Type::getInt32Ty(*TheContext), _actualSize));

  return createExpression(arrayType, arrayAlloca, _elementToFill,
                          _sizeToFillVal);
}

llvm::Value *FillExpressionGenerationStrategy::createLocalExpression(
    llvm::Type *arrayType, llvm::AllocaInst *arrayAlloca) {
  // Get And Set Default Value

  this->createExpression(arrayType, arrayAlloca, _elementToFill,
                         _sizeToFillVal);

  _codeGenerationContext->getAllocaChain()->setAllocaInst(_containerName,
                                                          arrayAlloca);

  return arrayAlloca;
}

llvm::Value *FillExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {

  if (!canGenerateExpression(expression))
    return nullptr;

  // Load and Store the items in the allocated memory

  llvm::ArrayType *arrayType = llvm::ArrayType::get(_elementType, _actualSize);

  // Create a default value for the array
  std::vector<llvm::Constant *> defaultValues(
      _actualSize,
      llvm::cast<llvm::Constant>(
          _codeGenerationContext->getMapper()->getDefaultValue(_elementType)));
  llvm::Constant *defaultArray =
      llvm::ConstantArray::get(arrayType, defaultValues);

  llvm::GlobalVariable *_globalVariable = new llvm::GlobalVariable(
      *TheModule, arrayType, false, llvm::GlobalValue::ExternalLinkage,
      defaultArray, _containerName);

  return createGlobalExpression(arrayType, _globalVariable);
}
llvm::Value *FillExpressionGenerationStrategy::createExpression(
    llvm::Type *arrayType, llvm::Value *v, llvm::Value *elementToFill,
    llvm::Value *sizeToFillVal) {
  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
  // Create blocks
  llvm::BasicBlock *loopStart = llvm::BasicBlock::Create(
      *TheContext, "FillExpr::loopStart", currentBlock->getParent());
  llvm::BasicBlock *loopBody = llvm::BasicBlock::Create(
      *TheContext, "FillExpr::loopBody", currentBlock->getParent());
  llvm::BasicBlock *loopEnd = llvm::BasicBlock::Create(
      *TheContext, "FillExpr::loopEnd", currentBlock->getParent());

  // Initialize counter
  llvm::AllocaInst *i = Builder->CreateAlloca(Builder->getInt32Ty());
  Builder->CreateStore(Builder->getInt32(0), i);

  // Jump to the loop start block
  Builder->CreateBr(loopStart);

  // Loop start block
  Builder->SetInsertPoint(loopStart);
  llvm::Value *iVal =
      Builder->CreateLoad(llvm::Type::getInt32Ty(*TheContext), i);
  llvm::Value *cond = Builder->CreateICmpSLT(iVal, sizeToFillVal);
  Builder->CreateCondBr(cond, loopBody, loopEnd);

  // Loop body block
  Builder->SetInsertPoint(loopBody);
  llvm::Value *elementPtr =
      Builder->CreateGEP(arrayType, v, {Builder->getInt32(0), iVal});

  Builder->CreateStore(elementToFill, elementPtr);
  llvm::Value *iNext = Builder->CreateAdd(iVal, Builder->getInt32(1));
  Builder->CreateStore(iNext, i);
  Builder->CreateBr(loopStart);

  // Loop end block
  Builder->SetInsertPoint(loopEnd);

  return nullptr;
}

llvm::Value *FillExpressionGenerationStrategy::createGlobalExpression(
    llvm::Type *arrayType, llvm::GlobalVariable *_globalVariable) {
  return this->createExpression(arrayType, _globalVariable, _elementToFill,
                                _sizeToFillVal);
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

  if (sizeToFillVal) {
    _sizeToFillVal = _int32TypeConverter->convertExplicit(sizeToFillVal);

    llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();

    llvm::BasicBlock *outOfBoundBlock = llvm::BasicBlock::Create(
        *TheContext, "FillExpr::outOfBound", currentBlock->getParent());

    llvm::BasicBlock *mergeBlock = llvm::BasicBlock::Create(
        *TheContext, "FillExpr::merge", currentBlock->getParent());
    llvm::Value *isGreaterThanEqual =
        Builder->CreateICmpSGT(_sizeToFillVal, Builder->getInt32(_actualSize));

    llvm::Value *isLessThan =
        Builder->CreateICmpSLE(_sizeToFillVal, Builder->getInt32(0));

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
    sizeToFillVal = Builder->getInt32(_actualSize);
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