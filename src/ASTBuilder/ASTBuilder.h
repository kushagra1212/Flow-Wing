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

#pragma once

#include <any>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/SourceTokenizer/SourceTokenizer.h"

class ParserContext;
class SourceTokenizer;
class CompilationUnitSyntax;
template <typename T> class SyntaxToken;

namespace FlowWing {
class DiagnosticHandler;
}

class ASTBuilder {
  std::unique_ptr<ParserContext> _parserCtx = nullptr;
  std::unique_ptr<SourceTokenizer> _lexer = nullptr;

public:
  ASTBuilder(const std::vector<std::string> &sourceCode,
             FlowWing::DiagnosticHandler *diagnosticHandler,
             const std::unordered_map<std::string, int8_t> &dependencyPathsMap =
                 std::unordered_map<std::string, int8_t>());

  ~ASTBuilder();

  //? getters
  const std::vector<std::unique_ptr<SyntaxToken<std::any>>> &getTokenListRef();
  const std::string &getFormattedSourceCode();

  std::unique_ptr<CompilationUnitSyntax> createCompilationUnit();
};
