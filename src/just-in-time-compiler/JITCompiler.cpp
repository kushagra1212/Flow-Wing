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
  Utils::prettyPrint(compilationUnit.get());

  try {
    std::unique_ptr<IRGenerator> _evaluator = std::make_unique<IRGenerator>(
        ENVIRONMENT::SOURCE_FILE, currentDiagnosticHandler.get(),
        globalScope.get()->functions, 0);

    _evaluator->generateEvaluateGlobalStatement(
        globalScope->globalStatement.get());
    _evaluator->getIRParserPtr()->printIR();
    this->execute(_evaluator->getIRParserPtr()->getIR());

    // _evaluator->executeGeneratedCode();
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
        globalScope.get()->functions, 0);
    _evaluator->generateEvaluateGlobalStatement(
        globalScope->globalStatement.get());

    _evaluator->executeGeneratedCode();

  } catch (const std::exception &e) {
    outputStream << RED << e.what() << RESET << "\n";
  }
}

void JITCompiler::execute(std::string irCode) {
  std::unique_ptr<llvm::LLVMContext> TheContext =
      std::make_unique<llvm::LLVMContext>();
  std::unique_ptr<llvm::IRBuilder<>> Builder =
      std::make_unique<llvm::IRBuilder<>>(*TheContext);
  std::unique_ptr<llvm::Module> TheModule =
      std::make_unique<llvm::Module>("Elang2", *TheContext);

  // create a file in currenct director temp.ll

  std::error_code EC;
  llvm::raw_fd_ostream OS("temp.ll", EC);
  OS << irCode;
  OS.close();

  llvm::SMDiagnostic err;
  bool LinkResult = llvm::Linker::linkModules(
      *TheModule, llvm::parseIRFile("temp.ll", err, *TheContext));
  if (LinkResult) {
    llvm::errs() << "Error linking " + ":" << err.getMessage() << "\n";
  }

  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();

  llvm::Function *evaluateBlockStatement =
      TheModule->getFunction("evaluateBlockStatement");

  std::string errorMessage;
  llvm::ExecutionEngine *executionEngine =
      llvm::EngineBuilder(std::move(TheModule))
          .setErrorStr(&errorMessage)
          .setEngineKind(llvm::EngineKind::JIT)
          .create();
  if (!executionEngine) {
    llvm::errs() << "Failed to create Execution Engine: " << errorMessage
                 << "\n";
  }

  // Step 2: Look up the function pointer
  if (!evaluateBlockStatement) {
    llvm::errs() << "Function not found in module.\n";
  }
  int hasError = 1;
  llvm::Type *returnType = evaluateBlockStatement->getReturnType();
  llvm::GenericValue resultValue = llvm::GenericValue();
  llvm::ArrayRef<llvm::GenericValue> ArgValues;
  try {
    resultValue =
        executionEngine->runFunction(evaluateBlockStatement, ArgValues);

    if (returnType->isIntegerTy()) {
      hasError = (resultValue.IntVal != 0) ? 1 : 0;
    }

  } catch (const std::exception &e) {
    std::cerr << e.what();
  }
  delete executionEngine;
  // return hasError;
}

#ifdef JIT_TEST_MODE

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#endif

#ifdef JIT_MODE

int main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
    return 0;
  }

  // Opens the file using the provided file path

  std::ifstream file;

  file.open(argv[1]);

  if (!file.is_open()) {

    std::cerr << "Unable to open file: " << argv[1] << std::endl;
    if (access(argv[1], R_OK) != 0) {
      std::cerr << "Please check if the file exists and you have read "
                   "permissions."
                << std::endl;
      std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
      return 1;
    }
    std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
    return 0;
  }

  std::string line;
  std::vector<std::string> text = std::vector<std::string>();

  Utils::Node::addPath(argv[1]);
  while (std::getline(file, line)) {
    text.push_back(line);
  }
  // Close the file (imp)
  file.close();

  std::unique_ptr<JITCompiler> jitCompiler =
      std::make_unique<JITCompiler>(argv[1]);

  jitCompiler->compile(text, std::cout);

  return 0;
}

#endif
