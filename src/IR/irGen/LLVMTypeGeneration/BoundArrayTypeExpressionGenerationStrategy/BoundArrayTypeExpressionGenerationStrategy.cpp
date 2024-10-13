#include "BoundArrayTypeExpressionGenerationStrategy.h"

#include "../../../../SemanticAnalyzer/BoundExpressions/BoundTypeExpression/BoundObjectTypeExpression/BoundObjectTypeExpression.h"
#include "../../expressions/LiteralExpressionGenerationStrategy/LiteralExpressionGenerationStrategy.h"

llvm::Type *BoundArrayTypeExpressionGenerationStrategy::getType(
    BoundTypeExpression *expression) {
  BoundArrayTypeExpression *boundArrayTypeExpression =
      static_cast<BoundArrayTypeExpression *>(expression);
  std::unique_ptr<LiteralExpressionGenerationStrategy>
      literalExpressionGenerationStrategy =
          std::make_unique<LiteralExpressionGenerationStrategy>(
              _codeGenerationContext);
  llvm::Type *elementType = nullptr;
  if (boundArrayTypeExpression->isTrivialType()) {
    elementType = _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
        boundArrayTypeExpression->getElementType());
  } else if (auto objectType = static_cast<BoundObjectTypeExpression *>(
                 boundArrayTypeExpression->getNonTrivialElementType().get())) {
    elementType =
        _codeGenerationContext->getFlowWingType(objectType->getTypeName())
            .getStructType();
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
  for (int64_t k = boundArrayTypeExpression->getDimensions().size() - 1; k >= 0;
       k--) {
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
  ;
}