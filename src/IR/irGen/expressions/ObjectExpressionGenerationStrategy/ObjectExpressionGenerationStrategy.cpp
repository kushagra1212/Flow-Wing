#include "ObjectExpressionGenerationStrategy.h"

ObjectExpressionGenerationStrategy::ObjectExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *ObjectExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  llvm::Value *res = this->createExpression(expression, _variable, _typeName);

  if (llvm::isa<llvm::AllocaInst>(_variable)) {
    llvm::AllocaInst *allocaInst = llvm::cast<llvm::AllocaInst>(_variable);
    llvm::MDString *argInfoMD = llvm::MDString::get(*TheContext, _typeName);
    llvm::StringRef Kind = allocaInst->getName();
    allocaInst->setMetadata(Kind, llvm::MDNode::get(*TheContext, argInfoMD));
  }
  return res;
}

llvm::Value *ObjectExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  this->_variableIsGlobal = true;
  llvm::Value *res = this->createExpression(expression, _variable, _typeName);

  if (llvm::isa<llvm::GlobalVariable>(_variable)) {
    llvm::GlobalVariable *globalVariable =
        llvm::cast<llvm::GlobalVariable>(_variable);
    llvm::MDString *argInfoMD = llvm::MDString::get(*TheContext, _typeName);
    llvm::StringRef Kind = globalVariable->getName();
    globalVariable->setMetadata(Kind,
                                llvm::MDNode::get(*TheContext, argInfoMD));
  }

  return res;
}

llvm::Value *ObjectExpressionGenerationStrategy::createExpression(
    BoundExpression *expression, llvm::Value *variable,
    const std::string &typeName) {
  BoundObjectExpression *objectExpression =
      static_cast<BoundObjectExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      expression->getLocation());

  llvm::StructType *structType =
      _codeGenerationContext->getTypeChain()->getType(typeName);

  BoundCustomTypeStatement *boundCustomTypeStatement =
      _codeGenerationContext->getCustomTypeChain()->getExpr(typeName);

  std::unordered_map<std::string, BoundTypeExpression *> propertiesMap;

  uint64_t index = 0;
  for (const auto &[bLitExpr, bExpr] :
       boundCustomTypeStatement->getKeyPairs()) {
    std::string propertyName = std::any_cast<std::string>(bLitExpr->getValue());
    propertiesMap[propertyName] = bExpr.get();

    if (bExpr->getSyntaxType() !=
        SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
      llvm::Constant *defaultValue =
          llvm::Constant::getNullValue(structType->getElementType(index));

      llvm::Value *elementPtr =
          Builder->CreateGEP(structType, variable,
                             {Builder->getInt32(0), Builder->getInt32(index)});

      Builder->CreateStore(defaultValue, elementPtr);
    }

    index++;
  }

  for (const auto &[bLitExpr, bExpr] : objectExpression->getKeyValuePairs()) {
    std::string propertyName = std::any_cast<std::string>(bLitExpr->getValue());

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        bLitExpr->getLocation());

    if (propertiesMap.find(propertyName) == propertiesMap.end()) {
      _codeGenerationContext->getLogger()->LogError(
          "Property " + propertyName + " not found in type " + typeName);
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
          "' does not match type of property in type " + typeName);

      return nullptr;
    }

    std::string key =
        boundCustomTypeStatement->getTypeNameAsString() + "." + propertyName;
    const size_t index = _codeGenerationContext->getTypeChain()->getIndex(key);

    if (index == -1) {
      _codeGenerationContext->getLogger()->LogError(
          "Property " + std::any_cast<std::string>(bLitExpr->getValue()) +
          " not found in type " + typeName);
      return nullptr;
    }

    llvm::Value *rhs = nullptr;

    llvm::Value *elementPtr = Builder->CreateGEP(
        structType, variable, {Builder->getInt32(0), Builder->getInt32(index)});

    if (bExpr->getKind() == BinderKindUtils::BoundObjectExpression) {
      BoundObjectExpression *objectExpression =
          static_cast<BoundObjectExpression *>(bExpr.get());

      BoundObjectTypeExpression *boundObjectTypeExpression =
          static_cast<BoundObjectTypeExpression *>(propertiesMap[propertyName]);

      std::unique_ptr<ObjectExpressionGenerationStrategy> objExpGenStrat =
          std::make_unique<ObjectExpressionGenerationStrategy>(
              _codeGenerationContext);

      llvm::StructType *elementType =
          (_codeGenerationContext->getTypeChain()->getType(
              boundObjectTypeExpression->getTypeName()));

      objExpGenStrat->setTypeName(elementType->getStructName().str());

      //  Types in metaData

      std::string var_name = variable->getName().str() + "." + propertyName;
      llvm::Value *var = nullptr;

      if (_variableIsGlobal) {
        var = new llvm::GlobalVariable(
            *TheModule, elementType, false, llvm::GlobalValue::ExternalLinkage,
            llvm::Constant::getNullValue(elementType), var_name);
        objExpGenStrat->setVariable(var);
        objExpGenStrat->generateGlobalExpression(objectExpression);
      } else {
        var = Builder->CreateAlloca(elementType, nullptr, var_name);
        _codeGenerationContext->getAllocaChain()->setAllocaInst(
            var_name, llvm::cast<llvm::AllocaInst>(var));
        objExpGenStrat->setVariable(var);
        objExpGenStrat->generateExpression(objectExpression);
      }

      Builder->CreateStore(var, elementPtr);
    } else {
      rhs = _expressionGenerationFactory->createStrategy(bExpr->getKind())
                ->generateExpression(bExpr.get());

      if (!rhs) {
        _codeGenerationContext->getLogger()->LogError(
            "Property " + std::any_cast<std::string>(bLitExpr->getValue()) +
            " not found in type " + typeName);
        return nullptr;
      }

      if (_codeGenerationContext->getMapper()->isPrimitiveType(
              rhs->getType()) &&
          _codeGenerationContext->getMapper()->isPrimitiveType(
              structType->getElementType(index)) &&
          rhs->getType() != structType->getElementType(index)) {
        _codeGenerationContext->getLogger()->LogError(
            "Type of property " +
            std::any_cast<std::string>(bLitExpr->getValue()) +
            " does not match type in type " + typeName + " Expected " +
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
            " does not match type in type " + typeName + "Expected " +
            Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
                structType->getElementType(index))) +
            " but got " +
            Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
                rhs->getType())));

        return nullptr;
      }

      Builder->CreateStore(rhs, elementPtr);
    }
  }

  return nullptr;
}