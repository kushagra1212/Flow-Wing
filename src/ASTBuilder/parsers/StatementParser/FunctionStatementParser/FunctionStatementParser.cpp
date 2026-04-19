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

#include "FunctionStatementParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/FunctionParameterExpressionParser/FunctionParameterExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/FunctionReturnTypeExpressionParser/FunctionReturnTypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/IdentifierExpressionParser/IdentifierExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/TypeExpressionParser/TypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/ASTBuilder/parsers/StatementParser/BlockStatementParser/BlockStatementParser.h"
#include "src/ASTBuilder/parsers/StatementParser/StatementParserFactory.h"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/statements/FunctionStatementSyntax/FunctionStatementSyntax.h"
#include "src/syntax/statements/ParameterExpressionSyntax/ParameterExpressionSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"
#include <memory>

namespace flow_wing {
namespace parser {

FunctionStatementParser::FunctionStatementParser(ParserContext *ctx)
    : m_ctx(ctx) {}

std::unique_ptr<syntax::StatementSyntax> FunctionStatementParser::parse() {
  auto fun_keyword_token =
      m_ctx->matchIf(lexer::TokenKind::kFunctionKeyword); // fun

  auto function_identifier = std::make_unique<IdentifierExpressionParser>(m_ctx)
                                 ->parse(); // function_identifier

  auto open_parenthesis_token =
      m_ctx->match(lexer::TokenKind::kOpenParenthesisToken); // (

  auto function_parameters =
      std::vector<std::unique_ptr<syntax::ExpressionSyntax>>();

  auto comma_tokens = std::vector<const syntax::SyntaxToken *>();

  auto parameter_expression_parser =
      std::make_unique<FunctionParameterExpressionParser>(m_ctx);

  size_t count = 0;

  while (m_ctx->getCurrentTokenKind() !=
             lexer::TokenKind::kCloseParenthesisToken &&
         m_ctx->getCurrentTokenKind() != lexer::TokenKind::kEndOfFileToken) {

    if (count)
      comma_tokens.push_back(m_ctx->match(lexer::TokenKind::kCommaToken)); // ,

    function_parameters.push_back(
        parameter_expression_parser->parse()); //  x: int

    count++;
  }

  auto close_parenthesis_token =
      m_ctx->match(lexer::TokenKind::kCloseParenthesisToken); // )

  auto right_arrow_token =
      m_ctx->matchIf(lexer::TokenKind::kRightArrowToken); // ->

  std::unique_ptr<syntax::ExpressionSyntax> function_return_type_expression =
      nullptr;

  if (right_arrow_token != nullptr) {
    function_return_type_expression =
        std::make_unique<FunctionReturnTypeExpressionParser>(m_ctx)
            ->parse(); // int
                       // int, str
                       // decl
                       // as  int
  }

  std::unique_ptr<syntax::StatementSyntax> body = nullptr;

  auto decl_keyword = m_ctx->matchIf(lexer::TokenKind::kDeclKeyword); // decl

  if (decl_keyword == nullptr) {
    body = std::make_unique<BlockStatementParser>(m_ctx)->parse(); // { }
  }

  return std::make_unique<syntax::FunctionStatementSyntax>(
      fun_keyword_token, std::move(function_identifier), open_parenthesis_token,
      std::move(function_parameters), comma_tokens, close_parenthesis_token,
      right_arrow_token, std::move(function_return_type_expression),
      decl_keyword, std::move(body));
}
} // namespace parser
} // namespace flow_wing
