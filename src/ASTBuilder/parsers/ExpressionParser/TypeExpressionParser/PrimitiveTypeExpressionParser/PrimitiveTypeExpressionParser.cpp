/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
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

#include "PrimitiveTypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/diagnostics/Diagnostic/Diagnostic.h"
#include "src/diagnostics/Diagnostic/DiagnosticCodeData.h"
#include "src/diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"
#include "src/utils/Utils.h"

std::unique_ptr<SyntaxToken<std::any>>
PrimitiveTypeExpressionParser::parseExpression(ParserContext *ctx) {
  switch (ctx->getKind()) {
  case SyntaxKindUtils::SyntaxKind::Int32Keyword: {
    return ctx->match(SyntaxKindUtils::SyntaxKind::Int32Keyword);
  }

  case SyntaxKindUtils::SyntaxKind::Int64Keyword: {
    return ctx->match(SyntaxKindUtils::SyntaxKind::Int64Keyword);
  }

  case SyntaxKindUtils::SyntaxKind::Deci32Keyword: {
    return ctx->match(SyntaxKindUtils::SyntaxKind::Deci32Keyword);
  }

  case SyntaxKindUtils::SyntaxKind::Int8Keyword: {
    return ctx->match(SyntaxKindUtils::SyntaxKind::Int8Keyword);
  }

  case SyntaxKindUtils::SyntaxKind::DeciKeyword: {
    return ctx->match(SyntaxKindUtils::SyntaxKind::DeciKeyword);
  }

  case SyntaxKindUtils::SyntaxKind::StrKeyword: {
    return ctx->match(SyntaxKindUtils::SyntaxKind::StrKeyword);
  }

  case SyntaxKindUtils::SyntaxKind::BoolKeyword: {
    return ctx->match(SyntaxKindUtils::SyntaxKind::BoolKeyword);
  }
  case SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE: {
    return ctx->match(SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE);
  }
  case SyntaxKindUtils::SyntaxKind::NthgKeyword: {
    return ctx->match(SyntaxKindUtils::SyntaxKind::NthgKeyword);
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
