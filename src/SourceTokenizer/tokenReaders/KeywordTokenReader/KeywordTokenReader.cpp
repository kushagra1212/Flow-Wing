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

#include "KeywordTokenReader.h"
#include "src/SourceTokenizer/SourceTokenizer.h"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace lexer {

static const std::unordered_map<std::string, lexer::TokenKind> kKeywords = {
    {"true", lexer::TokenKind::kTrueKeyword},
    {"false", lexer::TokenKind::kFalseKeyword},
    {"var", lexer::TokenKind::kVarKeyword},
    {"if", lexer::TokenKind::kIfKeyword},
    {"or", lexer::TokenKind::kOrKeyword},
    {"else", lexer::TokenKind::kElseKeyword},
    {"while", lexer::TokenKind::kWhileKeyword},
    {"for", lexer::TokenKind::kForKeyword},
    {"fun", lexer::TokenKind::kFunctionKeyword},
    {"to", lexer::TokenKind::kToKeyword},
    {"continue", lexer::TokenKind::kContinueKeyword},
    {"break", lexer::TokenKind::kBreakKeyword},
    {"return", lexer::TokenKind::kReturnKeyword},
    {"const", lexer::TokenKind::kConstKeyword},
    {"nthg", lexer::TokenKind::kNthgKeyword},
    {"int", lexer::TokenKind::kInt32Keyword},
    {"int8", lexer::TokenKind::kInt8Keyword},
    {"char", lexer::TokenKind::kCharKeyword},
    {"int64", lexer::TokenKind::kInt64Keyword},
    {"bool", lexer::TokenKind::kBoolKeyword},
    {"str", lexer::TokenKind::kStrKeyword},
    {"deci", lexer::TokenKind::kDeciKeyword},
    {"deci32", lexer::TokenKind::kDeci32Keyword},
    {"null", lexer::TokenKind::kNirastKeyword},
    {"bring", lexer::TokenKind::kBringKeyword},
    {"super", lexer::TokenKind::kSuperKeyword},
    {"expose", lexer::TokenKind::kExposeKeyword},
    {"from", lexer::TokenKind::kFromKeyword},
    {"fill", lexer::TokenKind::kFillKeyword},
    {"type", lexer::TokenKind::kTypeKeyword},
    {"decl", lexer::TokenKind::kDeclKeyword},
    {"new", lexer::TokenKind::kNewKeyword},
    {"class", lexer::TokenKind::kClassKeyword},
    {"inout", lexer::TokenKind::kInOutKeyword},
    {"extends", lexer::TokenKind::kExtendsKeyword},
    {"as", lexer::TokenKind::kAsKeyword},
    {"module", lexer::TokenKind::kModuleKeyword},
    {"switch", lexer::TokenKind::kSwitchKeyword},
    {"case", lexer::TokenKind::kCaseKeyword},
    {"default", lexer::TokenKind::kDefaultKeyword},
    // Reserved Keywords
    {"unknown", lexer::TokenKind::kReservedUnknownKeyword},
};

std::unique_ptr<syntax::SyntaxToken>
KeywordTokenReader::readToken(SourceTokenizer &lexer) {
  const size_t &start = lexer.position();

  while (!lexer.isEOLorEOF() &&
         (isalnum(lexer.currentChar()) || lexer.currentChar() == '_')) {
    lexer.advancePosition();
  }
  const size_t &length = lexer.position() - start;
  const std::string &text =
      lexer.getLine(lexer.lineNumber()).substr(start, length);

  const lexer::TokenKind &keywordKind = getKeywordKind(text);

  switch (keywordKind) {

  case lexer::TokenKind::kTrueKeyword:
    return std::make_unique<syntax::SyntaxToken>(
        keywordKind, text, true,
        diagnostic::SourceLocation(lexer.lineNumber(), start, text.size()));

  case lexer::TokenKind::kFalseKeyword:
    return std::make_unique<syntax::SyntaxToken>(
        keywordKind, text, false,
        diagnostic::SourceLocation(lexer.lineNumber(), start, text.size()));

  case lexer::TokenKind::kIdentifierToken:
    return std::make_unique<syntax::SyntaxToken>(
        lexer::TokenKind::kIdentifierToken, text, text,
        diagnostic::SourceLocation(lexer.lineNumber(), start, text.size()));

  default:
    return std::make_unique<syntax::SyntaxToken>(
        keywordKind, text, text,
        diagnostic::SourceLocation(lexer.lineNumber(), start, text.size()));
  }
}

lexer::TokenKind
KeywordTokenReader::getKeywordKind(const std::string &text) const {
  auto it = kKeywords.find(text);
  if (it != kKeywords.end()) {
    return it->second;
  }
  return lexer::TokenKind::kIdentifierToken;
}

} // namespace lexer
} // namespace flow_wing
