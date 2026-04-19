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


#include "ModuleAccessExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/syntax/OperatorPrecedence/OperatorPrecedence.h"
#include "src/syntax/expression/ModuleAccessExpressionSyntax/ModuleAccessExpressionSyntax.h"
#include <cassert>

namespace flow_wing {
namespace parser {

ModuleAccessExpressionParser::ModuleAccessExpressionParser(ParserContext *ctx)
    : m_ctx(ctx) {}

std::unique_ptr<syntax::ExpressionSyntax>
ModuleAccessExpressionParser::parsePostfix(
    std::unique_ptr<syntax::ExpressionSyntax> module_identifier_expression) {

  const syntax::SyntaxToken *colon_colon_token =
      m_ctx->match(lexer::TokenKind::kColonColonToken); // ::

  auto member_access_expression = PrecedenceAwareExpressionParser::parse(
      m_ctx, syntax::OperatorPrecedence::kModuleAccessRhsPrecedenceFloor);

  return std::make_unique<syntax::ModuleAccessExpressionSyntax>(
      std::move(module_identifier_expression), colon_colon_token,
      std::move(
          member_access_expression)); // module_name::x or module_name::x.y or
                                      // module_name::x(2,3) or
                                      // module_name::x[2] or
                                      // module_name::class_name
}

std::unique_ptr<syntax::ExpressionSyntax>
ModuleAccessExpressionParser::parse() {
  assert(false && "ModuleAccessExpressionParser::parse() is not implemented");
  return nullptr;
}

} // namespace parser
} // namespace flow_wing