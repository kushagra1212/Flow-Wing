/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "FunctionTypeExpressionBinder.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundTypeExpression/BoundFunctionTypeExpression/BoundFunctionTypeExpression.h"
#include "src/SemanticAnalyzer/SyntaxBinder/ExpressionBinder/ExpressionBinderFactory.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/TypeExpressionSyntax/FunctionTypeExpressionSyntax/FunctionTypeExpressionSyntax.h"
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