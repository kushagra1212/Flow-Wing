#include "FunctionTypeExpressionBinder.h"
#include <memory>

std::unique_ptr<BoundExpression>
FunctionTypeExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                             ExpressionSyntax *expression) {

  FunctionTypeExpressionSyntax *functionTypeExpressionSyntax =
      static_cast<FunctionTypeExpressionSyntax *>(expression);

  std::unique_ptr<BoundFunctionTypeExpression> boundFunctionTypeExpression =
      std::make_unique<BoundFunctionTypeExpression>(
          functionTypeExpressionSyntax->getSourceLocation(),
          functionTypeExpressionSyntax->getTypeRef()->getKind());

  for (const auto &param :
       functionTypeExpressionSyntax->getParameterTypesRef()) {
    std::unique_ptr<BoundTypeExpression> boundTypeExpr(
        static_cast<BoundTypeExpression *>(
            ExpressionBinderFactory::create(param->getKind())
                ->bindExpression(ctx, param.get())
                .release()));

    boundFunctionTypeExpression->addParameterType(std::move(boundTypeExpr));
    boundFunctionTypeExpression->addAsParam(false);
  }

  if (functionTypeExpressionSyntax->getAsKeywordRef()) {
    boundFunctionTypeExpression->setHasAsReturnType(true);
  }

  for (const auto &asType :
       functionTypeExpressionSyntax->getAsParametersKeywordsRef()) {
    boundFunctionTypeExpression->setAsParam(asType.first, true);
  }

  for (const auto &retType :
       functionTypeExpressionSyntax->getReturnTypesRef()) {

    std::unique_ptr<BoundTypeExpression> boundTypeExpr(
        static_cast<BoundTypeExpression *>(
            ExpressionBinderFactory::create(retType->getKind())
                ->bindExpression(ctx, retType.get())
                .release()));

    boundFunctionTypeExpression->addReturnType(std::move(boundTypeExpr));
  }

  return std::move(boundFunctionTypeExpression);
}