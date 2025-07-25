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

#include "../../utils/Colors.h"
#include <cstdint>
#include <sstream>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace FLOW_WING {
namespace DIAGNOSTIC {

enum class DiagnosticCode : int16_t;
struct MessageTemplate {
  std::string message;
  std::string help;
  std::string note;
}; // namespace DIAGNOSTIC

using DiagnosticArg = std::variant<std::string, int, double, bool>;

std::string argToString(const DiagnosticArg &arg);

std::string formatMessage(std::string templateStr,
                          const std::vector<DiagnosticArg> &args,
                          const bool withHighlight = true);

std::string getErrorCode(const DiagnosticCode &code);

} // namespace DIAGNOSTIC
} // namespace FLOW_WING
