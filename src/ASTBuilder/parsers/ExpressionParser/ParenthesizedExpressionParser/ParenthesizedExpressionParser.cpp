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
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/syntax/expression/ParenthesizedExpressionSyntax/ParenthesizedExpressionSyntax.h"
namespace flow_wing {

namespace parser {

ParenthesizedExpressionParser::ParenthesizedExpressionParser(ParserContext *ctx)
    : m_ctx(ctx) {}

std::unique_ptr<syntax::ExpressionSyntax>
ParenthesizedExpressionParser::parse() {
  auto open_parenthesis_token =
      m_ctx->match(lexer::TokenKind::kOpenParenthesisToken); // (

  auto expression =
      PrecedenceAwareExpressionParser::parse(m_ctx); // 2 * 5 or call_1() * 5

  auto close_parenthesis_token =
      m_ctx->match(lexer::TokenKind::kCloseParenthesisToken); // )

  return std::make_unique<syntax::ParenthesizedExpressionSyntax>(
      open_parenthesis_token, std::move(expression), close_parenthesis_token);
  // (2 * 5)
}

} // namespace parser

} // namespace flow_wing
