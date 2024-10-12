#include "PrimaryExpressionParserFactory.h"
#include "BracketedExpressionParser/BracketedExpressionParser.h"
#include "CallExpressionParser/CallExpressionParser.h"
#include "CharacterExpressionParser/CharacterExpressionParser.h"
#include "CommaExpressionParser/CommaExpressionParser.h"
#include "DefaultPrimaryExpressionParser/DefaultPrimaryExpressionParser.h"
#include "ExpressionParser.h"
#include "FalseExpressionParser/FalseExpressionParser.h"
#include "IdentifierExpressionParser/IdentifierExpressionParser.h"
#include "NirastExpressionParser/NirastExpressionParser.h"
#include "NumberExpressionParser/NumberExpressionParser.h"
#include "ObjectExpressionParser/ObjectExpressionParser.h"
#include "StringExpressionParser/StringExpressionParser.h"
#include "TrueExpressionParser/TrueExpressionParser.h"
#include "TypeExpressionParser/ObjectTypeExpressionParser/ObjectTypeExpressionParser.h"

#include <memory>
std::unique_ptr<ExpressionParser>
PrimaryExpressionParserFactory::createPrimaryExpressionParser(
    const SyntaxKindUtils::SyntaxKind &kind) {
  switch (kind) {
  case SyntaxKindUtils::SyntaxKind::OpenParenthesisToken: {
    return std::make_unique<ParenthesizedExpressionParser>();
  }
  case SyntaxKindUtils::SyntaxKind::NumberToken: {
    return std::make_unique<NumberExpressionParser>();
  }
  case SyntaxKindUtils::SyntaxKind::StringToken: {
    return std::make_unique<StringExpressionParser>();
  }
  case SyntaxKindUtils::SyntaxKind::CharacterToken: {
    return std::make_unique<CharacterExpressionParser>();
  }
  case SyntaxKindUtils::SyntaxKind::TrueKeyword: {
    return std::make_unique<TrueExpressionParser>();
  }
  case SyntaxKindUtils::SyntaxKind::NirastKeyword: {
    return std::make_unique<NirastExpressionParser>();
  }
  case SyntaxKindUtils::SyntaxKind::FalseKeyword: {
    return std::make_unique<FalseExpressionParser>();
  }
  case SyntaxKindUtils::SyntaxKind::CommaToken: {
    return std::make_unique<CommaExpressionParser>();
  }
  case SyntaxKindUtils::SyntaxKind::NewKeyword: {
    return std::make_unique<CallExpressionParser>();
  }
  case SyntaxKindUtils::SyntaxKind::IdentifierToken: {
    return std::make_unique<IdentifierExpressionParser>();
  }
  case SyntaxKindUtils::SyntaxKind::OpenBracketToken: {
    return std::make_unique<BracketedExpressionParser>();
  }
  case SyntaxKindUtils::SyntaxKind::OpenBraceToken: {
    return std::make_unique<ObjectExpressionParser>();
  }

  default:
    break;
  };

  return std::make_unique<DefaultPrimaryExpressionParser>();
}
