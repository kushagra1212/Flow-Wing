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


#include "DimensionClauseExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/syntax/expression/DimensionClauseExpressionSyntax/DimensionClauseExpressionSyntax.h"

namespace flow_wing {
namespace parser {

DimensionClauseExpressionParser::DimensionClauseExpressionParser(
    ParserContext *ctx)
    : m_ctx(ctx) {}

std::unique_ptr<syntax::DimensionClauseExpressionSyntax>
DimensionClauseExpressionParser::parsePostfix(
    const syntax::SyntaxToken *open_bracket_token) {

  auto size_literal = PrecedenceAwareExpressionParser::parse(m_ctx); // 2

  const syntax::SyntaxToken *close_bracket =
      m_ctx->match(lexer::TokenKind::kCloseBracketToken); // ]

  return std::make_unique<syntax::DimensionClauseExpressionSyntax>(
      open_bracket_token, std::move(size_literal),
      close_bracket); // [2]
}

std::unique_ptr<syntax::DimensionClauseExpressionSyntax>
DimensionClauseExpressionParser::parseClause() {

  const syntax::SyntaxToken *open_bracket_token =
      m_ctx->match(lexer::TokenKind::kOpenBracketToken); // [

  return parsePostfix(open_bracket_token);
}

std::unique_ptr<syntax::ExpressionSyntax>
DimensionClauseExpressionParser::parse() {
  return parseClause();
}

} // namespace parser
} // namespace flow_wing