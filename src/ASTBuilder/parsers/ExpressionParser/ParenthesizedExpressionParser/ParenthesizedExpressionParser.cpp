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

#include "ParenthesizedExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/expression/ParenthesizedExpressionSyntax/ParenthesizedExpressionSyntax.h"

std::unique_ptr<ExpressionSyntax>
ParenthesizedExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<SyntaxToken<std::any>> left =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken));

  std::unique_ptr<ExpressionSyntax> expression =
      std::move(PrecedenceAwareExpressionParser::parse(ctx));

  std::unique_ptr<SyntaxToken<std::any>> right =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken));

  return std::make_unique<ParenthesizedExpressionSyntax>(
      std::move(left), std::move(expression), std::move(right));
}