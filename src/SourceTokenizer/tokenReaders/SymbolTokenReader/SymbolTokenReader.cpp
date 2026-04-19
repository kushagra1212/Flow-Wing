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

#include "SymbolTokenReader.h"
#include "src/SourceTokenizer/SourceTokenizer.h"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace lexer {

static const std::unordered_map<std::string, lexer::TokenKind> kSymbols = {
    {"+", lexer::TokenKind::kPlusToken},
    {"-", lexer::TokenKind::kMinusToken},
    {"*", lexer::TokenKind::kStarToken},
    {";", lexer::TokenKind::kSemicolonToken},
    {",", lexer::TokenKind::kCommaToken},
    {"{", lexer::TokenKind::kOpenBraceToken},
    {"}", lexer::TokenKind::kCloseBraceToken},
    {"[", lexer::TokenKind::kOpenBracketToken},
    {"]", lexer::TokenKind::kCloseBracketToken},
    {"#", lexer::TokenKind::kHashToken},
    {"(", lexer::TokenKind::kOpenParenthesisToken},
    {")", lexer::TokenKind::kCloseParenthesisToken},
    {"^", lexer::TokenKind::kCaretToken},
    {"%", lexer::TokenKind::kPercentToken},
    {"~", lexer::TokenKind::kTildeToken},
    {":", lexer::TokenKind::kColonToken},
    {"::", lexer::TokenKind::kColonColonToken},
    {".", lexer::TokenKind::kDotToken},
    {"&", lexer::TokenKind::kAmpersandToken},
    {"&&", lexer::TokenKind::kAmpersandAmpersandToken},
    {"//", lexer::TokenKind::kSlashSlashToken},
    {"/", lexer::TokenKind::kSlashToken},
    {"||", lexer::TokenKind::kPipePipeToken},
    {"|", lexer::TokenKind::kPipeToken},
    {"=", lexer::TokenKind::kEqualsToken},
    {"==", lexer::TokenKind::kEqualsEqualsToken},
    {"!", lexer::TokenKind::kBangToken},
    {"!=", lexer::TokenKind::kBangEqualsToken},
    {"<", lexer::TokenKind::kLessToken},
    {"<-", lexer::TokenKind::kLeftArrowToken},
    {"->", lexer::TokenKind::kRightArrowToken},
    {"<=", lexer::TokenKind::kLessOrEqualsToken},
    {">", lexer::TokenKind::kGreaterToken},
    {">=", lexer::TokenKind::kGreaterOrEqualsToken},
    {"?", lexer::TokenKind::kQuestionToken}};

std::unique_ptr<syntax::SyntaxToken>
SymbolTokenReader::readToken(SourceTokenizer &lexer) {
  const size_t start = lexer.position();

  const std::string single_char_symbol(1, lexer.currentChar());
  lexer.advancePosition();
  const std::string &two_char_symbol = single_char_symbol + lexer.currentChar();

  auto token = kSymbols.find(two_char_symbol);

  if (token != kSymbols.end()) {
    lexer.advancePosition();
    return std::make_unique<syntax::SyntaxToken>(
        token->second, two_char_symbol, std::any(),
        diagnostic::SourceLocation(lexer.lineNumber(), start,
                                   two_char_symbol.size()));
  }

  token = kSymbols.find(single_char_symbol);

  if (token != kSymbols.end()) {
    return std::make_unique<syntax::SyntaxToken>(
        token->second, single_char_symbol, std::any(),
        diagnostic::SourceLocation(lexer.lineNumber(), start,
                                   single_char_symbol.size()));
  }

  return badCharacterToken(lexer, single_char_symbol, start);
}

std::unique_ptr<syntax::SyntaxToken>
SymbolTokenReader::badCharacterToken(SourceTokenizer &lexer,
                                     const std::string &single_char_symbol,
                                     const size_t &start) {

  std::unique_ptr<syntax::SyntaxToken> badSyntaxToken =
      std::make_unique<syntax::SyntaxToken>(
          lexer::TokenKind::kBadToken, single_char_symbol, std::any(),
          diagnostic::SourceLocation(lexer.lineNumber(), start,
                                     single_char_symbol.size()));

  lexer.reportError(flow_wing::diagnostic::DiagnosticCode::kBadCharacterInput,
                    {single_char_symbol}, badSyntaxToken->getSourceLocation());

  return badSyntaxToken;
}
} // namespace lexer
} // namespace flow_wing
