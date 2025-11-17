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


#include "FunctionParameterExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/IdentifierExpressionParser/IdentifierExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/TypeExpressionParser/TypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/statements/ParameterExpressionSyntax/ParameterExpressionSyntax.h"

namespace flow_wing {
namespace parser {

FunctionParameterExpressionParser::FunctionParameterExpressionParser(
    ParserContext *ctx)
    : m_ctx(ctx) {}

std::unique_ptr<syntax::ExpressionSyntax>
FunctionParameterExpressionParser::parse() {

  const syntax::SyntaxToken *inout_keyword =
      m_ctx->matchIf(lexer::TokenKind::kInOutKeyword); // inout

  const syntax::SyntaxToken *const_keyword =
      m_ctx->matchIf(lexer::TokenKind::kConstKeyword); // const

  auto identifier_expression =
      std::make_unique<IdentifierExpressionParser>(m_ctx)
          ->parse(); // identifier_expression

  const syntax::SyntaxToken *colon_token = nullptr, *as_keyword = nullptr;
  std::unique_ptr<syntax::ExpressionSyntax> type_expression = nullptr;

  if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kColonToken) {
    colon_token = m_ctx->match(lexer::TokenKind::kColonToken); // :

    as_keyword = m_ctx->matchIf(lexer::TokenKind::kAsKeyword); // as

    type_expression = std::make_unique<TypeExpressionParser>(m_ctx)
                          ->parse(); // type_expression
  }

  const syntax::SyntaxToken *equals_token = nullptr;
  std::unique_ptr<syntax::ExpressionSyntax> default_value_expression = nullptr;
  if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kEqualsToken) {
    equals_token = m_ctx->match(lexer::TokenKind::kEqualsToken); // =

    default_value_expression = PrecedenceAwareExpressionParser::parse(
        m_ctx); // default_value_expression
  }

  return std::make_unique<syntax::ParameterExpressionSyntax>(
      inout_keyword, const_keyword, std::move(identifier_expression),
      colon_token, as_keyword, std::move(type_expression), equals_token,
      std::move(default_value_expression));

  // x: int
  // x: int = 1
  // inout x: int
  // inout const x: int
}

} // namespace parser
} // namespace flow_wing