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

#include "IfStatementParser.h"
#include "src/ASTBuilder/CodeFormatter/CodeFormatter.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/ASTBuilder/parsers/StatementParser/BlockStatementParser/BlockStatementParser.h"
#include "src/ASTBuilder/parsers/StatementParser/ElseStatementParser/ElseStatementParser.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/statements/ElseClauseSyntax/ElseClauseSyntax.h"
#include "src/syntax/statements/IfStatementSyntax/IfStatementSyntax.h"
#include "src/syntax/statements/OrIfStatementSyntax/OrIfStatementSyntax.h"
#include <memory>

std::unique_ptr<StatementSyntax>
IfStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<IfStatementSyntax> ifStatement =
      std::make_unique<IfStatementSyntax>();

  std::unique_ptr<SyntaxToken<std::any>> keyword =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IfKeyword));
  ctx->getCodeFormatterRef()->appendWithSpace();

  std::unique_ptr<ExpressionSyntax> condition =
      std::move(PrecedenceAwareExpressionParser::parse(ctx));
  ctx->getCodeFormatterRef()->appendWithSpace();

  std::unique_ptr<BlockStatementSyntax> statement(
      static_cast<BlockStatementSyntax *>(
          std::make_unique<BlockStatementParser>()
              ->parseStatement(ctx)
              .release()));
  // appendNewLine();
  ifStatement->addIfKeyword(std::move(keyword));
  ifStatement->addCondition(std::move(condition));
  ifStatement->addStatement(std::move(statement));

  while (ctx->getKind() == SyntaxKindUtils::SyntaxKind::OrKeyword) {
    // _formattedSourceCode += INDENT;
    ctx->getCodeFormatterRef()->appendWithSpace();

    std::unique_ptr<SyntaxToken<std::any>> orKeyword =
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::OrKeyword));
    ctx->getCodeFormatterRef()->appendWithSpace();

    std::unique_ptr<SyntaxToken<std::any>> ifKeyword =
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IfKeyword));
    ctx->getCodeFormatterRef()->appendWithSpace();

    std::unique_ptr<ExpressionSyntax> condition =
        std::move(PrecedenceAwareExpressionParser::parse(ctx));
    ctx->getCodeFormatterRef()->appendWithSpace();

    std::unique_ptr<BlockStatementSyntax> statement(
        static_cast<BlockStatementSyntax *>(
            std::make_unique<BlockStatementParser>()
                ->parseStatement(ctx)
                .release()));
    // appendNewLine();

    ifStatement->addOrIfStatement(std::make_unique<OrIfStatementSyntax>(
        std::move(orKeyword), std::move(ifKeyword), std::move(condition),
        std::move(statement)));
  }
  std::unique_ptr<ElseClauseSyntax> elseClause = nullptr;

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::ElseKeyword) {
    // _formattedSourceCode += INDENT;
    ctx->getCodeFormatterRef()->appendWithSpace();
    elseClause = std::unique_ptr<ElseClauseSyntax>(
        static_cast<ElseClauseSyntax *>(std::make_unique<ElseStatementParser>()
                                            ->parseStatement(ctx)
                                            .release()));
  }

  ifStatement->addElseClause(std::move(elseClause));

  return std::move(ifStatement);
}
