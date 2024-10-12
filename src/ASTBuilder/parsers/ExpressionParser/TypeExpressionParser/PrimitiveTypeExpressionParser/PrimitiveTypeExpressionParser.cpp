#include "PrimitiveTypeExpressionParser.h"

std::unique_ptr<SyntaxToken<std::any>>
PrimitiveTypeExpressionParser::parseExpression(ParserContext *ctx) {
  switch (ctx->getKind()) {
  case SyntaxKindUtils::SyntaxKind::Int32Keyword: {
    return std::move(ctx->match(SyntaxKindUtils::SyntaxKind::Int32Keyword));
  }

  case SyntaxKindUtils::SyntaxKind::Int64Keyword: {
    return std::move(ctx->match(SyntaxKindUtils::SyntaxKind::Int64Keyword));
  }

  case SyntaxKindUtils::SyntaxKind::Deci32Keyword: {
    return std::move(ctx->match(SyntaxKindUtils::SyntaxKind::Deci32Keyword));
  }

  case SyntaxKindUtils::SyntaxKind::Int8Keyword: {
    return std::move(ctx->match(SyntaxKindUtils::SyntaxKind::Int8Keyword));
  }

  case SyntaxKindUtils::SyntaxKind::DeciKeyword: {
    return std::move(ctx->match(SyntaxKindUtils::SyntaxKind::DeciKeyword));
  }

  case SyntaxKindUtils::SyntaxKind::StrKeyword: {
    return std::move(ctx->match(SyntaxKindUtils::SyntaxKind::StrKeyword));
  }

  case SyntaxKindUtils::SyntaxKind::BoolKeyword: {
    return std::move(ctx->match(SyntaxKindUtils::SyntaxKind::BoolKeyword));
  }
  case SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE: {
    return std::move(ctx->match(SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE));
  }
  case SyntaxKindUtils::SyntaxKind::NthgKeyword: {
    return std::move(ctx->match(SyntaxKindUtils::SyntaxKind::NthgKeyword));
  }

  default:
    break;
  }

  ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
      "Unexpected Token <" + SyntaxKindUtils::to_string(ctx->getKind()) +
          ">, Expected <" +
          SyntaxKindUtils::to_string(
              SyntaxKindUtils::SyntaxKind::Int32Keyword) +
          "> or <" +
          SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::DeciKeyword) +
          "> or <" +
          SyntaxKindUtils::to_string(
              SyntaxKindUtils::SyntaxKind::Deci32Keyword) +
          "> or <" +
          SyntaxKindUtils::to_string(
              SyntaxKindUtils::SyntaxKind::Int64Keyword) +
          "> or <" +
          SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::StrKeyword) +
          "> or <" +
          SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::BoolKeyword) +
          "> or <" +
          SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::NthgKeyword) +
          "> or <" +
          SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::Int8Keyword) +
          ">",
      DiagnosticUtils::DiagnosticLevel::Error,
      DiagnosticUtils::DiagnosticType::Syntactic,
      Utils::getSourceLocation(ctx->getCurrent())));

  return nullptr;
}