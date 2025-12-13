/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 */
#pragma once

#include "DiagnosticCode.h" // For DiagnosticArg
#include "src/common/cli/CliColors.h"
#include <sstream>
#include <string>
#include <variant>
#include <vector>

namespace flow_wing {
namespace diagnostic {

inline std::string argToString(const DiagnosticArg &arg) {
  std::stringstream ss;
  std::visit([&](auto &&val) { ss << val; }, arg);
  return ss.str();
}

inline std::string formatMessage(std::string template_string,
                                 const std::vector<DiagnosticArg> &args,
                                 const bool withHighlight = true) {
  for (size_t i = 0; i < args.size(); ++i) {
    std::string place_holder = "{" + std::to_string(i) + "}";
    size_t pos = template_string.find(place_holder);
    while (pos != std::string::npos) {
      template_string.replace(
          pos, place_holder.length(),
          withHighlight ? HIGHLIGHT_TEXT + argToString(args[i]) + WHITE_TEXT
                        : argToString(args[i]));

      pos = template_string.find(place_holder, pos);
    }
  }
  return template_string;
}

inline std::string getErrorCodeString(const DiagnosticCode &code) {
  return "flow_wing_error_code_" + std::to_string(static_cast<int16_t>(code));
}

} // namespace diagnostic
} // namespace flow_wing
