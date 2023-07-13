
#ifndef SYNTAXKINDUTILS_H
#define SYNTAXKINDUTILS_H
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
extern std::map<SyntaxKind, std::string> enum_to_string_map;
bool isInt32(const std::string &str);

void init_enum_to_string_map();
} // namespace SyntaxKindUtils

#endif // SYNTAXKINDUTILS_H