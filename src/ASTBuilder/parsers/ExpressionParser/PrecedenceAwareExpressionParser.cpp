/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
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
#include "src/ASTBuilder/parsers/ExpressionParser/CallExpressionParser/CallExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/IndexExpressionParser/IndexExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/MemberAccessExpressionParser/MemberAccessExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/ModuleAccessExpressionParser/ModuleAccessExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrimaryExpressionParserFactory.h"
#include "src/ASTBuilder/parsers/ExpressionParser/TernaryExpressionParser/TernaryExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/syntax/OperatorPrecedence/OperatorPrecedence.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/AssignmentExpressionSyntax/AssignmentExpressionSyntax.h"
#include "src/syntax/expression/BinaryExpressionSyntax/BinaryExpressionSyntax.h"
#include "src/syntax/expression/ColonExpressionSyntax/ColonExpressionSyntax.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/NodeKind/NodeKind.h"
#include "src/syntax/expression/NewExpressionSyntax/NewExpressionSyntax.h"
#include "src/syntax/expression/UnaryExpressionSyntax/UnaryExpressionSyntax.h"
#include <cassert>

namespace flow_wing {
namespace parser {

// Block `3\n( ...` as a call; allow `f\n( ...` across a line break.
static bool isLiteralishPrimaryForNoCallAcrossNewline(
    const syntax::ExpressionSyntax *e) {
  if (!e) {
    return false;
  }
  switch (e->getKind()) {
  case syntax::NodeKind::kNumberLiteralExpression:
  case syntax::NodeKind::kInt64LiteralExpression:
  case syntax::NodeKind::kFloatLiteralExpression:
  case syntax::NodeKind::kDoubleLiteralExpression:
  case syntax::NodeKind::kStringLiteralExpression:
  case syntax::NodeKind::kTemplateStringLiteralExpression:
  case syntax::NodeKind::kCharacterLiteralExpression:
  case syntax::NodeKind::kBooleanLiteralExpression:
  case syntax::NodeKind::kDynLiteralExpression:
    return true;
  default:
    return false;
  }
}

std::unique_ptr<syntax::ExpressionSyntax>
PrecedenceAwareExpressionParser::parse(ParserContext *ctx,
                                       int parent_precedence) {
  std::unique_ptr<syntax::ExpressionSyntax> left;
  int prefix_precedence = syntax::OperatorPrecedence::getPrefixPrecedence(
      ctx->getCurrentTokenKind());

  if (prefix_precedence != 0 && prefix_precedence >= parent_precedence) {
    // --- Handle Prefix Operators ---

    auto operator_token = ctx->nextToken();
    auto operand = parse(ctx, prefix_precedence);

    switch (operator_token->getTokenKind()) {
    case lexer::TokenKind::kNewKeyword:
      left = std::make_unique<syntax::NewExpressionSyntax>(operator_token,
                                                           std::move(operand));
      break;

    default:
      left = std::make_unique<syntax::UnaryExpressionSyntax>(
          operator_token, std::move(operand));
      break;
    }
  } else {
    // --- Handle Primary Expressions ---
    left =
        PrimaryExpressionParserFactory::create(ctx, ctx->getCurrentTokenKind())
            ->parse();
  }

  while (true) {
    int postfix_precedence = syntax::OperatorPrecedence::getPostfixPrecedence(
        ctx->getCurrentTokenKind());
    int infix_precedence = syntax::OperatorPrecedence::getInfixPrecedence(
        ctx->getCurrentTokenKind());

    if (postfix_precedence != 0 && postfix_precedence > parent_precedence) {
      // --- Handle Postfix Operators ---
      // not parsing '(' as call postfix when it is after a newline before a
      // *literal* left operand (e.g. "3\n(expr)" should not be 3(expr)).
      // Identifiers and other exprs may split across lines: "f\n( a )" is
      // still a call.
      if (ctx->getCurrentTokenKind() ==
          lexer::TokenKind::kOpenParenthesisToken) {
        const auto *cur = ctx->getCurrent();
        if (cur && cur->hasLeadingEndOfLine() &&
            isLiteralishPrimaryForNoCallAcrossNewline(left.get())) {
          break;
        }
      }

      switch (ctx->getCurrentTokenKind()) {
      case lexer::TokenKind::kColonColonToken:
        left = std::make_unique<parser::ModuleAccessExpressionParser>(ctx)
                   ->parsePostfix(std::move(left));
        break;
      case lexer::TokenKind::kDotToken:
        left = std::make_unique<parser::MemberAccessExpressionParser>(ctx)
                   ->parsePostfix(std::move(left));
        break;
      case lexer::TokenKind::kOpenParenthesisToken:
        left =
            std::make_unique<parser::CallExpressionParser>(ctx)->parsePostfix(
                std::move(left));
        break;
      case lexer::TokenKind::kOpenBracketToken:
        left =
            std::make_unique<parser::IndexExpressionParser>(ctx)->parsePostfix(
                std::move(left));
        break;
      default:
        assert(false &&
               "Unexpected token kind for PrecedenceAwareExpressionParser");
        break;
      }

      continue;

    } else if (infix_precedence != 0 && infix_precedence > parent_precedence) {
      // --- Handle Infix Operators ---
      auto operator_token = ctx->nextToken();

      switch (operator_token->getTokenKind()) {

      case lexer::TokenKind::kQuestionToken: {
        left = std::make_unique<TernaryExpressionParser>(ctx)->parsePostfix(
            std::move(left), operator_token);
        break;
      }

      case lexer::TokenKind::kEqualsToken:
      case lexer::TokenKind::kLeftArrowToken: {
        auto right = parse(ctx);
        left = std::make_unique<syntax::AssignmentExpressionSyntax>(
            std::move(left), operator_token, std::move(right));
        break;
      }
      case lexer::TokenKind::kColonToken: {
        auto right = parseAssignmentExpression(ctx);
        left = std::make_unique<syntax::ColonExpressionSyntax>(
            std::move(left), operator_token, std::move(right));
        break;
      }

      default: {

        //  LEFT-ASSOCIATIVE ((var1, var2), var3)
        auto right = parse(ctx, infix_precedence);
        left = std::make_unique<syntax::BinaryExpressionSyntax>(
            std::move(left), operator_token, std::move(right));
        break;
      }
      }

      continue;
    }

    break;
  }

  return left;
}

std::unique_ptr<syntax::ExpressionSyntax>
PrecedenceAwareExpressionParser::parseAssignmentExpression(ParserContext *ctx) {

  int comma_precedence = syntax::OperatorPrecedence::getInfixPrecedence(
      lexer::TokenKind::kCommaToken);

  return parse(ctx, comma_precedence);
}
} // namespace parser
} // namespace flow_wing