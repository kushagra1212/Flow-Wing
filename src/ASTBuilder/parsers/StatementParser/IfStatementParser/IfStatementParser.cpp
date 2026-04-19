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

#include "IfStatementParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/ASTBuilder/parsers/StatementParser/StatementParserFactory.h"
#include "src/syntax/statements/ElseClauseSyntax/ElseClauseSyntax.h"
#include "src/syntax/statements/IfStatementSyntax/IfStatementSyntax.h"
#include "src/syntax/statements/OrIfStatementSyntax/OrIfStatementSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"

namespace flow_wing {
namespace parser {

IfStatementParser::IfStatementParser(ParserContext *ctx) : m_ctx(ctx) {}

std::unique_ptr<syntax::StatementSyntax> IfStatementParser::parse() {

  auto if_keyword = m_ctx->match(lexer::TokenKind::kIfKeyword); // if

  auto if_condition =
      PrecedenceAwareExpressionParser::parse(m_ctx); // condition expression

  auto if_statement =
      StatementParserFactory::create(*m_ctx)->parse(); // statement

  auto or_if_statements =
      std::vector<std::unique_ptr<syntax::OrIfStatementSyntax>>();

  while (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kOrKeyword) {
    auto or_keyword = m_ctx->match(lexer::TokenKind::kOrKeyword); // or
    auto if_keyword = m_ctx->match(lexer::TokenKind::kIfKeyword); // if
    auto or_if_condition =
        PrecedenceAwareExpressionParser::parse(m_ctx); // condition expression
    auto or_if_statement =
        StatementParserFactory::create(*m_ctx)->parse(); // statement

    or_if_statements.push_back(std::make_unique<syntax::OrIfStatementSyntax>(
        or_keyword, if_keyword, std::move(or_if_condition),
        std::move(or_if_statement)));
  }

  std::unique_ptr<syntax::ElseClauseSyntax> else_clause = nullptr;

  if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kElseKeyword) {
    auto else_keyword = m_ctx->match(lexer::TokenKind::kElseKeyword); // else
    auto else_statement =
        StatementParserFactory::create(*m_ctx)->parse(); // statement

    else_clause = std::make_unique<syntax::ElseClauseSyntax>(
        else_keyword, std::move(else_statement)); // else statement
  }

  return std::make_unique<syntax::IfStatementSyntax>(
      if_keyword, std::move(if_condition), std::move(if_statement),
      std::move(or_if_statements), std::move(else_clause));

  /*
  if (condition) {
    statement;
  } or if (condition) {
    statement;
  } else {
    statement;
  }

  if (condition) {
    statement;
  } or if (condition) {
    statement;
  }

  if (condition) {
    statement;
  } else {
    statement;
  }

  if (condition) {
    statement;
  } or if (condition) {
    statement;
  } or if (condition) {
    statement;
  } else {
    statement;
  }

  if condition
  statement;
  */
}
} // namespace parser
} // namespace flow_wing
