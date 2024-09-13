#include "LLVMTypeGenerationFactory.h"

#include "BoundArrayTypeExpressionGenerationStrategy/BoundArrayTypeExpressionGenerationStrategy.h"
#include "BoundFunctionTypeExpressionGenerationStrategy/BoundFunctionTypeExpressionGenerationStrategy.h"
#include "BoundObjectTypeExpressionGenerationStrategy/BoundObjectTypeExpressionGenerationStrategy.h"
#include "BoundTypeExpressionGenerationStrategy/BoundTypeExpressionGenerationStrategy.h"

LLVMTypeGenerationFactory::LLVMTypeGenerationFactory(
    CodeGenerationContext *context)
    : _codeGenerationContext(context) {}

std::unique_ptr<LLVMTypeGenerationStrategy>
LLVMTypeGenerationFactory::createStrategy(BinderKindUtils::BoundNodeKind kind) {
  switch (kind) {
    case BinderKindUtils::BoundNodeKind::BoundTypeExpression:
      return std::make_unique<BoundTypeExpressionGenerationStrategy>(
          _codeGenerationContext);

    case BinderKindUtils::BoundNodeKind::BoundArrayTypeExpression:
      return std::make_unique<BoundArrayTypeExpressionGenerationStrategy>(
          _codeGenerationContext);

    case BinderKindUtils::BoundNodeKind::BoundObjectTypeExpression:
      return std::make_unique<BoundObjectTypeExpressionGenerationStrategy>(
          _codeGenerationContext);

    case BinderKindUtils::BoundNodeKind::BoundFunctionTypeExpression:
      return std::make_unique<BoundFunctionTypeExpressionGenerationStrategy>(
          _codeGenerationContext);

    default:
      _codeGenerationContext->getLogger()->LogError(
          "Unsupported Expression Type ");
      return nullptr;
  }
}