
#include "BoundObjectTypeExpressionGenerationStrategy.h"

llvm::Type *BoundObjectTypeExpressionGenerationStrategy::getType(
    BoundTypeExpression *expression) {
  BoundObjectTypeExpression *objectTypeExpression =
      static_cast<BoundObjectTypeExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      objectTypeExpression->getLocation());

  llvm::StructType *structType =
      _codeGenerationContext
          ->_classLLVMTypes[objectTypeExpression->getTypeName()];

  std::string typeName = "";
  if (!structType) {
    typeName = objectTypeExpression->getTypeName();

    structType =
        _codeGenerationContext->getFlowWingType(typeName).getStructType();
    if (!structType) {
      _codeGenerationContext->getLogger()->LogError(
          "Expected an object type " + Utils::getActualTypeName(typeName) +
          " but, got " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(structType));
      return nullptr;
    }
  }

  return structType;
}