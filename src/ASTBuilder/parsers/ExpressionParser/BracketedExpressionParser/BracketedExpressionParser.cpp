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

#include "BracketedExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/ContainerExpressionParser/ContainerExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/FillExpressionParser/FillExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/BracketedExpressionSyntax/BracketedExpressionSyntax.h"
#include <memory>

std::unique_ptr<ExpressionSyntax>
BracketedExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<BracketedExpressionSyntax> bracketedExpression =
      std::make_unique<BracketedExpressionSyntax>();

  if (ctx->peek(1)->getKind() == SyntaxKindUtils::SyntaxKind::FillKeyword

      || ctx->peek(2)->getKind() == SyntaxKindUtils::SyntaxKind::FillKeyword) {

    bracketedExpression->setExpression(std::move(
        std::make_unique<FillExpressionParser>()->parseExpression(ctx)));

  } else {
    bracketedExpression->setExpression(std::move(
        std::make_unique<ContainerExpressionParser>()->parseExpression(ctx)));
  }

  return std::move(bracketedExpression);
}