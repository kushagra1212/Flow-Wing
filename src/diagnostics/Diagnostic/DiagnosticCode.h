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
