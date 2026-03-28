/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
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

#include "ModuleStatementParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/IdentifierExpressionParser/IdentifierExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/ASTBuilder/parsers/StatementParser/StatementParserFactory.h"
#include "src/syntax/statements/ModuleStatementSyntax/ModuleStatementSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"
namespace flow_wing {
namespace parser {

ModuleStatementParser::ModuleStatementParser(ParserContext *ctx) : m_ctx(ctx) {}

std::unique_ptr<syntax::StatementSyntax> ModuleStatementParser::parse() {
  auto module_keyword_token =
      m_ctx->match(lexer::TokenKind::kModuleKeyword); // module

  auto open_bracket_token =
      m_ctx->match(lexer::TokenKind::kOpenBracketToken); // [

  auto module_name_identifier_expression =
      std::make_unique<IdentifierExpressionParser>(m_ctx)
          ->parse(); // module_name

  auto close_bracket_token =
      m_ctx->match(lexer::TokenKind::kCloseBracketToken); // ]

  auto module_statements =
      std::vector<std::unique_ptr<syntax::StatementSyntax>>();

  while (m_ctx->getCurrentTokenKind() != lexer::TokenKind::kEndOfFileToken) {

    module_statements.push_back(
        StatementParserFactory::create(*m_ctx)
            ->parse()); //  CustomTypeStatement, FunctionDeclaration,
                        //  VariableDeclaration, ClassStatement, CallExpression
  }

  auto end_of_file_token = m_ctx->match(lexer::TokenKind::kEndOfFileToken); //

  return std::make_unique<syntax::ModuleStatementSyntax>(
      module_keyword_token, open_bracket_token,
      std::move(module_name_identifier_expression), close_bracket_token,
      std::move(module_statements), end_of_file_token);
}
} // namespace parser
} // namespace flow_wing
