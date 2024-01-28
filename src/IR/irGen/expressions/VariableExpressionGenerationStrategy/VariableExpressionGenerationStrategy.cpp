#include "VariableExpressionGenerationStrategy.h"

VariableExpressionGenerationStrategy::VariableExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *
VariableExpressionGenerationStrategy::getTypedPrimitiveLocalVariableValue(
    const std::string &variableName, llvm::Value *variableValue,
    llvm::AllocaInst *v) {
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

  // When Local Variable is an array type
  if (v && llvm::isa<llvm::ArrayType>(v->getAllocatedType())) {
    return v;
  }
  if (!v) {
    _codeGenerationContext->getLogger()->LogError(
        "Variable " + variableName + " not found in variable expression");

    return nullptr;
  }

  // When Local Variable is a struct type
  if (v && llvm::isa<llvm::StructType>(v->getAllocatedType())) {
    return getObjectValue(_typeExpression, v, 0, variableName);
  }

  // When Primitive Local Variable is not a dynamic type
  if (!_codeGenerationContext->getDynamicType()->isDyn(v->getAllocatedType())) {
    return this->getTypedPrimitiveLocalVariableValue(variableName,
                                                     variableValue, v);
  }

  // When Local Variable is a dynamic type
  if (_codeGenerationContext->getDynamicType()->isDyn(v->getAllocatedType())) {
    return this->getUnTypedLocalVariableValue(variableValue, v, variableName);
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

  _typeExpression = _variableExpression->getVariableTypeRef().get();

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

llvm::Value *VariableExpressionGenerationStrategy::getObjectValue(
    BoundTypeExpression *bTE, llvm::Value *variableElementPtr, size_t listIndex,
    const std::string &parPropertyKey) {
  BoundObjectTypeExpression *objType =
      static_cast<BoundObjectTypeExpression *>(bTE);

  llvm::StructType *objTypeType = nullptr;

  if (llvm::isa<llvm::GlobalVariable>(variableElementPtr)) {
    objTypeType = llvm::cast<llvm::StructType>(
        (llvm::cast<llvm::GlobalVariable>(variableElementPtr))->getValueType());
  } else if (llvm::isa<llvm::AllocaInst>(variableElementPtr)) {
    objTypeType = llvm::cast<llvm::StructType>(
        (llvm::cast<llvm::AllocaInst>(variableElementPtr))->getAllocatedType());
  } else {
    objTypeType =
        _codeGenerationContext->getTypeChain()->getType(objType->getTypeName());
  }

  BoundCustomTypeStatement *boundCustomTypeStatement =
      _codeGenerationContext->getCustomTypeChain()->getExpr(
          objTypeType->getStructName().str());

  std::unordered_map<std::string, BoundTypeExpression *> boundTypeExpressionMap;

  for (const auto &[bLE, bTE] : boundCustomTypeStatement->getKeyPairs()) {
    std::string typeName = std::any_cast<std::string>(bLE->getValue());
    boundTypeExpressionMap[typeName] = bTE.get();
  }

  std::string key = boundCustomTypeStatement->getTypeNameAsString() + ":";

  std::string propertyKey = std::any_cast<std::string>(
      _variableExpression->getDotExpressionList()[listIndex]->getValue());

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      _variableExpression->getDotExpressionList()[listIndex]->getLocation());

  if (boundTypeExpressionMap.find(propertyKey) ==
      boundTypeExpressionMap.end()) {
    _codeGenerationContext->getLogger()->LogError(
        "Property " + propertyKey + " not found in Property " + parPropertyKey);

    return nullptr;
  }
  key += propertyKey;
  size_t index = _codeGenerationContext->getTypeChain()->getIndex(key);

  llvm::Type *type = objTypeType->getElementType(index);

  if (index == -1) {
    _codeGenerationContext->getLogger()->LogError(
        "Variable " + key + " not found in variable expression ");

    return nullptr;
  }

  if (_variableExpression->getDotExpressionList().size() > listIndex + 1 &&
      boundTypeExpressionMap[propertyKey]->getSyntaxType() !=
          SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
    _codeGenerationContext->getLogger()->LogError(
        "Property " + propertyKey + " is not an object type in variable " +
        parPropertyKey);
    return nullptr;
  }
  llvm::Value *elementPtr =
      Builder->CreateStructGEP(objTypeType, variableElementPtr, index);

  if (_variableExpression->getDotExpressionList().size() > listIndex + 1 &&
      boundTypeExpressionMap[propertyKey]->getSyntaxType() ==
          SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
    return getObjectValue(boundTypeExpressionMap[propertyKey], elementPtr,
                          listIndex + 1, propertyKey);
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
    if (_variableExpression->getDotExpressionList().size() == 0) {
      return variable;
    }
    return getObjectValue(_typeExpression, variable, 0, variableName);
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