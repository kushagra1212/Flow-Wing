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

#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include <string>

namespace flow_wing {
namespace diagnostic {

enum class DiagnosticLevel { kInfo, kWarning, kError, kDebug };

enum class DiagnosticType {
  kFileSystem,
  kLexical,
  kSyntactic,
  kSemantic,
  kCodeGen,
  kRuntime,
  kLinker,
  kFatal,
};

class Diagnostic {
public:
  Diagnostic(std::string message, std::string help, std::string note,
             DiagnosticLevel level, DiagnosticType type,
             const SourceLocation &location, DiagnosticCode code)
      : m_message(std::move(message)), m_help(std::move(help)),
        m_note(std::move(note)), m_level(level), m_type(type),
        m_location(location), m_code(code) {}

  // Getters
  const std::string &getMessage() const { return m_message; }
  const std::string &getHelp() const { return m_help; }
  const std::string &getNote() const { return m_note; }
  const SourceLocation &getLocation() const { return m_location; }

  DiagnosticLevel getLevel() const { return m_level; }
  DiagnosticType getType() const { return m_type; }
  DiagnosticCode getCode() const { return m_code; }

private:
  std::string m_message;
  std::string m_help;
  std::string m_note;

  DiagnosticLevel m_level;
  DiagnosticType m_type;
  SourceLocation m_location;
  DiagnosticCode m_code;
};

} // namespace diagnostic
} // namespace flow_wing
