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


#ifndef LLVMLOGGER_H
#define LLVMLOGGER_H

#include "../../diagnostics/Diagnostic/DiagnosticCode.h"
#include "../../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../../diagnostics/DiagnosticUtils/DiagnosticUtils.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/Support/Error.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"

class LLVMLogger {
  FlowWing::DiagnosticHandler *_diagnosticHandler;
  unsigned int errorCount;

public:
  LLVMLogger(FlowWing::DiagnosticHandler *diagnosticHandler);

  void logLLVMError(llvm::Error E);
  void logLLVMWarning(llvm::Error E);

  //[[deprecated("Use logError(Diagnostic) instead")]]
  void LogError(const std::string &errorMessage,
                const DiagnosticUtils::SourceLocation &location);

  //[[deprecated("Use logError(Diagnostic) instead")]]
  void LogError(const std::string &errorMessage);

  void logError(const FLOW_WING::DIAGNOSTIC::DiagnosticCode code,
                const std::vector<FLOW_WING::DIAGNOSTIC::DiagnosticArg> &args);

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