#include "AOTCompiler.h"

AOTCompiler::AOTCompiler(std::string filePath) : Compiler(filePath) {}

void AOTCompiler::execute() {

  std::unique_ptr<DiagnosticHandler> currentDiagnosticHandler =
      std::make_unique<DiagnosticHandler>();

  std::unique_ptr<llvm::LLVMContext> TheContext =
      std::make_unique<llvm::LLVMContext>();
  std::unique_ptr<llvm::IRBuilder<>> Builder =
      std::make_unique<llvm::IRBuilder<>>(*TheContext);
  std::unique_ptr<llvm::Module> TheModule =
      std::make_unique<llvm::Module>("Module.FLOWWING", *TheContext);
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();
  std::vector<std::string> irFilePaths;

#if defined(DEBUG) || defined(AOT_TEST_MODE)
  irFilePaths = {"lib/FlowWing/built_in_module.ll"};
#else
  std::string builtInModulePath =
      this->executable_directory_string + "/../lib/FlowWing/";
  std::cout << builtInModulePath;
  irFilePaths = {builtInModulePath + "built_in_module.ll"};
#endif

  std::vector<std::string> _userDefinedIRFilePaths =
      Utils::getAllFilesInDirectoryWithExtension(".", ".ll", false);

  irFilePaths.insert(irFilePaths.end(), _userDefinedIRFilePaths.begin(),
                     _userDefinedIRFilePaths.end());

  if (irFilePaths.size() == 0) {
    Utils::printErrors({"No IR files found in current directory."}, std::cout);
    return;
  }

  for (const std::string &path : irFilePaths) {
    llvm::SMDiagnostic err;

#if defined(DEBUG) || defined(AOT_MODE)

    currentDiagnosticHandler->printDiagnostic(
        std::cout,
        Diagnostic("Linking " + path, DiagnosticUtils::DiagnosticLevel::Info,
                   DiagnosticUtils::DiagnosticType::Linker,
                   DiagnosticUtils::SourceLocation(0, 0, path)));

#endif

    bool LinkResult = llvm::Linker::linkModules(
        *TheModule.get(), llvm::parseIRFile(path, err, *TheContext.get()),
        llvm::Linker::Flags::OverrideFromSrc);
    if (LinkResult) {
      currentDiagnosticHandler->printDiagnostic(
          std::cout, Diagnostic("Error linking " + path,
                                DiagnosticUtils::DiagnosticLevel::Error,
                                DiagnosticUtils::DiagnosticType::Linker,
                                DiagnosticUtils::SourceLocation(0, 0, path)));
      return;
    }
  }

  /*
    Create the main function
    START
  */

  llvm::Function *mainFunction =
      TheModule->getFunction(FLOWWING_GLOBAL_ENTRY_POINT);

  /*
    Create the main function
    END
  */

#if defined(DEBUG) || defined(AOT_MODE)

  currentDiagnosticHandler->printDiagnostic(
      std::cout, Diagnostic("Finished linking modules.",
                            DiagnosticUtils::DiagnosticLevel::Info,
                            DiagnosticUtils::DiagnosticType::Linker,
                            DiagnosticUtils::SourceLocation(
                                0, 0, "FLOWWING_GLOBAL_ENTRY_POINT")));

  TheModule->print(llvm::outs(), nullptr);

  // llFileSaveStrategy->saveToFile("my_module.ll", TheModule.get());

#endif

  std::string errorMessage;
  llvm::ExecutionEngine *executionEngine =
      llvm::EngineBuilder(std::move(TheModule))
          .setErrorStr(&errorMessage)
          .setEngineKind(llvm::EngineKind::JIT)
          .setOptLevel(llvm::CodeGenOpt::Less)
          .create();

  if (!executionEngine) {
    Utils::printErrors({"Failed to create Execution Engine: ", errorMessage},
                       std::cerr);
    return;
  }

  if (!mainFunction) {
    Utils::printErrors({"Function not found in module."}, std::cerr);
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
    currentDiagnosticHandler->printDiagnostic(
        std::cout, Diagnostic("Error executing function.",
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Runtime,
                              DiagnosticUtils::SourceLocation(
                                  0, 0, FLOWWING_GLOBAL_ENTRY_POINT)));
  }
  delete executionEngine;
  // return hasError;
}

void signalHandler(int signal) {
  // Output information about the signal:

  std::cerr << RED_TEXT << "Signal " << signal << " (" << strsignal(signal)
            << ") received." << RESET << std::endl;

  exit(1); // Exit with a non-zero status to indicate an error.
}

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

  std::unique_ptr<AOTCompiler> jitCompiler =
      std::make_unique<AOTCompiler>(argv[1]);
  jitCompiler->executable_directory_string = executable_directory_string;

  jitCompiler->compile(text, std::cout);

  return 0;
}

#endif
