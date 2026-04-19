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

#include "BracketedExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/ContainerExpressionSyntax/ContainerExpressionSyntax.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/expression/FillExpressionSyntax/FillExpressionSyntax.h"

namespace flow_wing {
namespace parser {

BracketedExpressionParser::BracketedExpressionParser(ParserContext *ctx)
    : m_ctx(ctx) {}

std::unique_ptr<syntax::ExpressionSyntax> BracketedExpressionParser::parse() {

  auto open_bracket_token =
      m_ctx->match(lexer::TokenKind::kOpenBracketToken); // [

  if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kCloseBracketToken) {
    auto close_bracket_token =
        m_ctx->match(lexer::TokenKind::kCloseBracketToken); // ]

    return std::make_unique<syntax::ContainerExpressionSyntax>(
        open_bracket_token, close_bracket_token);
  }

  std::unique_ptr<syntax::ExpressionSyntax> value_expression;

  value_expression = PrecedenceAwareExpressionParser::parse(m_ctx); // 2

  if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kFillKeyword) {

    auto fill_token = m_ctx->match(lexer::TokenKind::kFillKeyword); // fill

    auto fill_expression = PrecedenceAwareExpressionParser::parse(m_ctx); // 5

    auto close_bracket_token =
        m_ctx->match(lexer::TokenKind::kCloseBracketToken); // ]

    return std::make_unique<syntax::FillExpressionSyntax>(
        open_bracket_token, std::move(value_expression), fill_token,
        std::move(fill_expression), close_bracket_token); // [2 fill 5]
  }

  auto close_bracket_token =
      m_ctx->match(lexer::TokenKind::kCloseBracketToken); // ]

  return std::make_unique<syntax::ContainerExpressionSyntax>(
      open_bracket_token, std::move(value_expression),
      close_bracket_token); // [2, 5, "Hello", 1.0]
}

} // namespace parser
} // namespace flow_wing
