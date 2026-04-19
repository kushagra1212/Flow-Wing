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

#include "CaseStatementParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/ASTBuilder/parsers/StatementParser/StatementParserFactory.h"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/syntax/OperatorPrecedence/OperatorPrecedence.h"
#include "src/syntax/statements/CaseStatementSyntax/CaseStatementSyntax.h"
#include "src/syntax/statements/DefaultCaseStatementSyntax/DefaultCaseStatementSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"
namespace flow_wing {
namespace parser {

CaseStatementParser::CaseStatementParser(ParserContext *ctx) : m_ctx(ctx) {}

std::unique_ptr<syntax::StatementSyntax> CaseStatementParser::parse() {

  if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kDefaultKeyword) {
    auto default_keyword =
        m_ctx->match(lexer::TokenKind::kDefaultKeyword); // default

    auto colon_token = m_ctx->match(lexer::TokenKind::kColonToken); // :

    auto statement =
        StatementParserFactory::create(*m_ctx)->parse(); // statement

    return std::make_unique<syntax::DefaultCaseStatementSyntax>(
        default_keyword, colon_token, std::move(statement));

    /*
     default: {
     print("default case");
     }
    */

  } else {
    auto case_keyword = m_ctx->match(lexer::TokenKind::kCaseKeyword); // case

    const int colon_precedence = syntax::OperatorPrecedence::getInfixPrecedence(
        lexer::TokenKind::kColonToken);
    auto case_expression = PrecedenceAwareExpressionParser::parse(
        m_ctx, colon_precedence); // case_expression

    auto colon_token = m_ctx->match(lexer::TokenKind::kColonToken); // :

    auto statement =
        StatementParserFactory::create(*m_ctx)->parse(); // statement

    return std::make_unique<syntax::CaseStatementSyntax>(
        case_keyword, std::move(case_expression), colon_token,
        std::move(statement));
    /*
     case a > 0 && a < 10: {
     print("a is between 0 and 10");
     }
    */
  }
}
} // namespace parser
} // namespace flow_wing
