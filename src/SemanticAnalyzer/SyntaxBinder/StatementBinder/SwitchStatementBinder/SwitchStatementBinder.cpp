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

#include "SwitchStatementBinder.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundSwitchStatement/BoundSwitchStatement.h"
#include "src/SemanticAnalyzer/SyntaxBinder/ExpressionBinder/ExpressionBinderFactory.h"
#include "src/SemanticAnalyzer/SyntaxBinder/StatementBinder/CaseStatementBinder/CaseStatementBinder.h"
#include "src/SemanticAnalyzer/SyntaxBinder/SyntaxBinderContext/SyntaxBinderContext.h"
#include "src/diagnostics/Diagnostic/Diagnostic.h"
#include "src/diagnostics/Diagnostic/DiagnosticCodeData.h"
#include "src/syntax/statements/SwitchStatementSyntax/SwitchStatementSyntax.h"

std::unique_ptr<BoundStatement>
SwitchStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                     StatementSyntax *statement) {

  SwitchStatementSyntax *switchStatement =
      static_cast<SwitchStatementSyntax *>(statement);

  std::unique_ptr<BoundSwitchStatement> boundSwitchStatement =
      std::make_unique<BoundSwitchStatement>(
          switchStatement->getSourceLocation());

  boundSwitchStatement->setSwitchExpression(
      std::move(ExpressionBinderFactory::create(
                    switchStatement->getSwitchExpressionRef()->getKind())
                    ->bindExpression(
                        ctx, switchStatement->getSwitchExpressionRef().get())));

  std::unique_ptr<CaseStatementBinder> caseStatementBinder =
      std::make_unique<CaseStatementBinder>();

  for (auto &caseStatement : switchStatement->getCaseStatementsRef()) {
    std::unique_ptr<BoundCaseStatement> boundCaseStatement(
        static_cast<BoundCaseStatement *>(
            caseStatementBinder->bindStatement(ctx, caseStatement.get())
                .release()));

    boundSwitchStatement->addCaseStatement(std::move(boundCaseStatement));
  }

  if (boundSwitchStatement->getHasNoDefaultCase()) {
    ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic, {},
        switchStatement->getSourceLocation(),
        FLOW_WING::DIAGNOSTIC::DiagnosticCode::NoDefaultCaseInSwitchStatement));

    return std::move(boundSwitchStatement);
  }

  if (boundSwitchStatement->getHasMoreThanOneDefaultCase()) {
    ctx->getDiagnosticHandler()->addDiagnostic(
        Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic, {},
                   switchStatement->getSourceLocation(),
                   FLOW_WING::DIAGNOSTIC::DiagnosticCode::
                       MoreThanOneDefaultCaseInSwitchStatement));
    return std::move(boundSwitchStatement);
  }

  if (!boundSwitchStatement->getHasAtLeastOneCaseStatement()) {
    ctx->getDiagnosticHandler()->addDiagnostic(
        Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic, {},
                   switchStatement->getSourceLocation(),
                   FLOW_WING::DIAGNOSTIC::DiagnosticCode::
                       NoCaseStatementInSwitchStatement));

    return std::move(boundSwitchStatement);
  }

  return std::move(boundSwitchStatement);
}