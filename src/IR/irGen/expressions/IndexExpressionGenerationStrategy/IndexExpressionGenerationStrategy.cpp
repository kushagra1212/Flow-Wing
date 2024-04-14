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

int8_t IndexExpressionGenerationStrategy::populateIndices() {
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      _indexExpression->getLocation());

  for (auto &index : _indexExpression->getBoundIndexExpressions()) {
    llvm::Value *indexValue =
        _expressionGenerationFactory->createStrategy(index.get()->getKind())
            ->generateExpression(index.get());

    if (!_codeGenerationContext->getMapper()->isInt32Type(
            indexValue->getType())) {
      _codeGenerationContext->getLogger()->LogError(
          "Index value must be of type int");
      return EXIT_FAILURE;
    }

    indexValue = _int32TypeConverter->convertExplicit(indexValue);

    if (!_codeGenerationContext->getMapper()->isInt32Type(
            indexValue->getType())) {
      _codeGenerationContext->getLogger()->LogError(
          "Expected index value to be of type int but got " +
          Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
              indexValue->getType())));
      return EXIT_FAILURE;
    }
    _indices.push_back(indexValue);
  }
  return EXIT_SUCCESS;
}

int8_t IndexExpressionGenerationStrategy::populateVariableName() {

  _variableName = std::any_cast<std::string>(
      (_indexExpression->getBoundIdentifierExpression().get())->getValue());
  return EXIT_SUCCESS;
}

llvm::Value *IndexExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  BoundIndexExpression *indexExpression =
      static_cast<BoundIndexExpression *>(expression);
  _indexExpression = indexExpression;

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      indexExpression->getLocation());

  if (this->populateIndices() || this->populateVariableName() ||
      !this->canGenerateExpression(_variableName))
    return nullptr;
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

  if (_indexExpression->isObject()) {
    BoundVariableExpression *variableExpression =
        static_cast<BoundVariableExpression *>(
            _indexExpression->getVariableExpression().get());

    llvm::StructType *parObjTypeType =
        llvm::cast<llvm::StructType>(_arrayType->getArrayElementType());

    if (variableExpression->getDotExpressionList().size() == 0) {
      _codeGenerationContext->getValueStackHandler()->push(
          parObjTypeType->getStructName().str(), elementPtr, "struct",
          parObjTypeType);

      return elementPtr;
    }
    std::unique_ptr<VariableExpressionGenerationStrategy> strategy =
        std::make_unique<VariableExpressionGenerationStrategy>(
            _codeGenerationContext);
    std::vector<llvm::Value *> indices = {Builder->getInt32(0)};
    strategy->setVariableExpression(variableExpression);
    return strategy->getObjectValueNF(elementPtr, 0, _variable->getName().str(),
                                      indices, parObjTypeType);
  }

  if (llvm::isa<llvm::StructType>(_arrayType->getElementType())) {
    llvm::StructType *structType =
        llvm::cast<llvm::StructType>(_arrayType->getElementType());
    _codeGenerationContext->getValueStackHandler()->push(
        structType->getStructName().str(), elementPtr, "struct", structType);
    return elementPtr;
  }
  _codeGenerationContext->getValueStackHandler()->push(
      "", elementPtr, "primitive", _arrayElementType);
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
