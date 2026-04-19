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


#include "FunctionReturnTypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/TypeExpressionParser/TypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/ASTBuilder/parsers/StatementParser/StatementParser.h"
#include "src/ASTBuilder/parsers/StatementParser/StatementParserFactory.h"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/expression/FunctionReturnTypeExpressionSyntax/FunctionReturnTypeExpressionSyntax.h"

namespace flow_wing {
namespace parser {

FunctionReturnTypeExpressionParser::FunctionReturnTypeExpressionParser(
    ParserContext *ctx)
    : m_ctx(ctx) {}

std::unique_ptr<syntax::ExpressionSyntax>
FunctionReturnTypeExpressionParser::parse() {

  auto as_keyword = m_ctx->matchIf(lexer::TokenKind::kAsKeyword); // as

  auto type_expressions =
      std::vector<std::unique_ptr<syntax::ExpressionSyntax>>();

  auto comma_tokens = std::vector<const syntax::SyntaxToken *>();

  size_t count = 0;

  auto type_expression_parser = std::make_unique<TypeExpressionParser>(m_ctx);

  do {
    if (count)
      comma_tokens.push_back(m_ctx->match(lexer::TokenKind::kCommaToken)); // ,

    type_expressions.push_back(type_expression_parser->parse()); // int

    count++;
  } while (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kCommaToken);

  return std::make_unique<syntax::FunctionReturnTypeExpressionSyntax>(
      as_keyword, std::move(type_expressions), comma_tokens);
  // int
  // int, str
  // as  int
  // module_name::type_name
}

} // namespace parser
} // namespace flow_wing