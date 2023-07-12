
#include "Common.h"
namespace SyntaxKindUtils {
enum SyntaxKind {
  NumberToken,
  WhitespaceToken,
  PlusToken,
  MinusToken,
  StarToken,
  SlashToken,
  OpenParenthesisToken,
  CloseParenthesisToken,
  BadToken,
  EndOfFileToken,
  NumberExpression,
  BinaryExpression,
  ParenthesizedExpression,
  CompilationUnit,
};
std::map<SyntaxKind, std::string> enum_to_string_map;
bool isInt32(const std::string &str) {
  try {
    size_t pos;
    int32_t number = std::stoi(str, &pos);
    return pos == str.size() && number >= std::numeric_limits<int32_t>::min() &&
           number <= std::numeric_limits<int32_t>::max();
  } catch (const std::exception &) {
    return false;
  }
}

void init_enum_to_string_map() {
  enum_to_string_map[SyntaxKind::NumberToken] = "NumberToken";
  enum_to_string_map[SyntaxKind::WhitespaceToken] = "WhitespaceToken";
  enum_to_string_map[SyntaxKind::PlusToken] = "PlusToken";
  enum_to_string_map[SyntaxKind::MinusToken] = "MinusToken";
  enum_to_string_map[SyntaxKind::StarToken] = "StarToken";
  enum_to_string_map[SyntaxKind::SlashToken] = "SlashToken";
  enum_to_string_map[SyntaxKind::OpenParenthesisToken] = "OpenParenthesisToken";
  enum_to_string_map[SyntaxKind::CloseParenthesisToken] =
      "CloseParenthesisToken";
  enum_to_string_map[SyntaxKind::BadToken] = "BadToken";
  enum_to_string_map[SyntaxKind::EndOfFileToken] = "EndOfFileToken";
  enum_to_string_map[SyntaxKind::NumberExpression] = "NumberExpression";
  enum_to_string_map[SyntaxKind::BinaryExpression] = "BinaryExpression";
  enum_to_string_map[SyntaxKind::ParenthesizedExpression] =
      "ParenthesizedExpression";
  enum_to_string_map[SyntaxKind::CompilationUnit] = "CompilationUnit";
}
} // namespace SyntaxKindUtils
