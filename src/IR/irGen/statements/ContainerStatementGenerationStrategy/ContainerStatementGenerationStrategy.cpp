#include "ContainerStatementGenerationStrategy.h"

#include "../../expressions/BracketedExpressionGenerationStrategy/BracketedExpressionGenerationStrategy.h"
#include "../../expressions/ContainerExpressionGenerationStrategy/ContainerExpressionGenerationStrategy.h"
#include "../../expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"
#include "../../expressions/FillExpressionGenerationStrategy/FillExpressionGenerationStrategy.h"

ContainerStatementGenerationStrategy::ContainerStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *ContainerStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {

  auto containerStatement = static_cast<BoundContainerStatement *>(statement);
  const Utils::type &containerElementType =
      containerStatement->getContainerTypeRef();
  std::vector<uint64_t> actualSizes =
      this->getActualContainerSize(containerStatement);
  const std::string &containerName = containerStatement->getVariableNameRef();

  llvm::Type *elementType =
      _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
          Utils::toContainerElementType(containerElementType));
  if (containerElementType == Utils::type::UNKNOWN_CONTAINER) {
    _codeGenerationContext->getLogger()->LogError(
        "Container of dynamic type is not supported");

    elementType = _codeGenerationContext->getDynamicType()->get();
  }

  BoundBracketedExpression *bracketedExpression =
      static_cast<BoundBracketedExpression *>(
          containerStatement->getBracketedExpressionRef().get());

  BinderKindUtils::BoundNodeKind bracketedExpressionKind =
      bracketedExpression->getExpressionRef().get()->getKind();

  switch (bracketedExpressionKind) {

  case BinderKindUtils::BoundNodeKind::BoundContainerExpression: {

    std::unique_ptr<ContainerExpressionGenerationStrategy> specificStrategy =
        std::make_unique<ContainerExpressionGenerationStrategy>(
            _codeGenerationContext, actualSizes, elementType, containerName);

    return specificStrategy->generateExpression(
        bracketedExpression->getExpressionRef().get());
  }

  case BinderKindUtils::BoundNodeKind::BoundFillExpression: {

    std::unique_ptr<FillExpressionGenerationStrategy> specificStrategy =
        std::make_unique<FillExpressionGenerationStrategy>(
            _codeGenerationContext, actualSizes, elementType, containerName);

    return specificStrategy->generateExpression(
        bracketedExpression->getExpressionRef().get());
  }

  default: {
    _codeGenerationContext->getLogger()->LogError(
        "Unsupported Container Expression Type ");
    break;
  }
  }

  return nullptr;
}

llvm::Value *ContainerStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {

  auto containerStatement = static_cast<BoundContainerStatement *>(statement);
  const Utils::type &containerElementType =
      containerStatement->getContainerTypeRef();
  std::vector<uint64_t> actualSizes =
      this->getActualContainerSize(containerStatement);
  const std::string &containerName = containerStatement->getVariableNameRef();

  llvm::Type *elementType =
      _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
          Utils::toContainerElementType(containerElementType));

  if (containerElementType == Utils::type::UNKNOWN_CONTAINER) {
    _codeGenerationContext->getLogger()->LogError(
        "Container of dynamic type is not supported");
    return nullptr;
  }

  BoundBracketedExpression *bracketedExpression =
      static_cast<BoundBracketedExpression *>(
          containerStatement->getBracketedExpressionRef().get());

  BinderKindUtils::BoundNodeKind bracketedExpressionKind =
      bracketedExpression->getExpressionRef().get()->getKind();

  switch (bracketedExpressionKind) {

  case BinderKindUtils::BoundNodeKind::BoundContainerExpression: {

    std::unique_ptr<ContainerExpressionGenerationStrategy> specificStrategy =
        std::make_unique<ContainerExpressionGenerationStrategy>(
            _codeGenerationContext, actualSizes, elementType, containerName);

    return specificStrategy->generateGlobalExpression(
        bracketedExpression->getExpressionRef().get());
  }

  case BinderKindUtils::BoundNodeKind::BoundFillExpression: {

    std::unique_ptr<FillExpressionGenerationStrategy> specificStrategy =
        std::make_unique<FillExpressionGenerationStrategy>(
            _codeGenerationContext, actualSizes, elementType, containerName);

    return specificStrategy->generateGlobalExpression(
        bracketedExpression->getExpressionRef().get());
  }

  default: {
    _codeGenerationContext->getLogger()->LogError(
        "Unsupported Container Expression Type ");
    break;
  }
  }

  return nullptr;
}

std::vector<uint64_t>
ContainerStatementGenerationStrategy::getActualContainerSize(
    BoundContainerStatement *containerStatement) {

  std::vector<uint64_t> actualSizes;

  for (uint64_t i = 0;
       i < containerStatement->getContainerSizeExpressions().size(); i++) {
    llvm::Value *sizeValue =
        _expressionGenerationFactory
            ->createStrategy(
                containerStatement->getContainerSizeExpressions()[i]
                    .get()
                    ->getKind())
            ->generateExpression(
                containerStatement->getContainerSizeExpressions()[i].get());

    llvm::ConstantInt *sizeConstInt =
        llvm::dyn_cast<llvm::ConstantInt>(sizeValue);
    if (!sizeConstInt) {
      _codeGenerationContext->getLogger()->LogError(
          "Container size must be an integer");
      return {};
    }

    actualSizes.push_back(sizeConstInt->getZExtValue());
  }

  return actualSizes;
}
