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

#include "src/ASTBuilder/parsers/ExpressionParser/IndexExpressionParser/IndexExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/DimensionClauseExpressionParser/DimensionClauseExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/expression/IndexExpressionSyntax/IndexExpressionSyntax.h"
#include <cassert>

namespace flow_wing {
namespace parser {

IndexExpressionParser::IndexExpressionParser(ParserContext *ctx) : m_ctx(ctx) {}

std::unique_ptr<syntax::ExpressionSyntax> IndexExpressionParser::parsePostfix(
    std::unique_ptr<syntax::ExpressionSyntax> identifier_expression) {

  auto dimension_clause_expressions =
      std::vector<std::unique_ptr<syntax::ExpressionSyntax>>();

  while (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kOpenBracketToken &&
         m_ctx->getCurrentTokenKind() != lexer::TokenKind::kEndOfFileToken) {

    dimension_clause_expressions.push_back(
        std::make_unique<parser::DimensionClauseExpressionParser>(m_ctx)
            ->parse()); // [2]
  }

  return std::make_unique<syntax::IndexExpressionSyntax>(
      std::move(identifier_expression),
      std::move(
          dimension_clause_expressions)); // identifier[2] or identifier[2][3]
}

std::unique_ptr<syntax::ExpressionSyntax> IndexExpressionParser::parse() {
  assert(false && "IndexExpressionParser::parse() is not implemented");
  return nullptr;
}

} // namespace parser
} // namespace flow_wing
