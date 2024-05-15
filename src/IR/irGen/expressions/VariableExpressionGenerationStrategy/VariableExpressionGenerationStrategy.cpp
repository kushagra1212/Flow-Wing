#include "VariableExpressionGenerationStrategy.h"

VariableExpressionGenerationStrategy::VariableExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *VariableExpressionGenerationStrategy::getUnTypedLocalVariableValue(
    llvm::Value *variableValue, llvm::Value *v,
    const std::string &variableName) {
  return _codeGenerationContext->getDynamicType()->getMemberValueOfDynVar(
      v, variableName);
}

llvm::Value *VariableExpressionGenerationStrategy::getVariable(
    llvm::Value *v, llvm::Type *variableType, const std::string &variableName,
    int64_t pos) {

  if (!_variableExpression ||
      _variableExpression->getDotExpressionList().size() - pos == 0) {
    return handleSingleVariable(variableType, v, variableName);
  }

  // When Variable is a struct type
  if (llvm::isa<llvm::StructType>(variableType)) {
    return getObjectValueNF(v, pos, variableName,
                            llvm::cast<llvm::StructType>(variableType));
  }

  _codeGenerationContext->getLogger()->LogError(
      "Variable " + variableName + " not found in variable expression ");
  return nullptr;
}

llvm::Value *VariableExpressionGenerationStrategy::handleSingleVariable(
    llvm::Type *&variableType, llvm::Value *v,
    const std::string &variableName) {
  // When Local Variable is an array type
  if (llvm::isa<llvm::ArrayType>(variableType)) {

    _codeGenerationContext->getValueStackHandler()->push(
        "", v, "array", llvm::cast<llvm::ArrayType>(variableType));
    return v;
  }

  if (_codeGenerationContext->getDynamicType()->isDyn(variableType)) {
    return _codeGenerationContext->getDynamicType()->getMemberValueOfDynVar(
        v, variableName);
  }

  if (llvm::isa<llvm::StructType>(variableType)) {

    llvm::StructType *structType = llvm::cast<llvm::StructType>(variableType);

    // if (_codeGenerationContext->_classTypes.find(
    //         structType->getStructName().str()) !=
    //     _codeGenerationContext->_classTypes.end()) {

    //   _codeGenerationContext->getLogger()->LogError(
    //       "Access member of Class " +
    //       _codeGenerationContext->getMapper()->getLLVMTypeName(structType) +
    //       " using dot operator in variable " + variableName);
    //   return nullptr;
    // }
    _codeGenerationContext->getValueStackHandler()->push(
        structType->getStructName().str(), v, "struct", structType);

    return v;
  }

  llvm::Value *varValue = Builder->CreateLoad(variableType, v, variableName);
  // when Primitive Typed Global Variable (Value)

  _codeGenerationContext->getValueStackHandler()->push("", v, "primitive",
                                                       variableType);

  return varValue;
}

llvm::Value *VariableExpressionGenerationStrategy::getClassMember(
    int64_t pos, std::string &className, llvm::Value *v) {

  const std::string memberName = std::any_cast<std::string>(
      ((BoundLiteralExpression<std::any> *)_variableExpression
           ->getDotExpressionList()[pos]
           .get())
          ->getValue());
  if (_codeGenerationContext->_classTypes[className] &&
      _codeGenerationContext->_classTypes[className]->doesElementExist(
          memberName)) {
    auto [elementType, elementIndex, elementName, classType] =
        _codeGenerationContext->_classTypes[className]->getElement(memberName);
    llvm::Value *elementPtr =
        Builder->CreateStructGEP(parObjTypeType, v, elementIndex);

    return getVariable(elementPtr, elementType, memberName, pos + 1);
  }

  _codeGenerationContext->getLogger()->LogError(
      "Variable " + memberName +
      " not found in variable expression Expected to be a member of class " +
      _codeGenerationContext->getMapper()->getLLVMTypeName(
          _codeGenerationContext->_classTypes[className]->getClassType()));
  return nullptr;
}

