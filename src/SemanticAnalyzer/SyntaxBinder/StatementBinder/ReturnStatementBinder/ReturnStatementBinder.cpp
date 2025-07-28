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

#include "ReturnStatementBinder.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundReturnStatement/BoundReturnStatement.h"
#include "src/SemanticAnalyzer/SyntaxBinder/ExpressionBinder/ExpressionBinder.h"
#include "src/SemanticAnalyzer/SyntaxBinder/ExpressionBinder/ExpressionBinderFactory.h"
#include "src/SemanticAnalyzer/SyntaxBinder/SyntaxBinderContext/SyntaxBinderContext.h"
#include "src/diagnostics/Diagnostic/Diagnostic.h"
#include "src/diagnostics/Diagnostic/DiagnosticCodeData.h"
#include "src/diagnostics/DiagnosticUtils/DiagnosticLevel.h"
#include "src/diagnostics/DiagnosticUtils/DiagnosticType.h"
#include "src/syntax/statements/ReturnStatementSyntax/ReturnStatementSyntax.h"

std::unique_ptr<BoundStatement>
ReturnStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                     StatementSyntax *statement) {

  ReturnStatementSyntax *returnStatement =
      static_cast<ReturnStatementSyntax *>(statement);

  std::unique_ptr<BoundReturnStatement> boundRetExpression =
      std::make_unique<BoundReturnStatement>(
          returnStatement->getSourceLocation());

  if (!ctx->getRootRef()->isInFunction()) {
    ctx->getDiagnosticHandler()->addDiagnostic(
        Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic, {},
                   returnStatement->getSourceLocation(),
                   FLOW_WING::DIAGNOSTIC::DiagnosticCode::
                       ReturnStatementOutsideOfFunction));
  } else {
    // TODO IMPLEMENT all Expression

    for (const auto &expr : returnStatement->getReturnExpressionListRef()) {
      boundRetExpression->addReturnExpression(
          (ExpressionBinderFactory::create(expr->getKind())
               ->bindExpression(ctx, expr.get())));
    }
  }

  return std::move(boundRetExpression);
}
