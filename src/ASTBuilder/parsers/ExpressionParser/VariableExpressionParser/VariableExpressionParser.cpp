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

#include "VariableExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/IdentifierExpressionParser/IdentifierExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/expression/AssignmentExpressionSyntax/AssignmentExpressionSyntax.h"
#include "src/syntax/expression/CallExpressionSyntax/CallExpressionSyntax.h"
#include "src/syntax/expression/IndexExpressionSyntax/IndexExpressionSyntax.h"
#include "src/syntax/expression/LiteralExpressionSyntax/LiteralExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/TypeExpressionSyntax.h"
#include "src/syntax/expression/VariableExpressionSyntax/VariableExpressionSyntax.h"
#include "src/utils/LogConfig.h"
#include <cassert>

std::unique_ptr<ExpressionSyntax>
VariableExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<SyntaxToken<std::any>> identifierToken =
      ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken);

  if (identifierToken->getValue().type() == typeid(std::string) &&
      std::any_cast<std::string>(identifierToken->getValue()) == "self") {
    if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::DotToken) {
      ctx->match(SyntaxKindUtils::SyntaxKind::DotToken);

      auto expression =
          std::make_unique<IdentifierExpressionParser>()->parseExpression(ctx);

      if (expression->getKind() ==
          SyntaxKindUtils::SyntaxKind::VariableExpressionSyntax) {
        static_cast<VariableExpressionSyntax *>(expression.get())
            ->setSelfKeyword(std::move(identifierToken));
        return expression;
      } else if (expression->getKind() ==
                 SyntaxKindUtils::SyntaxKind::IndexExpression) {
        static_cast<IndexExpressionSyntax *>(expression.get())
            ->setSelfKeyword(std::move(identifierToken));
        return expression;
      } else if (expression->getKind() ==
                 SyntaxKindUtils::SyntaxKind::AssignmentExpression) {

        auto assignmentExpression =
            static_cast<AssignmentExpressionSyntax *>(expression.get());

        if (auto *varExp = dynamic_cast<VariableExpressionSyntax *>(
                assignmentExpression->getLeftRef().get())) {
          varExp->setSelfKeyword(std::move(identifierToken));

        } else if (auto *newIndexExp = dynamic_cast<IndexExpressionSyntax *>(
                       assignmentExpression->getLeftRef().get())) {
          newIndexExp->setSelfKeyword(std::move(identifierToken));
        }

      } else if (expression->getKind() ==
                 SyntaxKindUtils::SyntaxKind::CallExpression) {
        return expression;
      } else {
        DEBUG_LOG("expression: {}",
                  SyntaxKindUtils::to_string(expression->getKind()));
        assert(false &&
               "Failed to cast expression to VariableExpressionSyntax");
      }

      return expression;
    }
  }

  std::any value = identifierToken->getValue();

  std::unique_ptr<TypeExpressionSyntax> typeExpression =
      std::make_unique<TypeExpressionSyntax>(
          std::make_unique<SyntaxToken<std::any>>(
              ctx->getDiagnosticHandler()->getAbsoluteFilePath(), 0,
              SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE, 0,
              "NBU_UNKNOWN_TYPE", "NBU_UNKNOWN_TYPE"));

  std::unique_ptr<VariableExpressionSyntax> variExp =
      std::make_unique<VariableExpressionSyntax>(
          std::make_unique<LiteralExpressionSyntax<std::any>>(
              std::move(identifierToken), value),
          false, std::move(typeExpression));

  while (ctx->getKind() == SyntaxKindUtils::SyntaxKind::DotToken) {
    ctx->match(SyntaxKindUtils::SyntaxKind::DotToken);

    if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::IdentifierToken &&
        ctx->peek(1)->getKind() ==
            SyntaxKindUtils::SyntaxKind::OpenBracketToken) {

      std::unique_ptr<SyntaxToken<std::any>> localIdentifierToken =
          ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken);

      std::any localValue = localIdentifierToken->getValue();
      std::unique_ptr<IndexExpressionSyntax> localIndexExpression =
          std::make_unique<IndexExpressionSyntax>(
              std::make_unique<LiteralExpressionSyntax<std::any>>(
                  std::move(localIdentifierToken), localValue));

      while (ctx->getKind() == SyntaxKindUtils::SyntaxKind::OpenBracketToken) {

        ctx->match(SyntaxKindUtils::SyntaxKind::OpenBracketToken);

        localIndexExpression->addIndexExpression(
            PrecedenceAwareExpressionParser::parse(ctx));

        ctx->match(SyntaxKindUtils::SyntaxKind::CloseBracketToken);
      }

      variExp->addDotExpression(std::move(localIndexExpression));
    } else {

      if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::IdentifierToken &&
          ctx->peek(1)->getKind() ==
              SyntaxKindUtils::SyntaxKind::OpenParenthesisToken) {

        variExp->addDotExpression(
            std::make_unique<IdentifierExpressionParser>()->parseExpression(
                ctx));
      } else {

        std::unique_ptr<SyntaxToken<std::any>> localIdentifierToken =
            ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken);
        std::any localValue = localIdentifierToken->getValue();

        variExp->addDotExpression(
            std::make_unique<LiteralExpressionSyntax<std::any>>(
                std::move(localIdentifierToken), localValue));
      }
    }
  }

  return variExp;
}