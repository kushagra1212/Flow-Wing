#include "IndexExpressionGenerationStrategy.h"

#include "../VariableExpressionGenerationStrategy/VariableExpressionGenerationStrategy.h"

IndexExpressionGenerationStrategy::IndexExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

const bool IndexExpressionGenerationStrategy::canGenerateExpression(
    const std::string &variableName) {

  std::pair<llvm::Value *, llvm::Type *> var =
      _codeGenerationContext->getAllocaChain()->getPtr(variableName);

  if (_indexExpression->isSelf()) {

    std::pair<llvm::Value *, llvm::Type *> cl =
        _codeGenerationContext->getAllocaChain()->getPtr("self");
    if (cl.first && cl.second && llvm::isa<llvm::StructType>(cl.second)) {
      llvm::StructType *classType = llvm::cast<llvm::StructType>(cl.second);
      cl.first =
          Builder->CreateLoad(llvm::Type::getInt8PtrTy(*TheContext), cl.first);
      std::string className =
          Utils::getActualTypeName(classType->getStructName().str());
      auto [elementType, atIndex, memberName, _classType] =
          _codeGenerationContext->_classTypes[className]->getElement(
              variableName);
      if (atIndex == -1) {
        _codeGenerationContext->getLogger()->LogError(
            "Variable " + variableName +
            " not found in index expression Expected to be a member of "
            "class " +
            _codeGenerationContext->getMapper()->getLLVMTypeName(_classType));
        return false;
      }

      llvm::Value *elementPtr =
          Builder->CreateStructGEP(classType, cl.first, atIndex);

      _arrayType = llvm::cast<llvm::ArrayType>(elementType);
      _variable = elementPtr;
      return true;
    }
  }

  // When Local Variable is an array type
  if (var.second && var.first && llvm::isa<llvm::ArrayType>(var.second)) {

    // llvm::Value *varValue =
    //     Builder->CreateLoad(var.second, var.first, variableName);
    _arrayType = llvm::cast<llvm::ArrayType>(var.second);
    _variable = var.first;

    return true;
  }

  if (var.second && var.first &&
      var.second == llvm::Type::getInt8PtrTy(*TheContext)) {
    _arrayType = nullptr;
    _variable = var.first;
    return true;
  }

  // Variable not found, handle error
  llvm::GlobalVariable *variable = TheModule->getGlobalVariable(_variableName);

  if (!variable) {
    _codeGenerationContext->getLogger()->LogError(
        "variable " + _variableName + " not found in variable expression");

    return false;
  }

  if (variable && !llvm::isa<llvm::ArrayType>(variable->getValueType()) &&
      variable->getValueType() !=
          llvm::Type::getInt8PtrTy(Builder->getContext())) {

    _codeGenerationContext->getLogger()->LogError(
        "variable " + _variableName + " Expected to be of type array of " +
        Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
            _arrayElementType)) +
        " but got " +
        Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
            variable->getValueType())));

    return false;
  }

  if (llvm::isa<llvm::ArrayType>(variable->getValueType()))
    _arrayType = llvm::cast<llvm::ArrayType>(variable->getValueType());

  _variable = variable;

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

  _arrayElementType = _arrayType;

  if (_arrayType == nullptr) {
    return handleStringIndexing();
  }

  _codeGenerationContext->createArraySizesAndArrayElementType(
      sizes, _arrayElementType);

  for (int i = 0; i < sizes.size(); i++) {
    _actualSizes.push_back(Builder->getInt32(sizes[i]));
  }

  return this->handleArrayTypeIndexing();
}

llvm::Value *IndexExpressionGenerationStrategy::handleStringIndexing() {
  if (_indices.size() != 1) {
    _codeGenerationContext->getLogger()->LogError(
        "String index expression must have one index");
    return nullptr;
  }

  // TODO Throw Error From Binder Check of index count

  llvm::Value *loadedStrPtr =
      Builder->CreateLoad(llvm::Type::getInt8PtrTy(*TheContext), _variable);

  llvm::Value *strElementPtr = Builder->CreateInBoundsGEP(
      llvm::Type::getInt8Ty(*TheContext), loadedStrPtr, _indices, "arrayInx");

  _codeGenerationContext->getValueStackHandler()->push(
      "", strElementPtr, "primary", llvm::Type::getInt8Ty(*TheContext));

  return strElementPtr;
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
        llvm::cast<llvm::StructType>(_arrayElementType);

    if (variableExpression->getDotExpressionList().size() == 0) {
      _codeGenerationContext->getValueStackHandler()->push(
          Utils::getActualTypeName(parObjTypeType->getStructName().str()),
          elementPtr, "struct", parObjTypeType);

      return elementPtr;
    }
    std::unique_ptr<VariableExpressionGenerationStrategy> strategy =
        std::make_unique<VariableExpressionGenerationStrategy>(
            _codeGenerationContext);
    strategy->setVariableExpression(variableExpression);
    return strategy->getObjectValueNF(elementPtr, 0, _variable->getName().str(),
                                      parObjTypeType);
  }

  if (llvm::isa<llvm::StructType>(_arrayType->getElementType())) {
    llvm::StructType *structType =
        llvm::cast<llvm::StructType>(_arrayType->getElementType());
    _codeGenerationContext->getValueStackHandler()->push(
        Utils::getActualTypeName(structType->getStructName().str()), elementPtr,
        "struct", structType);
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
