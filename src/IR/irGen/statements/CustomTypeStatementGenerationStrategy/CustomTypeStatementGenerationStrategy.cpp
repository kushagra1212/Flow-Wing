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
    llvm::Type *type = nullptr;
    const std::string propertyName =
        std::any_cast<std::string>(boundLiteralExpression->getValue());

    switch (bTE->getKind()) {
    case BinderKindUtils::BoundTypeExpression: {
      type = _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
          bTE->getSyntaxType());
      break;
    }
    case BinderKindUtils::BoundArrayTypeExpression: {
      BoundArrayTypeExpression *boundArrayTypeExpression =
          static_cast<BoundArrayTypeExpression *>(bTE.get());
      std::unique_ptr<LiteralExpressionGenerationStrategy>
          literalExpressionGenerationStrategy =
              std::make_unique<LiteralExpressionGenerationStrategy>(
                  _codeGenerationContext);

      llvm::Type *elementType =
          _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
              boundArrayTypeExpression->getElementType());

      llvm::Type *arrayType = elementType;
      std::vector<uint64_t> dimensions(
          boundArrayTypeExpression->getDimensions().size(), 0);
      for (int64_t k = boundArrayTypeExpression->getDimensions().size() - 1;
           k >= 0; k--) {
        llvm::Value *arraySize =
            literalExpressionGenerationStrategy->generateExpression(
                boundArrayTypeExpression->getDimensions()[k].get());

        if (!llvm::isa<llvm::ConstantInt>(arraySize)) {
          _codeGenerationContext->getLogger()->LogError(
              "Array size must be a constant integer");
        }

        dimensions[k] =
            llvm::cast<llvm::ConstantInt>(arraySize)->getSExtValue();

        arrayType = llvm::ArrayType::get(arrayType, dimensions[k]);
      }
      type = arrayType;
      break;
    }
    case BinderKindUtils::BoundObjectTypeExpression: {
      BoundObjectTypeExpression *bOT =
          static_cast<BoundObjectTypeExpression *>(bTE.get());

      BoundLiteralExpression<std::any> *bLE =
          bOT->getObjectTypeIdentifier().get();

      const std::string typeName = std::any_cast<std::string>(bLE->getValue());

      type = _codeGenerationContext->getTypeChain()->getType(typeName);
      break;
    }
    default: {
      _codeGenerationContext->getLogger()->LogError(
          "Invalid type expression in type statement");

      return nullptr;
    }
    }

    const std::string key =
        boundCustomTypeStatement->getTypeNameAsString() + "." + propertyName;

    structElements.push_back(type);
    _codeGenerationContext->getTypeChain()->setIndex(key, index);
    _codeGenerationContext->getTypeChain()->setElementType(key, type);

    index++;
  }
  structType =
      llvm::StructType::create(*TheContext, structElements,
                               boundCustomTypeStatement->getTypeNameAsString());

  _codeGenerationContext->getTypeChain()->setType(
      boundCustomTypeStatement->getTypeNameAsString(), structType);

  _codeGenerationContext->getCustomTypeChain()->setExpr(
      boundCustomTypeStatement->getTypeNameAsString(),
      boundCustomTypeStatement);

  return nullptr;
}

llvm::Value *CustomTypeStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  return this->generateStatement(statement);
}