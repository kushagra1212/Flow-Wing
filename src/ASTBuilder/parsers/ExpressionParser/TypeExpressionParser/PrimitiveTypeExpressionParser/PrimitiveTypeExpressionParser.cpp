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

#include "PrimitiveTypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/BoolTypeExpressionSyntax/BoolTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/CharTypeExpressionSyntax/CharTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/Deci32TypeExpressionSyntax/Deci32TypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/DeciTypeExpressionSyntax/DeciTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/DynTypeExpressionSyntax/DynTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/Int32TypeExpressionSyntax/Int32TypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/Int64TypeExpressionSyntax/Int64TypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/Int8TypeExpressionSyntax/Int8TypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/NthgTypeExpressionSyntax/NthgTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/StrTypeExpressionSyntax/StrTypeExpressionSyntax.h"

namespace flow_wing {
namespace parser {

PrimitiveTypeExpressionParser::PrimitiveTypeExpressionParser(ParserContext *ctx)
    : m_ctx(ctx) {}

std::unique_ptr<syntax::ExpressionSyntax>
PrimitiveTypeExpressionParser::parse() {
  switch (m_ctx->getCurrentTokenKind()) {
    // Handle Primitive Type Expressions
  case lexer::TokenKind::kInt8Keyword:
    return std::make_unique<syntax::Int8TypeExpressionSyntax>(
        m_ctx->match(lexer::TokenKind::kInt8Keyword)); // int8
  case lexer::TokenKind::kCharKeyword:
    return std::make_unique<syntax::CharTypeExpressionSyntax>(
        m_ctx->match(lexer::TokenKind::kCharKeyword)); // char
  case lexer::TokenKind::kInt32Keyword:
    return std::make_unique<syntax::Int32TypeExpressionSyntax>(
        m_ctx->match(lexer::TokenKind::kInt32Keyword)); // int
  case lexer::TokenKind::kInt64Keyword:
    return std::make_unique<syntax::Int64TypeExpressionSyntax>(
        m_ctx->match(lexer::TokenKind::kInt64Keyword)); // int64
  case lexer::TokenKind::kDeciKeyword:
    return std::make_unique<syntax::DeciTypeExpressionSyntax>(
        m_ctx->match(lexer::TokenKind::kDeciKeyword)); // deci
  case lexer::TokenKind::kDeci32Keyword:
    return std::make_unique<syntax::Deci32TypeExpressionSyntax>(
        m_ctx->match(lexer::TokenKind::kDeci32Keyword)); // deci32
  case lexer::TokenKind::kStrKeyword:
    return std::make_unique<syntax::StrTypeExpressionSyntax>(
        m_ctx->match(lexer::TokenKind::kStrKeyword)); // str
  case lexer::TokenKind::kBoolKeyword:
    return std::make_unique<syntax::BoolTypeExpressionSyntax>(
        m_ctx->match(lexer::TokenKind::kBoolKeyword)); // bool
  case lexer::TokenKind::kNthgKeyword:
    return std::make_unique<syntax::NthgTypeExpressionSyntax>(
        m_ctx->match(lexer::TokenKind::kNthgKeyword)); // nthg
        case lexer::TokenKind::kDynKeyword:
    return std::make_unique<syntax::DynTypeExpressionSyntax>(
        m_ctx->match(lexer::TokenKind::kDynKeyword)); // dyn
  default:
    return nullptr;
  }
}

} // namespace parser
} // namespace flow_wing