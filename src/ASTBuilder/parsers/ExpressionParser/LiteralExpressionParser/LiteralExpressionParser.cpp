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

#include "src/ASTBuilder/parsers/ExpressionParser/LiteralExpressionParser/LiteralExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/expression/BooleanLiteralExpressionSyntax/BooleanLiteralExpressionSyntax.h"
#include "src/syntax/expression/CharacterLiteralExpressionSyntax/CharacterLiteralExpressionSyntax.h"
#include "src/syntax/expression/DoubleLiteralExpressionSyntax/DoubleLiteralExpressionSyntax.h"
#include "src/syntax/expression/FloatLiteralExpressionSyntax/FloatLiteralExpressionSyntax.h"
#include "src/syntax/expression/Int64LiteralExpressionSyntax/Int64LiteralExpressionSyntax.h"
#include "src/syntax/expression/IntegerLiteralExpressionSyntax/IntegerLiteralExpressionSyntax.h"
#include "src/syntax/expression/StringLiteralExpressionSyntax/StringLiteralExpressionSyntax.h"
#include "src/syntax/expression/TemplateStringLiteralExpressionSyntax/TemplateStringLiteralExpressionSyntax.h"
#include <cassert>

namespace flow_wing {
namespace parser {

LiteralExpressionParser::LiteralExpressionParser(ParserContext *ctx)
    : m_ctx(ctx) {}

std::unique_ptr<syntax::ExpressionSyntax> LiteralExpressionParser::parse() {
  auto token = m_ctx->nextToken();
  switch (token->getTokenKind()) {
  case lexer::TokenKind::kIntegerLiteralToken:
    return std::make_unique<syntax::IntegerLiteralExpressionSyntax>(
        token); // 123
  case lexer::TokenKind::kInt64LiteralToken:
    return std::make_unique<syntax::Int64LiteralExpressionSyntax>(
        token); // 123l
  case lexer::TokenKind::kDoubleLiteralToken:
    return std::make_unique<syntax::DoubleLiteralExpressionSyntax>(
        token); // 123.456
  case lexer::TokenKind::kFloatLiteralToken:
    return std::make_unique<syntax::FloatLiteralExpressionSyntax>(
        token); // 123.456d
  case lexer::TokenKind::kCharacterLiteralToken:
    return std::make_unique<syntax::CharacterLiteralExpressionSyntax>(
        token); // 'a'
  case lexer::TokenKind::kStringLiteralToken:
    return std::make_unique<syntax::StringLiteralExpressionSyntax>(
        token); // "Hello"
  case lexer::TokenKind::kTemplateStringLiteralToken:
    return std::make_unique<syntax::TemplateStringLiteralExpressionSyntax>(
        token); // `Hello`
  case lexer::TokenKind::kTrueKeyword:
  case lexer::TokenKind::kFalseKeyword:
    return std::make_unique<syntax::BooleanLiteralExpressionSyntax>(
        token, token->getTokenKind() ==
                   lexer::TokenKind::kTrueKeyword); // true or false
  default:
    assert(false && "Unexpected token kind for LiteralExpressionParser");
    break;
  }
}

} // namespace parser
} // namespace flow_wing
