#ifndef DIAGNOSTIC_HANDLER_H
#define DIAGNOSTIC_HANDLER_H

#include "../Diagnostic/Diagnostic.h"
#include "../DiagnosticUtils/DiagnosticUtils.h"

class DiagnosticHandler {
private:
  std::vector<Diagnostic> diagnostics;
  DiagnosticHandler *parent;
  int previousLineCount = 0;

public:
  DiagnosticHandler(DiagnosticHandler *parent = nullptr);
  void addDiagnostic(const Diagnostic &diagnostic);

  void addParentDiagnostics(DiagnosticHandler *parent);
  const void
  logDiagnostics(std::ostream &outputStream,
                 std::function<bool(const Diagnostic &)> filter) const;

  const void printDiagnostic(std::ostream &outputStream,
                             const Diagnostic &diagnostic) const;

  bool hasError(DiagnosticUtils::DiagnosticLevel) const;

  bool hasError(DiagnosticUtils::DiagnosticType) const;

  void updatePreviousLineCount(const int count);
};

#endif // DIAGNOSTIC_HANDLER_H