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


#include "MemberAccessExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/IdentifierExpressionParser/IdentifierExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/syntax/expression/MemberAccessExpressionSyntax/MemberAccessExpressionSyntax.h"
#include <cassert>

namespace flow_wing {
namespace parser {

MemberAccessExpressionParser::MemberAccessExpressionParser(ParserContext *ctx)
    : m_ctx(ctx) {}

std::unique_ptr<syntax::ExpressionSyntax>
MemberAccessExpressionParser::parsePostfix(
    std::unique_ptr<syntax::ExpressionSyntax> expression) {

  const syntax::SyntaxToken *colon_colon_token =
      m_ctx->match(lexer::TokenKind::kDotToken); // .

  auto member_identifier =
      std::make_unique<IdentifierExpressionParser>(m_ctx)->parse();

  return std::make_unique<syntax::MemberAccessExpressionSyntax>(
      std::move(expression), colon_colon_token,
      std::move(member_identifier)); // expression.x or expression.x.y or
                                     // expression.x(2,3) or
                                     // expression.x[2] or
                                     // class_object.x or
                                     // class_object.x.y or
                                     // class_object.x(2,3) or
                                     // class_object.x[2] or
                                     // call().x or
                                     // call().x.y or
                                     // call().x(2,3) or
                                     // call().x[2] or
                                     // call().class_object.x or
                                     // call().class_object.x.y or
                                     // call().class_object.x(2,3) or
                                     // call().class_object.x[2] or
                                     // call().call().x or
}

std::unique_ptr<syntax::ExpressionSyntax>
MemberAccessExpressionParser::parse() {
  assert(false && "MemberAccessExpressionParser::parse() is not implemented");
  return nullptr;
}

} // namespace parser
} // namespace flow_wing