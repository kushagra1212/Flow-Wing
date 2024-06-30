#include "JITCompiler.h"
#include "../cli/argh.h"
#include "../common/version.h"

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

  exit(1); // Exit with a non-zero status to indicate an error.
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
  //? Opens the file using the provided file path

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
  //! Close the file
  file.close();

  Utils::Node::addPath(Utils::getAbsoluteFilePath(_filePath));
  std::vector<std::string> text =
      Utils::readLines(Utils::getAbsoluteFilePath(_filePath));

  std::unique_ptr<JITCompiler> jitCompiler =
      std::make_unique<JITCompiler>(_filePath);

  if (cmdl[{FlowWingCliOptions::OPTIONS::Format.name.c_str(),
            FlowWingCliOptions::OPTIONS::ShortFormat.name.c_str()}]) {

    jitCompiler->Format.setValue(true);
    jitCompiler->ShortFormat.setValue(true);
  }

  if (cmdl[{FlowWingCliOptions::OPTIONS::FormatPrint.name.c_str(),
            FlowWingCliOptions::OPTIONS::ShortFormatPrint.name.c_str()}]) {

    jitCompiler->FormatPrint.setValue(true);
    jitCompiler->ShortFormatPrint.setValue(true);
  }

  std::string OUTPUT_FILE_PATH =
      !cmdl(FlowWingCliOptions::OPTIONS::OutputFile.name.c_str()).str().empty()
          ? cmdl(FlowWingCliOptions::OPTIONS::OutputFile.name.c_str()).str()
          : cmdl(FlowWingCliOptions::OPTIONS::ShortOutputFile.name.c_str())
                .str();

  if (!OUTPUT_FILE_PATH.empty()) {
    jitCompiler->setOutputFilePath(OUTPUT_FILE_PATH);
  }

  jitCompiler->_executable_path = std::filesystem::path(argv[0]);
  jitCompiler->compile(text, std::cout);

  return EXIT_SUCCESS;
}

#endif
