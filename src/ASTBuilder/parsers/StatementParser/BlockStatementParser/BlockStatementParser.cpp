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

#include "BlockStatementParser.h"
#include "src/ASTBuilder/CodeFormatter/CodeFormatter.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/statements/StatementSyntax.h"

std::unique_ptr<StatementSyntax>
BlockStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<BlockStatementSyntax> blockStatement =
      std::make_unique<BlockStatementSyntax>();

  std::unique_ptr<SyntaxToken<std::any>> openBraceToken =
      ctx->match(SyntaxKindUtils::SyntaxKind::OpenBraceToken);
  ctx->getCodeFormatterRef()->appendNewLine();

  blockStatement->setOpenBraceToken(std::move(openBraceToken));

  std::vector<std::unique_ptr<StatementSyntax>> statements;
  ctx->getCodeFormatterRef()->appendIndentAmount(TAB_SPACE);

  while (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseBraceToken &&
         ctx->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {

    ctx->getCodeFormatterRef()->append(
        ctx->getCodeFormatterRef()->getIndentAmount());

    SyntaxKindUtils::SyntaxKind currentKind = ctx->getKind();

    if (currentKind == SyntaxKindUtils::SyntaxKind::ExposeKeyword) {
      currentKind = ctx->peek(1)->getKind();
    }

    blockStatement->addStatement(
        StatementParserFactory::createStatementParser(currentKind)
            ->parseStatement(ctx));

    ctx->getCodeFormatterRef()->appendNewLine();
  }
  ctx->getCodeFormatterRef()->setIndentAmount(
      ctx->getCodeFormatterRef()->getIndentAmount().substr(
          0, ctx->getCodeFormatterRef()->getIndentAmount().length() -
                 (sizeof(TAB_SPACE) - 1)));

  ctx->getCodeFormatterRef()->append(
      ctx->getCodeFormatterRef()->getIndentAmount());

  std::unique_ptr<SyntaxToken<std::any>> closeBraceToken =
      ctx->match(SyntaxKindUtils::SyntaxKind::CloseBraceToken);

  blockStatement->setCloseBraceToken(std::move(closeBraceToken));

  return blockStatement;
}
