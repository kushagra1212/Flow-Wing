#include "AOTCompiler.h"
#include "../cli/argh.h"
#include "../common/version.h"

AOTCompiler::AOTCompiler(std::string filePath,
                         const bool &isFormattedCodeRequired)
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

    LINKING_DEBUG_LOG(cmd);

    int status = std::system(cmd.c_str());

    if (status != 0) {
      FlowWing::AOT::LINKING_FAIL_ERROR(status, fileNameWithOutExtension,
                                        VERSION_INFO);
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
  // Output information about the signal:

  std::cerr << RED_TEXT << "Signal " << signal << " (" << strsignal(signal)
            << ") received." << RESET << std::endl;

  exit(1); // Exit with a non-zero status to indicate an error.
}

#endif

#ifdef AOT_TEST_MODE

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  signal(SIGSEGV, signalHandler);
  return RUN_ALL_TESTS();
}

#elif AOT_MODE
int main(int argc, char *argv[]) {
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
