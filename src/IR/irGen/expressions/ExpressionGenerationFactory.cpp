#include "ExpressionGenerationFactory.h"

#include "AssignmentExpressionGenerationStrategy/AssignmentExpressionGenerationStrategy.h"
#include "BinaryExpressionGenerationStrategy/BinaryExpressionGenerationStrategy.h"
#include "BracketedExpressionGenerationStrategy/BracketedExpressionGenerationStrategy.h"
#include "CallExpressionGenerationStrategy/CallExpressionGenerationStrategy.h"
#include "ContainerExpressionGenerationStrategy/ContainerExpressionGenerationStrategy.h"
#include "IndexExpressionGenerationStrategy/IndexExpressionGenerationStrategy.h"
#include "LiteralExpressionGenerationStrategy/LiteralExpressionGenerationStrategy.h"
#include "NirastExpressionGenerationStrategy/NirastExpressionGenerationStrategy.h"
#include "ParenthesizedExpressionGenerationStrategy/ParenthesizedExpressionGenerationStrategy.h"
#include "UnaryExpressionGenerationStrategy/UnaryExpressionGenerationStrategy.h"
#include "VariableExpressionGenerationStrategy/VariableExpressionGenerationStrategy.h"

ExpressionGenerationFactory::ExpressionGenerationFactory(
    CodeGenerationContext *context)
    : _codeGenerationContext(context){};

std::unique_ptr<ExpressionGenerationStrategy>
ExpressionGenerationFactory::createStrategy(
    BinderKindUtils::BoundNodeKind kind) {
  switch (kind) {
  case BinderKindUtils::BoundNodeKind::LiteralExpression:
    return std::make_unique<LiteralExpressionGenerationStrategy>(
        _codeGenerationContext);
  case BinderKindUtils::BoundNodeKind::UnaryExpression:
    return std::make_unique<UnaryExpressionGenerationStrategy>(
        _codeGenerationContext);
  case BinderKindUtils::BoundNodeKind::VariableExpression:
    return std::make_unique<VariableExpressionGenerationStrategy>(
        _codeGenerationContext);
  case BinderKindUtils::BoundNodeKind::AssignmentExpression:
    return std::make_unique<AssignmentExpressionGenerationStrategy>(
        _codeGenerationContext);
  case BinderKindUtils::BoundNodeKind::BinaryExpression:
    return std::make_unique<BinaryExpressionGenerationStrategy>(
        _codeGenerationContext);
  case BinderKindUtils::BoundNodeKind::ParenthesizedExpression:
    return std::make_unique<ParenthesizedExpressionGenerationStrategy>(
        _codeGenerationContext);
  case BinderKindUtils::BoundNodeKind::CallExpression:
    return std::make_unique<CallExpressionGenerationStrategy>(
        _codeGenerationContext);
  case BinderKindUtils::BoundNodeKind::IndexExpression:
    return std::make_unique<IndexExpressionGenerationStrategy>(
        _codeGenerationContext);
  case BinderKindUtils::BoundNodeKind::BoundBracketedExpression:
    return std::make_unique<BracketedExpressionGenerationStrategy>(
        _codeGenerationContext);
  case BinderKindUtils::BoundNodeKind::BoundNirastExpression:
    return std::make_unique<NirastExpressionGenerationStrategy>(
        _codeGenerationContext);

  default: {

    _codeGenerationContext->getLogger()->LogError(
        "Unsupported Expression Type ");
    return nullptr;
  }
  }
}
