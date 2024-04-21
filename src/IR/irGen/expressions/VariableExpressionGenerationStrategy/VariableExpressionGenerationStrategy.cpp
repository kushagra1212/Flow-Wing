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
  _codeGenerationContext->getValueStackHandler()->push(
      "", v, "primitive", variableValue->getType());
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

    _codeGenerationContext->getValueStackHandler()->push(
        "", v, "array",
        llvm::cast<llvm::ArrayType>(
            (llvm::cast<llvm::AllocaInst>(v))->getAllocatedType()));
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

  // when Primitive Typed Global Variable (Value)

  _codeGenerationContext->getValueStackHandler()->push("", v, "primitive",
                                                       v->getAllocatedType());

  return Builder->CreateLoad(v->getAllocatedType(), v, variableName);
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

  std::string dotPropertyKey = "";
  if (_variableExpression->getDotExpressionList()[listIndex]->getKind() ==
      BinderKindUtils::IndexExpression) {
    BoundIndexExpression *boundIndexExpression =
        static_cast<BoundIndexExpression *>(
            _variableExpression->getDotExpressionList()[listIndex].get());

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        boundIndexExpression->getLocation());
    dotPropertyKey = std::any_cast<std::string>(
        boundIndexExpression->getBoundIdentifierExpression().get()->getValue());

  } else {

    BoundLiteralExpression<std::any> *litExp =
        static_cast<BoundLiteralExpression<std::any> *>(
            _variableExpression->getDotExpressionList()[listIndex].get());
    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        litExp->getLocation());
    dotPropertyKey = std::any_cast<std::string>(litExp->getValue());
  }

  BoundCustomTypeStatement *boundCustomTypeStatement =
      _codeGenerationContext->getCustomTypeChain()->getExpr(
          parObjType->getStructName().str());

  uint64_t loopIndex = 0;

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

      if (isNested) {
        if (bTE->getSyntaxType() ==
            SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE) {
          if (!llvm::isa<llvm::ArrayType>(type)) {
            _codeGenerationContext->getLogger()->LogError(
                "Dot operator on non array type is not allowed, variable " +
                parObjType->getStructName().str() + " is not an array type");
            return nullptr;
          } else {

            llvm::ArrayType *arrayType = llvm::cast<llvm::ArrayType>(type);

            if (!llvm::isa<llvm::StructType>(arrayType->getElementType())) {
              _codeGenerationContext->getLogger()->LogError(
                  "Dot operator on non struct type is not allowed, variable " +
                  parObjType->getStructName().str() + " is not an struct type");
              return nullptr;
            }
          }

        } else if (bTE->getSyntaxType() !=
                   SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
          return logError();
        }
      }

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
      } else if (llvm::isa<llvm::ArrayType>(type) &&
                 bTE->getSyntaxType() ==
                     SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE) {
        llvm::ArrayType *arrayType = llvm::cast<llvm::ArrayType>(type);
        if (_variableExpression->getDotExpressionList()[listIndex]->getKind() ==
            BinderKindUtils::IndexExpression) {
          BoundIndexExpression *boundIndexExpression =
              static_cast<BoundIndexExpression *>(
                  _variableExpression->getDotExpressionList()[listIndex].get());
          std::unique_ptr<IndexExpressionGenerationStrategy>
              indexExpressionGenerationStrategy =
                  std::make_unique<IndexExpressionGenerationStrategy>(
                      _codeGenerationContext);

          _codeGenerationContext->getLogger()->setCurrentSourceLocation(
              boundIndexExpression->getLocation());
          indexExpressionGenerationStrategy->setIndexExpression(
              boundIndexExpression);
          indexExpressionGenerationStrategy->setVariable(innerElementPtr);
          indexExpressionGenerationStrategy->populateIndices();
          indexExpressionGenerationStrategy->setArrayType(arrayType);
          indexExpressionGenerationStrategy->populateArraySize();
          llvm::Value *val =
              indexExpressionGenerationStrategy->handleArrayTypeIndexing();
          if (llvm::isa<llvm::StructType>(arrayType->getArrayElementType()) &&
              listIndex + 1 <
                  _variableExpression->getDotExpressionList().size()) {

            std::vector<llvm::Value *> indices = {Builder->getInt32(0)};
            return getObjectValueNF(
                val, listIndex + 1, propertyName, indices,
                llvm::cast<llvm::StructType>(type->getArrayElementType()));
          }

          return val;
        }

        if (llvm::isa<llvm::ArrayType>(type) &&
            _variableExpression->getDotExpressionList()[listIndex]->getKind() !=
                BinderKindUtils::IndexExpression &&
            listIndex + 1 <
                _variableExpression->getDotExpressionList().size()) {
          _codeGenerationContext->getLogger()->LogError(
              "Applying dot operator on entire " +
              _codeGenerationContext->getMapper()->getLLVMTypeName(type) +
              " instead of a array element");
          return nullptr;
        }
        _codeGenerationContext->getValueStackHandler()->push(
            "", innerElementPtr, "array", arrayType);

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

  BoundLiteralExpression<std::any> *litExp =
      static_cast<BoundLiteralExpression<std::any> *>(
          _variableExpression->getDotExpressionList()[listIndex].get());

  std::string propertyKey = std::any_cast<std::string>(litExp->getValue());

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      litExp->getLocation());

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
        variable, variableName);
  }

  // Typed Global Variables

  // when Global Variable (Value) is an array type
  if (llvm::isa<llvm::ArrayType>(variable->getValueType())) {

    if (_variableExpression->getDotExpressionList().size() == 0) {
      _codeGenerationContext->getValueStackHandler()->push(
          "", variable, "array",
          llvm::cast<llvm::ArrayType>(variable->getValueType()));
      return variable;
    } else {
      _codeGenerationContext->getLogger()->LogError(
          "Array Element should be accessed using index in variable " +
          variableName + " " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(
              variable->getValueType()));
      return nullptr;
    }
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

  _codeGenerationContext->getValueStackHandler()->push(
      "", variable, "primitive", variable->getValueType());

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