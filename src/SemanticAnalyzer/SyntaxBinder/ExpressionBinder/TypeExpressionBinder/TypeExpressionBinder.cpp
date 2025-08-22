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

#include "TypeExpressionBinder.h"
#include "src/SemanticAnalyzer/SyntaxBinder/ExpressionBinder/ExpressionBinderFactory.h"
#include "src/SemanticAnalyzer/SyntaxBinder/SyntaxBinderContext/SyntaxBinderContext.h"
#include "src/diagnostics/Diagnostic/Diagnostic.h"
#include "src/diagnostics/Diagnostic/DiagnosticCodeData.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/expression/TypeExpressionSyntax/TypeExpressionSyntax.h"

std::unique_ptr<BoundExpression>
TypeExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                     ExpressionSyntax *expression) {

  TypeExpressionSyntax *typeExpressionSyntax =
      static_cast<TypeExpressionSyntax *>(expression);

  switch (typeExpressionSyntax->getKind()) {
  case SyntaxKindUtils::SyntaxKind::ArrayTypeExpression:
  case SyntaxKindUtils::SyntaxKind::PrimitiveTypeExpression:
  case SyntaxKindUtils::SyntaxKind::ObjectTypeExpression:
  case SyntaxKindUtils::SyntaxKind::FunctionTypeExpression: {
    return ExpressionBinderFactory::create(typeExpressionSyntax->getKind())
        ->bindExpression(ctx, typeExpressionSyntax);
  }
  default: {
    break;
  }
  }

  ctx->getDiagnosticHandler()->addDiagnostic(
      Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                 DiagnosticUtils::DiagnosticType::Semantic,
                 {std::to_string(typeExpressionSyntax->getKind())},
                 typeExpressionSyntax->getSourceLocation(),
                 FLOW_WING::DIAGNOSTIC::DiagnosticCode::InValidTypeExpression));

  return nullptr;
}