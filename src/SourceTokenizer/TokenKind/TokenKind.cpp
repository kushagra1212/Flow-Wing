/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 */
#include "TokenKind.h"
#include <unordered_map>

namespace flow_wing {
namespace lexer {

const std::string &toString(TokenKind kind) {
  static const std::unordered_map<TokenKind, std::string> kKindStrings = {
      // Tokens
      {TokenKind::kWhitespaceToken, "WhitespaceToken"},
      {TokenKind::kPlusToken, "PlusToken"},
      {TokenKind::kMinusToken, "MinusToken"},
      {TokenKind::kStarToken, "StarToken"},
      {TokenKind::kSlashToken, "SlashToken"},
      {TokenKind::kOpenParenthesisToken, "OpenParenthesisToken"},
      {TokenKind::kCloseParenthesisToken, "CloseParenthesisToken"},
      {TokenKind::kBadToken, "BadToken"},
      {TokenKind::kEndOfFileToken, "EndOfFileToken"},
      {TokenKind::kAmpersandAmpersandToken, "AmpersandAmpersandToken"},
      {TokenKind::kPipePipeToken, "PipePipeToken"},
      {TokenKind::kEqualsEqualsToken, "EqualsEqualsToken"},
      {TokenKind::kEqualsToken, "EqualsToken"},
      {TokenKind::kBangToken, "BangToken"},
      {TokenKind::kBangEqualsToken, "BangEqualsToken"},
      {TokenKind::kLessOrEqualsToken, "LessOrEqualsToken"},
      {TokenKind::kLessToken, "LessToken"},
      {TokenKind::kQuestionToken, "QuestionToken"},
      {TokenKind::kGreaterOrEqualsToken, "GreaterOrEqualsToken"},
      {TokenKind::kGreaterToken, "GreaterToken"},
      {TokenKind::kColonToken, "ColonToken"},
      {TokenKind::kCommaToken, "CommaToken"},
      {TokenKind::kEndOfLineToken, "EndOfLineToken"},
      {TokenKind::kSlashHashToken, "SlashHashToken"},
      {TokenKind::kHashSlashToken, "HashSlashToken"},
      {TokenKind::kHashToken, "HashToken"},
      {TokenKind::kSlashSlashToken, "SlashSlashToken"},
      {TokenKind::kDotToken, "DotToken"},
      {TokenKind::kLeftArrowToken, "kLeftArrowToken"},
      {TokenKind::kRightArrowToken, "RightArrowToken"},
      {TokenKind::kColonColonToken, "ColonColonToken"},

      // Literals
      {TokenKind::kIntegerLiteralToken, "IntegerLiteralToken"},
      {TokenKind::kInt64LiteralToken, "Int64LiteralToken"},
      {TokenKind::kFloatLiteralToken, "FloatLiteralToken"},
      {TokenKind::kDoubleLiteralToken, "DoubleLiteralToken"},
      {TokenKind::kCharacterLiteralToken, "CharacterLiteralToken"},
      {TokenKind::kStringLiteralToken, "StringLiteralToken"},
      {TokenKind::kTemplateStringLiteralToken, "TemplateStringLiteralToken"},

      // Bitwise
      {TokenKind::kAmpersandToken, "AmpersandToken"},
      {TokenKind::kPipeToken, "PipeToken"},
      {TokenKind::kCaretToken, "CaretToken"},
      {TokenKind::kTildeToken, "TildeToken"},
      {TokenKind::kPercentToken, "PercentToken"},

      // Braces
      {TokenKind::kOpenBraceToken, "OpenBraceToken"},
      {TokenKind::kCloseBraceToken, "CloseBraceToken"},
      {TokenKind::kOpenBracketToken, "OpenBracketToken"},
      {TokenKind::kCloseBracketToken, "CloseBracketToken"},

      // Strings,
      {TokenKind::kIdentifierToken, "IdentifierToken"},

      // Keywords
      {TokenKind::kTrueKeyword, "TrueKeyword"},
      {TokenKind::kFalseKeyword, "FalseKeyword"},
      {TokenKind::kVarKeyword, "VarKeyword"},
      {TokenKind::kConstKeyword, "ConstKeyword"},
      {TokenKind::kIfKeyword, "IfKeyword"},
      {TokenKind::kElseKeyword, "ElseKeyword"},
      {TokenKind::kWhileKeyword, "WhileKeyword"},
      {TokenKind::kForKeyword, "ForKeyword"},
      {TokenKind::kToKeyword, "ToKeyword"},
      {TokenKind::kFunctionKeyword, "FunctionKeyword"},
      {TokenKind::kContinueKeyword, "ContinueKeyword"},
      {TokenKind::kBreakKeyword, "BreakKeyword"},
      {TokenKind::kReturnKeyword, "ReturnKeyword"},
      {TokenKind::kOrKeyword, "OrKeyword"},
      {TokenKind::kExposeKeyword, "ExposeKeyword"},
      {TokenKind::kFromKeyword, "FromKeyword"},
      {TokenKind::kFillKeyword, "FillKeyword"},
      {TokenKind::kTypeKeyword, "TypeKeyword"},
      {TokenKind::kDeclKeyword, "DeclKeyword"},
      {TokenKind::kNewKeyword, "NewKeyword"},
      {TokenKind::kClassKeyword, "ClassKeyword"},
      {TokenKind::kInOutKeyword, "InOutKeyword"},
      {TokenKind::kExtendsKeyword, "ExtendsKeyword"},
      {TokenKind::kAsKeyword, "AsKeyword"},
      {TokenKind::kSwitchKeyword, "SwitchKeyword"},
      {TokenKind::kCaseKeyword, "CaseKeyword"},
      {TokenKind::kDefaultKeyword, "DefaultKeyword"},
      {TokenKind::kModuleKeyword, "ModuleKeyword"},
      {TokenKind::kNthgKeyword, "NthgKeyword"},
      {TokenKind::kNirastKeyword, "NirastKeyword"},
      {TokenKind::kBringKeyword, "BringKeyword"},
      {TokenKind::kInt32Keyword, "Int32Keyword"},
      {TokenKind::kInt64Keyword, "Int64Keyword"},
      {TokenKind::kInt8Keyword, "Int8Keyword"},
      {TokenKind::kCharKeyword, "CharKeyword"},
      {TokenKind::kDeciKeyword, "DeciKeyword"},
      {TokenKind::kDeci32Keyword, "Deci32Keyword"},
      {TokenKind::kStrKeyword, "StrKeyword"},
      {TokenKind::kBoolKeyword, "BoolKeyword"},

      // Comments
      {TokenKind::kSingleLineCommentToken, "SingleLineCommentToken"},
      {TokenKind::kMultiLineCommentToken, "MultiLineCommentToken"},

      // Reserved Keywords
      {TokenKind::kReservedUnknownKeyword, "ReservedUnknownKeyword"},
      {TokenKind::kSemicolonToken, "ReservedSemicolonToken"},
  };

  static const std::string kNotDefined = "NotDefined";
  auto it = kKindStrings.find(kind);
  if (it != kKindStrings.end()) {
    return it->second;
  }
  return kNotDefined;
}

bool isType(TokenKind kind) {
  switch (kind) {
  case TokenKind::kBoolKeyword:
  case TokenKind::kInt8Keyword:
  case TokenKind::kInt32Keyword:
  case TokenKind::kInt64Keyword:
  case TokenKind::kDeciKeyword:
  case TokenKind::kDeci32Keyword:
  case TokenKind::kStrKeyword:
  case TokenKind::kCharKeyword:
    return true;
  default:
    return false;
  }
}

} // namespace lexer
} // namespace flow_wing
