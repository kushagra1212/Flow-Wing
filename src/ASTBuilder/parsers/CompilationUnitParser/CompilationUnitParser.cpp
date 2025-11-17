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

#include "CompilationUnitParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/ASTBuilder/parsers/StatementParser/ExposeStatementParser/ExposeStatementParser.h"
#include "src/ASTBuilder/parsers/StatementParser/StatementParserFactory.h"
#include "src/syntax/CompilationUnitSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"
#include <memory>

namespace flow_wing {
namespace parser {

CompilationUnitParser::CompilationUnitParser(ParserContext *ctx) : m_ctx(ctx) {}

std::unique_ptr<syntax::StatementSyntax>
CompilationUnitParser::parseStatement() {

  if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kExposeKeyword) {
    return std::make_unique<ExposeStatementParser>(m_ctx)->parse();
  }

  return StatementParserFactory::create(*m_ctx)->parse();
}

std::unique_ptr<syntax::CompilationUnitSyntax> CompilationUnitParser::parse() {

  auto global_statements =
      std::vector<std::unique_ptr<syntax::StatementSyntax>>();

  while (m_ctx->getCurrentTokenKind() != lexer::TokenKind::kEndOfFileToken) {
    global_statements.emplace_back(parseStatement());
  }

  return std::make_unique<syntax::CompilationUnitSyntax>(
      std::move(global_statements),
      m_ctx->match(lexer::TokenKind::kEndOfFileToken));
}
} // namespace parser

} // namespace flow_wing