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

#include "ForStatementParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/ASTBuilder/parsers/StatementParser/StatementParserFactory.h"
#include "src/ASTBuilder/parsers/StatementParser/VariableDeclarationParser/VariableDeclarationParser.h"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/syntax/OperatorPrecedence/OperatorPrecedence.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/AssignmentExpressionSyntax/AssignmentExpressionSyntax.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/statements/ForStatementSyntax/ForStatementSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"
#include "src/syntax/statements/VariableDeclarationSyntax/VariableDeclarationSyntax.h"
namespace flow_wing {
namespace parser {

ForStatementParser::ForStatementParser(ParserContext *ctx) : m_ctx(ctx) {}

std::unique_ptr<syntax::StatementSyntax> ForStatementParser::parse() {
  auto for_keyword = m_ctx->match(lexer::TokenKind::kForKeyword); // for

  auto open_parenthesis_token =
      m_ctx->matchIf(lexer::TokenKind::kOpenParenthesisToken); // (

  std::unique_ptr<syntax::StatementSyntax> variable_declaration = nullptr;
  std::unique_ptr<syntax::ExpressionSyntax> assignment_expression = nullptr;

  if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kVarKeyword) {
    variable_declaration = std::make_unique<VariableDeclarationParser>(m_ctx)
                               ->parse(); // var x: int = 5
  } else {
    assignment_expression =
        std::make_unique<syntax::AssignmentExpressionSyntax>(
            PrecedenceAwareExpressionParser::parse(m_ctx),
            m_ctx->match(lexer::TokenKind::kEqualsToken),
            PrecedenceAwareExpressionParser::parse(m_ctx)); // x = 5
  }

  auto to_keyword = m_ctx->match(lexer::TokenKind::kToKeyword); // to

  const int colon_precedence = syntax::OperatorPrecedence::getInfixPrecedence(
      lexer::TokenKind::kColonToken);
  auto upper_bound =
      PrecedenceAwareExpressionParser::parse(m_ctx, colon_precedence); // 10

  const syntax::SyntaxToken *step_colon_token = nullptr;
  std::unique_ptr<syntax::ExpressionSyntax> step = nullptr;

  if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kColonToken) {
    step_colon_token = m_ctx->match(lexer::TokenKind::kColonToken); // :
    step = PrecedenceAwareExpressionParser::parse(m_ctx);           // 2
  }

  auto close_parenthesis_token =
      open_parenthesis_token
          ? m_ctx->match(lexer::TokenKind::kCloseParenthesisToken) // )
          : nullptr;

  auto body = StatementParserFactory::create(*m_ctx)->parse(); // statement

  return std::make_unique<syntax::ForStatementSyntax>(
      for_keyword, std::move(open_parenthesis_token),
      std::move(variable_declaration), std::move(assignment_expression),
      to_keyword, std::move(upper_bound), std::move(step_colon_token),
      std::move(step), std::move(close_parenthesis_token), std::move(body));

  /*
  for (var x: int = 5 to 10 : 2) {
      print(x);
    }
    for (x = 5 to 10) {
      print(x);
    }
    for (x = 5 to 10 : 2) {
      print(x);
    }

    for x = 5 to 10 {
      print(x);
    }
  */
}
} // namespace parser
} // namespace flow_wing
