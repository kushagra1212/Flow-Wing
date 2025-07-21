#include "utility.h"

namespace ExpressionSupport {

llvm::Value *getExpressionValue(CodeGenerationContext *context,
                                BoundExpression *expression, bool &isClassType,
                                int8_t &isDynamicValue) {

  context->getValueStackHandler()->popAll();

  std::unique_ptr<ExpressionGenerationFactory> expressionGenerationFactory =
      std::make_unique<ExpressionGenerationFactory>(context);

  llvm::Value *value =
      expressionGenerationFactory->createStrategy(expression->getKind())
          ->generateExpression(expression);

  if (context->getValueStackHandler()->isDynamicValueType()) {
    isDynamicValue = 1;
  }

  if (context->getValueStackHandler()->isStructType()) {
    if (!context->isValidClassType(llvm::cast<llvm::StructType>(
            context->getValueStackHandler()->getLLVMType()))) {
      context->getLogger()->LogError("Operation is not supported for objects");
      return nullptr;
    }
    value = context->getBuilder()->CreateLoad(
        llvm::Type::getInt8PtrTy(*context->getContext()),
        context->getValueStackHandler()->getValue());
    isClassType = true;
  }

  if (context->getValueStackHandler()->isPrimaryType()) {
    value = context->getBuilder()->CreateLoad(
        context->getValueStackHandler()->getLLVMType(),
        context->getValueStackHandler()->getValue());
  }

  if (context->getValueStackHandler()->isLLVMConstant()) {
    value = context->getValueStackHandler()->getValue();
  }

  context->getValueStackHandler()->popAll();

  return value;
}
} // namespace ExpressionSupport