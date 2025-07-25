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


#include "DiagnosticCode.h"

namespace FLOW_WING {
namespace DIAGNOSTIC {

std::string argToString(const DiagnosticArg &arg) {
  std::stringstream ss;
  std::visit([&](auto &&val) { ss << val; }, arg);
  return ss.str();
}

std::string formatMessage(std::string templateStr,
                          const std::vector<DiagnosticArg> &args,
                          const bool withHighlight) {
  for (size_t i = 0; i < args.size(); ++i) {
    std::string placeholder = "{" + std::to_string(i) + "}";
    size_t pos = templateStr.find(placeholder);
    while (pos != std::string::npos) {
      templateStr.replace(pos, placeholder.length(),
                          withHighlight
                              ? BOLD_YELLOW_TEXT + argToString(args[i]) +
                                    RESET + BOLD_WHITE_TEXT
                              : argToString(args[i]));
      pos = templateStr.find(placeholder, pos);
    }
  }
  return templateStr;
}

std::string getErrorCode(const DiagnosticCode &code) {

  return "FG_ERROR_CODE_" + std::to_string(static_cast<int16_t>(code));
}
} // namespace DIAGNOSTIC
} // namespace FLOW_WING
