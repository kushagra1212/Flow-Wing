#include "DiagnosticHandler.h"

DiagnosticHandler::DiagnosticHandler(DiagnosticHandler *parent) {
  this->parent = parent;
}

void DiagnosticHandler::addDiagnostic(const Diagnostic &diagnostic) {
  diagnostics.push_back(diagnostic);
}

void DiagnosticHandler::addParentDiagnostics(DiagnosticHandler *pat) {
  if (pat != nullptr) {
    this->parent = pat;
  }
}

const void DiagnosticHandler::logDiagnostics(
    std::ostream &outputStream,
    std::function<bool(const Diagnostic &)> filter) {
  for (auto &diagnostic : diagnostics) {
    if (filter(diagnostic)) {
      printDiagnostic(outputStream, diagnostic);
    }
  }

  // Reset the diagnostics
}

std::string DiagnosticHandler::getLogString(const Diagnostic &diagnostic) {
  std::string fileName = diagnostic.getLocation().fileName;
  std::string message = diagnostic.getMessage();
  std::string level = DiagnosticUtils::toString(diagnostic.getLevel());
  std::string type = DiagnosticUtils::toString(diagnostic.getType());
  std::string lineNumber = std::to_string(diagnostic.getLocation().lineNumber +
                                          1 - previousLineCount);
  std::string columnNumber =
      std::to_string(diagnostic.getLocation().columnNumber + 1);

  std::string logString = "";
  logString += RED + fileName + " [" + level + "] : " + RED_TEXT + "Line " +
               lineNumber + ":" + columnNumber + RED + " \"" + message + "\"" +
               RESET + "\n";
  return logString;
}

const void DiagnosticHandler::printDiagnostic(std::ostream &outputStream,
                                              const Diagnostic &diagnostic) {
  outputStream << getLogString(diagnostic);
}

bool DiagnosticHandler::hasError(DiagnosticUtils::DiagnosticLevel level) const {
  return std::any_of(diagnostics.begin(), diagnostics.end(),
                     [level](const Diagnostic &diagnostic) {
                       return diagnostic.getLevel() == level;
                     });
}

bool DiagnosticHandler::hasError(DiagnosticUtils::DiagnosticType type) const {
  return std::any_of(diagnostics.begin(), diagnostics.end(),
                     [type](const Diagnostic &diagnostic) {
                       return diagnostic.getType() == type &&
                              diagnostic.getLevel() ==
                                  DiagnosticUtils::DiagnosticLevel::Error;
                     });
}

void DiagnosticHandler::updatePreviousLineCount(const int count) {
  this->previousLineCount = count;
}