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

#pragma once
#include <string>

namespace flow_wing {
namespace lexer {

enum class TokenKind : int {

  // --- Tokens ---
  kWhitespaceToken,
  kPlusToken,
  kMinusToken,
  kStarToken,
  kSlashToken,
  kOpenParenthesisToken,
  kCloseParenthesisToken,
  kBadToken,
  kEndOfFileToken,
  kAmpersandAmpersandToken,
  kPipePipeToken,
  kEqualsEqualsToken,
  kEqualsToken,
  kBangToken,
  kBangEqualsToken,
  kLessOrEqualsToken,
  kLessToken,
  kQuestionToken,
  kGreaterOrEqualsToken,
  kGreaterToken,
  kSemicolonToken,
  kColonToken,
  kCommaToken,
  kEndOfLineToken,
  kSlashHashToken,
  kHashSlashToken,
  kHashToken,
  kSlashSlashToken,
  kDotToken,
  kLeftArrowToken,
  kRightArrowToken,
  kColonColonToken,

  // --- Keywords ---
  kTrueKeyword,
  kFalseKeyword,
  kVarKeyword,
  kConstKeyword,
  kIfKeyword,
  kElseKeyword,
  kWhileKeyword,
  kForKeyword,
  kToKeyword,
  kFunctionKeyword,
  kContinueKeyword,
  kBreakKeyword,
  kReturnKeyword,
  kOrKeyword,
  kExposeKeyword,
  kFromKeyword,
  kFillKeyword,
  kTypeKeyword,
  kDeclKeyword,
  kNewKeyword,
  kClassKeyword,
  kInOutKeyword,
  kExtendsKeyword,
  kAsKeyword,
  kSwitchKeyword,
  kCaseKeyword,
  kDefaultKeyword,
  kModuleKeyword,
  kNthgKeyword,
  kNirastKeyword,
  kBringKeyword,
  kSuperKeyword,
  kDynKeyword,

  // --- Type Keywords ---
  kInt32Keyword,
  kInt64Keyword,
  kInt8Keyword,
  kCharKeyword,
  kDeciKeyword,
  kDeci32Keyword,
  kStrKeyword,
  kBoolKeyword,

  // --- Bitwise Operators ---
  kAmpersandToken,
  kPipeToken,
  kCaretToken,
  kTildeToken,
  kPercentToken,

  // --- Braces & Brackets ---
  kOpenBraceToken,
  kCloseBraceToken,
  kOpenBracketToken,
  kCloseBracketToken,

  // --- Literals ---
  kIntegerLiteralToken,
  kInt64LiteralToken,
  kFloatLiteralToken,
  kDoubleLiteralToken,
  kCharacterLiteralToken,
  kStringLiteralToken,
  kTemplateStringLiteralToken,
  kIdentifierToken,

  // --- Comments ---
  kSingleLineCommentToken,
  kMultiLineCommentToken,

  // Reserved Keywords
  kReservedUnknownKeyword,
};

const std::string &toString(TokenKind kind);
bool isType(TokenKind kind);

} // namespace lexer
} // namespace flow_wing
