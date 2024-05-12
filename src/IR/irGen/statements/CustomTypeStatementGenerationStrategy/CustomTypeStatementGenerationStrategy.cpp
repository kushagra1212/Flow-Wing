#include "CustomTypeStatementGenerationStrategy.h"

#include "../../expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

CustomTypeStatementGenerationStrategy::CustomTypeStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *CustomTypeStatementGenerationStrategy::generateStatement(
    BoundStatement *expression) {
  BoundCustomTypeStatement *boundCustomTypeStatement =
      static_cast<BoundCustomTypeStatement *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundCustomTypeStatement->getLocation());

  std::vector<llvm::Type *> structElements = {};
  size_t index = 0;
  llvm::StructType *structType = nullptr;

  for (auto &[boundLiteralExpression, bTE] :
       boundCustomTypeStatement->getKeyPairs()) {

    const std::string propertyName =
        std::any_cast<std::string>(boundLiteralExpression->getValue());

    llvm::Type *type = getType(bTE.get());

    const std::string key =
        boundCustomTypeStatement->getTypeNameAsString() + "." + propertyName;

    structElements.push_back(type);
    if (_isGlobal) {
      _codeGenerationContext->getTypeChain()->setGlobalIndex(key, index);
    } else {
      _codeGenerationContext->getTypeChain()->setIndex(key, index);
    }

    index++;
  }
  structType =
      llvm::StructType::create(*TheContext, structElements,
                               boundCustomTypeStatement->getTypeNameAsString());

  if (_isGlobal) {
    _codeGenerationContext->getTypeChain()->setGlobalType(
        boundCustomTypeStatement->getTypeNameAsString(), structType);

    _codeGenerationContext->getCustomTypeChain()->setGlobalExpr(
        boundCustomTypeStatement->getTypeNameAsString(),
        boundCustomTypeStatement);
  } else {
    _codeGenerationContext->getTypeChain()->setType(
        boundCustomTypeStatement->getTypeNameAsString(), structType);

    _codeGenerationContext->getCustomTypeChain()->setExpr(
        boundCustomTypeStatement->getTypeNameAsString(),
        boundCustomTypeStatement);
  }

  return nullptr;
}

llvm::Value *CustomTypeStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  _isGlobal = true;
  return this->generateStatement(statement);
}

llvm::Type *
CustomTypeStatementGenerationStrategy::getType(BoundTypeExpression *bTE) {

  switch (bTE->getKind()) {

  case BinderKindUtils::BoundTypeExpression: {
    return _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
        bTE->getSyntaxType());
  }
  case BinderKindUtils::BoundArrayTypeExpression: {
    BoundArrayTypeExpression *boundArrayTypeExpression =
        static_cast<BoundArrayTypeExpression *>(bTE);
    std::unique_ptr<LiteralExpressionGenerationStrategy>
        literalExpressionGenerationStrategy =
            std::make_unique<LiteralExpressionGenerationStrategy>(
                _codeGenerationContext);
    llvm::Type *elementType = nullptr;
    if (boundArrayTypeExpression->isTrivialType()) {
      elementType =
          _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
              boundArrayTypeExpression->getElementType());
    } else if (auto objectType = static_cast<BoundObjectTypeExpression *>(
                   boundArrayTypeExpression->getNonTrivialElementType()
                       .get())) {
      std::string typeName = _className != ""
                                 ? _className + "_:" + objectType->getTypeName()
                                 : objectType->getTypeName();

      elementType = _codeGenerationContext->getTypeChain()->getType(typeName);

      if (!elementType) {
        typeName = objectType->getTypeName();
        elementType = _codeGenerationContext->getTypeChain()->getType(typeName);
      }
    }
    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        boundArrayTypeExpression->getLocation());
    if (!elementType) {
      _codeGenerationContext->getLogger()->LogError(
          "Expected a array element type in custom type statement");
      return nullptr;
    }
    llvm::Type *arrayType = elementType;
    std::vector<uint64_t> dimensions(
        boundArrayTypeExpression->getDimensions().size(), 0);
    for (int64_t k = boundArrayTypeExpression->getDimensions().size() - 1;
         k >= 0; k--) {
      llvm::Value *arraySize =
          literalExpressionGenerationStrategy->generateExpression(
              boundArrayTypeExpression->getDimensions()[k].get());
      _codeGenerationContext->getLogger()->setCurrentSourceLocation(
          boundArrayTypeExpression->getDimensions()[k]->getLocation());

      if (!llvm::isa<llvm::ConstantInt>(arraySize)) {
        _codeGenerationContext->getLogger()->LogError(
            "Array size must be a constant integer");
      }

      dimensions[k] = llvm::cast<llvm::ConstantInt>(arraySize)->getSExtValue();

      arrayType = llvm::ArrayType::get(arrayType, dimensions[k]);
    }
    return arrayType;
  }
  case BinderKindUtils::BoundObjectTypeExpression: {
    BoundObjectTypeExpression *bOT =
        static_cast<BoundObjectTypeExpression *>(bTE);

    BoundLiteralExpression<std::any> *bLE =
        bOT->getObjectTypeIdentifier().get();

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        bOT->getLocation());
    std::string typeName =
        _className != ""
            ? _className + "_:" + std::any_cast<std::string>(bLE->getValue())
            : std::any_cast<std::string>(bLE->getValue());
    llvm::StructType *type =
        _codeGenerationContext->getTypeChain()->getType(typeName);
    if (!type) {
      typeName = std::any_cast<std::string>(bLE->getValue());
      type = _codeGenerationContext->getTypeChain()->getType(typeName);
    }

    if (!type) {
      _codeGenerationContext->getLogger()->LogError("Type " + typeName +
                                                    " is not defined");

      return nullptr;
    }
    return type;
    break;
  }
  default: {
    _codeGenerationContext->getLogger()->LogError(
        "Invalid type expression in type statement");

    return nullptr;
  }
  }
}

llvm::Value *CustomTypeStatementGenerationStrategy::generateForClassElement(
    BoundStatement *statement, std::string className) {
  _isGlobal = true;
  _className = className;
  return this->generateStatement(statement);
}

llvm::Type *CustomTypeStatementGenerationStrategy::getClassElementType(
    BoundTypeExpression *bTE, std::string className) {
  _className = className;

  return getType(bTE);
}