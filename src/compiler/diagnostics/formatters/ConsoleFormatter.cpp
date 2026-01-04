/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
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
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include <sstream>

namespace flow_wing {

namespace diagnostic {

std::string ConsoleFormatter::format(const Diagnostic &diagnostic,
                                     const CompilationContext &context) const {
  std::stringstream ss;

  ss << getErrorCodeSnippet(diagnostic, context);
  ss << getMessageSnippet(diagnostic);
  ss << getFileSnippet(diagnostic, context);
  ss << getLocationSnippet(diagnostic, context);
  ss << getNoteSnippet(diagnostic);
  ss << getHelpSnippet(diagnostic);

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

  const auto note = diagnostic.getNote();
  if (note.empty()) {
    return "";
  }

  std::stringstream snippet;
  snippet << CLEAR_COLOR << "\n"
          << GREEN_TEXT << "[Note] " << WHITE_TEXT << note << "\n\n"
          << CLEAR_COLOR;
  return snippet.str();
}

std::string
ConsoleFormatter::getHelpSnippet(const Diagnostic &diagnostic) const {

  const auto help = diagnostic.getHelp();
  if (help.empty()) {
    return "";
  }

  std::stringstream snippet;
  snippet << CLEAR_COLOR << "\n"
          << GREEN_TEXT << "[Help] " << WHITE_TEXT << help << "\n\n"
          << CLEAR_COLOR;
  return snippet.str();
}

std::string
ConsoleFormatter::getFileSnippet(const Diagnostic &diagnostic,
                                 const CompilationContext &context) const {

  if (skipSnippet(diagnostic)) {
    return "";
  }

  std::stringstream snippet;
  snippet << CLEAR_COLOR << YELLOW_TEXT << "File: ----> " << WHITE_TEXT
          << getFileName(context.getAbsoluteSourceFilePath()) << WHITE_TEXT
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

  const auto errorCode = getErrorCodeString(diagnostic.getCode());
  snippet << CLEAR_COLOR << "\n"
          << highlight_text << "["
          << flow_wing::diagnostic::utils::toString(diagnostic.getLevel())
          << errorCode << "] : " << YELLOW_TEXT << getLineSnippet(diagnostic)
          << WHITE_TEXT << " \"" << diagnostic.getMessage() << "\"\n\n"
          << CLEAR_COLOR;

  return snippet.str();
}

std::string
ConsoleFormatter::getLocationSnippet(const Diagnostic &diagnostic,
                                     const CompilationContext &context) const {

  if (skipSnippet(diagnostic)) {
    return "";
  }

  std::stringstream snippet;
  snippet << CLEAR_COLOR << "\n"
          << YELLOW_TEXT << "Location: ----> " << GREEN_TEXT
          << context.getAbsoluteSourceFilePath() << CLEAR_COLOR << "\n";
  return snippet.str();
}

std::string
ConsoleFormatter::getErrorCodeSnippet(const Diagnostic &diagnostic,
                                      const CompilationContext &context) const {
  std::string snippet = "\n";
  auto lines = context.getSourceLines();
  size_t line_count = lines.size();
  auto start = diagnostic.getLocation().m_start;
  auto end = diagnostic.getLocation().m_end;
  const size_t delta_length = 4;

  size_t start_line = std::max(
      (start.line_number > delta_length ? start.line_number - delta_length : 0),
      static_cast<size_t>(0));

  size_t end_line = std::min(end.line_number + delta_length > line_count
                                 ? line_count
                                 : end.line_number + delta_length,
                             line_count - 1);

  DEBUG_LOG("start_line: ", start.line_number, ":", start.column_number);
  DEBUG_LOG("end_line: ", end.line_number, ":", end.column_number);

  for (size_t line_number = start_line; line_number <= end_line;
       line_number++) {
    std::string line_number_string = std::to_string(line_number) + "| ";
    snippet += YELLOW_TEXT + line_number_string + RESET;

    size_t column_count = lines[line_number].size();

    std::string arrow = GREEN_TEXT;

    size_t line_number_string_length = std::to_string(line_number).length();
    for (size_t i = 0; i <= line_number_string_length; i++) {
      arrow += " ";
    }

    for (size_t column_number = 0; column_number < column_count;
         column_number++) {

      SourcePoint point(line_number, column_number);

      if (point >= start && point <= end) {
        snippet += RED_TEXT;
        arrow += "^";
      } else {
        snippet += RESET;
        arrow += " ";
      }

      snippet += lines[line_number][column_number];
    }

    if (arrow.find("^") != std::string::npos) {
      snippet += "\n" + arrow;
    }

    snippet += RESET;
    snippet += "\n";
  }

  return snippet;
}

} // namespace diagnostic

} // namespace flow_wing
