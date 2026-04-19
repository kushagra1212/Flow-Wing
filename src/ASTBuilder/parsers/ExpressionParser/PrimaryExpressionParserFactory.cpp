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

#include "PrimaryExpressionParserFactory.h"
#include "src/ASTBuilder/parsers/ExpressionParser/BracketedExpressionParser/BracketedExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/ErrorExpressionParser/ErrorExpressionParser.hpp"
#include "src/ASTBuilder/parsers/ExpressionParser/IdentifierExpressionParser/IdentifierExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/LiteralExpressionParser/LiteralExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/NirastExpressionParser/NirastExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/SuperExpressionParser/SuperExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/ObjectExpressionParser/ObjectExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/ParenthesizedExpressionParser/ParenthesizedExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/syntax/SyntaxToken.h"
#include <cassert>

namespace flow_wing {
namespace parser {

std::unique_ptr<parser::ExpressionParser>
PrimaryExpressionParserFactory::create(ParserContext *ctx,
                                       const lexer::TokenKind &kind) {
  switch (kind) {
  case lexer::TokenKind::kOpenParenthesisToken: {
    return std::make_unique<ParenthesizedExpressionParser>(ctx);
  }
  case lexer::TokenKind::kIntegerLiteralToken:
  case lexer::TokenKind::kInt64LiteralToken:
  case lexer::TokenKind::kStringLiteralToken:
  case lexer::TokenKind::kCharacterLiteralToken:
  case lexer::TokenKind::kTemplateStringLiteralToken:
  case lexer::TokenKind::kFloatLiteralToken:
  case lexer::TokenKind::kDoubleLiteralToken:
  case lexer::TokenKind::kTrueKeyword:
  case lexer::TokenKind::kFalseKeyword: {
    return std::make_unique<LiteralExpressionParser>(ctx);
  }

  case lexer::TokenKind::kNirastKeyword: {
    return std::make_unique<NirastExpressionParser>(ctx);
  }

  case lexer::TokenKind::kIdentifierToken: {
    return std::make_unique<IdentifierExpressionParser>(ctx);
  }

  case lexer::TokenKind::kSuperKeyword: {
    return std::make_unique<SuperExpressionParser>(ctx);
  }

  case lexer::TokenKind::kOpenBracketToken: {
    return std::make_unique<BracketedExpressionParser>(ctx);
  }
  case lexer::TokenKind::kOpenBraceToken: {
    return std::make_unique<ObjectExpressionParser>(ctx);
  }

  default:
    return std::make_unique<ErrorExpressionParser>(ctx);
  }
}

} // namespace parser
} // namespace flow_wing