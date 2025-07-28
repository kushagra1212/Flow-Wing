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

#include "CompilerUtils.h"
#include "src/IR/constants/FlowWingIRConstants.h"
#include "src/diagnostics/Diagnostic/Diagnostic.h"
#include "src/utils/PathUtils.h"
#include "src/utils/Utils.h"
#include <cstdlib>
#include <memory>
#include <stdexcept>

namespace FlowWing {

namespace Compiler {

std::unique_ptr<llvm::MemoryBuffer>
getMemoryBuffer(const std::string &filePath,
                FlowWing::DiagnosticHandler *diagHandler) {
  if (auto bufferOrErr = llvm::MemoryBuffer::getFile(filePath)) {
    return std::move(*bufferOrErr);
  } else {
    diagHandler->printDiagnostic(
        std::cerr, Diagnostic("Error reading bitcode file: " + filePath + " " +
                                  bufferOrErr.getError().message(),
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Linker,
                              DiagnosticUtils::SourceLocation()));
    throw std::runtime_error("Error reading bitcode file: " + filePath);
    return nullptr;
  }
}

std::vector<std::string>
getIRFilePaths(FlowWing::DiagnosticHandler *diagHandler,
               const std::string &directoryPath) {
  std::vector<std::string> irFilesPath = {};

#ifdef DEBUG
  irFilesPath =
      Utils::getAllFilesInDirectoryWithExtension(directoryPath, ".ll", false);
#else
  irFilesPath =
      Utils::getAllFilesInDirectoryWithExtension(directoryPath, ".bc", false);
#endif

  if (irFilesPath.size() == 0) {
    diagHandler->printDiagnostic(
        std::cerr,
        Diagnostic("No user defined IR files found. in " + directoryPath,
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Linker,
                   DiagnosticUtils::SourceLocation(0, 0, 0, "")));
    return {};
  }

  return irFilesPath;
}

std::unique_ptr<llvm::Module>
createLLVMModuleFromCodeorIR(std::unique_ptr<llvm::LLVMContext> &TheContext,
                             FlowWing::DiagnosticHandler *diagHandler) {

  const std::string &filePath =
      FlowWing::PathUtils::getBuiltInBCPath().string();

  LINKING_DEBUG_LOG(" [INFO]: Built In Module Path ", filePath);

#if defined(RELEASE)
  std::unique_ptr<llvm::Module> TheModule =
      (createModuleFromBitcode(filePath, TheContext, diagHandler));

#else
  std::unique_ptr<llvm::Module> TheModule =
      isValidLLFile(filePath) == EXIT_SUCCESS
          ? std::move(createModuleFromIR(filePath, TheContext, diagHandler))
          : std::move(
                createModuleFromBitcode(filePath, TheContext, diagHandler));

#endif

  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();

#if defined(__APPLE__)
  TheModule->setTargetTriple(llvm::sys::getDefaultTargetTriple());
#elif defined(__linux__)
  TheModule->setTargetTriple(
      llvm::Triple::normalize(llvm::sys::getDefaultTargetTriple()));
#endif

  return TheModule;
}

int8_t isValidLLFile(const std::string &filePath) {
  if (filePath.length() <= 3) {
    throw std::runtime_error(filePath + " is not an valid file path");
    return EXIT_FAILURE;
  }

  if (Utils::hasFileExtenstion(filePath, "ll") == EXIT_SUCCESS) {
    return EXIT_SUCCESS;
  }

  if (Utils::hasFileExtenstion(filePath, "bc") == EXIT_SUCCESS) {
    return EXIT_FAILURE;
  }

  throw std::runtime_error(filePath + " is not an valid file path");
  return EXIT_FAILURE;
}

std::unique_ptr<llvm::Module>
getLinkedModule(std::unique_ptr<llvm::LLVMContext> &TheContext,
                FlowWing::DiagnosticHandler *diagHandler) {

  std::unique_ptr<llvm::Module> TheModule =
      (FlowWing::Compiler::createLLVMModuleFromCodeorIR(TheContext,
                                                        diagHandler));

  std::vector<std::string> filesPath = FlowWing::Compiler::getIRFilePaths(
      diagHandler,
      Utils::getTempDir() + FLOWWING::IR::CONSTANTS::TEMP_BC_FILES_DIR);

//! Need to Include the built in .bc files for both DEBUG and Release
#if defined(RELEASE) && defined(JIT_MODE)

#endif

  for (const std::string &path : filesPath) {
    llvm::SMDiagnostic err;

    LINKING_DEBUG_LOG(" [INFO]: Linking ", path);

    bool LinkResult = llvm::Linker::linkModules(
        *TheModule.get(), llvm::parseIRFile(path, err, *TheContext.get()),
        llvm::Linker::Flags::OverrideFromSrc);
    if (LinkResult) {
      diagHandler->printDiagnostic(
          std::cerr,
          Diagnostic("Error linking " + path,
                     DiagnosticUtils::DiagnosticLevel::Error,
                     DiagnosticUtils::DiagnosticType::Linker,
                     DiagnosticUtils::SourceLocation(0, 0, 0, path)));
      return nullptr;
    }
  }

  LINKING_DEBUG_LOG(" [INFO]: Finished linking modules Done. ", "");

  return TheModule;
}

void loadArchiveIntoExecutionEngine(llvm::ExecutionEngine *executionEngine,
                                    const std::string &archivePath,
                                    FlowWing::DiagnosticHandler *diagHandler) {
  // Read the archive file into a MemoryBuffer
  llvm::ErrorOr<std::unique_ptr<llvm::MemoryBuffer>> buffer =
      llvm::MemoryBuffer::getFile(archivePath);

  LINKING_DEBUG_LOG(" [INFO]: Loading Archive: ", archivePath);

  if (!buffer) {
    diagHandler->printDiagnostic(
        std::cerr, Diagnostic("Failed to read archive: " + archivePath,
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Linker,
                              DiagnosticUtils::SourceLocation()));

    return;
  }
  // Parse the archive
  llvm::Expected<std::unique_ptr<llvm::object::Archive>> archive =
      llvm::object::Archive::create(buffer->get()->getMemBufferRef());

  if (!archive) {
    diagHandler->printDiagnostic(
        std::cerr, Diagnostic("Failed to parse archive: " + archivePath,
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Linker,
                              DiagnosticUtils::SourceLocation()));
    return;
  }

  std::unique_ptr<llvm::object::Archive> archivePtr = std::move(archive.get());
  std::unique_ptr<llvm::MemoryBuffer> bufferPtr = std::move(buffer.get());
  // Iterate over the archive members (object files) and add them to the
  // execution engine

  executionEngine->addArchive(llvm::object::OwningBinary<llvm::object::Archive>(
      std::move(archivePtr), std::move(bufferPtr)));

  LEXER_DEBUG_LOG(" [INFO]: Finished loading archive: ", archivePath);
}

std::unique_ptr<llvm::Module>
createModuleFromIR(const std::string &filePath,
                   std::unique_ptr<llvm::LLVMContext> &TheContext,
                   FlowWing::DiagnosticHandler *diagHandler) {
  llvm::SMDiagnostic Err;
  std::unique_ptr<llvm::Module> TheModule =
      llvm::parseIRFile(filePath, Err, *TheContext);

  if (!TheModule) {
    diagHandler->printDiagnostic(
        std::cerr, Diagnostic("Error reading IR file: " + filePath,
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Linker,
                              DiagnosticUtils::SourceLocation(0, 0, 0, "")));
    return nullptr;
  }

  return TheModule;
}

std::unique_ptr<llvm::Module>
createModuleFromBitcode(const std::string &filePath,
                        std::unique_ptr<llvm::LLVMContext> &TheContext,
                        FlowWing::DiagnosticHandler *diagHandler) {

  std::unique_ptr<llvm::MemoryBuffer> buffer =
      (getMemoryBuffer(filePath, diagHandler));

  if (auto moduleOrErr =
          llvm::parseBitcodeFile(buffer->getMemBufferRef(), *TheContext)) {
    return std::move(*moduleOrErr);
  } else {
    diagHandler->printDiagnostic(
        std::cerr, Diagnostic("Error reading bitcode file: " + filePath,
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Linker,
                              DiagnosticUtils::SourceLocation(0, 0, 0, "")));
    return nullptr;
  }
}

void logNoErrorJSONIfAsked(const std::string &outputFilePath) {
  if (Utils::getExtension(outputFilePath) == ".json") {
    JSON jsonObj = {{"error", false}};
    Utils::logJSON(jsonObj,
                   outputFilePath.substr(0, outputFilePath.find_last_of(".")) +
                       ".err.json");
  }
}

} // namespace Compiler

} // namespace FlowWing