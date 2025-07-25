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
#include "TernaryExpressionParser/TernaryExpressionParser.h"
#include <memory>

std::unique_ptr<ExpressionSyntax>
PrecedenceAwareExpressionParser::parse(ParserContext *ctx,
                                       const int &parentPrecedence) {
  std::unique_ptr<ExpressionSyntax> left = nullptr;
  size_t unaryOperatorPrecedence =
      ctx->getCurrent()->getUnaryOperatorPrecedence();

  if (unaryOperatorPrecedence != 0 &&
      unaryOperatorPrecedence >= parentPrecedence) {
    std::unique_ptr<SyntaxToken<std::any>> operatorToken =
        std::move(ctx->match(ctx->getKind()));
    std::unique_ptr<ExpressionSyntax> operand = std::move(
        PrecedenceAwareExpressionParser::parse(ctx, unaryOperatorPrecedence));
    left = std::make_unique<UnaryExpressionSyntax>(std::move(operatorToken),
                                                   std::move(operand));

  } else {
    left =
        std::move(PrimaryExpressionParserFactory::createPrimaryExpressionParser(
                      ctx->getKind()))
            ->parseExpression(ctx);
  }

  while (true) {
    int precedence = ctx->getCurrent()->getBinaryOperatorPrecedence();
    if (precedence == 0 || precedence <= parentPrecedence) {
      break;
    }
    ctx->getCodeFormatterRef()->appendWithSpace();
    std::unique_ptr<SyntaxToken<std::any>> operatorToken =
        std::move(ctx->match(ctx->getKind()));
    ctx->getCodeFormatterRef()->appendWithSpace();

    std::unique_ptr<ExpressionSyntax> right =
        std::move(PrecedenceAwareExpressionParser::parse(ctx, precedence));

    left = std::make_unique<BinaryExpressionSyntax>(
        std::move(left), std::move(operatorToken), std::move(right));
  }

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::QuestionToken) {
    auto ternaryExpression = std::move(
        std::make_unique<TernaryExpressionParser>()->parseExpression(ctx));

    static_cast<TernaryExpressionSyntax *>(ternaryExpression.get())
        ->addConditionExpression(std::move(left));

    left = std::move(ternaryExpression);
  }

  return std::move(left);
}