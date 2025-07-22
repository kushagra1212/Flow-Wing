#include "PrimitiveTypeExpressionParser.h"
#include "../../../../../diagnostics/Diagnostic/DiagnosticCodeData.h"

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
      DiagnosticUtils::DiagnosticLevel::Error,
      DiagnosticUtils::DiagnosticType::Syntactic,
      {SyntaxKindUtils::to_string(ctx->getKind()),
       SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::Int32Keyword),
       SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::DeciKeyword),
       SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::Deci32Keyword),
       SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::Int64Keyword),
       SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::StrKeyword),
       SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::BoolKeyword),
       SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::NthgKeyword),
       SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::Int8Keyword)},
      Utils::getSourceLocation(ctx->getCurrent()),
      FLOW_WING::DIAGNOSTIC::DiagnosticCode::UnexpectedTypeExpression));

  return nullptr;
}
