#include "LLVMLogger.h"

void LLVMLogger::logLLVMError(llvm::Error E) {
  llvm::handleAllErrors(std::move(E), [&](llvm::ErrorInfoBase &EIB) {
    // _sourceMgr.PrintMessage(llvm::SMLoc(), llvm::SourceMgr::DK_Error,
    //                         _llvmErrorMsg + EIB.message());

    llvm::errs() << RED_TEXT << _llvmErrorMsg << RED << EIB.message() << RESET
                 << "\n";
  });
}

void LLVMLogger::logLLVMWarning(llvm::Error E) {
  llvm::handleAllErrors(std::move(E), [&](llvm::ErrorInfoBase &EIB) {
    // _sourceMgr.PrintMessage(llvm::SMLoc(), llvm::SourceMgr::DK_Warning,
    //                         _llvmWarningMsg + EIB.message());

    llvm::errs() << YELLOW_TEXT << _llvmWarningMsg << YELLOW << EIB.message()
                 << RESET << "\n";
  });
}

void LLVMLogger::LogError(const std::string &errorMessgae,
                          const DiagnosticUtils::SourceLocation &location) {

  const std::string &message = _diagnosticHandler->getLogString(
      Diagnostic(errorMessgae, DiagnosticUtils::DiagnosticLevel::Error,
                 DiagnosticUtils::DiagnosticType::Runtime, location));

  this->logLLVMError(llvm::make_error<llvm::StringError>(
      message, llvm::inconvertibleErrorCode()));

  // llvm::createStringError(llvm::inconvertibleErrorCode(), message)
}