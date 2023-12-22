#include "Diagnostic.h"
Diagnostic::Diagnostic(const std::string &message,
                       DiagnosticUtils::DiagnosticLevel level,
                       DiagnosticUtils::DiagnosticType type,
                       const DiagnosticUtils::SourceLocation &location)
    : _message(message), _level(level), _type(type), _location(location) {}

const std::string &Diagnostic::getMessage() const { return _message; }

DiagnosticUtils::DiagnosticLevel Diagnostic::getLevel() const { return _level; }

DiagnosticUtils::DiagnosticType Diagnostic::getType() const { return _type; }

const DiagnosticUtils::SourceLocation &Diagnostic::getLocation() const {
  return _location;
}
