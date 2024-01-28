#include "JITCompiler.h"

JITCompiler::JITCompiler(std::string filePath) : Compiler(filePath) {}

void JITCompiler::execute() {
  std::unique_ptr<llvm::LLVMContext> TheContext =
      std::make_unique<llvm::LLVMContext>();
  std::unique_ptr<llvm::IRBuilder<>> Builder =
      std::make_unique<llvm::IRBuilder<>>(*TheContext);

  std::unique_ptr<llvm::Module> TheModule =
      std::move(getLinkedModule(TheContext));

  //  Get the main function

  llvm::Function *mainFunction =
      TheModule->getFunction(FLOWWING_GLOBAL_ENTRY_POINT);

  std::string errorMessage;
  executionEngine = llvm::EngineBuilder(std::move(TheModule))
                        .setErrorStr(&errorMessage)
                        .setEngineKind(llvm::EngineKind::Kind::JIT)
                        .setOptLevel(llvm::CodeGenOpt::Less)
                        .create();

  if (!executionEngine) {
    _currentDiagnosticHandler->printDiagnostic(
        std::cout,
        Diagnostic("Failed to create Execution Engine: " + errorMessage,
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Linker,
                   DiagnosticUtils::SourceLocation(0, 0, "")));
    return;
  }

  if (!mainFunction) {
    _currentDiagnosticHandler->printDiagnostic(
        std::cout, Diagnostic("Function not found in module.",
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Linker,
                              DiagnosticUtils::SourceLocation(0, 0, "")));
    return;
  }
  int hasError = 1;
  llvm::Type *returnType = mainFunction->getReturnType();
  llvm::GenericValue resultValue = llvm::GenericValue();
  llvm::ArrayRef<llvm::GenericValue> ArgValues = {};

  try {
    resultValue = executionEngine->runFunction(mainFunction, ArgValues);

    if (returnType->isIntegerTy()) {
      hasError = (resultValue.IntVal != 0) ? 1 : 0;
    }
  } catch (const std::exception &e) {
    std::cerr << e.what();
    _currentDiagnosticHandler->printDiagnostic(
        std::cout, Diagnostic("Error executing function.",
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Linker,
                              DiagnosticUtils::SourceLocation(
                                  0, 0, FLOWWING_GLOBAL_ENTRY_POINT)));
  }
  // return hasError;
}

#if defined(JIT_MODE) || defined(JIT_TEST_MODE)

void signalHandler(int signal) {
  // Output information about the signal:

  std::cerr << RED_TEXT << "Signal " << signal << " (" << strsignal(signal)
            << ") received." << RESET << std::endl;

  exit(1);  // Exit with a non-zero status to indicate an error.
}

#endif

#ifdef JIT_TEST_MODE

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  signal(SIGSEGV, signalHandler);
  return RUN_ALL_TESTS();
}

#endif

#ifdef JIT_MODE

int main(int argc, char *argv[]) {
  signal(SIGSEGV, signalHandler);
  if (argc != 2) {
    Utils::printErrors({"Usage: " + std::string(argv[0]) + " <file_path> "},
                       std::cerr, true);
    return 0;
  }
  std::filesystem::path executable_path =
      std::filesystem::canonical(std::filesystem::path(argv[0]));

  std::filesystem::path executable_directory = executable_path.parent_path();
  std::string executable_directory_string = executable_directory.string();
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

      return 1;
    }
    return 0;
  }
  // Close the file (imp)
  file.close();

  Utils::Node::addPath(argv[1]);
  std::vector<std::string> text =
      Utils::readLines(Utils::getAbsoluteFilePath(argv[1]));

  std::unique_ptr<JITCompiler> jitCompiler =
      std::make_unique<JITCompiler>(argv[1]);
  jitCompiler->executable_directory_string = executable_directory_string;

  jitCompiler->compile(text, std::cout);

  return 0;
}

#endif
