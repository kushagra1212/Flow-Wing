#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H

#include "../../utils/Utils.h"
#include "../DiagnosticUtils/DiagnosticUtils.h"

class Diagnostic {
private:
  std::string _message;
  DiagnosticUtils::DiagnosticLevel _level;
  DiagnosticUtils::DiagnosticType _type;
  DiagnosticUtils::SourceLocation _location;

public:
  Diagnostic(const std::string &message, DiagnosticUtils::DiagnosticLevel level,
             DiagnosticUtils::DiagnosticType type,
             const DiagnosticUtils::SourceLocation &location = {});

  const std::string &getMessage() const;

  DiagnosticUtils::DiagnosticLevel getLevel() const;

  DiagnosticUtils::DiagnosticType getType() const;

  const DiagnosticUtils::SourceLocation &getLocation() const;
};

#endif // DIAGNOSTIC_H
