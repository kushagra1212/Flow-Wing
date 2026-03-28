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

#include "ClassStatementParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/IdentifierExpressionParser/IdentifierExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/ASTBuilder/parsers/StatementParser/FunctionStatementParser/FunctionStatementParser.h"
#include "src/ASTBuilder/parsers/StatementParser/StatementParserFactory.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/statements/ClassStatementSyntax/ClassStatementSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"

namespace flow_wing {
namespace parser {

ClassStatementParser::ClassStatementParser(ParserContext *ctx) : m_ctx(ctx) {}

std::unique_ptr<syntax::StatementSyntax> ClassStatementParser::parse() {
  auto class_keyword_token =
      m_ctx->match(lexer::TokenKind::kClassKeyword); // class

  auto class_name_identifier_expression =
      std::make_unique<IdentifierExpressionParser>(m_ctx)
          ->parse(); // class_name

  const syntax::SyntaxToken *extends_keyword_token = nullptr;
  std::unique_ptr<syntax::ExpressionSyntax> parent_class_identifier_expression =
      nullptr;

  if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kExtendsKeyword) {
    extends_keyword_token =
        m_ctx->match(lexer::TokenKind::kExtendsKeyword); // extends

    parent_class_identifier_expression =
        std::make_unique<IdentifierExpressionParser>(m_ctx)
            ->parse(); // parent_class_name
  }

  auto open_brace_token = m_ctx->match(lexer::TokenKind::kOpenBraceToken); // {

  auto class_member_statements =
      std::vector<std::unique_ptr<syntax::StatementSyntax>>();

  while (m_ctx->getCurrentTokenKind() != lexer::TokenKind::kCloseBraceToken &&
         m_ctx->getCurrentTokenKind() != lexer::TokenKind::kEndOfFileToken) {

    if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kFunctionKeyword) {
      class_member_statements.push_back(
          std::make_unique<FunctionStatementParser>(m_ctx)->parse());
    } else if (m_ctx->getCurrentTokenKind() ==
                   lexer::TokenKind::kIdentifierToken &&
               m_ctx->peek(1) != nullptr &&
               m_ctx->peek(1)->getTokenKind() ==
                   lexer::TokenKind::kOpenParenthesisToken) {
      class_member_statements.push_back(
          std::make_unique<FunctionStatementParser>(m_ctx)->parse());
    } else {
      class_member_statements.push_back(
          StatementParserFactory::create(*m_ctx)
              ->parse()); // CustomTypeStatement, VariableDeclaration, ...
    }
  }

  auto close_brace_token =
      m_ctx->match(lexer::TokenKind::kCloseBraceToken); // }

  return std::make_unique<syntax::ClassStatementSyntax>(
      class_keyword_token, std::move(class_name_identifier_expression),
      extends_keyword_token, std::move(parent_class_identifier_expression),
      open_brace_token, std::move(class_member_statements), close_brace_token);
}
} // namespace parser
} // namespace flow_wing
