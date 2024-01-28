#include "ObjectExpressionGenerationStrategy.h"

ObjectExpressionGenerationStrategy::ObjectExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *ObjectExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  return this->createExpression(expression);
}

llvm::Value *ObjectExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  return this->createExpression(expression);
}

llvm::Value *ObjectExpressionGenerationStrategy::createExpression(
    BoundExpression *expression) {
  BoundObjectExpression *objectExpression =
      static_cast<BoundObjectExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      expression->getLocation());

  llvm::StructType *structType =
      _codeGenerationContext->getTypeChain()->getType(_typeName);

  BoundCustomTypeStatement *boundCustomTypeStatement =
      _codeGenerationContext->getCustomTypeChain()->getExpr(_typeName);

  std::unordered_map<std::string, BoundTypeExpression *> propertiesMap;

  for (const auto &[bLitExpr, bExpr] :
       boundCustomTypeStatement->getKeyPairs()) {
    std::string propertyName = std::any_cast<std::string>(bLitExpr->getValue());
    propertiesMap[propertyName] = bExpr.get();
  }

  for (const auto &[bLitExpr, bExpr] : objectExpression->getKeyValuePairs()) {
    std::string propertyName = std::any_cast<std::string>(bLitExpr->getValue());

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        bLitExpr->getLocation());

    if (propertiesMap.find(propertyName) == propertiesMap.end()) {
      _codeGenerationContext->getLogger()->LogError(
          "Property " + propertyName + " not found in type " + _typeName);
      return nullptr;
    }
    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        bExpr->getLocation());

    if ((propertiesMap[propertyName]->getSyntaxType() ==
             SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE &&
         bExpr->getKind() != BinderKindUtils::BoundObjectExpression) or
        (bExpr->getKind() == BinderKindUtils::BoundObjectExpression &&
         propertiesMap[propertyName]->getSyntaxType() !=
             SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE)) {
      _codeGenerationContext->getLogger()->LogError(
          "Type of property '" + propertyName +
          "' does not match type of property in type " + _typeName);

      return nullptr;
    }

    std::string key = _typeName + ":" + propertyName;
    const size_t index = _codeGenerationContext->getTypeChain()->getIndex(key);

    if (index == -1) {
      _codeGenerationContext->getLogger()->LogError(
          "Property " + std::any_cast<std::string>(bLitExpr->getValue()) +
          " not found in type " + _typeName);
      return nullptr;
    }

    llvm::Value *rhs = nullptr;

    if (bExpr->getKind() == BinderKindUtils::BoundObjectExpression) {
      BoundObjectExpression *objectExpression =
          static_cast<BoundObjectExpression *>(bExpr.get());

      BoundObjectTypeExpression *boundObjectTypeExpression =
          static_cast<BoundObjectTypeExpression *>(propertiesMap[propertyName]);

      std::unique_ptr<ObjectExpressionGenerationStrategy> objExpGenStrat =
          std::make_unique<ObjectExpressionGenerationStrategy>(
              _codeGenerationContext);

      llvm::Value *elementPtr =
          Builder->CreateGEP(structType, _globalVariable,
                             {Builder->getInt32(0), Builder->getInt32(index)});

      llvm::Type *elementType =
          (_codeGenerationContext->getTypeChain()->getType(
              boundObjectTypeExpression->getTypeName()));

      objExpGenStrat->setGlobalVariable(elementPtr);
      objExpGenStrat->setTypeName(elementType->getStructName().str());
      objExpGenStrat->generateGlobalExpression(objectExpression);

      continue;
    } else {
      rhs = _expressionGenerationFactory->createStrategy(bExpr->getKind())
                ->generateExpression(bExpr.get());
    }

    if (!rhs) {
      _codeGenerationContext->getLogger()->LogError(
          "Property " + std::any_cast<std::string>(bLitExpr->getValue()) +
          " not found in type " + _typeName);
      return nullptr;
    }

    if (_codeGenerationContext->getMapper()->isPrimitiveType(rhs->getType()) &&
        _codeGenerationContext->getMapper()->isPrimitiveType(
            structType->getElementType(index)) &&
        rhs->getType() != structType->getElementType(index)) {
      _codeGenerationContext->getLogger()->LogError(
          "Type of property " +
          std::any_cast<std::string>(bLitExpr->getValue()) +
          " does not match type in type " + _typeName + " Expected " +
          Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
              structType->getElementType(index))) +
          " but got " +
          Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
              rhs->getType())));

      return nullptr;
    }

    if (rhs->getType() != structType->getElementType(index)) {
      _codeGenerationContext->getLogger()->LogError(

          "Type of property " +
          std::any_cast<std::string>(bLitExpr->getValue()) +
          " does not match type in type " + _typeName + "Expected " +
          Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
              structType->getElementType(index))) +
          " but got " +
          Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
              rhs->getType())));
      return nullptr;
    }

    llvm::Value *elementPtr =
        Builder->CreateGEP(structType, _globalVariable,
                           {Builder->getInt32(0), Builder->getInt32(index)});

    Builder->CreateStore(rhs, elementPtr);
  }

  return nullptr;
}