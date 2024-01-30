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
        _codeGenerationContext->getLogger()->LogError("Not implemented yet");
        return nullptr;
      }
      case BinderKindUtils::BoundObjectTypeExpression: {
        // BoundObjectTypeExpression *bOT =
        //     static_cast<BoundObjectTypeExpression *>(bTE.get());

        // BoundLiteralExpression<std::any> *bLE =
        //     bOT->getObjectTypeIdentifier().get();

        // const std::string typeName =
        //     std::any_cast<std::string>(bLE->getValue());
        type = llvm::PointerType::get(*TheContext, 0);
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