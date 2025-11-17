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

#include "BringStatementParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/IdentifierExpressionParser/IdentifierExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/syntax/expression/StringLiteralExpressionSyntax/StringLiteralExpressionSyntax.h"
#include "src/syntax/statements/BringStatementSyntax/BringStatementSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"
namespace flow_wing {
namespace parser {

BringStatementParser::BringStatementParser(ParserContext *ctx) : m_ctx(ctx) {}

std::unique_ptr<syntax::StatementSyntax> BringStatementParser::parse() {

  auto bring_keyword_token =
      m_ctx->match(lexer::TokenKind::kBringKeyword); // bring

  auto open_brace_token =
      m_ctx->matchIf(lexer::TokenKind::kOpenBraceToken); // {

  auto identifier_expressions =
      std::vector<std::unique_ptr<syntax::ExpressionSyntax>>();
  auto comma_tokens = std::vector<const syntax::SyntaxToken *>();

  const syntax::SyntaxToken *close_brace_token = nullptr,
                            *from_keyword_token = nullptr;

  if (open_brace_token) {
    size_t count = 0;
    while (m_ctx->getCurrentTokenKind() != lexer::TokenKind::kCloseBraceToken &&
           m_ctx->getCurrentTokenKind() != lexer::TokenKind::kEndOfFileToken) {
      if (count)
        comma_tokens.push_back(
            m_ctx->match(lexer::TokenKind::kCommaToken)); // ,

      auto identifier_expression =
          std::make_unique<IdentifierExpressionParser>(m_ctx)
              ->parse(); // identifier_expression

      identifier_expressions.push_back(std::move(identifier_expression));
    }

    close_brace_token = m_ctx->match(lexer::TokenKind::kCloseBraceToken); // }

    from_keyword_token = m_ctx->matchIf(lexer::TokenKind::kFromKeyword); // from
  }

  auto string_literal_expression =
      std::make_unique<syntax::StringLiteralExpressionSyntax>(
          m_ctx->match(lexer::TokenKind::kStringLiteralToken)); // "file.fg" or
  // "moduleName-module.fg" or
  // "moduleName"

  return std::make_unique<syntax::BringStatementSyntax>(
      bring_keyword_token, open_brace_token, std::move(identifier_expressions),
      close_brace_token, from_keyword_token,
      std::move(string_literal_expression));
}
} // namespace parser
} // namespace flow_wing
