#include "VariableExpressionGenerationStrategy.h"

VariableExpressionGenerationStrategy::VariableExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *
VariableExpressionGenerationStrategy::getTypedPrimitiveLocalVariableValue(
    const std::string &variableName, llvm::Value *variableValue,
    llvm::AllocaInst *v) {
  // When Local Variable is a struct type
  // When Global Variable (Value) is a struct type
  if (llvm::isa<llvm::StructType>(v->getAllocatedType())) {
    if (_variableExpression->getDotExpressionList().size() == 0) {
      return v;
    }
    return getObjectValue(v, 0, variableName);
  }

  return Builder->CreateLoad(variableValue->getType(), v, variableName);
}

llvm::Value *VariableExpressionGenerationStrategy::getUnTypedLocalVariableValue(
    llvm::Value *variableValue, llvm::AllocaInst *v,
    const std::string &variableName) {
  return _codeGenerationContext->getDynamicType()->getMemberValueOfDynVar(
      v, variableName);
}

llvm::Value *VariableExpressionGenerationStrategy::getLocalVariableValue(
    const std::string &variableName, llvm::Value *variableValue,
    llvm::AllocaInst *v) {
  // Typed Local Variables

  if (!v) {
    _codeGenerationContext->getLogger()->LogError(
        "Variable " + variableName + " not found in variable expression");

    return nullptr;
  }

  // When Local Variable is an array type
  if (v && llvm::isa<llvm::ArrayType>(v->getAllocatedType())) {
    return v;
  }

  // When Local Variable is a dynamic type
  if (_codeGenerationContext->getDynamicType()->isDyn(v->getAllocatedType())) {
    return this->getUnTypedLocalVariableValue(variableValue, v, variableName);
  }

  // When Local Variable is a struct type
  if (llvm::isa<llvm::StructType>(v->getAllocatedType())) {
    parObjTypeType = llvm::cast<llvm::StructType>(
        (llvm::cast<llvm::AllocaInst>(v))->getAllocatedType());

    if (_variableExpression->getDotExpressionList().size() == 0) {
      _codeGenerationContext->getValueStackHandler()->push(
          parObjTypeType->getStructName().str(), v, "struct", parObjTypeType);

      return v;
    }

    std::vector<llvm::Value *> indices = {Builder->getInt32(0)};
    return getObjectValueNF(v, 0, variableName, indices, parObjTypeType);
  }

  // When Primitive Local Variable is not a dynamic type
  if (!_codeGenerationContext->getDynamicType()->isDyn(v->getAllocatedType())) {
    return this->getTypedPrimitiveLocalVariableValue(variableName,
                                                     variableValue, v);
  }

  _codeGenerationContext->getLogger()->LogError(
      "Variable " + variableName + " not found in variable expression ");

  return nullptr;
}

llvm::Value *VariableExpressionGenerationStrategy::getVariableValue(
    const std::string &variableName) {
  llvm::AllocaInst *v =
      _codeGenerationContext->getAllocaChain()->getAllocaInst(variableName);

  llvm::Value *variableValue =
      _codeGenerationContext->getNamedValueChain()->getNamedValue(variableName);

  // Get Local Variable Value
  if (!variableValue) {
    if (v) {
      return this->getLocalVariableValue(variableName, variableValue, v);
    }

    llvm::GlobalVariable *variable = TheModule->getGlobalVariable(variableName);

    if (variable) {
      return this->getGlobalVariableValue(variableName, variable);
    }
  }

  return this->getLocalVariableValue(variableName, variableValue, v);
}

llvm::Value *VariableExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  _variableExpression = static_cast<BoundVariableExpression *>(expression);

  _typeExpression = _variableExpression->getVariableTypeRef();

  BoundObjectTypeExpression *objType =
      static_cast<BoundObjectTypeExpression *>(_typeExpression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      _variableExpression->getLocation());

  std::string variableName = std::any_cast<std::string>(
      ((BoundLiteralExpression<std::any> *)_variableExpression
           ->getIdentifierExpressionPtr()
           .get())
          ->getValue());

  return this->getVariableValue(variableName);
}