llvm::Value *VariableExpressionGenerationStrategy::getVariableValue(
    const std::string &variableName) {

  if (_variableExpression && _variableExpression->isSelf()) {

    std::pair<llvm::Value *, llvm::Type *> cl =
        _codeGenerationContext->getAllocaChain()->getPtr("self");
    if (cl.first && cl.second && llvm::isa<llvm::StructType>(cl.second)) {
      llvm::StructType *classType = llvm::cast<llvm::StructType>(cl.second);
      std::string className = classType->getStructName().str();
      auto [elementType, atIndex, memberName, _classType] =
          _codeGenerationContext->_classTypes[className]->getElement(
              variableName);

      if (atIndex == -1) {
        _codeGenerationContext->getLogger()->LogError(
            "Variable " + variableName +
            " not found in variable expression Expected to be a member of "
            "class " +
            _codeGenerationContext->getMapper()->getLLVMTypeName(_classType));
        return nullptr;
      }

      llvm::Value *elementPtr =
          Builder->CreateStructGEP(classType, cl.first, atIndex);

      if (_variableExpression &&
          _variableExpression->getDotExpressionList().size() != 0) {
        return this->getVariable(elementPtr, elementType, variableName);
      }

      return handleSingleVariable(elementType, elementPtr, variableName);
    }

    _codeGenerationContext->getLogger()->LogError(
        "Variable " + variableName +
        " not found in variable expression Expected to member of class ");

    return nullptr;
  }

  std::pair<llvm::Value *, llvm::Type *> var =
      _codeGenerationContext->getAllocaChain()->getPtr(variableName);

  if (var.first && var.second) {
    return this->getVariable(var.first, var.second, variableName);
  } else {
    return this->getGlobalVariableValue(
        variableName, TheModule->getGlobalVariable(variableName));
  }

  _codeGenerationContext->getLogger()->LogError(
      "Variable " + variableName + " not found in variable expression ");
  return nullptr;
}

llvm::Value *VariableExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  _variableExpression = static_cast<BoundVariableExpression *>(expression);

  _typeExpression = _variableExpression->getVariableTypeRef();

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
    const std::string &parPropertyName, llvm::StructType *parObjType,
    bool itsClass) {

  std::string dotPropertyName = getPropertyName(listIndex);

  itsClass = _codeGenerationContext->_classTypes.find(
                 parObjType->getStructName().str()) !=
             _codeGenerationContext->_classTypes.end();

  bool isNested =
      _variableExpression->getDotExpressionList().size() > listIndex + 1;

  if (itsClass &&
      _variableExpression->getDotExpressionList()[listIndex]->getKind() ==
          BinderKindUtils::BoundNodeKind::CallExpression) {
    BoundCallExpression *callExpression = static_cast<BoundCallExpression *>(
        _variableExpression->getDotExpressionList()[listIndex].get());

    std::string className = parObjType->getStructName().str();

    std::unique_ptr<CallExpressionGenerationStrategy> call =
        std::make_unique<CallExpressionGenerationStrategy>(
            _codeGenerationContext);
    std::vector<llvm::Value *> args = {outerElementPtr};

    llvm::Value *callinst = call->generateCommonCallExpression(
        callExpression,
        TheModule->getFunction(callExpression->getCallerNameRef()), args,
        _codeGenerationContext->_classTypes[className]->getClassType(),
        outerElementPtr);
    if (!isNested)
      return callinst;
    llvm::Value *ptr =
        _codeGenerationContext->getValueStackHandler()->getValue();
    llvm::Type *type =
        _codeGenerationContext->getValueStackHandler()->getLLVMType();
    _codeGenerationContext->getValueStackHandler()->popAll();

    return getVariable(ptr, type, dotPropertyName, listIndex + 1);
  }

  if (itsClass &&
      !_codeGenerationContext->_classTypes[parObjType->getStructName().str()]
           ->doesElementExist(dotPropertyName)) {

    _codeGenerationContext->getLogger()->LogError(
        "Variable " + dotPropertyName +
        " not found in variable expression Expected to be a member of "
        "class " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(parObjTypeType));

    return nullptr;
  }

  return handleVariableGet(parObjType, itsClass, dotPropertyName, listIndex,
                           parPropertyName, isNested, outerElementPtr);
}

