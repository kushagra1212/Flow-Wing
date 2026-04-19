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

#include "VariableDeclarationParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/IdentifierExpressionParser/IdentifierExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/TypeExpressionParser/TypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/DeclaratorExpressionSyntax/DeclaratorExpressionSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"
#include "src/syntax/statements/VariableDeclarationSyntax/VariableDeclarationSyntax.h"
namespace flow_wing {
namespace parser {

VariableDeclarationParser::VariableDeclarationParser(ParserContext *ctx)
    : m_ctx(ctx) {}

std::unique_ptr<syntax::StatementSyntax> VariableDeclarationParser::parse() {

  const syntax::SyntaxToken *const_keyword_token = nullptr,
                            *var_keyword_token = nullptr;
  if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kConstKeyword) {
    const_keyword_token =
        m_ctx->match(lexer::TokenKind::kConstKeyword); // const
  } else {
    var_keyword_token = m_ctx->match(lexer::TokenKind::kVarKeyword); // var
  }

  auto declarators =
      std::vector<std::unique_ptr<syntax::DeclaratorExpressionSyntax>>();
  auto comma_tokens = std::vector<const syntax::SyntaxToken *>();

  size_t count = 0;

  do {

    if (count)
      comma_tokens.push_back(m_ctx->match(lexer::TokenKind::kCommaToken)); // ,

    auto identifier_token = std::make_unique<IdentifierExpressionParser>(m_ctx)
                                ->parse(); // variable_identifier

    const syntax::SyntaxToken *colon_token = nullptr;
    std::unique_ptr<syntax::ExpressionSyntax> type_expression = nullptr;

    if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kColonToken) {
      colon_token = m_ctx->match(lexer::TokenKind::kColonToken); // :

      type_expression = std::make_unique<TypeExpressionParser>(m_ctx)
                            ->parse(); // type_expression
    }

    declarators.push_back(std::make_unique<syntax::DeclaratorExpressionSyntax>(
        std::move(identifier_token), colon_token,
        std::move(type_expression))); // variable_identifier: type_expression

    count++;
  } while (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kCommaToken);

  auto equals_token = m_ctx->matchIf(lexer::TokenKind::kEqualsToken); // =
  auto left_arrow_token =
      m_ctx->matchIf(lexer::TokenKind::kLeftArrowToken); // <-

  std::unique_ptr<syntax::ExpressionSyntax> initializer = nullptr;
  if (equals_token || left_arrow_token) {
    initializer =
        PrecedenceAwareExpressionParser::parse(m_ctx); // initializer expression
  }

  return std::make_unique<syntax::VariableDeclarationSyntax>(
      const_keyword_token, var_keyword_token, std::move(declarators),
      comma_tokens,
      std::move(initializer)); // var y: int = 2
                               // var x: int, y: int = 2, 5
                               // var x
                               // var y = 5
                               // var x, y =  5, 6
}
} // namespace parser
} // namespace flow_wing
