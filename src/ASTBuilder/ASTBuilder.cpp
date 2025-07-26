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

#include "ASTBuilder.h"
#include "src/ASTBuilder/CodeFormatter/CodeFormatter.h"
#include "src/ASTBuilder/parsers/CompilationUnitParser/CompilationUnitParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/SourceTokenizer/SourceTokenizer.h"
#include "src/syntax/SyntaxToken.h"

ASTBuilder::ASTBuilder(
    const std::vector<std::string> &sourceCode,
    FlowWing::DiagnosticHandler *diagnosticHandler,
    const std::unordered_map<std::string, int8_t> &dependencyPathsMap)
    : _parserCtx(std::make_unique<ParserContext>(diagnosticHandler,
                                                 dependencyPathsMap)),
      _lexer(std::make_unique<SourceTokenizer>(sourceCode, diagnosticHandler)) {

  _parserCtx->buildTokenList(_lexer.get());
}

ASTBuilder::~ASTBuilder() { _lexer.reset(); }

std::unique_ptr<CompilationUnitSyntax> ASTBuilder::createCompilationUnit() {
  return std::make_unique<CompilationUnitParser>()->parseCompilationUnit(
      _parserCtx.get());
}

const std::vector<std::unique_ptr<SyntaxToken<std::any>>> &
ASTBuilder::getTokenListRef() {
  return _parserCtx->getTokenListRef();
}

const std::string &ASTBuilder::getFormattedSourceCode() {
  return _parserCtx->getCodeFormatterRef()->getFormattedSourceCode();
}