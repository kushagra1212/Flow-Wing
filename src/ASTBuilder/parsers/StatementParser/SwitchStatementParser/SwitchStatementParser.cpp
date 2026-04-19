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

#include "SwitchStatementParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/ASTBuilder/parsers/StatementParser/CaseStatementParser/CaseStatementParser.h"
#include "src/syntax/statements/StatementSyntax.h"
#include "src/syntax/statements/SwitchStatementSyntax/SwitchStatementSyntax.h"

namespace flow_wing {
namespace parser {

SwitchStatementParser::SwitchStatementParser(ParserContext *ctx) : m_ctx(ctx) {}

std::unique_ptr<syntax::StatementSyntax> SwitchStatementParser::parse() {

  auto switch_keyword =
      m_ctx->match(lexer::TokenKind::kSwitchKeyword); // switch

  auto switch_condition_expression =
      PrecedenceAwareExpressionParser::parse(m_ctx); // switch_condition

  auto open_brace_token = m_ctx->match(lexer::TokenKind::kOpenBraceToken); // {

  auto case_statements =
      std::vector<std::unique_ptr<syntax::StatementSyntax>>();

  auto case_statement_parser = std::make_unique<CaseStatementParser>(m_ctx);

  while (m_ctx->getCurrentTokenKind() != lexer::TokenKind::kCloseBraceToken &&
         m_ctx->getCurrentTokenKind() != lexer::TokenKind::kEndOfFileToken) {
    auto case_statement = case_statement_parser->parse(); // case_statement

    case_statements.push_back(std::move(case_statement));
  }

  auto close_brace_token =
      m_ctx->match(lexer::TokenKind::kCloseBraceToken); // }

  return std::make_unique<syntax::SwitchStatementSyntax>(
      switch_keyword, std::move(switch_condition_expression), open_brace_token,
      std::move(case_statements), close_brace_token);
}
} // namespace parser
} // namespace flow_wing