llvm::Value *VariableExpressionGenerationStrategy::getObjectValueNF(
    llvm::Value *outerElementPtr, size_t listIndex,
    const std::string &parPropertyKey, std::vector<llvm::Value *> indices,
    llvm::StructType *parObjType) {
  BoundCustomTypeStatement *boundCustomTypeStatement =
      _codeGenerationContext->getCustomTypeChain()->getExpr(
          parObjType->getStructName().str());

  uint64_t loopIndex = 0;

  std::string dotPropertyKey = std::any_cast<std::string>(
      _variableExpression->getDotExpressionList()[listIndex]->getValue());

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      _variableExpression->getDotExpressionList()[listIndex]->getLocation());

  auto logError = [&]() {
    _codeGenerationContext->getLogger()->LogError(
        "Property " + dotPropertyKey + " is not an object in " +
        (listIndex == 0 ? "variable " : "property ") + parPropertyKey +
        " of Type " + parObjType->getStructName().str());

    return nullptr;
  };

  for (const auto &[bLE, bTE] : boundCustomTypeStatement->getKeyPairs()) {
    std::string propertyName = std::any_cast<std::string>(bLE->getValue());
    if (propertyName == dotPropertyKey) {
      llvm::Type *type = parObjType->getElementType(loopIndex);

      const bool isNested =
          _variableExpression->getDotExpressionList().size() > listIndex + 1;

      if (isNested &&
          bTE->getSyntaxType() != SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE)
        return logError();

      llvm::Value *innerElementPtr =
          Builder->CreateStructGEP(parObjType, outerElementPtr, loopIndex);
      if (isNested && bTE->getSyntaxType() ==
                          SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
        if (!llvm::isa<llvm::StructType>(type)) {
          return logError();
        }

        llvm::StructType *structType = llvm::cast<llvm::StructType>(type);

        return getObjectValueNF(innerElementPtr, listIndex + 1, propertyName,
                                indices, structType);
      }
      if (bTE->getSyntaxType() ==
          SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
        llvm::StructType *structType = llvm::cast<llvm::StructType>(type);
        _codeGenerationContext->getValueStackHandler()->push(
            structType->getStructName().str(), innerElementPtr, "struct",
            structType);

        return innerElementPtr;
      }
      _codeGenerationContext->getValueStackHandler()->push("", innerElementPtr,
                                                           "primitive", type);
      return Builder->CreateLoad(type, innerElementPtr);
    }
    loopIndex++;
  }

  _codeGenerationContext->getLogger()->LogError(
      "Property " + dotPropertyKey + " does not exist in " +
      (listIndex == 0 ? "variable " : "property ") + parPropertyKey +
      " of Type " + parObjType->getStructName().str());
  return nullptr;
  // std::string key =
  //     boundCustomTypeStatement->getTypeNameAsString() + "." + propertyKey;
  // size_t index = _codeGenerationContext->getTypeChain()->getIndex(key);

  // if (index == -1) {
  //   _codeGenerationContext->getLogger()->LogError(
  //       "Property " + propertyKey + " not found in variable " +
  //       parPropertyKey + " of type " + objTypeType->getStructName().str());

  //   return nullptr;
  // }
}

