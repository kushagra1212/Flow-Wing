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

#include "ExpressionStatementParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/ExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrecedenceAwareExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/PrimaryExpressionParserFactory.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/ASTBuilder/parsers/StatementParser/StatementParserFactory.h"
#include "src/syntax/statements/ExpressionStatementSyntax/ExpressionStatementSyntax.hpp"
#include "src/syntax/statements/StatementSyntax.h"

namespace flow_wing {
namespace parser {

ExpressionStatementParser::ExpressionStatementParser(ParserContext *ctx)
    : m_ctx(ctx) {}

std::unique_ptr<syntax::StatementSyntax> ExpressionStatementParser::parse() {

  auto expression = PrecedenceAwareExpressionParser::parse(m_ctx, 0);

  return std::make_unique<syntax::ExpressionStatementSyntax>(
      std::move(expression));
}
} // namespace parser
} // namespace flow_wing
