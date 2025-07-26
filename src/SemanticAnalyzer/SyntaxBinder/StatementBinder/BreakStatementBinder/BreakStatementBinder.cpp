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

#include "BreakStatementBinder.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundBreakStatement/BoundBreakStatement.h"
#include "src/SemanticAnalyzer/SyntaxBinder/SyntaxBinderContext/SyntaxBinderContext.h"
#include "src/diagnostics/Diagnostic/Diagnostic.h"
#include "src/diagnostics/Diagnostic/DiagnosticCodeData.h"
#include "src/syntax/statements/BreakStatementSyntax/BreakStatementSyntax.h"

std::unique_ptr<BoundStatement>
BreakStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                    StatementSyntax *statement) {
  BreakStatementSyntax *breakStatement =
      static_cast<BreakStatementSyntax *>(statement);

  if (!ctx->getRootRef()->isBreakable()) {
    ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic, {},
        Utils::getSourceLocation(breakStatement->getBreakKeywordPtr().get()),
        FLOW_WING::DIAGNOSTIC::DiagnosticCode::InvalidBreakStatementUsage));
  }
  return std::make_unique<BoundBreakStatement>(
      breakStatement->getSourceLocation());
}
