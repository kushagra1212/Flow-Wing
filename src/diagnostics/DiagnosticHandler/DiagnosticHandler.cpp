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
    std::function<bool(const Diagnostic &)> filter) const {
  for (auto &diagnostic : diagnostics) {
    if (filter(diagnostic)) {
      printDiagnostic(outputStream, diagnostic);
    }
  }

  // Reset the diagnostics
}

const void
DiagnosticHandler::printDiagnostic(std::ostream &outputStream,
                                   const Diagnostic &diagnostic) const {
  outputStream << RED << diagnostic.getLocation().fileName << " ["
               << DiagnosticUtils::toString(diagnostic.getLevel())
               << "] : " << RED_TEXT << "Line "
               << diagnostic.getLocation().lineNumber + 1 - previousLineCount
               << ":" << diagnostic.getLocation().columnNumber + 1 << RED
               << " \"" << diagnostic.getMessage() << "\"" << RESET << "\n";
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