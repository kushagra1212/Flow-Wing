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

#include "OperatorPrecedence.h"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"

namespace flow_wing {
namespace syntax {

int OperatorPrecedence::getPrefixPrecedence(lexer::TokenKind kind) {
  switch (kind) {
  case lexer::TokenKind::kPlusToken:
  case lexer::TokenKind::kMinusToken:
  case lexer::TokenKind::kBangToken:
  case lexer::TokenKind::kTildeToken:
  case lexer::TokenKind::kNewKeyword:
    return 13;
  default:
    return 0;
  }
}
int OperatorPrecedence::getInfixPrecedence(lexer::TokenKind kind) {
  switch (kind) {
  case lexer::TokenKind::kStarToken:
  case lexer::TokenKind::kSlashSlashToken:
  case lexer::TokenKind::kSlashToken:
  case lexer::TokenKind::kPercentToken:
    return 12;
  case lexer::TokenKind::kPlusToken:
  case lexer::TokenKind::kMinusToken:
    return 11;
  case lexer::TokenKind::kLessToken:
  case lexer::TokenKind::kLessOrEqualsToken:
  case lexer::TokenKind::kGreaterToken:
  case lexer::TokenKind::kGreaterOrEqualsToken:
    return 10;
  case lexer::TokenKind::kEqualsEqualsToken:
  case lexer::TokenKind::kBangEqualsToken:
    return 9;
  case lexer::TokenKind::kAmpersandToken:
    return 8;
  case lexer::TokenKind::kCaretToken:
    return 7;
  case lexer::TokenKind::kPipeToken:
    return 6;
  case lexer::TokenKind::kAmpersandAmpersandToken:
    return 5;
  case lexer::TokenKind::kPipePipeToken:
    return 4;
  case lexer::TokenKind::kColonToken:
    return 3;
  case lexer::TokenKind::kCommaToken:
  case lexer::TokenKind::kQuestionToken:
    return 2;
  case lexer::TokenKind::kLeftArrowToken:
  case lexer::TokenKind::kEqualsToken:
    return 1;
  default:
    return 0;
  }
}

int OperatorPrecedence::getPostfixPrecedence(lexer::TokenKind kind) {
  switch (kind) {
  case lexer::TokenKind::kOpenBracketToken:     // For array types/indexing
  case lexer::TokenKind::kOpenParenthesisToken: // For function calls
  case lexer::TokenKind::kDotToken:             // For member access
  case lexer::TokenKind::kColonColonToken: // For module member access (value)
    return 13;
  default:
    return 0;
  }
}

} // namespace syntax
} // namespace flow_wing
