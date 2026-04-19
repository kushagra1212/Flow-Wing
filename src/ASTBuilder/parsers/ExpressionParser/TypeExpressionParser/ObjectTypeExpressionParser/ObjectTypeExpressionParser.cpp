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

#include "ObjectTypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/ObjectTypeExpressionSyntax/ObjectTypeExpressionSyntax.h"

namespace flow_wing {
namespace parser {

ObjectTypeExpressionParser::ObjectTypeExpressionParser(ParserContext *ctx)
    : m_ctx(ctx) {}

std::unique_ptr<syntax::ExpressionSyntax>
ObjectTypeExpressionParser::parsePostfix(
    std::unique_ptr<syntax::IdentifierExpressionSyntax> identifier_expression) {
  return std::make_unique<syntax::ObjectTypeExpressionSyntax>(
      std::move(identifier_expression));
}

std::unique_ptr<syntax::ExpressionSyntax> ObjectTypeExpressionParser::parse() {

  auto identifier_expression =
      std::make_unique<syntax::IdentifierExpressionSyntax>(m_ctx->match(
          lexer::TokenKind::kIdentifierToken)); // object_type_identifier

  return parsePostfix(std::move(identifier_expression));
}

} // namespace parser
} // namespace flow_wing