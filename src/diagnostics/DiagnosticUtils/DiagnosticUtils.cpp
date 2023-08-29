#include "DiagnosticUtils.h"

namespace DiagnosticUtils {

std::string toString(DiagnosticLevel level) {
  switch (level) {
  case DiagnosticLevel::Error:
    return "Error";
  case DiagnosticLevel::Warning:
    return "Warning";
  case DiagnosticLevel::Info:
    return "Info";
  case DiagnosticLevel::Debug:
    return "Debug";
  default:
    break;
  }
  return "Unknown";
}

std::string toString(DiagnosticType type) {
  switch (type) {
  case DiagnosticType::Lexical:
    return "Lexical";
  case DiagnosticType::Syntactic:
    return "Syntactic";
  case DiagnosticType::Semantic:
    return "Semantic";
  case DiagnosticType::CodeGen:
    return "CodeGen";
  case DiagnosticType::Runtime:
    return "Runtime";
  default:
    break;
  }
  return "Unknown";
}

} // namespace DiagnosticUtils