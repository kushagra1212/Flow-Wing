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

#include "ArrayTypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/TypeExpressionParser/ObjectTypeExpressionParser/ObjectTypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/TypeExpressionParser/PrimitiveTypeExpressionParser/PrimitiveTypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/common/constants/FlowWingUtilsConstants.h"
#include "src/diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/LiteralExpressionSyntax/LiteralExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/ArrayTypeExpressionSyntax/ArrayTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/ObjectTypeExpressionSyntax/ObjectTypeExpressionSyntax.h"
#include <memory>

std::unique_ptr<ExpressionSyntax>
ArrayTypeExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<ArrayTypeExpressionSyntax> arrayTypeExpression =
      std::make_unique<ArrayTypeExpressionSyntax>(
          std::make_unique<SyntaxToken<std::any>>(
              ctx->getDiagnosticHandler()->getAbsoluteFilePath(), 0,
              SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE, 0, "NBU_ARRAY_TYPE",
              "NBU_ARRAY_TYPE"));

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::IdentifierToken &&
      ctx->peek(1)->getKind() == SyntaxKindUtils::SyntaxKind::ColonToken &&
      ctx->peek(2)->getKind() == SyntaxKindUtils::SyntaxKind::ColonToken) {
    std::unique_ptr<SyntaxToken<std::any>> iden =
        ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken);

    ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken);
    ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken);

    std::unique_ptr<ObjectTypeExpressionSyntax> objectType(
        static_cast<ObjectTypeExpressionSyntax *>(
            std::make_unique<ObjectTypeExpressionParser>()
                ->parseExpression(ctx)
                .release()));

    objectType->getObjectTypeIdentifierRef()->getTokenPtr()->setValue(
        std::any_cast<std::string>(iden->getValue()) +
        FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX +
        std::any_cast<std::string>(objectType->getObjectTypeIdentifierRef()
                                       ->getTokenPtr()
                                       ->getValue()));
    objectType->getObjectTypeIdentifierRef()->getTokenPtr()->setText(
        (iden->getText()) + FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX +
        (objectType->getObjectTypeIdentifierRef()->getTokenPtr()->getText()));
    arrayTypeExpression->setNonTrivialElementType(std::move(objectType));
  } else if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::IdentifierToken) {
    arrayTypeExpression->setNonTrivialElementType(
        std::unique_ptr<ObjectTypeExpressionSyntax>(
            (static_cast<ObjectTypeExpressionSyntax *>(
                std::make_unique<ObjectTypeExpressionParser>()
                    ->parseExpression(ctx)
                    .release()))));

  } else {
    arrayTypeExpression->setElementType(
        std::make_unique<PrimitiveTypeExpressionParser>()->parseExpression(
            ctx));
  }

  while (ctx->getKind() == SyntaxKindUtils::SyntaxKind::OpenBracketToken) {
    ctx->match(SyntaxKindUtils::SyntaxKind::OpenBracketToken);

    std::unique_ptr<SyntaxToken<std::any>> numToken =
        ctx->match(SyntaxKindUtils::SyntaxKind::NumberToken);

    std::any value = numToken->getValue();

    arrayTypeExpression->addDimension(
        std::make_unique<LiteralExpressionSyntax<std::any>>(std::move(numToken),
                                                            value));

    ctx->match(SyntaxKindUtils::SyntaxKind::CloseBracketToken);
  }

  return arrayTypeExpression;
}