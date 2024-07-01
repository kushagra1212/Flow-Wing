#include "LLVMLogger.h"

void LLVMLogger::logLLVMError(llvm::Error E) {
  increaseErrorCount();
  llvm::handleAllErrors(std::move(E), [&](llvm::ErrorInfoBase &EIB) {
    // _sourceMgr.PrintMessage(llvm::SMLoc(), llvm::SourceMgr::DK_Error,
    //                         _llvmErrorMsg + EIB.message());

    llvm::errs() << RED_TEXT << _llvmErrorMsg << RED << EIB.message() << RESET
                 << "\n";
    exit(0);
  });
#ifndef JIT_TEST_MODE
  exit(1);

#endif
}

void LLVMLogger::logLLVMWarning(llvm::Error E) {
  increaseErrorCount();
  llvm::handleAllErrors(std::move(E), [&](llvm::ErrorInfoBase &EIB) {
    // _sourceMgr.PrintMessage(llvm::SMLoc(), llvm::SourceMgr::DK_Warning,
    //                         _llvmWarningMsg + EIB.message());

    llvm::errs() << YELLOW_TEXT << _llvmWarningMsg << YELLOW << EIB.message()
                 << RESET << "\n";
  });
}

void LLVMLogger::logLLVMInfo(llvm::Error E) {
  llvm::handleAllErrors(std::move(E), [&](llvm::ErrorInfoBase &EIB) {
    llvm::errs() << GREEN_TEXT << _llvmInfoMsg << GREEN << EIB.message()
                 << RESET << "\n";
  });
}

void LLVMLogger::LogInfo(const std::string &infoMessage) {

  const std::string &message = _diagnosticHandler->getLogString(
      Diagnostic(infoMessage, DiagnosticUtils::DiagnosticLevel::Info,
                 DiagnosticUtils::DiagnosticType::CodeGen, _location));

  this->logLLVMInfo(llvm::make_error<llvm::StringError>(
      message, llvm::inconvertibleErrorCode()));

  // llvm::createStringError(llvm::inconvertibleErrorCode(), message)
}

void LLVMLogger::LogError(const std::string &errorMessage,
                          const DiagnosticUtils::SourceLocation &location) {

  const std::string &message = _diagnosticHandler->getLogString(
      Diagnostic(errorMessage, DiagnosticUtils::DiagnosticLevel::Error,
                 DiagnosticUtils::DiagnosticType::Runtime, location));

  this->logLLVMError(llvm::make_error<llvm::StringError>(
      message, llvm::inconvertibleErrorCode()));

  // llvm::createStringError(llvm::inconvertibleErrorCode(), message)
}

void LLVMLogger::LogError(const std::string &errorMessage) {
  increaseErrorCount();
  const std::string &message = _diagnosticHandler->getLogString(
      Diagnostic(errorMessage, DiagnosticUtils::DiagnosticLevel::Error,
                 DiagnosticUtils::DiagnosticType::Runtime, _location));

  this->logLLVMError(llvm::make_error<llvm::StringError>(
      message, llvm::inconvertibleErrorCode()));
}

const std::string
LLVMLogger::getLLVMErrorMsg(const std::string &errorMessage,
                            const DiagnosticUtils::SourceLocation &location) {

  return _diagnosticHandler->getLogString(
      Diagnostic(errorMessage, DiagnosticUtils::DiagnosticLevel::Error,
                 DiagnosticUtils::DiagnosticType::Runtime, location));
}

void LLVMLogger::setCurrentSourceLocation(
    const DiagnosticUtils::SourceLocation &location) {
  _location = location;
}

const int32_t LLVMLogger::getErrorCount() const { return errorCount; }

DiagnosticUtils::SourceLocation LLVMLogger::getCurrentSourceLocation() const {
  return _location;
}

auto LLVMLogger::increaseErrorCount() -> void { errorCount++; }