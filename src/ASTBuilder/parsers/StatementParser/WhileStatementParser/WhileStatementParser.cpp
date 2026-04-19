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

#include "WhileStatementParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/ASTBuilder/parsers/StatementParser/StatementParserFactory.h"
#include "src/syntax/statements/StatementSyntax.h"
#include "src/syntax/statements/WhileStatementSyntax/WhileStatementSyntax.h"
namespace flow_wing {
namespace parser {

WhileStatementParser::WhileStatementParser(ParserContext *ctx) : m_ctx(ctx) {}

std::unique_ptr<syntax::StatementSyntax> WhileStatementParser::parse() {
  auto while_keyword = m_ctx->match(lexer::TokenKind::kWhileKeyword); // while
  auto condition = PrecedenceAwareExpressionParser::parse(m_ctx);   // condition
  auto statement = StatementParserFactory::create(*m_ctx)->parse(); // statement

  return std::make_unique<syntax::WhileStatementSyntax>(
      while_keyword, std::move(condition), std::move(statement));

  /*
  while (condition) {
    statement;
  }
  */
}
} // namespace parser
} // namespace flow_wing
