#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H

#include "../../utils/Utils.h"
#include "../Diagnostic/DiagnosticCode.h"
#include "../DiagnosticUtils/DiagnosticUtils.h"
#include "DiagnosticCode.h"

class Diagnostic {
private:
  std::string _message;
  std::string _help;
  std::string _note;
  FLOW_WING::DIAGNOSTIC::MessageTemplate _messageTemplate;
  DiagnosticUtils::DiagnosticLevel _level;
  DiagnosticUtils::DiagnosticType _type;
  DiagnosticUtils::SourceLocation _location;
  FLOW_WING::DIAGNOSTIC::DiagnosticCode _code;

public:
  Diagnostic(const std::string &message, DiagnosticUtils::DiagnosticLevel level,
             DiagnosticUtils::DiagnosticType type,
             const DiagnosticUtils::SourceLocation &location = {},
             const FLOW_WING::DIAGNOSTIC::DiagnosticCode &code =
                 (FLOW_WING::DIAGNOSTIC::DiagnosticCode)0 // NONE
  );
  Diagnostic(DiagnosticUtils::DiagnosticLevel level,
             DiagnosticUtils::DiagnosticType type,
             const std::vector<FLOW_WING::DIAGNOSTIC::DiagnosticArg> &args = {},
             const DiagnosticUtils::SourceLocation &location = {},
             const FLOW_WING::DIAGNOSTIC::DiagnosticCode &code =
                 (FLOW_WING::DIAGNOSTIC::DiagnosticCode)0);

  const std::string &getMessage() const;
  const std::string &getHelp() const;
  const std::string &getNote() const;
  const FLOW_WING::DIAGNOSTIC::DiagnosticCode &getCode() const;

  const FLOW_WING::DIAGNOSTIC::MessageTemplate &getMessageTemplate() const;

  DiagnosticUtils::DiagnosticLevel getLevel() const;

  DiagnosticUtils::DiagnosticType getType() const;

  const DiagnosticUtils::SourceLocation &getLocation() const;

  static std::unordered_map<FLOW_WING::DIAGNOSTIC::DiagnosticCode,
                            FLOW_WING::DIAGNOSTIC::MessageTemplate>
      messageTemplate;
};

#endif // DIAGNOSTIC_H
