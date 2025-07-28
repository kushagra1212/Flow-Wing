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

#include "SwitchStatementParser.h"
#include "src/ASTBuilder/CodeFormatter/CodeFormatter.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/ASTBuilder/parsers/StatementParser/CaseStatementParser/CaseStatementParser.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/statements/SwitchStatementSyntax/SwitchStatementSyntax.h"
#include <memory>

std::unique_ptr<StatementSyntax>
SwitchStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<SwitchStatementSyntax> switchStatement =
      std::make_unique<SwitchStatementSyntax>();
  switchStatement->setSwitchToken(
      (ctx->match(SyntaxKindUtils::SyntaxKind::SwitchKeyword)));

  ctx->getCodeFormatterRef()->appendWithSpace();

  switchStatement->setSwitchExpression(
      PrecedenceAwareExpressionParser::parse(ctx));

  ctx->getCodeFormatterRef()->appendWithSpace();

  switchStatement->setOpenCurlyToken(
      ctx->match(SyntaxKindUtils::SyntaxKind::OpenBraceToken));

  ctx->getCodeFormatterRef()->appendNewLine();

  ctx->getCodeFormatterRef()->appendIndentAmount(TAB_SPACE);

  while (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseBraceToken &&
         ctx->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
    ctx->getCodeFormatterRef()->append(
        ctx->getCodeFormatterRef()->getIndentAmount());
    std::unique_ptr<CaseStatementSyntax> caseStatement(
        static_cast<CaseStatementSyntax *>(
            std::make_unique<CaseStatementParser>()
                ->parseStatement(ctx)
                .release()));

    switchStatement->addCaseStatement(std::move(caseStatement));
  }

  ctx->getCodeFormatterRef()->setIndentAmount(
      ctx->getCodeFormatterRef()->getIndentAmount().substr(
          0, ctx->getCodeFormatterRef()->getIndentAmount().length() -
                 (sizeof(TAB_SPACE) - 1)));
  switchStatement->setCloseCurlyToken(
      ctx->match(SyntaxKindUtils::SyntaxKind::CloseBraceToken));

  ctx->getCodeFormatterRef()->appendNewLine();

  return std::move(switchStatement);
}
