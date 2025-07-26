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

#include "CharacterTokenReader.h"
#include "src/SourceTokenizer/SourceTokenizer.h"
#include "src/diagnostics/Diagnostic/Diagnostic.h"
#include "src/diagnostics/Diagnostic/DiagnosticCodeData.h"
#include "src/diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"
#include "src/utils/Utils.h"

std::unique_ptr<SyntaxToken<std::any>>
CharacterTokenReader::readToken(SourceTokenizer &lexer) {
  const size_t &start = lexer.position();
  lexer.advancePosition();
  std::string text = "", valueText = "";
  while (!lexer.isEOLorEOF() && lexer.currentChar() != '\'') {
    if (lexer.currentChar() == '\0') {
      return unTerminatedCharacterToken(lexer, start);
    }

    if (lexer.currentChar() == '\\') {
      text += lexer.currentChar();
      lexer.advancePosition();
      text += lexer.currentChar();
      switch (lexer.currentChar()) {
      case '\'':
        valueText += '\'';
        break;
      case '\\':
        valueText += '\\';
        break;
      case 'n':
        valueText += '\n';
        break;
      case 'r':
        valueText += '\r';
        break;
      case 't':
        valueText += '\t';
        break;
      default: {
        return badEscapeSequenceToken(lexer, start);
      }
      }
    } else {
      text += lexer.currentChar();
      valueText += lexer.currentChar();
    }
    lexer.advancePosition();
  }
  if (lexer.currentChar() != '\'') {
    return unTerminatedCharacterToken(lexer, start);
  }

  lexer.advancePosition();
  return std::make_unique<SyntaxToken<std::any>>(
      lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
      SyntaxKindUtils::SyntaxKind::CharacterToken, start, '\'' + text + '\'',
      valueText);
}

std::unique_ptr<SyntaxToken<std::any>>
CharacterTokenReader::unTerminatedCharacterToken(SourceTokenizer &lexer,
                                                 const size_t &start) {
  std::unique_ptr<SyntaxToken<std::any>> unTerminatedSyntaxToken =
      std::make_unique<SyntaxToken<std::any>>(
          lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
          SyntaxKindUtils::SyntaxKind::BadToken, start,
          lexer.getLine(lexer.lineNumber())
              .substr(start, lexer.position() - start),
          0);

  lexer.diagnosticHandler()->addDiagnostic(Diagnostic(
      DiagnosticUtils::DiagnosticLevel::Error,
      DiagnosticUtils::DiagnosticType::Lexical, {},
      Utils::getSourceLocation(unTerminatedSyntaxToken.get()),
      FLOW_WING::DIAGNOSTIC::DiagnosticCode::UnTerminatedSingleQuote));

  return (unTerminatedSyntaxToken);
}

std::unique_ptr<SyntaxToken<std::any>>
CharacterTokenReader::badEscapeSequenceToken(SourceTokenizer &lexer,
                                             const size_t &start) {
  std::unique_ptr<SyntaxToken<std::any>> badSyntaxToken =
      std::make_unique<SyntaxToken<std::any>>(
          lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
          SyntaxKindUtils::SyntaxKind::BadToken, start,
          lexer.getLine(lexer.lineNumber())
              .substr(start, lexer.position() - start),
          0);

  lexer.diagnosticHandler()->addDiagnostic(Diagnostic(
      DiagnosticUtils::DiagnosticLevel::Error,
      DiagnosticUtils::DiagnosticType::Lexical,
      {
          lexer.getLine(lexer.lineNumber()).substr(lexer.position(), 1),
      },
      Utils::getSourceLocation(badSyntaxToken.get()),
      FLOW_WING::DIAGNOSTIC::DiagnosticCode::BadCharacterEscapeSequence));

  return (badSyntaxToken);
}