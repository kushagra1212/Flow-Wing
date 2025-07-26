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

#include "SymbolTokenReader.h"
#include "src/SourceTokenizer/SourceTokenizer.h"
#include "src/SourceTokenizer/tokenReaders/TokenReaderData.h"
#include "src/diagnostics/Diagnostic/Diagnostic.h"
#include "src/diagnostics/Diagnostic/DiagnosticCodeData.h"
#include "src/diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"
#include "src/utils/Utils.h"

std::unique_ptr<SyntaxToken<std::any>>
SymbolTokenReader::readToken(SourceTokenizer &lexer) {
  const size_t start = lexer.position();

  const std::string singleCharSymbol(1, lexer.currentChar());
  const std::string &twoCharSymbol = singleCharSymbol + lexer.peek(1);

  for (size_t i = 0; i < __gl_FLOW_WING_SYMBOLS_SIZE; ++i) {
    const auto &symbol = __gl_FLOW_WING_SYMBOLS[i];

    if (twoCharSymbol == symbol._tokenName) {
      lexer.advancePosition();
      lexer.advancePosition();
      return std::make_unique<SyntaxToken<std::any>>(
          lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
          symbol._tokenType, start, symbol._tokenName, nullptr);
    }
  }
  for (size_t i = 0; i < __gl_FLOW_WING_SYMBOLS_SIZE; ++i) {
    const auto &symbol = __gl_FLOW_WING_SYMBOLS[i];

    if (singleCharSymbol == symbol._tokenName) {
      lexer.advancePosition();
      return std::make_unique<SyntaxToken<std::any>>(
          lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
          symbol._tokenType, start, symbol._tokenName, nullptr);
    }
  }

  return badCharacterToken(lexer, start);
}

std::unique_ptr<SyntaxToken<std::any>>
SymbolTokenReader::badCharacterToken(SourceTokenizer &lexer,
                                     const size_t &start) {
  const size_t &len = lexer.getLine(lexer.lineNumber()).length() - start;

  const std::string &str = lexer.getLine(lexer.lineNumber()).substr(start, len);

  lexer.advancePosition();

  std::unique_ptr<SyntaxToken<std::any>> badSyntaxToken =
      std::make_unique<SyntaxToken<std::any>>(
          lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
          SyntaxKindUtils::SyntaxKind::BadToken, start, str, nullptr);

  lexer.diagnosticHandler()->addDiagnostic(
      Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                 DiagnosticUtils::DiagnosticType::Lexical, {str},
                 Utils::getSourceLocation(badSyntaxToken.get()),
                 FLOW_WING::DIAGNOSTIC::DiagnosticCode::BadCharacterInput));

  return badSyntaxToken;
}