llvm::Value *VariableExpressionGenerationStrategy::getObjectValue(
    llvm::Value *variableElementPtr, size_t listIndex,
    const std::string &parPropertyKey) {
  llvm::StructType *objTypeType = nullptr;

  if (llvm::isa<llvm::GlobalVariable>(variableElementPtr)) {
    objTypeType = llvm::cast<llvm::StructType>(
        (llvm::cast<llvm::GlobalVariable>(variableElementPtr))->getValueType());
  } else if (llvm::isa<llvm::AllocaInst>(variableElementPtr)) {
    objTypeType = llvm::cast<llvm::StructType>(
        (llvm::cast<llvm::AllocaInst>(variableElementPtr))->getAllocatedType());
  }

  BoundCustomTypeStatement *boundCustomTypeStatement =
      _codeGenerationContext->getCustomTypeChain()->getExpr(
          objTypeType->getStructName().str());

  std::unordered_map<std::string, BoundTypeExpression *> boundTypeExpressionMap;

  for (const auto &[bLE, bTE] : boundCustomTypeStatement->getKeyPairs()) {
    std::string propertyName = std::any_cast<std::string>(bLE->getValue());
    boundTypeExpressionMap[propertyName] = bTE.get();
  }

  std::string propertyKey = std::any_cast<std::string>(
      _variableExpression->getDotExpressionList()[listIndex]->getValue());

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      _variableExpression->getDotExpressionList()[listIndex]->getLocation());

  if (boundTypeExpressionMap.find(propertyKey) ==
      boundTypeExpressionMap.end()) {
    _codeGenerationContext->getLogger()->LogError(
        "Property " + propertyKey + " not found in variable " + parPropertyKey +
        " of type " + objTypeType->getStructName().str());

    return nullptr;
  }
  std::string key =
      boundCustomTypeStatement->getTypeNameAsString() + "." + propertyKey;
  size_t index = _codeGenerationContext->getTypeChain()->getIndex(key);

  llvm::Type *type = objTypeType->getElementType(index);

  if (index == -1) {
    _codeGenerationContext->getLogger()->LogError(
        "Property " + propertyKey + " not found in variable " + parPropertyKey +
        " of type " + objTypeType->getStructName().str());

    return nullptr;
  }
  auto logError = [&]() {
    _codeGenerationContext->getLogger()->LogError(
        "Property " + propertyKey + " is not an object in variable " +
        parPropertyKey + " of Type " + objTypeType->getStructName().str());

    return nullptr;
  };

  const bool isNested =
      _variableExpression->getDotExpressionList().size() > listIndex + 1;

  if (isNested && boundTypeExpressionMap[propertyKey]->getSyntaxType() !=
                      SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
    return logError();
  }
  llvm::Value *elementPtr =
      Builder->CreateStructGEP(objTypeType, variableElementPtr, index);

  if (boundTypeExpressionMap[propertyKey]->getSyntaxType() ==
      SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
    const std::string var_name =
        variableElementPtr->getName().str() + "." + propertyKey;

    llvm::GlobalVariable *globalVariable =
        TheModule->getGlobalVariable(var_name);

    llvm::AllocaInst *allocaInst =
        _codeGenerationContext->getAllocaChain()->getAllocaInst(var_name);

    if (allocaInst) {
      const bool isStruct =
          llvm::isa<llvm::StructType>(allocaInst->getAllocatedType());

      if (!isStruct)
        return logError();

      if (isNested)
        return getObjectValue(allocaInst, listIndex + 1, propertyKey);

      return allocaInst;
    }

    if (globalVariable) {
      const bool isStruct =
          llvm::isa<llvm::StructType>(globalVariable->getValueType());

      if (!isStruct)
        return logError();

      if (isNested)
        return getObjectValue(globalVariable, listIndex + 1, propertyKey);

      return globalVariable;
    }

    return logError();
  }

  llvm::LoadInst *loaded = Builder->CreateLoad(type, elementPtr);

  return loaded;
}

llvm::Value *VariableExpressionGenerationStrategy::getGlobalVariableValue(
    const std::string &variableName, llvm::GlobalVariable *variable) {
  if (!variable) {
    _codeGenerationContext->getLogger()->LogError(
        "Variable " + variableName + " not found in variable expression ");

    return nullptr;
  }

  // when Global Variable (Value) is a dynamic type
  if (_codeGenerationContext->getDynamicType()->isDyn(
          variable->getValueType())) {
    return _codeGenerationContext->getDynamicType()->getMemberValueOfDynVar(
        variable,
        FLOWWING::UTILS::CONSTANTS::GLOBAL_VARIABLE_PREFIX + variableName);
  }

  // Typed Global Variables

  // when Global Variable (Value) is an array type
  if (llvm::isa<llvm::ArrayType>(variable->getValueType())) {
    return variable;
  }

  // When Global Variable (Value) is a struct type
  if (llvm::isa<llvm::StructType>(variable->getValueType())) {
    if (llvm::isa<llvm::GlobalVariable>(variable)) {
      parObjTypeType = llvm::cast<llvm::StructType>(
          (llvm::cast<llvm::GlobalVariable>(variable))->getValueType());
    } else if (llvm::isa<llvm::AllocaInst>(variable)) {
      parObjTypeType = llvm::cast<llvm::StructType>(
          (llvm::cast<llvm::AllocaInst>(variable))->getAllocatedType());
    }

    if (_variableExpression->getDotExpressionList().size() == 0) {
      _codeGenerationContext->getValueStackHandler()->push(
          parObjTypeType->getStructName().str(), variable, "struct",
          parObjTypeType);

      return variable;
    }

    std::vector<llvm::Value *> indices = {Builder->getInt32(0)};
    return getObjectValueNF(variable, 0, variableName, indices, parObjTypeType);
  }

  // when Primitive Typed Global Variable (Value)

  return Builder->CreateLoad(variable->getValueType(), variable, variableName);
}

llvm::Value *VariableExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  BoundVariableExpression *variableExpression =
      static_cast<BoundVariableExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      variableExpression->getLocation());

  _codeGenerationContext->getLogger()->LogError(
      "Variable Expression is not allowed in global scope ");

  return nullptr;
}