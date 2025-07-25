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


#include "ObjectTypeExpressionBinder.h"
#include "../../../../../diagnostics/Diagnostic/DiagnosticCodeData.h"
#include <memory>

std::unique_ptr<BoundExpression>
ObjectTypeExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                           ExpressionSyntax *expression) {

  ObjectTypeExpressionSyntax *objectTypeExpressionSyntax =
      static_cast<ObjectTypeExpressionSyntax *>(expression);

  std::unique_ptr<BoundObjectTypeExpression> boundObjectTypeExpression =
      std::make_unique<BoundObjectTypeExpression>(
          objectTypeExpressionSyntax->getSourceLocation(),
          objectTypeExpressionSyntax->getTypeRef()->getKind());

  std::unique_ptr<BoundLiteralExpression<std::any>> oLitExpr(
      static_cast<BoundLiteralExpression<std::any> *>(
          ExpressionBinderFactory::create(
              objectTypeExpressionSyntax->getObjectTypeIdentifierRef()
                  ->getKind())
              ->bindExpression(
                  ctx, objectTypeExpressionSyntax->getObjectTypeIdentifierRef()
                           .get())
              .release()));

  boundObjectTypeExpression->setObjectTypeIdentifier(std::move(oLitExpr));

  std::string name = objectTypeExpressionSyntax->getObjectTypeIdentifierRef()
                         ->getTokenPtr()
                         ->getText();

  //! Verify if this is a class or object type
  boundObjectTypeExpression->setTypeName(name);

  //? name -> class Type or Object Type

  BoundCustomTypeStatement *bCT = ctx->getRootRef()->tryGetCustomType(name);
  BINDER_DEBUG_LOG("CURRENT_MODULE_NAME: " + name);

  if (!bCT && !ctx->getRootRef()->tryGetClass(name)) {
    ctx->getDiagnosticHandler()->addDiagnostic(
        Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic, {name},
                   objectTypeExpressionSyntax->getObjectTypeIdentifierRef()
                       ->getTokenPtr()
                       ->getSourceLocation(),
                   FLOW_WING::DIAGNOSTIC::DiagnosticCode::TypeOrClassNotFound));

    return std::move(boundObjectTypeExpression);
  }

  if (bCT) {
    std::unique_ptr<BoundLiteralExpression<std::any>> oLitExpr(
        static_cast<BoundLiteralExpression<std::any> *>(
            ExpressionBinderFactory::create(

                objectTypeExpressionSyntax->getObjectTypeIdentifierRef()
                    ->getKind())
                ->bindExpression(ctx, objectTypeExpressionSyntax
                                          ->getObjectTypeIdentifierRef()
                                          .get())
                .release()));

    boundObjectTypeExpression->setObjectTypeIdentifier(std::move(oLitExpr));

    boundObjectTypeExpression->setTypeName(bCT->getTypeNameAsString());
  }

  return std::move(boundObjectTypeExpression);
}