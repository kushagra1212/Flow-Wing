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

#include "Diagnostic.h"
#include "src/compiler/diagnostics/DiagnosticFormatUtils.h"
#include "src/compiler/diagnostics/DiagnosticMessageDatabase/DiagnosticMessageDatabase.h"
#include <vector>

namespace flow_wing {
namespace diagnostic {

struct DiagnosticFactory {
  static Diagnostic create(DiagnosticCode code,
                           const std::vector<DiagnosticArg> &args,
                           const SourceLocation &location,
                           DiagnosticLevel level, DiagnosticType type) {

    const auto &message_template = DiagnosticMessageDatabase::getTemplate(code);

    std::string message = formatMessage(message_template.message, args);
    std::string help = formatMessage(message_template.help, args);
    std::string note = formatMessage(message_template.note, args);

    return Diagnostic(std::move(message), std::move(help), std::move(note),
                      level, type, location, code);
  }
};

} // namespace diagnostic
} // namespace flow_wing
