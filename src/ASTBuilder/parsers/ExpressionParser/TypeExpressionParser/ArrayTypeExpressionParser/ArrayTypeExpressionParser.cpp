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

#include "ArrayTypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/DimensionClauseExpressionParser/DimensionClauseExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/syntax/expression/DimensionClauseExpressionSyntax/DimensionClauseExpressionSyntax.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/ArrayTypeExpressionSyntax/ArrayTypeExpressionSyntax.h"
#include <vector>

namespace flow_wing {
namespace parser {

ArrayTypeExpressionParser::ArrayTypeExpressionParser(ParserContext *ctx)
    : m_ctx(ctx) {}

std::unique_ptr<syntax::ExpressionSyntax>
ArrayTypeExpressionParser::parsePostfix(
    std::unique_ptr<syntax::ExpressionSyntax> underlying_type) {

  auto open_bracket_token =
      m_ctx->match(lexer::TokenKind::kOpenBracketToken); // [

  std::vector<std::unique_ptr<syntax::DimensionClauseExpressionSyntax>>
      dimensions; // [2]

  dimensions.push_back(
      std::make_unique<parser::DimensionClauseExpressionParser>(m_ctx)
          ->parsePostfix(open_bracket_token));

  while (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kOpenBracketToken) {
    dimensions.push_back(
        std::make_unique<parser::DimensionClauseExpressionParser>(m_ctx)
            ->parseClause()); // [2]
  }

  return std::make_unique<syntax::ArrayTypeExpressionSyntax>(
      std::move(underlying_type),
      std::move(dimensions)); // int[2][3] or objectType[2][3]
}

std::unique_ptr<syntax::ExpressionSyntax> ArrayTypeExpressionParser::parse() {
  return nullptr;
}

} // namespace parser
} // namespace flow_wing
