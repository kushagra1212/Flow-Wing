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

#include "PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/CodeFormatter/CodeFormatter.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrimaryExpressionParserFactory.h"
#include "src/ASTBuilder/parsers/ExpressionParser/TernaryExpressionParser/TernaryExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/expression/BinaryExpressionSyntax/BinaryExpressionSyntax.h"
#include "src/syntax/expression/TernaryExpressionSyntax/TernaryExpressionSyntax.h"
#include "src/syntax/expression/UnaryExpressionSyntax/UnaryExpressionSyntax.h"

std::unique_ptr<ExpressionSyntax>
PrecedenceAwareExpressionParser::parse(ParserContext *ctx,
                                       int parentPrecedence) {
  std::unique_ptr<ExpressionSyntax> left = nullptr;
  int unaryOperatorPrecedence = ctx->getCurrent()->getUnaryOperatorPrecedence();

  if (unaryOperatorPrecedence != 0 &&
      unaryOperatorPrecedence >= parentPrecedence) {
    std::unique_ptr<SyntaxToken<std::any>> operatorToken =
        ctx->match(ctx->getKind());
    std::unique_ptr<ExpressionSyntax> operand =
        PrecedenceAwareExpressionParser::parse(ctx, unaryOperatorPrecedence);
    left = std::make_unique<UnaryExpressionSyntax>(std::move(operatorToken),
                                                   std::move(operand));

  } else {
    left = PrimaryExpressionParserFactory::createPrimaryExpressionParser(
               ctx->getKind())
               ->parseExpression(ctx);
  }

  while (true) {
    int precedence = ctx->getCurrent()->getBinaryOperatorPrecedence();
    if (precedence == 0 || precedence <= parentPrecedence) {
      break;
    }
    ctx->getCodeFormatterRef()->appendWithSpace();
    std::unique_ptr<SyntaxToken<std::any>> operatorToken =
        ctx->match(ctx->getKind());
    ctx->getCodeFormatterRef()->appendWithSpace();

    std::unique_ptr<ExpressionSyntax> right =
        PrecedenceAwareExpressionParser::parse(ctx, precedence);

    left = std::make_unique<BinaryExpressionSyntax>(
        std::move(left), std::move(operatorToken), std::move(right));
  }

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::QuestionToken) {
    auto ternaryExpression =
        std::make_unique<TernaryExpressionParser>()->parseExpression(ctx);

    static_cast<TernaryExpressionSyntax *>(ternaryExpression.get())
        ->addConditionExpression(std::move(left));

    left = std::move(ternaryExpression);
  }

  return left;
}