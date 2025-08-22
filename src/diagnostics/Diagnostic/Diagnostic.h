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

#include "src/diagnostics/Diagnostic/DiagnosticCode.h"
#include "src/diagnostics/DiagnosticUtils/DiagnosticLevel.h"
#include "src/diagnostics/DiagnosticUtils/DiagnosticType.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include <unordered_map>

class Diagnostic {
private:
  std::string _message;
  std::string _help;
  std::string _note;
  FLOW_WING::DIAGNOSTIC::MessageTemplate _messageTemplate;
  DiagnosticUtils::DiagnosticLevel _level;
  DiagnosticUtils::DiagnosticType _type;
  DiagnosticUtils::SourceLocation _location;
  FLOW_WING::DIAGNOSTIC::DiagnosticCode _code;

public:
  Diagnostic(const std::string &message, DiagnosticUtils::DiagnosticLevel level,
             DiagnosticUtils::DiagnosticType type,
             const DiagnosticUtils::SourceLocation &location = {},
             const FLOW_WING::DIAGNOSTIC::DiagnosticCode &code =
                 (FLOW_WING::DIAGNOSTIC::DiagnosticCode)0 // NONE
  );
  Diagnostic(DiagnosticUtils::DiagnosticLevel level,
             DiagnosticUtils::DiagnosticType type,
             const std::vector<FLOW_WING::DIAGNOSTIC::DiagnosticArg> &args = {},
             const DiagnosticUtils::SourceLocation &location = {},
             const FLOW_WING::DIAGNOSTIC::DiagnosticCode &code =
                 (FLOW_WING::DIAGNOSTIC::DiagnosticCode)0);

  const std::string &getMessage() const;
  const std::string &getHelp() const;
  const std::string &getNote() const;
  const FLOW_WING::DIAGNOSTIC::DiagnosticCode &getCode() const;

  const FLOW_WING::DIAGNOSTIC::MessageTemplate &getMessageTemplate() const;

  DiagnosticUtils::DiagnosticLevel getLevel() const;

  DiagnosticUtils::DiagnosticType getType() const;

  const DiagnosticUtils::SourceLocation &getLocation() const;

  static std::unordered_map<FLOW_WING::DIAGNOSTIC::DiagnosticCode,
                            FLOW_WING::DIAGNOSTIC::MessageTemplate>
      messageTemplate;
};
