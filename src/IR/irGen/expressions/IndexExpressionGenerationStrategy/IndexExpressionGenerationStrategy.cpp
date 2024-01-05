#include "IndexExpressionGenerationStrategy.h"

IndexExpressionGenerationStrategy::IndexExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

const bool IndexExpressionGenerationStrategy::canGenerateExpression(
    const std::string &variableName) {
  llvm::AllocaInst *v =
      _codeGenerationContext->getAllocaChain()->getAllocaInst(_variableName);

  if (v && !(llvm::isa<llvm::ArrayType>(v->getAllocatedType()))) {

    _codeGenerationContext->getLogger()->LogError(
        "variable " + _variableName + " Expected to be of type array of " +
        Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
            _arrayElementType)) +
        " but got " +
        Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
            v->getAllocatedType())));
    return false;
  }

  if (!v) {
    // Variable not found, handle error
    llvm::GlobalVariable *variable =
        TheModule->getGlobalVariable(_variableName);

    if (!variable) {
      _codeGenerationContext->getLogger()->LogError(
          "variable " + _variableName + " not found in variable expression");

      return false;
    }

    if (variable && !llvm::isa<llvm::ArrayType>(variable->getValueType())) {

      _codeGenerationContext->getLogger()->LogError(
          "variable " + _variableName + " Expected to be of type array of " +
          Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
              _arrayElementType)) +
          " but got " +
          Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
              variable->getValueType())));

      return false;
    }
    _arrayElementType =
        _codeGenerationContext->getArrayElementTypeMetadata(variable);
    _arrayType = llvm::cast<llvm::ArrayType>(variable->getValueType());
    _variable = variable;

    return true;
  }
  _arrayElementType = _codeGenerationContext->getArrayElementTypeMetadata(v);
  _arrayType = llvm::cast<llvm::ArrayType>(v->getAllocatedType());
  _variable = v;

  return true;
}

llvm::Value *IndexExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  BoundIndexExpression *indexExpression =
      static_cast<BoundIndexExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      indexExpression->getLocation());

  for (auto &index : indexExpression->getBoundIndexExpressions()) {
    llvm::Value *indexValue =
        _expressionGenerationFactory->createStrategy(index.get()->getKind())
            ->generateExpression(index.get());

    if (!_codeGenerationContext->getMapper()->isInt32Type(
            indexValue->getType())) {
      _codeGenerationContext->getLogger()->LogError(
          "Index value must be of type int");
      return nullptr;
    }

    indexValue = _int32TypeConverter->convertExplicit(indexValue);

    if (!_codeGenerationContext->getMapper()->isInt32Type(
            indexValue->getType())) {
      _codeGenerationContext->getLogger()->LogError(
          "Expected index value to be of type int but got " +
          Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
              indexValue->getType())));
      return nullptr;
    }
    _indices.push_back(indexValue);
  }

  _variableName = std::any_cast<std::string>(
      (indexExpression->getBoundIdentifierExpression().get())->getValue());

  if (!this->canGenerateExpression(_variableName)) {
    return nullptr;
  }

  std::vector<uint64_t> sizes;
  _codeGenerationContext->getArraySizeMetadata(_variable, sizes);

  for (int i = 0; i < sizes.size(); i++) {
    _actualSizes.push_back(Builder->getInt32(sizes[i]));
  }

  return this->handleArrayTypeIndexing();
}

void IndexExpressionGenerationStrategy::verifyBounds(
    llvm::Value *indexValue, llvm::ConstantInt *actualSize) {
  llvm::Function *function = Builder->GetInsertBlock()->getParent();
  llvm::BasicBlock *thenBB =
      llvm::BasicBlock::Create(*TheContext, "GlobalIndexExpr::then", function);
  llvm::BasicBlock *elseBB =
      llvm::BasicBlock::Create(*TheContext, "GlobalIndexExpr::else", function);
  llvm::BasicBlock *mergeBB =
      llvm::BasicBlock::Create(*TheContext, "GlobalIndexExpr::merge", function);

  // TODO: TO 64 Bit
  llvm::Value *isLessThan = Builder->CreateICmpSLT(
      indexValue, actualSize, "GlobalIndexExpr::isLessThan");

  llvm::Value *isGreaterThan = Builder->CreateICmpSGE(
      indexValue,
      llvm::ConstantInt::get(llvm::Type::getInt32Ty(*TheContext), 0, true),
      "GlobalIndexExpr::isGreaterThan");

  llvm::Value *isWithinBounds = Builder->CreateAnd(
      isLessThan, isGreaterThan, "GlobalIndexExpr::isWithinBounds");

  // Create the conditional branch
  Builder->CreateCondBr(isWithinBounds, thenBB, elseBB);

  // In the then block, you can continue with the array access
  Builder->SetInsertPoint(thenBB);

  Builder->CreateBr(mergeBB);

  Builder->SetInsertPoint(elseBB);

  _codeGenerationContext->callREF(
      "Index out of bounds of '" + _variableName +
      "' in index expression, index value should be between 0 and " +
      (std::to_string(actualSize->getSExtValue())));

  Builder->CreateBr(mergeBB);

  // Continue from the merge block
  Builder->SetInsertPoint(mergeBB);
}

llvm::Value *IndexExpressionGenerationStrategy::handleArrayTypeIndexing() {

  if (_actualSizes.size() != _indices.size()) {
    _codeGenerationContext->getLogger()->LogError(
        "Expected " + std::to_string(_actualSizes.size()) +
        " indices but got " + std::to_string(_indices.size()));
    return nullptr;
  }

  int64_t n = _actualSizes.size();

  for (int64_t i = 0; i < n; i++) {
    this->verifyBounds(_indices[i], _actualSizes[i]);
  }

  std::vector<llvm::Value *> indexList = {Builder->getInt32(0)};

  for (int i = 0; i < n; i++) {
    indexList.push_back(_indices[i]);
  }

  llvm::Value *elementPtr =
      Builder->CreateGEP(_arrayType, _variable, indexList);
  return Builder->CreateLoad(_arrayElementType, elementPtr);
}

llvm::Value *IndexExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  BoundIndexExpression *indexExpression =
      static_cast<BoundIndexExpression *>(expression);
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      indexExpression->getLocation());

  _codeGenerationContext->getLogger()->LogError(
      "Index expression not allowed in global scope");

  return nullptr;
}
