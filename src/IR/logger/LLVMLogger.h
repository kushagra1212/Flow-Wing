#ifndef LLVMLOGGER_H
#define LLVMLOGGER_H

#include "../../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../../diagnostics/DiagnosticUtils/DiagnosticUtils.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/Support/Error.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
class LLVMLogger {
  FLowWing::DiagnosticHandler *_diagnosticHandler;
  unsigned int errorCount;

public:
  LLVMLogger(FLowWing::DiagnosticHandler *diagnosticHandler)
      : _sourceMgr(), _errs(llvm::errs()), _llvmErrorMsg("FlowWing::Error: "),
        _llvmWarningMsg("FlowWing::Warning: "), _llvmInfoMsg("FlowWing::Info"),
        _diagnosticHandler(diagnosticHandler), errorCount(0) {}

  void logLLVMError(llvm::Error E);
  void logLLVMWarning(llvm::Error E);

  void LogError(const std::string &errorMessage,
                const DiagnosticUtils::SourceLocation &location);

  void LogError(const std::string &errorMessage);

  const std::string
  getLLVMErrorMsg(const std::string &errorMessage,
                  const DiagnosticUtils::SourceLocation &location);

  void LogInfo(const std::string &infoMessage);

  void
  setCurrentSourceLocation(const DiagnosticUtils::SourceLocation &location);

  DiagnosticUtils::SourceLocation getCurrentSourceLocation() const;

  const unsigned int getErrorCount() const;

  auto increaseErrorCount() -> void;

  void logLLVMInfo(llvm::Error E);

  inline auto setOutputFilePath(const std::string &outputFilePath) -> void {
    _outputFilePath = outputFilePath;
  }

private:
  llvm::SourceMgr _sourceMgr;
  llvm::raw_ostream &_errs;
  std::string _llvmErrorMsg;
  std::string _llvmWarningMsg;
  std::string _llvmInfoMsg;
  DiagnosticUtils::SourceLocation _location;

  std::string _outputFilePath = "";
};

#endif // LLVMLOGGER_H