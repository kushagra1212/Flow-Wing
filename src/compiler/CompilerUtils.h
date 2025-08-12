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

#pragma once

#include "src/diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include <cstdint>

// clang-format off
#include "src/diagnostics/Diagnostic/diagnostic_push.h"
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Linker/Linker.h>
#include <llvm/Object/Archive.h>
#include <llvm/Object/Binary.h>
#include <llvm/Object/ObjectFile.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/TargetParser/Triple.h>
#include "src/diagnostics/Diagnostic/diagnostic_pop.h"
// clang-format on

namespace FlowWing {

namespace Compiler {

std::unique_ptr<llvm::MemoryBuffer>
getMemoryBuffer(const std::string &filePath,
                FlowWing::DiagnosticHandler *diagHandler);

std::vector<std::string>
getIRFilePaths(FlowWing::DiagnosticHandler *diagHandler,
               const std::string &directoryPath);

std::unique_ptr<llvm::Module>
createLLVMModule(std::unique_ptr<llvm::LLVMContext> &TheContext);

int8_t isValidLLFile(const std::string &filePath);

std::unique_ptr<llvm::Module>
getLinkedModule(std::unique_ptr<llvm::LLVMContext> &TheContext,
                FlowWing::DiagnosticHandler *diagHandler);

//? Create Module

std::unique_ptr<llvm::Module>
createModuleFromIR(const std::string &filePath,
                   std::unique_ptr<llvm::LLVMContext> &TheContext,
                   FlowWing::DiagnosticHandler *diagHandler);

// Function to load the .a file into the ExecutionEngine
void loadArchiveIntoExecutionEngine(llvm::ExecutionEngine *executionEngine,
                                    const std::string &archivePath,
                                    FlowWing::DiagnosticHandler *diagHandler);

//? INLINE FUNCTIONS

// JSON LOG FILE for (AST/ERR)
void logNoErrorJSONIfAsked(const std::string &outputFilePath);

} // namespace Compiler
} // namespace FlowWing