llvm::Value *VariableExpressionGenerationStrategy::handleVariableGet(
    llvm::StructType *parObjType, bool itsClass, std::string &dotPropertyName,
    size_t listIndex, const std::string &parPropertyName, bool isNested,
    llvm::Value *outerElementPtr) {
  auto logError = [&]() {
    _codeGenerationContext->getLogger()->LogError(
        "Property " + dotPropertyName + " is not an object in " +
        (listIndex == 0 ? "variable " : "property ") + parPropertyName +
        " of Type " + parObjType->getStructName().str());

    return nullptr;
  };

  BoundCustomTypeStatement *boundCustomTypeStatement =
      _codeGenerationContext->getCustomTypeChain()->getExpr(
          parObjType->getStructName().str());

  Class *classObj = nullptr;

  if (itsClass) {
    classObj =
        _codeGenerationContext->_classTypes[parObjType->getStructName().str()]
            .get();
  }

  if (!itsClass && !boundCustomTypeStatement) {
    return logError();
  }

  auto [bLE, bTE, atIndex] =
      itsClass ? classObj->getKeyValue(dotPropertyName)
               : boundCustomTypeStatement->getKeyValue(dotPropertyName);

  if (atIndex == -1) {
    _codeGenerationContext->getLogger()->LogError(
        "Property " + dotPropertyName + " does not exist in " +
        (listIndex == 0 ? (itsClass ? "class object " : "variable ")
                        : "property ") +
        parPropertyName + " of Type " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(parObjType));

    return nullptr;
  }

  llvm::Type *objElementType = parObjType->getElementType(atIndex);

  if (isNested) {
    if (bTE->getSyntaxType() == SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE) {
      if (!llvm::isa<llvm::ArrayType>(objElementType)) {
        _codeGenerationContext->getLogger()->LogError(
            "Dot operator on non array type is not allowed, variable " +
            parObjType->getStructName().str() + " is not an array type");
        return nullptr;
      }

      llvm::ArrayType *arrayType = llvm::cast<llvm::ArrayType>(objElementType);

      if (!llvm::isa<llvm::StructType>(arrayType->getElementType())) {
        _codeGenerationContext->getLogger()->LogError(
            "Dot operator on non struct type is not allowed, variable " +
            parObjType->getStructName().str() + " is not an struct type");
        return nullptr;
      }

    } else if (bTE->getSyntaxType() !=
               SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE)
      return logError();
  }

  llvm::Value *innerElementPtr =
      Builder->CreateStructGEP(parObjType, outerElementPtr, atIndex);

  if (!isNested) {

    if (_variableExpression->getDotExpressionList()[listIndex]->getKind() ==
            BinderKindUtils::IndexExpression &&
        llvm::isa<llvm::ArrayType>(objElementType) &&
        bTE->getSyntaxType() == SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE) {
      llvm::ArrayType *arrayType = llvm::cast<llvm::ArrayType>(objElementType);
      return handleIndexExpression(listIndex, innerElementPtr, arrayType);
    }

    return handleSingleVariable(objElementType, innerElementPtr,
                                dotPropertyName);
  }

  if (llvm::isa<llvm::StructType>(objElementType) &&
      bTE->getSyntaxType() == SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {

    return getObjectValueNF(innerElementPtr, listIndex + 1, dotPropertyName,
                            llvm::cast<llvm::StructType>(objElementType));
  } else if (llvm::isa<llvm::ArrayType>(objElementType) &&
             bTE->getSyntaxType() ==
                 SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE) {
    llvm::ArrayType *arrayType = llvm::cast<llvm::ArrayType>(objElementType);
    if (_variableExpression->getDotExpressionList()[listIndex]->getKind() ==
        BinderKindUtils::IndexExpression) {

      return getVariable(
          handleIndexExpression(listIndex, innerElementPtr, arrayType),
          arrayType->getArrayElementType(), dotPropertyName, listIndex + 1);
    }

    _codeGenerationContext->getLogger()->LogError(
        "Applying dot operator on entire " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(objElementType) +
        " instead of a array element");
    return nullptr;

    _codeGenerationContext->getValueStackHandler()->push("", innerElementPtr,
                                                         "array", arrayType);

    return innerElementPtr;
  }

  _codeGenerationContext->getValueStackHandler()->push(
      "", innerElementPtr, "primitive", objElementType);
  return Builder->CreateLoad(objElementType, innerElementPtr);
}

llvm::Value *VariableExpressionGenerationStrategy::handleIndexExpression(
    size_t listIndex, llvm::Value *innerElementPtr,
    llvm::ArrayType *arrayType) {

  BoundIndexExpression *boundIndexExpression =
      static_cast<BoundIndexExpression *>(
          _variableExpression->getDotExpressionList()[listIndex].get());
  std::unique_ptr<IndexExpressionGenerationStrategy>
      indexExpressionGenerationStrategy =
          std::make_unique<IndexExpressionGenerationStrategy>(
              _codeGenerationContext);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundIndexExpression->getLocation());
  indexExpressionGenerationStrategy->setIndexExpression(boundIndexExpression);
  indexExpressionGenerationStrategy->setVariable(innerElementPtr);
  indexExpressionGenerationStrategy->populateIndices();
  indexExpressionGenerationStrategy->setArrayType(arrayType);
  indexExpressionGenerationStrategy->populateArraySize();
  return indexExpressionGenerationStrategy->handleArrayTypeIndexing();
}

