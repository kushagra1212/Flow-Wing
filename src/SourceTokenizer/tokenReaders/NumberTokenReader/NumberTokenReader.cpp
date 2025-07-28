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

#include "NumberTokenReader.h"
#include "src/SourceTokenizer/SourceTokenizer.h"
#include "src/diagnostics/Diagnostic/Diagnostic.h"
#include "src/diagnostics/Diagnostic/DiagnosticCodeData.h"
#include "src/diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"
#include "src/utils/Utils.h"

std::unique_ptr<SyntaxToken<std::any>>
NumberTokenReader::readToken(SourceTokenizer &lexer) {
  int start = lexer.position();

  while (!lexer.isEOLorEOF() && isdigit(lexer.currentChar())) {
    lexer.advancePosition();
  }

  //  double check

  if (lexer.currentChar() == '.') {
    return readDecimal(lexer, start);
  }

  const size_t &length = lexer.position() - start;
  const std::string &text =
      lexer.getLine(lexer.lineNumber()).substr(start, length);

  if (SyntaxKindUtils::isNumberTooLarge(text) == true) {
    std::unique_ptr<SyntaxToken<std::any>> badSyntaxToken =
        std::make_unique<SyntaxToken<std::any>>(
            lexer.diagnosticHandler()->getAbsoluteFilePath(),
            lexer.lineNumber(), SyntaxKindUtils::SyntaxKind::BadToken, start,
            text, 0);

    lexer.diagnosticHandler()->addDiagnostic(Diagnostic(
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Lexical, {text},
        Utils::getSourceLocation(badSyntaxToken.get()),
        FLOW_WING::DIAGNOSTIC::DiagnosticCode::NumberTooLargeForInt));

    return (badSyntaxToken);
  }

  return std::make_unique<SyntaxToken<std::any>>(
      lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
      SyntaxKindUtils::SyntaxKind::NumberToken, start, text, text);
}

std::unique_ptr<SyntaxToken<std::any>>
NumberTokenReader::readDecimal(SourceTokenizer &lexer, const int &start) {
  lexer.advancePosition();
  while (!lexer.isEOLorEOF() && isdigit(lexer.currentChar())) {
    lexer.advancePosition();
  }

  if (lexer.currentChar() == 'd') {
    lexer.advancePosition();
  }

  const int &length = lexer.position() - start;
  const std::string &text =
      lexer.getLine(lexer.lineNumber()).substr(start, length);

  return std::make_unique<SyntaxToken<std::any>>(
      lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
      SyntaxKindUtils::SyntaxKind::NumberToken, start, text, text);
}