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

#include "FunctionTypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/TypeExpressionParser/TypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/FunctionTypeExpressionSyntax/FunctionTypeExpressionSyntax.h"
#include <unordered_map>
#include <vector>

namespace flow_wing {
namespace parser {

FunctionTypeExpressionParser::FunctionTypeExpressionParser(ParserContext *ctx)
    : m_ctx(ctx) {}

std::unique_ptr<syntax::ExpressionSyntax>
FunctionTypeExpressionParser::parse() {

  auto open_bracket_token =
      m_ctx->match(lexer::TokenKind::kOpenBracketToken); // [

  auto open_parenthesis_token =
      m_ctx->match(lexer::TokenKind::kOpenParenthesisToken); // (

  size_t parameterCount = 0;
  std::vector<std::unique_ptr<syntax::ExpressionSyntax>> parameter_types;
  std::vector<const syntax::SyntaxToken *> parameter_comma_tokens;
  std::unordered_map<size_t, const syntax::SyntaxToken *>
      as_parameter_keywords_table, constant_keyword_table, inout_keyword_table;

  while (m_ctx->getCurrentTokenKind() !=
             lexer::TokenKind::kCloseParenthesisToken &&
         m_ctx->getCurrentTokenKind() != lexer::TokenKind::kEndOfFileToken) {

    if (parameterCount) {
      parameter_comma_tokens.push_back(
          m_ctx->match(lexer::TokenKind::kCommaToken)); // ,
    }

    const syntax::SyntaxToken *as_keyword = nullptr, *const_keyword = nullptr,
                              *inout_keyword = nullptr;

    if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kConstKeyword) {
      const_keyword = m_ctx->match(lexer::TokenKind::kConstKeyword); // const
      constant_keyword_table.insert({parameterCount, const_keyword});
    }

    if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kInOutKeyword) {
      inout_keyword = m_ctx->match(lexer::TokenKind::kInOutKeyword); // inout
      inout_keyword_table.insert({parameterCount, inout_keyword});
    }

    if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kAsKeyword) {
      as_keyword = m_ctx->match(lexer::TokenKind::kAsKeyword); // as
      as_parameter_keywords_table.insert({parameterCount, as_keyword});
    }

    if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kCommaToken) {
      parameter_types.push_back(nullptr);
    } else {
      // parameter type to avoid missing module name prefix
      parameter_types.push_back(
          std::make_unique<parser::TypeExpressionParser>(m_ctx)
              ->parse()); // [parameter_type] or [parameter_type,
                          // parameter_type] or [module_name::parameter_type]
    }

    parameterCount++;
  }

  auto close_parenthesis_token =
      m_ctx->match(lexer::TokenKind::kCloseParenthesisToken); // )

  auto right_arrow_token = m_ctx->matchIf(lexer::TokenKind::kRightArrowToken);

  const syntax::SyntaxToken *as_return_keyword = nullptr;
  std::vector<std::unique_ptr<syntax::ExpressionSyntax>> return_types;
  std::vector<const syntax::SyntaxToken *> return_comma_tokens;

  if (right_arrow_token) {
    if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kAsKeyword) {
      as_return_keyword = m_ctx->match(lexer::TokenKind::kAsKeyword); // as

      return_types.push_back(
          std::make_unique<parser::TypeExpressionParser>(m_ctx)
              ->parse()); // [return_type]
    } else {

      size_t return_count = 0;
      while (m_ctx->getCurrentTokenKind() !=
                 lexer::TokenKind::kCloseBracketToken &&
             m_ctx->getCurrentTokenKind() !=
                 lexer::TokenKind::kEndOfFileToken) {
        if (return_count) {
          return_comma_tokens.push_back(
              m_ctx->match(lexer::TokenKind::kCommaToken)); // ,
        }

        return_types.push_back(
            std::make_unique<parser::TypeExpressionParser>(m_ctx)
                ->parse()); // [return_type]

        return_count++;
      }
    }
  } else {
    return_types.push_back(nullptr);
  }

  auto close_bracket_token =
      m_ctx->match(lexer::TokenKind::kCloseBracketToken); // ]

  return std::make_unique<syntax::FunctionTypeExpressionSyntax>(
      open_bracket_token, open_parenthesis_token, as_parameter_keywords_table,
      constant_keyword_table, inout_keyword_table, std::move(parameter_types),
      parameter_comma_tokens, close_parenthesis_token, right_arrow_token,
      as_return_keyword, std::move(return_types), close_bracket_token);
}
} // namespace parser
} // namespace flow_wing
