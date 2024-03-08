#include "AOTCompiler.h"
#include "../../all-targets/aot-compiler/aot-compiler-build/version.h"
#include "../cli/argh.h"

AOTCompiler::AOTCompiler(std::string filePath) : Compiler(filePath) {}

void AOTCompiler::execute() {
  std::unique_ptr<llvm::LLVMContext> TheContext =
      std::make_unique<llvm::LLVMContext>();
  std::unique_ptr<llvm::IRBuilder<>> Builder =
      std::make_unique<llvm::IRBuilder<>>(*TheContext);

  std::unique_ptr<llvm::Module> linkedModule =
      std::move(getLinkedModule(TheContext));

  std::unique_ptr<LLVMLogger> _llvmLogger =
      std::make_unique<LLVMLogger>(_currentDiagnosticHandler.get());

  std::unique_ptr<LLFileSaveStrategy> llFileSaveStrategy =
      std::make_unique<LLFileSaveStrategy>(_llvmLogger.get());

  const std::string fileNameWithOutExtension = Utils::removeExtensionFromString(
      Utils::getFileName(_currentDiagnosticHandler->getAbsoluteFilePath()));

  llFileSaveStrategy->saveToFile(fileNameWithOutExtension + ".ll",
                                 linkedModule.get());

  std::string CLANG_PATH =
      "/usr/local/lib/FlowWing/dependencies/llvm-17/bin/clang-17";

#ifdef DEBUG
  CLANG_PATH = "lib/FlowWing/dependencies/llvm-17/bin/clang-17";
#endif

  // check For Clang

  if (system(("ls " + CLANG_PATH + " --version > /dev/null 2>&1").c_str()) !=
      0) {
    _currentDiagnosticHandler->printDiagnostic(
        std::cout,
        Diagnostic("Clang not found.", DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Linker,
                   DiagnosticUtils::SourceLocation(
                       0, 0, FLOWWING_GLOBAL_ENTRY_POINT)));

    return;
  }

  std::system((CLANG_PATH + " -O3 -o " + fileNameWithOutExtension + " " +
               fileNameWithOutExtension + ".ll")
                  .c_str());
}

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
  if (cmdl[{"-V", "--version"}]) {
    std::cout << "Flowwing Compiler" << std::endl;
    std::cout << "Version: " << VERSION_INFO << std::endl;

    return EXIT_FAILURE;
  }

  if (argc != 2) {
    Utils::printErrors({"Usage: " + std::string(argv[0]) + " <file_path> "},
                       std::cerr, true);
    return EXIT_FAILURE;
  }

  // Opens the file using the provided file path

  std::ifstream file;

  file.open(argv[1]);

  if (!file.is_open()) {
    Utils::printErrors({"Unable to open file: " + std::string(argv[1]),
                        "Usage: " + std::string(argv[0]) + " <file_path> "},
                       std::cerr);

    if (access(argv[1], R_OK) != 0) {
      Utils::printErrors(
          {"Please check if the file exists and you have read permissions."},
          std::cerr);

      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
  }
  // Close the file (imp)
  file.close();

  Utils::Node::addPath(argv[1]);
  std::vector<std::string> text =
      Utils::readLines(Utils::getAbsoluteFilePath(argv[1]));

  std::unique_ptr<AOTCompiler> aotCompiler =
      std::make_unique<AOTCompiler>(argv[1]);

#if DEBUG
  std::filesystem::path executable_path =
      std::filesystem::canonical(std::filesystem::path(argv[0]));

  std::filesystem::path executable_directory = executable_path.parent_path();
  std::string executable_directory_string = executable_directory.string();
  aotCompiler->executable_directory_string = executable_directory_string;
#endif

  aotCompiler->compile(text, std::cout);

  return EXIT_SUCCESS;
}

#endif
