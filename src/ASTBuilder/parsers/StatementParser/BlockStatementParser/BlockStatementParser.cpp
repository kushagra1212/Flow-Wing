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

#include "BlockStatementParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/ASTBuilder/parsers/StatementParser/StatementParserFactory.h"
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"

namespace flow_wing {
namespace parser {

BlockStatementParser::BlockStatementParser(ParserContext *ctx) : m_ctx(ctx) {}

std::unique_ptr<syntax::StatementSyntax> BlockStatementParser::parse() {

  auto open_brace_token = m_ctx->match(lexer::TokenKind::kOpenBraceToken); //  {

  auto statements = std::vector<std::unique_ptr<syntax::StatementSyntax>>();

  while (m_ctx->getCurrentTokenKind() != lexer::TokenKind::kCloseBraceToken &&
         m_ctx->getCurrentTokenKind() != lexer::TokenKind::kEndOfFileToken) {

    statements.push_back(StatementParserFactory::create(*m_ctx)->parse());
  }

  auto close_brace_token =
      m_ctx->match(lexer::TokenKind::kCloseBraceToken); //  }

  return std::make_unique<syntax::BlockStatementSyntax>(
      open_brace_token, std::move(statements),
      close_brace_token); // { statements }
}
} // namespace parser
} // namespace flow_wing
