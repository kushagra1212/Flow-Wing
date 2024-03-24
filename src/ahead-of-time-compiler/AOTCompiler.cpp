#include "AOTCompiler.h"
#include "../cli/argh.h"
#include "../common/version.h"

AOTCompiler::AOTCompiler(std::string filePath,
                         const bool &isFormattedCodeRequired)
    : Compiler(filePath, isFormattedCodeRequired) {}

void AOTCompiler::link() {

  std::string fileNameWithOutExtension = Utils::removeExtensionFromString(
      Utils::getFileName(_currentDiagnosticHandler->getAbsoluteFilePath()));

  std::unique_ptr<LLVMLogger> _llvmLogger =
      std::make_unique<LLVMLogger>(_currentDiagnosticHandler.get());

  std::filesystem::path CLANG_PATH = getClangFilePath();
  std::filesystem::path LIB_PATH = getLibPath();

  std::string executeCmd = "";

#if defined(AOT_TEST_MODE)
  fileNameWithOutExtension =
      FLOWWING::IR::CONSTANTS::FLOWWING_GLOBAL_ENTRY_POINT;
  executeCmd = " && ./" + fileNameWithOutExtension;
#endif

  try {
    std::string cmd =
        (CLANG_PATH.string() + " -O3 -o " + fileNameWithOutExtension + " -e _" +
         FLOWWING_GLOBAL_ENTRY_POINT + " " + getObjectFilesJoinedAsString() +
         " -L" + LIB_PATH.string() + " -lbuilt_in_module " + executeCmd);

    std::system(cmd.c_str());

    // delete object files
    deleteObjectFiles();
  } catch (const std::exception &e) {
    std::cerr << "Exception occurred: " << e.what() << std::endl;
    // delete object files
    deleteObjectFiles();
  }

  // check For Clang

  // if (system(("ls " + CLANG_PATH.string() + " --version > /dev/null
  // 2>&1").c_str()) !=
  //     0) {
  //   _currentDiagnosticHandler->printDiagnostic(
  //       std::cout,
  //       Diagnostic("Clang not found " +  CLANG_PATH.string(),
  //       DiagnosticUtils::DiagnosticLevel::Error,
  //                  DiagnosticUtils::DiagnosticType::Linker,
  //                  DiagnosticUtils::SourceLocation(
  //                      0, 0, FLOWWING_GLOBAL_ENTRY_POINT)));

  //   return;
  // }
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
  if (cmdl[{"--version", "-V"}]) {
    std::cout << "Flowwing Compiler" << std::endl;
    std::cout << "Version: " << VERSION_INFO << std::endl;

    return EXIT_FAILURE;
  }

  bool isFormattedCodeRequired = false;
  if (cmdl[{"--format", "-FM"}]) {
    isFormattedCodeRequired = true;
  }

  if (!cmdl("file") && !cmdl("F")) {
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
  std::vector<std::string> text =
      Utils::readLines(Utils::getAbsoluteFilePath(_filePath));

  std::unique_ptr<AOTCompiler> aotCompiler =
      std::make_unique<AOTCompiler>(_filePath, isFormattedCodeRequired);

  // #if DEBUG
  //   std::filesystem::path executable_path =
  //       std::filesystem::canonical(std::filesystem::path(argv[0]));

  //   std::filesystem::path executable_directory =
  //   executable_path.parent_path(); std::string executable_directory_string =
  //   executable_directory.string(); aotCompiler->executable_directory_string =
  //   executable_directory_string;
  // #endif

  aotCompiler->_executable_path = std::filesystem::path(argv[0]);
  aotCompiler->compile(text, std::cout);

  return EXIT_SUCCESS;
}

#endif
