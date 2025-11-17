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



#include "ConsoleFormatter.h"
#include "src/common/cli/CliColors.h"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/compiler/diagnostics/DiagnosticFormatUtils.h"
#include "src/compiler/diagnostics/DiagnosticUtils/DiagnosticUtils.h"
#include <sstream>

namespace flow_wing {

namespace diagnostic {

std::string ConsoleFormatter::format(const Diagnostic &diagnostic,
                                     const CompilationContext &context) const {
  std::stringstream ss;

  ss << getMessageSnippet(diagnostic);
  ss << getLocationSnippet(diagnostic);
  ss << getFileSnippet(diagnostic);
  ss << getErrorCodeSnippet(diagnostic, context);
  ss << getNoteSnippet(diagnostic);
  ss << getHelpSnippet(diagnostic);
  ss << getErrorCodeString(diagnostic.getCode());

  return ss.str();
}

bool ConsoleFormatter::skipSnippet(const Diagnostic &diagnostic) const {
  return diagnostic.getType() == diagnostic::DiagnosticType::kLinker ||
         diagnostic.getType() == diagnostic::DiagnosticType::kFileSystem;
}

std::string
ConsoleFormatter::getLineSnippet(const Diagnostic &diagnostic) const {

  if (skipSnippet(diagnostic)) {
    return "";
  }

  std::stringstream snippet;

  snippet << "Line " << diagnostic.getLocation().m_start.line_number << ":"
          << diagnostic.getLocation().m_start.column_number << " ";

  return snippet.str();
}

std::string ConsoleFormatter::getFileName(const std::string &file_path) const {
  if (file_path.empty()) {
    return "REPL";
  }
  const size_t last_slash = file_path.find_last_of("/\\");
  if (last_slash != std::string::npos) {
    return file_path.substr(last_slash + 1);
  }
  return file_path;
}

std::string
ConsoleFormatter::getNoteSnippet(const Diagnostic &diagnostic) const {
  std::stringstream snippet;
  snippet << CLEAR_COLOR << "\n"
          << BLUE_TEXT << "Note: " << WHITE_TEXT << diagnostic.getNote()
          << "\n\n"
          << CLEAR_COLOR;
  return snippet.str();
}

std::string
ConsoleFormatter::getHelpSnippet(const Diagnostic &diagnostic) const {
  std::stringstream snippet;
  snippet << CLEAR_COLOR << "\n"
          << BLUE_TEXT << "Help: " << WHITE_TEXT << diagnostic.getHelp()
          << "\n\n"
          << CLEAR_COLOR;
  return snippet.str();
}

std::string
ConsoleFormatter::getFileSnippet(const Diagnostic &diagnostic) const {

  if (skipSnippet(diagnostic)) {
    return "";
  }

  std::stringstream snippet;
  snippet << CLEAR_COLOR << "\n"
          << YELLOW_TEXT << "File: ----> "
          << WHITE_TEXT
          // TODO(kushagra): Add file name

          << "\n\n"
          << CLEAR_COLOR;
  return snippet.str();
}

std::string
ConsoleFormatter::getMessageSnippet(const Diagnostic &diagnostic) const {
  std::stringstream snippet;
  const auto highlight_text =
      (diagnostic.getLevel() == diagnostic::DiagnosticLevel::kError ? RED_TEXT
       : diagnostic.getLevel() == diagnostic::DiagnosticLevel::kWarning
           ? YELLOW_TEXT
       : diagnostic.getLevel() == diagnostic::DiagnosticLevel::kInfo
           ? GREEN_TEXT
           : BLUE_TEXT);

  snippet << CLEAR_COLOR << "\n"
          << highlight_text << "["
          << flow_wing::diagnostic::utils::toString(diagnostic.getLevel())
          << "] : " << YELLOW_TEXT << getLineSnippet(diagnostic) << WHITE_TEXT
          << " \"" << diagnostic.getMessage() << "\"\n\n"
          << CLEAR_COLOR;

  return snippet.str();
}

std::string
ConsoleFormatter::getLocationSnippet(const Diagnostic &diagnostic) const {

  if (skipSnippet(diagnostic)) {
    return "";
  }

  std::stringstream snippet;
  snippet << CLEAR_COLOR << "\n"
          << YELLOW_TEXT << "Location: ----> "
          << GREEN_TEXT
          // TODO(kushagra): Add file name
          << CLEAR_COLOR;
  return snippet.str();
}

std::string
ConsoleFormatter::getErrorCodeSnippet(const Diagnostic &diagnostic,
                                      const CompilationContext &context) const {
  std::string snippet = "\n";
  const std::vector<std::string> &lines = context.getSourceLines();
  const size_t lineNumber = diagnostic.getLocation().m_start.line_number;
  const size_t columnNumber = diagnostic.getLocation().m_start.column_number;
  size_t lineCount = lines.size();
  size_t currentLineNumber = 1;

  auto errorMarker = [&]() {
    std::string marker = "";
    marker += GREEN_TEXT;
    marker += BOLD_TEXT;
    for (size_t i = 0; i < columnNumber; i++) {
      marker += " ";
    }
    marker += "\n";
    marker += "   ";
    for (size_t i = 0; i < columnNumber; i++) {
      if (i == columnNumber - 1) {
        marker += "^";
      } else {
        marker += "~";
      }
    }
    marker += RESET;
    marker += "\n";
    return marker;
  };

  while (currentLineNumber <= lineCount) {
    if (currentLineNumber <= lineNumber + 4 &&
        currentLineNumber >= lineNumber - 4) {
      snippet += YELLOW_TEXT + std::to_string(currentLineNumber) + "| " + RESET;
      if (currentLineNumber <= lineNumber && currentLineNumber >= lineNumber) {
        snippet += RED_TEXT;
        snippet += BOLD_TEXT;
      } else {
        snippet += RESET;
      }
      snippet += lines[static_cast<size_t>(currentLineNumber) - 1] + "\n";
      snippet += RESET;
      if (lineNumber == currentLineNumber) {

        snippet += errorMarker();
      }
    }
    currentLineNumber++;
  }
  if (lineNumber == currentLineNumber && snippet != "\n") {
    snippet += errorMarker();
  }
  return snippet;
}

} // namespace diagnostic

} // namespace flow_wing
