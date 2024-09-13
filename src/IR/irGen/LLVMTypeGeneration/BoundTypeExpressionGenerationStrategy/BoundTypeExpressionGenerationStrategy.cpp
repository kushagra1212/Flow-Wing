#include "BoundTypeExpressionGenerationStrategy.h"

llvm::Type *BoundTypeExpressionGenerationStrategy::getType(
    BoundTypeExpression *expression) {
  return _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
      expression->getSyntaxType());
}