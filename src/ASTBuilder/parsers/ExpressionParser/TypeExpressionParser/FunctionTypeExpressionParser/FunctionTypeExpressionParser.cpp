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

#include "FunctionTypeExpressionParser.h"
#include "src/ASTBuilder/CodeFormatter/CodeFormatter.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"
#include <memory>

std::unique_ptr<ExpressionSyntax>
FunctionTypeExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<FunctionTypeExpressionSyntax> funcTypeExpression =
      std::make_unique<FunctionTypeExpressionSyntax>(
          std::make_unique<SyntaxToken<std::any>>(
              ctx->getDiagnosticHandler()->getAbsoluteFilePath(), 0,
              SyntaxKindUtils::SyntaxKind::NBU_FUNCTION_TYPE, 0,
              "NBU_FUNCTION_TYPE", "NBU_FUNCTION_TYPE"));

  funcTypeExpression->setOpenBracketToken(
      ctx->match(SyntaxKindUtils::SyntaxKind::OpenBracketToken));

  funcTypeExpression->setOpenParenthesisToken(
      ctx->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken));

  ctx->getCodeFormatterRef()->appendWithSpace();
  size_t parameterCount = 0;
  while (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseParenthesisToken &&
         ctx->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
    if (parameterCount) {
      ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken);
      ctx->getCodeFormatterRef()->appendWithSpace();
    }

    if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::AsKeyword) {
      funcTypeExpression->addAsParameterKeyword(
          parameterCount, ctx->match(SyntaxKindUtils::SyntaxKind::AsKeyword));
      ctx->getCodeFormatterRef()->appendWithSpace();
    }

    std::unique_ptr<TypeExpressionSyntax> typeExp(
        static_cast<TypeExpressionSyntax *>(
            std::make_unique<TypeExpressionParser>()
                ->parseExpression(ctx)
                .release()));

    funcTypeExpression->addParameterType(std::move(typeExp));

    parameterCount++;
  }

  ctx->getCodeFormatterRef()->appendWithSpace();

  funcTypeExpression->setCloseParenthesisToken(
      ctx->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken));

  ctx->getCodeFormatterRef()->appendWithSpace();
  ctx->match(SyntaxKindUtils::SyntaxKind::MinusToken);
  ctx->match(SyntaxKindUtils::SyntaxKind::GreaterToken);
  ctx->getCodeFormatterRef()->appendWithSpace();

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::AsKeyword) {
    funcTypeExpression->setAsKeyword(
        ctx->match(SyntaxKindUtils::SyntaxKind::AsKeyword));
    ctx->getCodeFormatterRef()->appendWithSpace();
  }

  do {
    if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken) {
      funcTypeExpression->addSeparator(
          ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken));
      ctx->getCodeFormatterRef()->appendWithSpace();
    }

    funcTypeExpression->addReturnType(std::unique_ptr<TypeExpressionSyntax>(
        (static_cast<TypeExpressionSyntax *>(
            std::make_unique<TypeExpressionParser>()
                ->parseExpression(ctx)
                .release()))));

  } while (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken);

  funcTypeExpression->setCloseBracketToken(
      ctx->match(SyntaxKindUtils::SyntaxKind::CloseBracketToken));
  ctx->getCodeFormatterRef()->appendWithSpace();

  return funcTypeExpression;
}