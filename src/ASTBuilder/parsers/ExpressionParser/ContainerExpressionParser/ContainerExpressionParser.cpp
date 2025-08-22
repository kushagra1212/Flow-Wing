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

#include "ContainerExpressionParser.h"
#include "src/ASTBuilder/CodeFormatter/CodeFormatter.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/expression/ContainerExpressionSyntax/ContainerExpressionSyntax.h"

std::unique_ptr<ExpressionSyntax>
ContainerExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<ContainerExpressionSyntax> containerExpression =
      std::make_unique<ContainerExpressionSyntax>();

  ctx->setIsInsideContainerExpression(true);

  containerExpression->setOpenBracketToken(
      ctx->match(SyntaxKindUtils::SyntaxKind::OpenBracketToken));

  while (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseBracketToken &&
         ctx->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
    std::unique_ptr<ExpressionSyntax> expression = nullptr;

    if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::OpenBracketToken) {
      expression = this->parseExpression(ctx);
    } else {
      expression = PrecedenceAwareExpressionParser::parse(ctx);
    }

    containerExpression->setElement(std::move(expression));

    if (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseBracketToken) {
      ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken);
      ctx->getCodeFormatterRef()->appendWithSpace();
    }
  }

  containerExpression->setCloseBracketToken(
      ctx->match(SyntaxKindUtils::SyntaxKind::CloseBracketToken));

  ctx->setIsInsideContainerExpression(false);

  return containerExpression;
}