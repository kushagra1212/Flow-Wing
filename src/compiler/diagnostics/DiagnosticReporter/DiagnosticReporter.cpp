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

#include "DiagnosticReporter.h"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/compiler/diagnostics/DiagnosticHandler/DiagnosticHandler.h"

namespace flow_wing {

namespace diagnostic {

DiagnosticReporter::DiagnosticReporter(
    std::ostream &output_stream,
    std::unique_ptr<IDiagnosticFormatter> formatter)
    : m_output_stream(output_stream), m_formatter(std::move(formatter)) {}

void DiagnosticReporter::report(const DiagnosticHandler &handler,
                                const CompilationContext &context) {
  auto diagnostics = handler.getDiagnostics();
  if (!diagnostics.empty()) {
    // Print the last diagnostic
    m_output_stream << m_formatter->format(diagnostics.back(), context);
  }
}
} // namespace diagnostic

} // namespace flow_wing
