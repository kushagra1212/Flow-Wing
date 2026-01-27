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

#include "src/ASTBuilder/parsers/ExpressionParser/ErrorExpressionParser/ErrorExpressionParser.hpp"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/compiler/diagnostics/Diagnostic.h"
#include "src/compiler/diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/ErrorExpressionSyntax/ErrorExpressionSyntax.hpp"
#include "src/utils/LogConfig.h"
namespace flow_wing {
namespace parser {

ErrorExpressionParser::ErrorExpressionParser(ParserContext *ctx) : m_ctx(ctx) {}

std::unique_ptr<syntax::ExpressionSyntax> ErrorExpressionParser::parse() {

  auto bad_token = m_ctx->getCurrent();

  m_ctx->reportError(diagnostic::DiagnosticCode::kUnexpectedToken,
                     {lexer::toString(bad_token->getTokenKind()),
                      "Valid Expression or Statement"},
                     bad_token->getSourceLocation());

  std::vector<const syntax::SyntaxToken *> skipped_tokens;
  PARSER_DEBUG_LOG("Skipped tokens: ",
                   lexer::toString(m_ctx->getCurrentTokenKind()));

  skipped_tokens.push_back(m_ctx->nextToken());

  if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kEndOfFileToken) {

    flow_wing::diagnostic::Diagnostic diagnostic =
        m_ctx->getCompilationContext()
            .getDiagnostics()
            ->getDiagnostics()[m_ctx->getCompilationContext()
                                   .getDiagnostics()
                                   ->getDiagnostics()
                                   .size() -
                               1];

    return std::make_unique<syntax::ErrorExpressionSyntax>(skipped_tokens,
                                                           diagnostic);
  }

  while (!isExpressionDelimiter(m_ctx->getCurrentTokenKind())) {
    PARSER_DEBUG_LOG("Skipping garbage token: ",
                     lexer::toString(m_ctx->getCurrentTokenKind()));
    skipped_tokens.push_back(m_ctx->nextToken());

    if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kEndOfFileToken) {
      break;
    }
  }

  flow_wing::diagnostic::Diagnostic diagnostic =
      m_ctx->getCompilationContext()
          .getDiagnostics()
          ->getDiagnostics()[m_ctx->getCompilationContext()
                                 .getDiagnostics()
                                 ->getDiagnostics()
                                 .size() -
                             1];

  return std::make_unique<syntax::ErrorExpressionSyntax>(skipped_tokens,
                                                         diagnostic);
}

bool ErrorExpressionParser::isExpressionDelimiter(
    lexer::TokenKind token_kind) const {
  switch (token_kind) {

  case lexer::TokenKind::kCloseBraceToken:
  case lexer::TokenKind::kCloseBracketToken:
  case lexer::TokenKind::kCloseParenthesisToken:
  case lexer::TokenKind::kVarKeyword:
  case lexer::TokenKind::kConstKeyword:
  case lexer::TokenKind::kFunctionKeyword:
  case lexer::TokenKind::kClassKeyword:
  case lexer::TokenKind::kModuleKeyword:
  case lexer::TokenKind::kTypeKeyword:
  case lexer::TokenKind::kSwitchKeyword:
  case lexer::TokenKind::kBringKeyword:
  case lexer::TokenKind::kExposeKeyword:
  case lexer::TokenKind::kForKeyword:
  case lexer::TokenKind::kWhileKeyword:
  case lexer::TokenKind::kIfKeyword:
  case lexer::TokenKind::kMultiLineCommentToken:
  case lexer::TokenKind::kSingleLineCommentToken:
  case lexer::TokenKind::kOpenBraceToken:
  case lexer::TokenKind::kOpenBracketToken:
  case lexer::TokenKind::kOpenParenthesisToken:
    return true;
  default:
    break;
  }

  return false;
}

} // namespace parser
} // namespace flow_wing
