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


#include "ReturnStatementParser.h"

std::unique_ptr<StatementSyntax>
ReturnStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<SyntaxToken<std::any>> returnKeyword =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::ReturnKeyword));
  ctx->setIsInsideReturnStatement(true);
  std::unique_ptr<ReturnStatementSyntax> returnStatement =
      std::make_unique<ReturnStatementSyntax>(std::move(returnKeyword));

  auto parseStatementLambda = [&]() {
    do {

      if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken) {
        ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken);
        ctx->getCodeFormatterRef()->appendWithSpace();
      }

      std::unique_ptr<ExpressionSyntax> expression =
          std::move(PrecedenceAwareExpressionParser::parse(ctx));

      returnStatement->addReturnExpression(std::move(expression));

    } while (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken);
  };

  ctx->getCodeFormatterRef()->appendWithSpace();
  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::OpenParenthesisToken) {
    ctx->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken);
    ctx->getCodeFormatterRef()->appendWithSpace();
    parseStatementLambda();
    ctx->getCodeFormatterRef()->appendWithSpace();
    ctx->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken);

  } else if (ctx->getKind() != SyntaxKindUtils::SyntaxKind::ColonToken) {
    parseStatementLambda();
  } else {
    ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken);
  }

  ctx->setIsInsideReturnStatement(false);
  return std::move(returnStatement);
}
