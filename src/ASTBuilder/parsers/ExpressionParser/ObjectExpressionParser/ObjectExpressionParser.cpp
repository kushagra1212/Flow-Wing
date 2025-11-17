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


#include "ObjectExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/syntax/expression/ObjectExpressionSyntax/ObjectExpressionSyntax.h"
#include "src/syntax/expression/ObjectMemberSyntax/ObjectMemberSyntax.h"

namespace flow_wing {
namespace parser {

ObjectExpressionParser::ObjectExpressionParser(ParserContext *ctx)
    : m_ctx(ctx) {}

std::unique_ptr<syntax::ExpressionSyntax> ObjectExpressionParser::parse() {
  auto open_brace_token = m_ctx->match(lexer::TokenKind::kOpenBraceToken); // {

  size_t count = 0;

  auto members = std::vector<std::unique_ptr<syntax::ObjectMemberSyntax>>();
  auto comma_tokens = std::vector<const syntax::SyntaxToken *>();

  while (m_ctx->getCurrentTokenKind() != lexer::TokenKind::kCloseBraceToken &&
         m_ctx->getCurrentTokenKind() != lexer::TokenKind::kEndOfFileToken) {

    if (count > 0) {
      comma_tokens.push_back(m_ctx->match(lexer::TokenKind::kCommaToken)); // ,
    }

    auto identifier_expression =
        PrecedenceAwareExpressionParser::parse(m_ctx); // identifier

    auto colon_token = m_ctx->match(lexer::TokenKind::kColonToken); // :

    auto value_expression =
        PrecedenceAwareExpressionParser::parse(m_ctx); // 2 or "hello"

    auto object_member_expression =
        std::make_unique<syntax::ObjectMemberSyntax>(
            std::move(identifier_expression), colon_token,
            std::move(value_expression)); // key: value

    count++;
  }

  auto close_brace_token =
      m_ctx->match(lexer::TokenKind::kCloseBraceToken); // }

  return std::make_unique<syntax::ObjectExpressionSyntax>(
      std::move(open_brace_token), std::move(members), comma_tokens,
      std::move(close_brace_token));
  // { key1: 2, key2: "hello", ... }
}

} // namespace parser
} // namespace flow_wing