/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 */
#include "DiagnosticHandler.h"
#include <algorithm>

namespace flow_wing {
namespace diagnostic {

bool DiagnosticHandler::hasError(diagnostic::DiagnosticType type) const {
  return std::any_of(
      m_diagnostics.begin(), m_diagnostics.end(), [type](const Diagnostic &d) {
        return d.getType() == type &&
               d.getLevel() == diagnostic::DiagnosticLevel::kError;
      });
}

} // namespace diagnostic

} // namespace flow_wing
