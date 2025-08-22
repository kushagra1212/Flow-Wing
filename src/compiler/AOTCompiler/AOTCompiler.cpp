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

#include "AOTCompiler.h"
#include "src/common/commandLineOptions/commandLineOptions.h"
#include "src/common/version.h"
#include "src/external/include/argh.h"
#include <signal.h>

#ifdef TESTS_ENABLED
#include <gtest/gtest.h>
#endif

AOTCompiler::AOTCompiler(std::string filePath,
                         [[maybe_unused]] const bool &isFormattedCodeRequired)
    : Compiler(filePath) {}

void AOTCompiler::link() {

  std::string fileNameWithOutExtension =
      FlowWing::AOT::getFileNameWithoutExtension(
          _currentDiagnosticHandler.get());

  std::unique_ptr<LLVMLogger> _llvmLogger =
      std::make_unique<LLVMLogger>(_currentDiagnosticHandler.get());

  FlowWing::AOT::RUN_ON_DEBUG_GENERATE_BC_FROM_LL();

  std::unique_ptr<CommandManager> _commandManager =
      std::make_unique<CommandManager>(fileNameWithOutExtension);

  try {

    std::string cmd = _commandManager->create();

    LINKING_DEBUG_LOG("", cmd);

    int status = std::system(cmd.c_str());

    if (status != 0) {
      FlowWing::AOT::LINKING_FAIL_ERROR(status, fileNameWithOutExtension,
                                        VERSION_INFO);

      FlowWing::AOT::deleteObjectFiles();
      return;
    }

    FlowWing::AOT::deleteObjectFiles();

  } catch (const std::exception &e) {
    std::cerr << "Exception occurred: " << e.what() << std::endl;

    FlowWing::AOT::deleteObjectFiles();
  }
}

void AOTCompiler::execute() { link(); }

#if defined(AOT_MODE) || defined(AOT_TEST_MODE)

void signalHandler(int signal) {
  std::cerr << RED_TEXT << "Signal " << signal << " (";

// Provide a platform-specific way to get the signal's name.
#if defined(_WIN32)
  // On Windows, there is no direct equivalent to strsignal.
  // We can provide descriptions for the most common signals.
  switch (signal) {
  case SIGSEGV:
    std::cerr << "Segmentation fault";
    break;
  case SIGILL:
    std::cerr << "Illegal instruction";
    break;
  case SIGFPE:
    std::cerr << "Floating-point exception";
    break;
  default:
    std::cerr << "Unknown signal";
    break;
  }
#else
  // On POSIX systems, strsignal is available.
  std::cerr << strsignal(signal);
#endif

  std::cerr << ") received." << RESET << std::endl;
  exit(1);
}

#endif

#ifdef AOT_TEST_MODE

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  signal(SIGSEGV, signalHandler);
  return RUN_ALL_TESTS();
}

#elif AOT_MODE
int main([[maybe_unused]] int argc, char *argv[]) {
  signal(SIGSEGV, signalHandler);
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

  std::unique_ptr<AOTCompiler> aotCompiler =
      std::make_unique<AOTCompiler>(filePath);

  aotCompiler->_executable_path = std::filesystem::path(argv[0]);
  aotCompiler->compile(text, std::cout);

  return EXIT_SUCCESS;
}

#endif
