#include "JITCompiler.h"

JITCompiler::JITCompiler(std::string filePath) { this->_filePath = filePath; }

JITCompiler::~JITCompiler() {}

void JITCompiler::compile(std::vector<std::string> &text,
                          std::ostream &outputStream) {

  std::unique_ptr<DiagnosticHandler> currentDiagnosticHandler =
      std::make_unique<DiagnosticHandler>(this->_filePath);

  std::unique_ptr<Parser> parser =
      std::make_unique<Parser>(text, currentDiagnosticHandler.get());

  if (currentDiagnosticHandler->hasError(
          DiagnosticUtils::DiagnosticType::Lexical)) {
    currentDiagnosticHandler->logDiagnostics(
        outputStream, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Lexical;
        });
    currentDiagnosticHandler.reset(new DiagnosticHandler(this->_filePath));
    return;
  }

  std::unique_ptr<CompilationUnitSyntax> compilationUnit =
      std::move(parser->parseCompilationUnit());

  if (currentDiagnosticHandler->hasError(
          DiagnosticUtils::DiagnosticType::Syntactic)) {
    currentDiagnosticHandler->logDiagnostics(
        outputStream, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Syntactic;
        });
    currentDiagnosticHandler.reset(new DiagnosticHandler(this->_filePath));

    return;
  }

  std::unique_ptr<BoundScopeGlobal> globalScope =
      std::move(Binder::bindGlobalScope(nullptr, compilationUnit.get(),
                                        currentDiagnosticHandler.get()));
  const bool &hasSemanticError = currentDiagnosticHandler->hasError(
      DiagnosticUtils::DiagnosticType::Semantic);

  if (hasSemanticError) {
    currentDiagnosticHandler->logDiagnostics(
        outputStream, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Semantic;
        });

    currentDiagnosticHandler.reset(new DiagnosticHandler(this->_filePath));

    return;
  }
  Utils::prettyPrint(globalScope->globalStatement.get());
  try {
    std::unique_ptr<IRGenerator> _evaluator = std::make_unique<IRGenerator>(
        ENVIRONMENT::SOURCE_FILE, currentDiagnosticHandler.get(),
        globalScope.get()->functions);

    _evaluator->generateEvaluateGlobalStatement(
        globalScope->globalStatement.get());
    // _evaluator->printIR();
    // _evaluator->executeGeneratedCode();

    //_evaluator->getIRParserPtr()->printIR();

    // _evaluator.reset(nullptr);

    if (!_evaluator->hasErrors()) {
      this->execute();
    }
    outputStream << std::endl;
  } catch (const std::exception &e) {
    outputStream << RED << e.what() << RESET << "\n";
  }
}

void JITCompiler::runTests(std::istream &inputStream,
                           std::ostream &outputStream) {

  std::unique_ptr<DiagnosticHandler> currentDiagnosticHandler =
      std::make_unique<DiagnosticHandler>();

  std::unique_ptr<Parser> parser =
      std::make_unique<Parser>(text, currentDiagnosticHandler.get());

  if (currentDiagnosticHandler->hasError(
          DiagnosticUtils::DiagnosticType::Lexical)) {
    currentDiagnosticHandler->logDiagnostics(
        outputStream, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Lexical;
        });
    currentDiagnosticHandler.reset(new DiagnosticHandler(this->_filePath));
    return;
  }

  std::unique_ptr<CompilationUnitSyntax> compilationUnit =
      std::move(parser->parseCompilationUnit());

  if (currentDiagnosticHandler->hasError(
          DiagnosticUtils::DiagnosticType::Syntactic)) {
    currentDiagnosticHandler->logDiagnostics(
        outputStream, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Syntactic;
        });
    currentDiagnosticHandler.reset(new DiagnosticHandler(this->_filePath));

    return;
  }

  std::unique_ptr<BoundScopeGlobal> globalScope =
      std::move(Binder::bindGlobalScope(nullptr, compilationUnit.get(),
                                        currentDiagnosticHandler.get()));

  const bool &hasSemanticError = currentDiagnosticHandler->hasError(
      DiagnosticUtils::DiagnosticType::Semantic);

  if (hasSemanticError) {
    currentDiagnosticHandler->logDiagnostics(
        outputStream, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Semantic;
        });

    currentDiagnosticHandler.reset(new DiagnosticHandler(this->_filePath));

    return;
  }

  try {
    std::unique_ptr<IRGenerator> _evaluator = std::make_unique<IRGenerator>(
        ENVIRONMENT::SOURCE_FILE, currentDiagnosticHandler.get(),
        globalScope.get()->functions);
    _evaluator->generateEvaluateGlobalStatement(
        globalScope->globalStatement.get());
    this->execute();

  } catch (const std::exception &e) {
    outputStream << RED << e.what() << RESET << "\n";
  }
}

void JITCompiler::execute() {

  // create a file in currenct director temp.ll

  std::unique_ptr<DiagnosticHandler> currentDiagnosticHandler =
      std::make_unique<DiagnosticHandler>();

  std::unique_ptr<llvm::LLVMContext> TheContext =
      std::make_unique<llvm::LLVMContext>();
  std::unique_ptr<llvm::IRBuilder<>> Builder =
      std::make_unique<llvm::IRBuilder<>>(*TheContext);
  std::unique_ptr<llvm::Module> TheModule =
      std::make_unique<llvm::Module>("Module.Elang", *TheContext);
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();
  std::vector<std::string> irFilePaths = {
      "../../../src/evaluator/BuiltinIRs/built_in_module.ll"};

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
#ifdef JIT_MODE

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
#ifdef JIT_MODE
  currentDiagnosticHandler->printDiagnostic(
      std::cout, Diagnostic("Finished linking modules.",
                            DiagnosticUtils::DiagnosticLevel::Info,
                            DiagnosticUtils::DiagnosticType::Linker,
                            DiagnosticUtils::SourceLocation(0, 0, "main")));

  TheModule->print(llvm::outs(), nullptr);
#endif
  llvm::Function *mainFunction =
      TheModule->getFunction(ELANG_GLOBAL_ENTRY_POINT);

  std::string errorMessage;
  llvm::ExecutionEngine *executionEngine =
      llvm::EngineBuilder(std::move(TheModule))
          .setErrorStr(&errorMessage)
          .setEngineKind(llvm::EngineKind::JIT)
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
                              DiagnosticUtils::SourceLocation(0, 0, "main")));
  }
  delete executionEngine;
  // return hasError;
}
void signalHandler(int signal) {
  // Output information about the signal:

  std::cerr << RED_TEXT << "Signal " << signal << " (" << strsignal(signal)
            << ") received." << std::endl;

  exit(1); // Exit with a non-zero status to indicate an error.
}
#ifdef JIT_TEST_MODE

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
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

  jitCompiler->compile(text, std::cout);

  return 0;
}

#endif
