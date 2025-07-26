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

#include "TemplateStringTokenReader.h"
#include "src/SourceTokenizer/SourceTokenizer.h"
#include "src/diagnostics/Diagnostic/Diagnostic.h"
#include "src/diagnostics/Diagnostic/DiagnosticCodeData.h"
#include "src/diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"
#include "src/utils/Utils.h"

std::unique_ptr<SyntaxToken<std::any>>
TemplateStringTokenReader::readToken(SourceTokenizer &lexer) {
  const size_t &start = lexer.position();
  std::string text = "", valueText = "";
  text += lexer.currentChar();
  lexer.advancePosition();

  while (!lexer.isEOF() && lexer.currentChar() != '`') {

    if (lexer.isEOL()) {
      text += "\n";
      valueText += "\n";
      lexer.advanceLine();
    } else {
      text += lexer.currentChar();
      valueText += lexer.currentChar();
      lexer.advancePosition();
    }
  }

  if (lexer.currentChar() != '`') {
    return unTerminatedTemplateStringToken(lexer, start);
  }

  text += lexer.currentChar();
  lexer.advancePosition();

  return std::make_unique<SyntaxToken<std::any>>(
      lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
      SyntaxKindUtils::SyntaxKind::StringToken, start, text,

      valueText);
}

std::unique_ptr<SyntaxToken<std::any>>
TemplateStringTokenReader::unTerminatedTemplateStringToken(
    SourceTokenizer &lexer, const size_t &start) {
  std::unique_ptr<SyntaxToken<std::any>> unTerminatedToken =
      std::make_unique<SyntaxToken<std::any>>(
          lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
          SyntaxKindUtils::SyntaxKind::BadToken, start, "", 0);

  lexer.diagnosticHandler()->addDiagnostic(
      Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                 DiagnosticUtils::DiagnosticType::Lexical, {},
                 Utils::getSourceLocation(unTerminatedToken.get()),
                 FLOW_WING::DIAGNOSTIC::DiagnosticCode::
                     UnTerminatedTemplateStringLiteral));

  return (unTerminatedToken);
}