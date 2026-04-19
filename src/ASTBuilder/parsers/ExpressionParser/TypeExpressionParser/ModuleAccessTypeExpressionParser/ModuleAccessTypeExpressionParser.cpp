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

#include "ModuleAccessTypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/TypeExpressionParser/ArrayTypeExpressionParser/ArrayTypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/TypeExpressionParser/ObjectTypeExpressionParser/ObjectTypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/ModuleAccessTypeExpressionSyntax/ModuleAccessTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/ObjectTypeExpressionSyntax/ObjectTypeExpressionSyntax.h"
#include <cassert>

namespace flow_wing {
namespace parser {

ModuleAccessTypeExpressionParser::ModuleAccessTypeExpressionParser(
    ParserContext *ctx)
    : m_ctx(ctx) {}

std::unique_ptr<syntax::ExpressionSyntax>
ModuleAccessTypeExpressionParser::parsePostfix(
    std::unique_ptr<syntax::IdentifierExpressionSyntax>
        module_identifier_expression) {

  auto colon_colon_token =
      m_ctx->match(lexer::TokenKind::kColonColonToken); // ::

  std::unique_ptr<syntax::ExpressionSyntax> type_expression =
      std::make_unique<parser::ObjectTypeExpressionParser>(m_ctx)
          ->parse(); // object type

  if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kOpenBracketToken) {
    type_expression =
        std::make_unique<parser::ArrayTypeExpressionParser>(m_ctx)
            ->parsePostfix(std::move(type_expression)); //  objectType[2][3]
  }

  return std::make_unique<syntax::ModuleAccessTypeExpressionSyntax>(
      std::move(module_identifier_expression), colon_colon_token,
      std::move(type_expression)); // module_name::objectType or
                                   // module_name::objectType[2][3]
}

std::unique_ptr<syntax::ExpressionSyntax>
ModuleAccessTypeExpressionParser::parse() {
  assert(false &&
         "ModuleAccessTypeExpressionParser::parse() is not implemented");

  return nullptr;
}
} // namespace parser
} // namespace flow_wing
