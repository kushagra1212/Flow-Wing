#include "AOTCompiler.h"
#include "../cli/argh.h"
#include "../common/version.h"

AOTCompiler::AOTCompiler(std::string filePath,
                         const bool &isFormattedCodeRequired)
    : Compiler(filePath) {}

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
  executeCmd = " && ./" + FLOWWING::IR::CONSTANTS::TEMP_BIN_DIR +
               fileNameWithOutExtension;
#endif

  std::string RAY_LIB_CMD = "";

#if defined(__APPLE__)

  RAY_LIB_CMD = "-lraylib -framework CoreFoundation -framework "
                "CoreGraphics -framework Cocoa -framework IOKit -framework "
                "CoreVideo ";
#endif

#if (defined(DEBUG) && defined(JIT_MODE)) ||                                   \
    (defined(DEBUG) && defined(AOT_MODE))
  std::vector<std::string> llFiles = Utils::getAllFilesInDirectoryWithExtension(
      std::filesystem::current_path(), ".ll", false);

  for (auto llFile : llFiles) {
    std::string cmd = CLANG_PATH.string() + " " + llFile + " -emit-llvm -c " +
                      " -o " + llFile.substr(0, llFile.length() - 3) + ".bc";
    std::cout << BLUE_TEXT << "Compiling: " << GREEN << llFile << RESET
              << std::endl;
    const int status = std::system(cmd.c_str());

    if (status != 0) {
      std::cerr << Utils::CE("Failed to compile: ") << llFile << std::endl;
      return;
    }
  }

#endif

  try {
    std::string cmd =
        (CLANG_PATH.string() + " -O3 -o " +
         FLOWWING::IR::CONSTANTS::TEMP_BIN_DIR + fileNameWithOutExtension +
         " -e _" + FLOWWING_GLOBAL_ENTRY_POINT + " " +
         getObjectFilesJoinedAsString() + " -L" + LIB_PATH.string() +
         " -lbuilt_in_module  -fPIE " + RAY_LIB_CMD + executeCmd);

#if (defined(DEBUG) && defined(JIT_MODE)) ||                                   \
    (defined(DEBUG) && defined(AOT_MODE))

    std::cout << YELLOW_TEXT << "Linking: " << GREEN
              << getObjectFilesJoinedAsString() << RESET << std::endl;
#endif

    std::system(cmd.c_str());

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
  std::vector<std::string> text =
      Utils::readLines(Utils::getAbsoluteFilePath(_filePath));

  std::unique_ptr<AOTCompiler> aotCompiler =
      std::make_unique<AOTCompiler>(_filePath);

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
