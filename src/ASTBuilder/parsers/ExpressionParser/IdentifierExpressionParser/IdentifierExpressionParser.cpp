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

#include "IdentifierExpressionParser.h"
#include "src/ASTBuilder/CodeFormatter/CodeFormatter.h"
#include "src/ASTBuilder/parsers/ExpressionParser/CallExpressionParser/CallExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/IndexExpressionParser/IndexExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/ModuleIdentifierExpressionParser/ModuleIdentifierExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/MultipleAssignmentExpressionParser/MultipleAssignmentExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/VariableExpressionParser/VariableExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/expression/AssignmentExpressionSyntax/AssignmentExpressionSyntax.h"
#include "src/syntax/expression/VariableExpressionSyntax/VariableExpressionSyntax.h"

std::unique_ptr<ExpressionSyntax>
IdentifierExpressionParser::parseExpression(ParserContext *ctx) {
  if (ctx->peek(1)->getKind() == SyntaxKindUtils::SyntaxKind::EqualsToken ||
      ctx->peek(1)->getKind() == SyntaxKindUtils::SyntaxKind::AssignmentToken ||
      ctx->peek(1)->getKind() == SyntaxKindUtils::SyntaxKind::DotToken) {

    std::unique_ptr<ExpressionSyntax> expression =
        std::make_unique<VariableExpressionParser>()->parseExpression(ctx);

    std::unique_ptr<VariableExpressionSyntax> variableExpression(
        static_cast<VariableExpressionSyntax *>(expression.release()));

    bool needDefaultInitialize = false;

    std::unique_ptr<SyntaxToken<std::any>> operatorToken = nullptr;
    if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::EqualsToken) {
      ctx->getCodeFormatterRef()->appendWithSpace();

      operatorToken =
          std::move(ctx->match(SyntaxKindUtils::SyntaxKind::EqualsToken));
    } else if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::AssignmentToken) {
      ctx->getCodeFormatterRef()->appendWithSpace();

      operatorToken =
          std::move(ctx->match(SyntaxKindUtils::SyntaxKind::AssignmentToken));
      needDefaultInitialize = true;
    } else {
      return std::move(variableExpression);
    }

    ctx->getCodeFormatterRef()->appendWithSpace();

    if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::NewKeyword) {
      variableExpression->setNewKeyword(
          std::move(ctx->match(SyntaxKindUtils::SyntaxKind::NewKeyword)));
      ctx->getCodeFormatterRef()->appendWithSpace();
    }

    std::unique_ptr<ExpressionSyntax> right =
        std::move(PrecedenceAwareExpressionParser::parse(ctx));

    ctx->getCodeFormatterRef()->appendWithSpace();

    return std::make_unique<AssignmentExpressionSyntax>(
        std::move(variableExpression), operatorToken->getKind(),
        std::move(right), needDefaultInitialize);

  } else if (ctx->peek(1)->getKind() ==
             SyntaxKindUtils::SyntaxKind::OpenBracketToken) {

    return std::move(
        std::make_unique<IndexExpressionParser>()->parseExpression(ctx));

  } else if (ctx->peek(1)->getKind() ==
             SyntaxKindUtils::SyntaxKind::OpenParenthesisToken) {

    return std::move(
        std::make_unique<CallExpressionParser>()->parseExpression(ctx));

  } else if (ctx->peek(1)->getKind() ==
                 SyntaxKindUtils::SyntaxKind::ColonToken &&
             ctx->peek(2)->getKind() ==
                 SyntaxKindUtils::SyntaxKind::ColonToken) {

    return std::move(
        std::make_unique<ModuleIdentifierExpressionParser>()->parseExpression(
            ctx));

  } else if (!ctx->getIsInsideCallExpression() &&
             !ctx->getIsInsideContainerExpression() &&
             !ctx->getIsInsideReturnStatement() &&
             ctx->peek(1)->getKind() ==
                 SyntaxKindUtils::SyntaxKind::CommaToken) {

    return std::move(
        std::make_unique<MultipleAssignmentExpressionParser>()->parseExpression(
            ctx));

  } else {
    return std::move(
        std::make_unique<VariableExpressionParser>()->parseExpression(ctx));
  }
}