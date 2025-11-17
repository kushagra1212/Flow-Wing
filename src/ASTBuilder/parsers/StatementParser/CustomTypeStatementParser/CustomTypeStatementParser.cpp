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

#include "CustomTypeStatementParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/IdentifierExpressionParser/IdentifierExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/TypeExpressionParser/TypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/syntax/expression/FieldDeclarationSyntax/FieldDeclarationSyntax.h"
#include "src/syntax/statements/CustomTypeStatementSyntax/CustomTypeStatementSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"
namespace flow_wing {
namespace parser {

CustomTypeStatementParser::CustomTypeStatementParser(ParserContext *ctx)
    : m_ctx(ctx) {}

std::unique_ptr<syntax::StatementSyntax> CustomTypeStatementParser::parse() {

  auto type_keyword = m_ctx->match(lexer::TokenKind::kTypeKeyword); // type

  auto identifier_expression =
      std::make_unique<IdentifierExpressionParser>(m_ctx)->parse(); // type_name

  auto equals_token = m_ctx->match(lexer::TokenKind::kEqualsToken); // =

  auto open_brace_token = m_ctx->match(lexer::TokenKind::kOpenBraceToken); // {

  auto field_declarations =
      std::vector<std::unique_ptr<syntax::FieldDeclarationSyntax>>();

  while (m_ctx->getCurrentTokenKind() != lexer::TokenKind::kCloseBraceToken &&
         m_ctx->getCurrentTokenKind() != lexer::TokenKind::kEndOfFileToken) {

    auto key_identifier_expression =
        std::make_unique<IdentifierExpressionParser>(m_ctx)
            ->parse(); // field_name

    auto colon_token = m_ctx->match(lexer::TokenKind::kColonToken); // :

    auto value_expression =
        std::make_unique<TypeExpressionParser>(m_ctx)->parse();

    field_declarations.push_back(
        std::make_unique<syntax::FieldDeclarationSyntax>(
            std::move(key_identifier_expression), colon_token,
            std::move(value_expression))); // field_name: field_value
  }

  auto close_brace_token =
      m_ctx->match(lexer::TokenKind::kCloseBraceToken); // }

  return std::make_unique<syntax::CustomTypeStatementSyntax>(
      type_keyword, std::move(identifier_expression), equals_token,
      open_brace_token, std::move(field_declarations),
      close_brace_token); // type type_name = {
                          // field_name: field_value
                          // }
}
} // namespace parser
} // namespace flow_wing
