#pragma once
#include "ExpressionParser.h"
#include "ParenthesizedExpressionParser/ParenthesizedExpressionParser.h"

class PrimaryExpressionParserFactory {
public:
  static std::unique_ptr<ExpressionParser>
  createPrimaryExpressionParser(const SyntaxKindUtils::SyntaxKind &kind);
};