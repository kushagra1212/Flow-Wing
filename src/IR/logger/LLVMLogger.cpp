/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "LLVMLogger.h"
#include "src/diagnostics/Diagnostic/Diagnostic.h"
#include "src/diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "src/utils/Colors.h"
#include <string>

LLVMLogger::LLVMLogger(FlowWing::DiagnosticHandler *diagnosticHandler)
    : _diagnosticHandler(diagnosticHandler), errorCount(0), _sourceMgr(),
      _errs(llvm::errs()), _llvmErrorMsg("FlowWing::Error: "),
      _llvmWarningMsg("FlowWing::Warning: "), _llvmInfoMsg("FlowWing::Info") {}

void LLVMLogger::logLLVMError(llvm::Error E) {
  increaseErrorCount();
  llvm::handleAllErrors(std::move(E), [&](llvm::ErrorInfoBase &EIB) {
    // _sourceMgr.PrintMessage(llvm::SMLoc(), llvm::SourceMgr::DK_Error,
    //                         _llvmErrorMsg + EIB.message());

    llvm::errs() << RED_TEXT << _llvmErrorMsg << RED << EIB.message() << RESET
                 << "\n";
#if not defined(JIT_TEST_MODE) && not defined(AOT_TEST_MODE)
    exit(0);
#endif
    // clang-format off


  });
  // clang-format on
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
      Diagnostic({infoMessage}, DiagnosticUtils::DiagnosticLevel::Info,
                 DiagnosticUtils::DiagnosticType::CodeGen, _location));

  this->logLLVMInfo(llvm::make_error<llvm::StringError>(
      message, llvm::inconvertibleErrorCode()));

  // llvm::createStringError(llvm::inconvertibleErrorCode(), message)
}

void LLVMLogger::LogError(const std::string &errorMessage,
                          const DiagnosticUtils::SourceLocation &location) {

  const std::string &message = _diagnosticHandler->getLogString(
      Diagnostic({errorMessage}, DiagnosticUtils::DiagnosticLevel::Error,
                 DiagnosticUtils::DiagnosticType::Runtime, location));

  this->logLLVMError(llvm::make_error<llvm::StringError>(
      message, llvm::inconvertibleErrorCode()));

  // llvm::createStringError(llvm::inconvertibleErrorCode(), message)
}

void LLVMLogger::LogError(const std::string &errorMessage) {
  increaseErrorCount();
  const Diagnostic diagnostic =
      Diagnostic({errorMessage}, DiagnosticUtils::DiagnosticLevel::Error,
                 DiagnosticUtils::DiagnosticType::Semantic, _location);

  _diagnosticHandler->logJSONifAsked(_outputFilePath, diagnostic);

  const std::string &message = _diagnosticHandler->getLogString(diagnostic);

  this->logLLVMError(llvm::make_error<llvm::StringError>(
      message, llvm::inconvertibleErrorCode()));
}

void LLVMLogger::logError(
    const FLOW_WING::DIAGNOSTIC::DiagnosticCode code,
    const std::vector<FLOW_WING::DIAGNOSTIC::DiagnosticArg> &args) {
  increaseErrorCount();

  const Diagnostic diagnostic = Diagnostic(
      DiagnosticUtils::DiagnosticLevel::Error,
      DiagnosticUtils::DiagnosticType::Semantic, args, _location, code);

  _diagnosticHandler->logJSONifAsked(_outputFilePath, diagnostic);

  this->logLLVMError(llvm::make_error<llvm::StringError>(
      _diagnosticHandler->getLogString(diagnostic),
      llvm::inconvertibleErrorCode()));
}

const std::string
LLVMLogger::getLLVMErrorMsg(const std::string &errorMessage,
                            const DiagnosticUtils::SourceLocation &location) {

  return _diagnosticHandler->getLogString(
      Diagnostic({errorMessage}, DiagnosticUtils::DiagnosticLevel::Error,
                 DiagnosticUtils::DiagnosticType::Runtime, location));
}

void LLVMLogger::setCurrentSourceLocation(
    const DiagnosticUtils::SourceLocation &location) {
  _location = location;
}

uint64_t LLVMLogger::getErrorCount() const { return errorCount; }

DiagnosticUtils::SourceLocation LLVMLogger::getCurrentSourceLocation() const {
  return _location;
}

auto LLVMLogger::increaseErrorCount() -> void { errorCount++; }