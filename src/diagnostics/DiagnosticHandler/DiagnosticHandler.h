#ifndef DIAGNOSTIC_HANDLER_H
#define DIAGNOSTIC_HANDLER_H

#include "../Diagnostic/Diagnostic.h"
#include "../DiagnosticUtils/DiagnosticUtils.h"
#include <string>

class DiagnosticHandler {
private:
  std::vector<Diagnostic> diagnostics;
  DiagnosticHandler *parent;
  int previousLineCount = 0;
  std::string _filePath;
  std::string getFileName(const std::string &filePath);

public:
  DiagnosticHandler(std::string filePath = "",
                    DiagnosticHandler *parent = nullptr);
  void addDiagnostic(const Diagnostic &diagnostic);
  std::string getLogString(const Diagnostic &diagnostic);

  std::string getAbsoluteFilePath();

  std::string getErrorProducingSnippet(int lineNumber, int columnNumber);
  void addParentDiagnostics(DiagnosticHandler *parent);
  const void logDiagnostics(std::ostream &outputStream,
                            std::function<bool(const Diagnostic &)> filter);

  const void printDiagnostic(std::ostream &outputStream,
                             const Diagnostic &diagnostic);

  bool hasError(DiagnosticUtils::DiagnosticLevel) const;

  bool hasError(DiagnosticUtils::DiagnosticType) const;

  void updatePreviousLineCount(const int count);
};

#endif // DIAGNOSTIC_HANDLER_H