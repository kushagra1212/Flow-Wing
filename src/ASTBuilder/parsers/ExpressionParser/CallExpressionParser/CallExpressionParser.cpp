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

#include "CallExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/syntax/expression/CallExpressionSyntax/CallExpressionSyntax.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include <cassert>
namespace flow_wing {
namespace parser {

CallExpressionParser::CallExpressionParser(ParserContext *ctx) : m_ctx(ctx) {}

std::unique_ptr<syntax::ExpressionSyntax> CallExpressionParser::parsePostfix(
    std::unique_ptr<syntax::ExpressionSyntax> identifier_expression) {

  auto open_parenthesis_token =
      m_ctx->match(lexer::TokenKind::kOpenParenthesisToken); // (

  std::unique_ptr<syntax::ExpressionSyntax> argument_expression = nullptr;

  argument_expression = PrecedenceAwareExpressionParser::parse(m_ctx);

  auto close_parenthesis_token =
      m_ctx->match(lexer::TokenKind::kCloseParenthesisToken); // )

  return std::make_unique<syntax::CallExpressionSyntax>(
      std::move(identifier_expression), open_parenthesis_token,
      std::move(argument_expression),
      close_parenthesis_token); // function_name(2, 5, "Hello", 1.0)
}

std::unique_ptr<syntax::ExpressionSyntax> CallExpressionParser::parse() {
  assert(false && "CallExpressionParser::parse() is not implemented");
  return nullptr;
}

} // namespace parser
} // namespace flow_wing
