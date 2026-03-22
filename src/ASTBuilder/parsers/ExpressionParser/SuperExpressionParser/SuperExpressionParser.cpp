/*
 * Flow-Wing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include "SuperExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/syntax/expression/SuperExpressionSyntax/SuperExpressionSyntax.h"

namespace flow_wing {
namespace parser {

SuperExpressionParser::SuperExpressionParser(ParserContext *ctx) : m_ctx(ctx) {}

std::unique_ptr<syntax::ExpressionSyntax> SuperExpressionParser::parse() {
  auto *tok = m_ctx->match(lexer::TokenKind::kSuperKeyword);
  return std::make_unique<syntax::SuperExpressionSyntax>(tok);
}

} // namespace parser
} // namespace flow_wing
