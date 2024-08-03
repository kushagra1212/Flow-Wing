#include "AOTCompiler.h"
#include "../cli/argh.h"
#include "../common/version.h"

AOTCompiler::AOTCompiler(std::string filePath, argh::parser *cmdl,
                         const bool &isFormattedCodeRequired)
    : Compiler(filePath), _cmdl(cmdl) {}

void AOTCompiler::link() {

  std::string fileNameWithOutExtension = this->getFileNameWithoutExtension();
  std::unique_ptr<LLVMLogger> _llvmLogger =
      std::make_unique<LLVMLogger>(_currentDiagnosticHandler.get());

  DEBUG_LOG_LL_FILES_INFO();

  std::unique_ptr<CommandManager> _commandManager =
      std::make_unique<CommandManager>(_cmdl, fileNameWithOutExtension);

  try {

    std::string cmd = _commandManager->create();

    DEBUG_LOG_LINKING_INFO();

    int status = std::system(cmd.c_str());

    if (status != 0) {
      LINKING_FAIL_ERROR(status, fileNameWithOutExtension, VERSION_INFO);
      return;
    }

    // delete object files
    deleteObjectFiles();
  } catch (const std::exception &e) {
    std::cerr << "Exception occurred: " << e.what() << std::endl;
    // delete object files
    deleteObjectFiles();
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

#endif

#ifdef AOT_MODE

int main(int argc, char *argv[]) {
  signal(SIGSEGV, signalHandler);
  argh::parser cmdl(argv);

  if (cmdl[{FlowWingCliOptions::OPTIONS::Version.name.c_str(),
            FlowWingCliOptions::OPTIONS::ShortVersion.name.c_str()}]) {
    std::cout << "Flowwing Compiler" << std::endl;
    std::cout << "Version: " << VERSION_INFO << std::endl;
    return EXIT_SUCCESS;
  }

  if (!cmdl(FlowWingCliOptions::OPTIONS::File.name.c_str()) &&
      !cmdl(FlowWingCliOptions::OPTIONS::ShortFile.name.c_str())) {
    Utils::printErrors({"Usage: " + std::string(argv[0]) + " <file_path> "},
                       std::cerr, true);
    return EXIT_FAILURE;
  }

  std::string _filePath = cmdl("file") ? cmdl("file").str() : cmdl("F").str();
  // Opens the file using the provided file path

  std::ifstream file;

  file.open(_filePath);

  if (!file.is_open()) {
    Utils::printErrors({"Unable to open file: " + std::string(_filePath),
                        "Usage: " + std::string(argv[0]) + " <file_path> "},
                       std::cerr);

    if (access(_filePath.c_str(), R_OK) != 0) {
      Utils::printErrors(
          {"Please check if the file exists and you have read permissions."},
          std::cerr);

      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
  }
  // Close the file (imp)
  file.close();

  Utils::Node::addPath(Utils::getAbsoluteFilePath(_filePath));
  std::vector<std::string> text = {};
  if (!cmdl(FlowWingCliOptions::OPTIONS::Code.name.c_str()).str().empty() ||
      !cmdl(FlowWingCliOptions::OPTIONS::ShortCode.name.c_str())
           .str()
           .empty()) {

    std::string code =
        !cmdl(FlowWingCliOptions::OPTIONS::Code.name.c_str()).str().empty()
            ? cmdl(FlowWingCliOptions::OPTIONS::Code.name.c_str()).str()
            : cmdl(FlowWingCliOptions::OPTIONS::ShortCode.name.c_str()).str();

    text = Utils::readLinesFromText(code);
  } else
    text = Utils::readLines(Utils::getAbsoluteFilePath(_filePath));

  std::unique_ptr<AOTCompiler> aotCompiler =
      std::make_unique<AOTCompiler>(_filePath, &cmdl);

  if (cmdl[{FlowWingCliOptions::OPTIONS::Format.name.c_str(),
            FlowWingCliOptions::OPTIONS::ShortFormat.name.c_str()}]) {

    aotCompiler->Format.setValue(true);
    aotCompiler->ShortFormat.setValue(true);
  }

  if (cmdl[{FlowWingCliOptions::OPTIONS::FormatPrint.name.c_str(),
            FlowWingCliOptions::OPTIONS::ShortFormatPrint.name.c_str()}]) {

    aotCompiler->FormatPrint.setValue(true);
    aotCompiler->ShortFormatPrint.setValue(true);
  }

  std::string OUTPUT_FILE_PATH =
      !cmdl(FlowWingCliOptions::OPTIONS::OutputFile.name.c_str()).str().empty()
          ? cmdl(FlowWingCliOptions::OPTIONS::OutputFile.name.c_str()).str()
          : cmdl(FlowWingCliOptions::OPTIONS::ShortOutputFile.name.c_str())
                .str();

  if (!OUTPUT_FILE_PATH.empty()) {
    aotCompiler->setOutputFilePath(OUTPUT_FILE_PATH);
  }

  aotCompiler->_executable_path = std::filesystem::path(argv[0]);
  aotCompiler->compile(text, std::cout);

  return EXIT_SUCCESS;
}

#endif
