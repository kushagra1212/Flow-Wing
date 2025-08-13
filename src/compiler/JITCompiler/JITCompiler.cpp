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

#include "JITCompiler.h"
#include "src/common/commandLineOptions/commandLineOptions.h"
#include "src/common/version.h"
#include "src/compiler/CompilerUtils.h"
#include "src/diagnostics/Diagnostic/Diagnostic.h"
#include "src/diagnostics/DiagnosticUtils/DiagnosticUtils.h"
#include "src/external/include/argh.h"
#include <signal.h>
#include <string>

#ifdef TESTS_ENABLED
#include <gtest/gtest.h>
#endif

JITCompiler::JITCompiler(std::string filePath) : Compiler(filePath) {}

void JITCompiler::execute() {
  std::unique_ptr<llvm::LLVMContext> TheContext =
      std::make_unique<llvm::LLVMContext>();
  std::unique_ptr<llvm::IRBuilder<>> Builder =
      std::make_unique<llvm::IRBuilder<>>(*TheContext);

  std::unique_ptr<llvm::Module> TheModule =
      (FlowWing::Compiler::getLinkedModule(TheContext,
                                           _currentDiagnosticHandler.get()));

  llvm::Function *mainFunction =
      TheModule->getFunction(FLOWWING_GLOBAL_ENTRY_POINT);

  std::string errorMessage;
  executionEngine = llvm::EngineBuilder(std::move(TheModule))
                        .setErrorStr(&errorMessage)
                        .setEngineKind(llvm::EngineKind::Kind::JIT)
                        .setOptLevel(llvm::CodeGenOpt::Less)
                        .create();

  //! TODO: add support for linking libraries
  // const auto allArchivesFiles = Utils::getAllFilesInDirectoryWithExtension(
  //     (FLOWWING_LIB_PATH), ".a", false);

  // for (const auto &archivePath : allArchivesFiles) {
  //   FlowWing::Compiler::loadArchiveIntoExecutionEngine(
  //       executionEngine, archivePath, _currentDiagnosticHandler.get());
  // }
  if (!executionEngine) {
    _currentDiagnosticHandler->printDiagnostic(
        std::cout,
        Diagnostic("Failed to create Execution Engine: " + errorMessage,
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Linker,
                   DiagnosticUtils::SourceLocation(0, 0, 0, "")));
    return;
  }

  if (!mainFunction) {
    _currentDiagnosticHandler->printDiagnostic(
        std::cout, Diagnostic("Function not found in module.",
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Linker,
                              DiagnosticUtils::SourceLocation(0, 0, 0, "")));
    return;
  }
  llvm::GenericValue resultValue = llvm::GenericValue();

  try {

    std::vector<llvm::GenericValue> args;

    // 2. Add argc (argument count). We'll simulate 1 argument.
    llvm::GenericValue argc_val;
    argc_val.IntVal = llvm::APInt(32, 1); // 32-bit integer with value 1
    args.push_back(argc_val);

    // 3. Add argv (argument vector). We'll pass a null pointer for simplicity.
    llvm::GenericValue argv_val;
    argv_val.PointerVal = nullptr;
    args.push_back(argv_val);

    resultValue = executionEngine->runFunction(mainFunction, args);

  } catch (const std::exception &e) {
    std::cerr << e.what();
    _currentDiagnosticHandler->printDiagnostic(
        std::cout, Diagnostic("Error executing function.",
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Linker,
                              DiagnosticUtils::SourceLocation(
                                  0, 0, 0, FLOWWING_GLOBAL_ENTRY_POINT)));
  }
  // return hasError;
}

#if defined(JIT_MODE) || defined(JIT_TEST_MODE)

void signalHandler(int signal) {
  // Output information about the signal:

  std::cerr << RED_TEXT << "Signal " << signal << " (" << strsignal(signal)
            << ") received." << RESET << std::endl;

  exit(1); // Exit with a non-zero status to indicate an error.
}

#endif

#ifdef JIT_TEST_MODE

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  signal(SIGSEGV, signalHandler);
  enableVirtualTerminalProcessing();
  return RUN_ALL_TESTS();
}

#elif JIT_MODE

int main([[maybe_unused]] int argc, char *argv[]) {
  signal(SIGSEGV, signalHandler);
  enableVirtualTerminalProcessing();
  argh::parser _cmdl(argv);

  FlowWing::Cli::cmdl = &(_cmdl);

  auto basicArgStatus = FlowWing::Cli::handleBasicArgs();

  if (basicArgStatus == FlowWing::Cli::STATUS::DONE) {
    return EXIT_SUCCESS;
  }

  if (basicArgStatus == FlowWing::Cli::STATUS::FAILURE) {
    return EXIT_FAILURE;
  }

  std::vector<std::string> text = {};

  std::string filePath = "";

  auto status = FlowWing::Cli::handleFileArgs(text, filePath, argv);

  if (status == FlowWing::Cli::STATUS::DONE) {
    return EXIT_SUCCESS;
  }

  if (status == FlowWing::Cli::STATUS::FAILURE) {
    return EXIT_FAILURE;
  }

  std::unique_ptr<JITCompiler> jitCompiler =
      std::make_unique<JITCompiler>(filePath);

  jitCompiler->_executable_path = std::filesystem::path(argv[0]);
  jitCompiler->compile(text, std::cout);

  return EXIT_SUCCESS;
}

#endif
