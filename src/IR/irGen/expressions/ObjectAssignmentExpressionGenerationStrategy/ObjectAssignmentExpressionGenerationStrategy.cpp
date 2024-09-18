#include "ObjectAssignmentExpressionGenerationStrategy.h"

ObjectAssignmentExpressionGenerationStrategy::
    ObjectAssignmentExpressionGenerationStrategy(CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *ObjectAssignmentExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  return nullptr;
}

llvm::Value *
ObjectAssignmentExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  return this->generateExpression(expression);
}

llvm::Value *ObjectAssignmentExpressionGenerationStrategy::copyObject(
    llvm::StructType *parStructType, llvm::Value *lshPtr, llvm::Value *rhsPtr) {

  auto processKeyTypePairs = [&](auto &keyTypePairs) {
    unsigned long i = 0;
    for (const auto &[bLE, bTE] : keyTypePairs) {
      llvm::Value *LHSinnerElementPtr =
          Builder->CreateStructGEP(parStructType, lshPtr, i);
      llvm::Value *RHSinnerElementPtr =
          Builder->CreateStructGEP(parStructType, rhsPtr, i);
      llvm::Type *innerElementType = parStructType->getElementType(i);
      if (bTE->getSyntaxType() ==
          SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
        copyObject(llvm::cast<llvm::StructType>(innerElementType),
                   LHSinnerElementPtr, RHSinnerElementPtr);
      } else {
        llvm::Value *loadedRHS =
            Builder->CreateLoad(innerElementType, RHSinnerElementPtr);

        Builder->CreateStore(loadedRHS, LHSinnerElementPtr);
      }
      i++;
    }
  };

  std::string typeName = parStructType->getStructName().str();

  if (_codeGenerationContext->isValidClassType(parStructType)) {
    processKeyTypePairs(
        _codeGenerationContext->_classTypes[typeName]->getKeyTypePairs());
  } else {
    processKeyTypePairs(_codeGenerationContext->getFlowWingType(typeName)
                            .getCustomType()
                            ->getKeyPairs());
  }

  return nullptr;
}

llvm::Value *ObjectAssignmentExpressionGenerationStrategy::assignObject(
    BoundObjectExpression *parObjectExpression, llvm::Value *variable,
    llvm::StructType *parStructType, std::string lhsVarName) {

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      parObjectExpression->getLocation());

  std::string typeName = parStructType->getStructName().str();

  std::unordered_map<std::string, BoundTypeExpression *> propertiesMap;
  std::unordered_map<std::string, unsigned long> propertiesMapIndexed;

  unsigned long index = 0;

  const std::string KEY_PRIFIX = typeName.substr(0, typeName.find("."));
  if (_codeGenerationContext->isValidClassType(parStructType)) {
    for (const auto &[bLitExpr, bExpr] :
         _codeGenerationContext->_classTypes[Utils::getActualTypeName(typeName)]
             ->getKeyTypePairs()) {
      std::string propertyName =
          KEY_PRIFIX + "." + std::any_cast<std::string>(bLitExpr->getValue());
      propertiesMap[propertyName] = bExpr;
      propertiesMapIndexed[propertyName] = index;
      index++;
    }
  } else {
    BoundCustomTypeStatement *boundCustomTypeStatement =
        _codeGenerationContext->getFlowWingType(typeName).getCustomType();
    for (const auto &[bLitExpr, bExpr] :
         boundCustomTypeStatement->getKeyPairs()) {
      std::string propertyName =
          KEY_PRIFIX + "." + std::any_cast<std::string>(bLitExpr->getValue());

      propertiesMap[propertyName] = bExpr.get();
      propertiesMapIndexed[propertyName] = index;
      index++;
    }
  }

  for (const auto &[bLitExpr, bExpr] :
       parObjectExpression->getKeyValuePairs()) {
    std::string propertyName =
        KEY_PRIFIX + "." + std::any_cast<std::string>(bLitExpr->getValue());
    unsigned long indexValue = propertiesMapIndexed[propertyName];
    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        bLitExpr->getLocation());

    if (propertiesMap.find(propertyName) == propertiesMap.end()) {
      _codeGenerationContext->getLogger()->LogError(
          "Property " + propertyName + " not found in type " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(parStructType));
      return nullptr;
    }

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        bExpr->getLocation());

    llvm::Value *innerElementPtr =
        Builder->CreateStructGEP(parStructType, variable, indexValue);

    _codeGenerationContext->getValueStackHandler()->popAll();
    if (propertiesMap[propertyName]->getSyntaxType() ==
            SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE &&
        bExpr->getKind() == BinderKindUtils::BoundObjectExpression) {
      BoundObjectExpression *innerObjectExpression =
          static_cast<BoundObjectExpression *>(bExpr.get());

      llvm::StructType *innerElementType = llvm::cast<llvm::StructType>(
          parStructType->getElementType(indexValue));

      this->assignObject(innerObjectExpression, innerElementPtr,
                         innerElementType, propertyName);
    } else {
      std::unique_ptr<AssignmentExpressionGenerationStrategy> assignmentEGS =
          std::make_unique<AssignmentExpressionGenerationStrategy>(
              _codeGenerationContext);

      std::unique_ptr<CustomTypeStatementGenerationStrategy> customTypeEGS =
          std::make_unique<CustomTypeStatementGenerationStrategy>(
              _codeGenerationContext);

      if (bExpr->getKind() == BinderKindUtils::CallExpression) {
        BoundCallExpression *innerCallExpression =
            static_cast<BoundCallExpression *>(bExpr.get());

        innerCallExpression->setArgumentAlloca(
            0., {innerElementPtr, parStructType->getElementType(indexValue)});
      }

      assignmentEGS->handleAssignExpression(
          innerElementPtr, parStructType->getElementType(indexValue),
          propertyName, bExpr.get());
    }
    indexValue++;
  }

  return nullptr;
}