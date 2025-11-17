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
#include "TernaryExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/expression/TernaryExpressionSyntax/TernaryExpressionSyntax.h"
#include <cassert>

namespace flow_wing {
namespace parser {

TernaryExpressionParser::TernaryExpressionParser(ParserContext *ctx)
    : m_ctx(ctx) {}

std::unique_ptr<syntax::ExpressionSyntax> TernaryExpressionParser::parsePostfix(
    std::unique_ptr<syntax::ExpressionSyntax> condition_expression,
    const syntax::SyntaxToken *question_token) {

  auto true_expression = PrecedenceAwareExpressionParser::parse(m_ctx); // 2

  auto colon_token = m_ctx->match(lexer::TokenKind::kColonToken); // :

  auto false_expression = PrecedenceAwareExpressionParser::parse(m_ctx); // 3

  return std::make_unique<syntax::TernaryExpressionSyntax>(
      std::move(condition_expression), question_token,
      std::move(true_expression), colon_token, std::move(false_expression));
}

std::unique_ptr<syntax::ExpressionSyntax> TernaryExpressionParser::parse() {
  assert(false && "TernaryExpressionParser::parse() is not implemented");
  return nullptr;
}

} // namespace parser
} // namespace flow_wing
