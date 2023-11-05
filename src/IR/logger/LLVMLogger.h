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
  DiagnosticHandler *_diagnosticHandler;

public:
  LLVMLogger(DiagnosticHandler *diagnosticHandler)
      : _sourceMgr(), _errs(llvm::errs()), _llvmErrorMsg("FlowWing Error: "),
        _llvmWarningMsg("FlowWing Warning: "),
        _diagnosticHandler(diagnosticHandler) {}

  void logLLVMError(llvm::Error E);
  void logLLVMWarning(llvm::Error E);

  void LogError(const std::string &errorMessgae,
                const DiagnosticUtils::SourceLocation &location);

private:
  llvm::SourceMgr _sourceMgr;
  llvm::raw_ostream &_errs;
  std::string _llvmErrorMsg;
  std::string _llvmWarningMsg;
};

#endif // LLVMLOGGER_H