std::string
VariableExpressionGenerationStrategy::getPropertyName(size_t listIndex) {
  BinderKindUtils::BoundNodeKind kind =
      _variableExpression->getDotExpressionList()[listIndex]->getKind();

  switch (kind) {
  case BinderKindUtils::IndexExpression: {
    BoundIndexExpression *boundIndexExpression =
        static_cast<BoundIndexExpression *>(
            _variableExpression->getDotExpressionList()[listIndex].get());

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        boundIndexExpression->getLocation());
    return std::any_cast<std::string>(
        boundIndexExpression->getBoundIdentifierExpression().get()->getValue());
  }
  case BinderKindUtils::LiteralExpression: {

    BoundLiteralExpression<std::any> *litExp =
        static_cast<BoundLiteralExpression<std::any> *>(
            _variableExpression->getDotExpressionList()[listIndex].get());
    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        litExp->getLocation());
    return std::any_cast<std::string>(litExp->getValue());
  }

  case BinderKindUtils::CallExpression: {
    BoundCallExpression *boundCallExpression =
        static_cast<BoundCallExpression *>(
            _variableExpression->getDotExpressionList()[listIndex].get());

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        boundCallExpression->getLocation());

    return boundCallExpression->getCallerNameRef();
  }

  default:
    break;
  }

  _codeGenerationContext->getLogger()->LogError(
      "Cannot get property name from variable " +
      _variableExpression->getVariableNameRef() + " in the dot expression");

  return "";
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

    return getObjectValueNF(variable, 0, variableName, parObjTypeType);
  }

  // when Primitive Typed Global Variable (Value)

  _codeGenerationContext->getValueStackHandler()->push(
      "", variable, "primitive", variable->getValueType());

  return Builder->CreateLoad(variable->getValueType(), variable, variableName);
}

llvm::Value *VariableExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  return this->generateExpression(expression);
}