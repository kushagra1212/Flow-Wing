#ifndef DIAGNOSTIC_HANDLER_H
#define DIAGNOSTIC_HANDLER_H

#include <string>

#include "../Diagnostic/Diagnostic.h"
#include "../DiagnosticUtils/DiagnosticUtils.h"

namespace FlowWing {
class DiagnosticHandler {
private:
  std::vector<Diagnostic> diagnostics;
  DiagnosticHandler *parent;
  int previousLineCount = 0;
  std::string _filePath;
  std::vector<std::string> _replLines;

  std::string _outputFilePath = "";

public:
  std::string getFileName(const std::string &filePath);
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

  void logJSONifAsked(const std::string &outputFilePath,
                      const Diagnostic &diagnostic);

  bool hasError(DiagnosticUtils::DiagnosticLevel) const;

  bool hasError(DiagnosticUtils::DiagnosticType) const;

  void updatePreviousLineCount(const int count);

  void setReplLines(const std::vector<std::string> &replLines);

  const std::vector<std::string> &getReplLines() const;

  std::vector<std::string> getLines();

  const int8_t isRepl() const;

  inline auto setOutputFilePath(const std::string &outputFilePath) -> void {
    this->_outputFilePath = outputFilePath;
  }

  inline auto getOutputFilePath() const -> const std::string & {
    return this->_outputFilePath;
  }
};
} // namespace FlowWing

#endif // DIAGNOSTIC_HANDLER_H