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

#include "CaseStatementParser.h"
#include "src/ASTBuilder/CodeFormatter/CodeFormatter.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/ASTBuilder/parsers/StatementParser/BlockStatementParser/BlockStatementParser.h"
#include "src/syntax/SyntaxKindUtils.h"

std::unique_ptr<StatementSyntax>
CaseStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<CaseStatementSyntax> caseStatement =
      std::make_unique<CaseStatementSyntax>();

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::DefaultKeyword) {
    caseStatement->setDefaultToken(
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::DefaultKeyword)));
  } else {
    caseStatement->setCaseToken(
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::CaseKeyword)));
    ctx->getCodeFormatterRef()->appendWithSpace();
    caseStatement->setCaseExpression(
        std::move(PrecedenceAwareExpressionParser::parse(ctx)));
  }
  ctx->getCodeFormatterRef()->appendWithSpace();
  caseStatement->setColonToken(
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken)));
  ctx->getCodeFormatterRef()->appendWithSpace();

  std::unique_ptr<BlockStatementSyntax> blockStatementSyntax(
      static_cast<BlockStatementSyntax *>(
          std::make_unique<BlockStatementParser>()
              ->parseStatement(ctx)
              .release()));

  caseStatement->setBlockStatement(std::move(blockStatementSyntax));
  ctx->getCodeFormatterRef()->appendNewLine();

  return std::move(caseStatement);
}
