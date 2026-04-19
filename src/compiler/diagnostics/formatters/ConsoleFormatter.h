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

#pragma once

#include "IDiagnosticFormatter.h"
#include <string>
#include <vector>

namespace flow_wing {
namespace diagnostic {

class ConsoleFormatter : public IDiagnosticFormatter {
public:
  std::string format(const diagnostic::Diagnostic &diagnostic,
                     const CompilationContext &context) const override;

private:
  std::string
  getErrorSnippet(const diagnostic::Diagnostic &diagnostic,
                  const std::vector<std::string> &source_lines) const;

  std::string getLineSnippet(const diagnostic::Diagnostic &diagnostic) const;

  std::string getNoteSnippet(const diagnostic::Diagnostic &diagnostic) const;
  std::string getHelpSnippet(const diagnostic::Diagnostic &diagnostic) const;
  std::string getFileSnippet(const diagnostic::Diagnostic &diagnostic,
                             const CompilationContext &context) const;
  std::string getMessageSnippet(const diagnostic::Diagnostic &diagnostic) const;
  std::string getErrorCodeSnippet(const Diagnostic &diagnostic,
                                  const CompilationContext &context) const;

  std::string getLocationSnippet(const diagnostic::Diagnostic &diagnostic,
                                 const CompilationContext &context) const;
  bool skipSnippet(const diagnostic::Diagnostic &diagnostic) const;

  std::string getFileName(const std::string &file_path) const;
};
} // namespace diagnostic

} // namespace flow_wing
