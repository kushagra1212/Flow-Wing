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


#include "BracketedExpressionBinder.h"
#include "../../../../diagnostics/Diagnostic/DiagnosticCodeData.h"
#include <memory>

std::unique_ptr<BoundExpression>
BracketedExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                          ExpressionSyntax *expression) {
  BracketedExpressionSyntax *bracketedExpression =
      static_cast<BracketedExpressionSyntax *>(expression);

  SyntaxKindUtils::SyntaxKind kind =
      bracketedExpression->getExpressionRef()->getKind();

  std::unique_ptr<BoundBracketedExpression> boundBracketedExpression =
      std::make_unique<BoundBracketedExpression>(
          bracketedExpression->getSourceLocation());

  switch (kind) {
  case SyntaxKindUtils::SyntaxKind::ContainerExpression:
  case SyntaxKindUtils::SyntaxKind::FillExpression: {
    boundBracketedExpression->setExpression(
        std::move(ExpressionBinderFactory::create(
                      bracketedExpression->getExpressionRef()->getKind())
                      ->bindExpression(
                          ctx, bracketedExpression->getExpressionRef().get())));
    break;
  }

  default: {
    ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic, {},
        bracketedExpression->getSourceLocation(),
        FLOW_WING::DIAGNOSTIC::DiagnosticCode::InvalidBracketedExpression));
    break;
  }
  }

  return std::move(boundBracketedExpression);
}