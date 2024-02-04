#include "ObjectAssignmentExpressionGenerationStrategy.h"

ObjectAssignmentExpressionGenerationStrategy::
    ObjectAssignmentExpressionGenerationStrategy(CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *ObjectAssignmentExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  if (!canGenerateAssignmentExpressionAssignment(
          (BoundAssignmentExpression *)expression)) {
    return nullptr;
  }

  return this->assignObject(_lhsVar, 0, _lhsVarExpr->getVariableNameRef(),
                            _lhsVarExpr->getDotExpressionList().size() == 0);
}

llvm::Value *
ObjectAssignmentExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  return this->generateExpression(expression);
}

llvm::Value *ObjectAssignmentExpressionGenerationStrategy::assignObject(
    llvm::Value *variableElementPtr, size_t listIndex,
    const std::string &parPropertyKey, bool reachedEnd) {
  llvm::StructType *parStructType = nullptr;

  if (llvm::isa<llvm::GlobalVariable>(variableElementPtr)) {
    parStructType = llvm::cast<llvm::StructType>(
        (llvm::cast<llvm::GlobalVariable>(variableElementPtr))->getValueType());
  } else if (llvm::isa<llvm::AllocaInst>(variableElementPtr)) {
    parStructType = llvm::cast<llvm::StructType>(
        (llvm::cast<llvm::AllocaInst>(variableElementPtr))->getAllocatedType());
  } else {
    _codeGenerationContext->getLogger()->LogError(
        "This is Currently not supported yet");
    return nullptr;
  }

  if (reachedEnd) {
    if (_assignmentExp->getRightPtr().get()->getKind() ==
        BinderKindUtils::BoundObjectExpression) {
      std::unique_ptr<ObjectExpressionGenerationStrategy> objExpGenStrat =
          std::make_unique<ObjectExpressionGenerationStrategy>(
              _codeGenerationContext);
      objExpGenStrat->setVariable(variableElementPtr);
      objExpGenStrat->setTypeName(parStructType->getName().str());

      if (_isGlobal) {
        return objExpGenStrat->generateGlobalExpression(
            _assignmentExp->getRightPtr().get());
      } else {
        return objExpGenStrat->generateExpression(
            _assignmentExp->getRightPtr().get());
      }
    } else if (_assignmentExp->getRightPtr().get()->getKind() ==
               BinderKindUtils::VariableExpression) {
      std::unique_ptr<ObjectExpressionGenerationStrategy> objExpGenStrat =
          std::make_unique<ObjectExpressionGenerationStrategy>(
              _codeGenerationContext);

      llvm::Value *rhsValue =
          _expressionGenerationFactory
              ->createStrategy(_assignmentExp->getRightPtr().get()->getKind())
              ->generateExpression(_assignmentExp->getRightPtr().get());

      return objExpGenStrat->generateVariable(variableElementPtr,
                                              parStructType->getName().str(),
                                              rhsValue, _isGlobal);
    } else {
      _codeGenerationContext->getLogger()->LogError(
          "This is Currently not supported yet");
      return nullptr;
    }
  }

  BoundCustomTypeStatement *boundCustomTypeStatement =
      _codeGenerationContext->getCustomTypeChain()->getExpr(
          parStructType->getStructName().str());

  std::unordered_map<std::string, BoundTypeExpression *> boundTypeExpressionMap;

  for (const auto &[bLE, bTE] : boundCustomTypeStatement->getKeyPairs()) {
    std::string propertyName = std::any_cast<std::string>(bLE->getValue());
    boundTypeExpressionMap[propertyName] = bTE.get();
  }

  std::string propertyKey = std::any_cast<std::string>(
      _lhsVarExpr->getDotExpressionList()[listIndex]->getValue());

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      _lhsVarExpr->getDotExpressionList()[listIndex]->getLocation());

  if (boundTypeExpressionMap.find(propertyKey) ==
      boundTypeExpressionMap.end()) {
    _codeGenerationContext->getLogger()->LogError(
        "Property " + propertyKey + " not found in variable " + parPropertyKey +
        " of type " + parStructType->getStructName().str());

    return nullptr;
  }
  std::string key =
      boundCustomTypeStatement->getTypeNameAsString() + "." + propertyKey;
  size_t index = _codeGenerationContext->getTypeChain()->getIndex(key);

  llvm::Type *type = parStructType->getElementType(index);

  if (index == -1) {
    _codeGenerationContext->getLogger()->LogError(
        "Property " + propertyKey + " not found in variable " + parPropertyKey +
        " of type " + parStructType->getStructName().str());

    return nullptr;
  }
  auto logError = [&]() {
    _codeGenerationContext->getLogger()->LogError(
        "Property " + propertyKey + " is not an object in variable " +
        parPropertyKey + " of Type " + parStructType->getStructName().str());

    return nullptr;
  };

  const bool isNested =
      _lhsVarExpr->getDotExpressionList().size() > listIndex + 1;

  if (isNested && boundTypeExpressionMap[propertyKey]->getSyntaxType() !=
                      SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
    return logError();
  }

  if (boundTypeExpressionMap[propertyKey]->getSyntaxType() ==
      SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
    std::unique_ptr<ObjectExpressionGenerationStrategy> objExpGenStrat =
        std::make_unique<ObjectExpressionGenerationStrategy>(
            _codeGenerationContext);

    BoundObjectTypeExpression *boundObjectTypeExpression =
        static_cast<BoundObjectTypeExpression *>(
            boundTypeExpressionMap[propertyKey]);

    llvm::StructType *elementType =
        (_codeGenerationContext->getTypeChain()->getType(
            boundObjectTypeExpression->getTypeName()));

    const std::string var_name =
        variableElementPtr->getName().str() + "." + propertyKey;

    llvm::Value *allocaInstAndGl =
        _codeGenerationContext->getAllocaChain()->getAllocaInst(var_name);

    if (!allocaInstAndGl) {
      allocaInstAndGl = TheModule->getGlobalVariable(var_name);
    }
    if (!allocaInstAndGl) {
      if (_isGlobal) {
        allocaInstAndGl = new llvm::GlobalVariable(
            *TheModule, elementType, false, llvm::GlobalValue::ExternalLinkage,
            llvm::Constant::getNullValue(elementType), var_name);

      } else {
        allocaInstAndGl = Builder->CreateAlloca(elementType, nullptr, var_name);
        _codeGenerationContext->getAllocaChain()->setAllocaInst(
            var_name, llvm::cast<llvm::AllocaInst>(allocaInstAndGl));
      }
    }

    return assignObject(allocaInstAndGl, listIndex + 1, propertyKey,
                        (!isNested));
  }

  llvm::Value *rhsValue =
      _expressionGenerationFactory
          ->createStrategy(_assignmentExp->getRightPtr().get()->getKind())
          ->generateExpression(_assignmentExp->getRightPtr().get());

  if (rhsValue->getType() != type) {
    _codeGenerationContext->getLogger()->LogError(
        "Type mismatch in assignment expression, expected " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(type) +
        " but found " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(
            rhsValue->getType()) +
        " ");

    return nullptr;
  }

  llvm::Value *elementPtr =
      Builder->CreateStructGEP(parStructType, variableElementPtr, index);
  Builder->CreateStore(rhsValue, elementPtr);

  return rhsValue;
}

bool ObjectAssignmentExpressionGenerationStrategy::
    canGenerateAssignmentExpressionAssignment(
        BoundAssignmentExpression *assignmentExpression) {
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      assignmentExpression->getLocation());

  _assignmentExp = assignmentExpression;
  _lhsVarExpr = static_cast<BoundVariableExpression *>(
      assignmentExpression->getLeftPtr().get());

  llvm::Value *val =
      _codeGenerationContext->getNamedValueChain()->getNamedValue(
          _lhsVarExpr->getVariableNameRef());

  _isGlobal = false;

  if (!val) {
    // Variable not found locally, handle error

    _lhsVar = _codeGenerationContext->getAllocaChain()->getAllocaInst(
        _lhsVarExpr->getVariableNameRef());

    if (_lhsVar) {
      return true;
    }

    _lhsVar = TheModule->getGlobalVariable(_lhsVarExpr->getVariableNameRef());

    if (_lhsVar) {
      _isGlobal = true;
      return true;
    }

    _codeGenerationContext->getLogger()->LogError(
        "Variable not found in assignment expression '" +
        _lhsVarExpr->getVariableNameRef() + "'");

    return false;
  }

  return true;
}
