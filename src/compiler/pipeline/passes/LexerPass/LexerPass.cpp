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



#include "LexerPass.h"
#include "src/SourceTokenizer/SourceTokenizer.h"
#include "src/common/debug/DebugConfig.h"
#include "src/common/debug/DebugUtils.h"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include <cstdlib>

namespace flow_wing {

namespace compiler {
namespace pipeline {

std::string LexerPass::getName() const { return "Lexing"; }

ReturnStatus LexerPass::run(CompilationContext &context) {
  auto &diagnostics = context.getDiagnostics();

  lexer::SourceTokenizer lexer(context);

  std::vector<std::unique_ptr<syntax::SyntaxToken>> tokens;

  lexer::TokenKind token_kind;
  do {
    auto token = lexer.nextToken();
    token_kind = token->getTokenKind();
    tokens.push_back(std::move(token));
  } while (token_kind != lexer::TokenKind::kEndOfFileToken);

  if (diagnostics->hasError(diagnostic::DiagnosticType::kLexical)) {
    return ReturnStatus::kFailure;
  }

  LEXER_DEBUG_LOG("Tokens set successfully with size", tokens.size());
  context.setTokens(std::move(tokens));

  return ReturnStatus::kSuccess;
}
} // namespace pipeline
} // namespace compiler
} // namespace flow_wing
