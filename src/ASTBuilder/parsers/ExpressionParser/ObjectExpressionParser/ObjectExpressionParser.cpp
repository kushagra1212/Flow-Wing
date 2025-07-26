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

#include "ObjectExpressionParser.h"
#include "src/ASTBuilder/CodeFormatter/CodeFormatter.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/expression/LiteralExpressionSyntax/LiteralExpressionSyntax.h"

std::unique_ptr<ExpressionSyntax>
ObjectExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<ObjectExpressionSyntax> objES =
      std::make_unique<ObjectExpressionSyntax>();
  objES->setOpenBraceToken(
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::OpenBraceToken)));
  ctx->getCodeFormatterRef()->appendNewLine();

  ctx->getCodeFormatterRef()->appendIndentAmount(TAB_SPACE);

  while (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseBraceToken &&
         ctx->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {

    ctx->getCodeFormatterRef()->append(
        ctx->getCodeFormatterRef()->getIndentAmount());

    std::unique_ptr<SyntaxToken<std::any>> idenfierToken =
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

    std::any val = idenfierToken->getValue();

    std::unique_ptr<LiteralExpressionSyntax<std::any>> idenfierExp =
        std::make_unique<LiteralExpressionSyntax<std::any>>(
            std::move(idenfierToken), val);

    ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken);
    ctx->getCodeFormatterRef()->appendWithSpace();

    std::unique_ptr<ExpressionSyntax> expression =
        std::move(PrecedenceAwareExpressionParser::parse(ctx));

    objES->addAttribute(std::move(idenfierExp), std::move(expression));

    if (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseBraceToken) {
      ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken);
      ctx->getCodeFormatterRef()->appendNewLine();
    }
  }
  ctx->getCodeFormatterRef()->appendNewLine();

  ctx->getCodeFormatterRef()->setIndentAmount(
      ctx->getCodeFormatterRef()->getIndentAmount().substr(
          0, ctx->getCodeFormatterRef()->getIndentAmount().length() -
                 (sizeof(TAB_SPACE) - 1)));

  ctx->getCodeFormatterRef()->append(
      ctx->getCodeFormatterRef()->getIndentAmount());

  objES->setCloseBraceToken(
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::CloseBraceToken)));

  return std::move(objES);
}