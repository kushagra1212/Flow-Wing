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

#include "ObjectExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/syntax/expression/BinaryExpressionSyntax/BinaryExpressionSyntax.h"
#include "src/syntax/expression/ObjectExpressionSyntax/ObjectExpressionSyntax.h"

namespace flow_wing {

namespace parser {

ObjectExpressionParser::ObjectExpressionParser(ParserContext *ctx)
    : m_ctx(ctx) {}

std::unique_ptr<syntax::ExpressionSyntax> ObjectExpressionParser::parse() {

  auto open_brace_token = m_ctx->match(lexer::TokenKind::kOpenBraceToken); // {

  std::unique_ptr<syntax::ExpressionSyntax> accumulated_expr = nullptr;

  // {}

  if (m_ctx->getCurrentTokenKind() != lexer::TokenKind::kCloseBraceToken) {

    accumulated_expr =
        PrecedenceAwareExpressionParser::parseAssignmentExpression(m_ctx);

    while (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kCommaToken &&
           m_ctx->getCurrentTokenKind() != lexer::TokenKind::kCloseBraceToken &&
           m_ctx->getCurrentTokenKind() != lexer::TokenKind::kEndOfFileToken) {

      auto comma_token = m_ctx->match(lexer::TokenKind::kCommaToken); //  ,

      // TRAILING COMMA CHECK:

      if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kCloseBraceToken) {
        break;
      }

      auto next_expr =
          PrecedenceAwareExpressionParser::parseAssignmentExpression(m_ctx);

      accumulated_expr = std::make_unique<syntax::BinaryExpressionSyntax>(
          std::move(accumulated_expr), comma_token, std::move(next_expr));
    }
  }

  auto close_brace_token =
      m_ctx->match(lexer::TokenKind::kCloseBraceToken); // }

  return std::make_unique<syntax::ObjectExpressionSyntax>(
      std::move(open_brace_token), std::move(accumulated_expr),
      std::move(close_brace_token));
}

} // namespace parser

} // namespace flow_wing