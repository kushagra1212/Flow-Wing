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

#include "ContinueStatementBinder.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundContinueStatement/BoundContinueStatement.h"
#include "src/SemanticAnalyzer/SyntaxBinder/SyntaxBinderContext/SyntaxBinderContext.h"
#include "src/diagnostics/Diagnostic/Diagnostic.h"
#include "src/diagnostics/Diagnostic/DiagnosticCodeData.h"
#include "src/syntax/statements/ContinueStatementSyntax/ContinueStatementSyntax.h"

std::unique_ptr<BoundStatement>
ContinueStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                       StatementSyntax *statement) {
  ContinueStatementSyntax *continueStatement =
      static_cast<ContinueStatementSyntax *>(statement);

  if (!ctx->getRootRef()->isContinuable()) {
    ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic, {},
        continueStatement->getSourceLocation(),
        FLOW_WING::DIAGNOSTIC::DiagnosticCode::ContinueStatementOutsideOfLoop));
  }
  return std::make_unique<BoundContinueStatement>(
      continueStatement->getSourceLocation());
}
