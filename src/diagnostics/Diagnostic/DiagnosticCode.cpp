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
