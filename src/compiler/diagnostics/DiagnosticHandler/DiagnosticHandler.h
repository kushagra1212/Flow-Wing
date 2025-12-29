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

#include "src/compiler/diagnostics/Diagnostic.h"
#include "src/compiler/diagnostics/formatters/IDiagnosticFormatter.h"
#include "src/utils/LogConfig.h"
#include <vector>

namespace flow_wing {

namespace diagnostic {
class DiagnosticHandler {
public:
  void report(const Diagnostic &diagnostic) {
    m_diagnostics.push_back(diagnostic);
  }

  const std::vector<Diagnostic> &getDiagnostics() const {
    return m_diagnostics;
  }

  // Checks if any errors of a specific type have been reported.
  bool hasError(diagnostic::DiagnosticType type) const;

private:
  std::vector<Diagnostic> m_diagnostics;
};
}; // namespace diagnostic

} // namespace flow_wing
