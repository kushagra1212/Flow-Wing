#include "Compiler.h"

Compiler::Compiler(std::string filePath, const bool &isFormattedCodeReq)
    : _filePath(filePath),
      llFileSaveStrategy(std::make_unique<LLFileSaveStrategy>(nullptr)),
      _currentDiagnosticHandler(
          std::make_unique<FLowWing::DiagnosticHandler>(filePath)),
      executionEngine(nullptr), isFormattedCodeRequired(isFormattedCodeReq) {}

const std::string Compiler::getBuiltInModulePath() const {
  std::string filePath = "";
#if defined(DEBUG) || defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  filePath = "../../../src/IR/BuiltinIRs/built_in_module.ll";
#elif defined(RELEASE) && defined(__LINUX__)
  filePath = "/usr/local/lib/FlowWing/built_in_module.bc";
#elif defined(RELEASE) && defined(__APPLE__)
  filePath = _executable_path.parent_path().string() + "/../Library" +
             "/built_in_module.ll";
#endif
  // std::cout << "Executable directory: " << filePath << std::endl;
  return filePath;
}

std::unique_ptr<llvm::MemoryBuffer>
Compiler::getMemoryBuffer(std::string filePath) {
  if (auto bufferOrErr = llvm::MemoryBuffer::getFile(filePath)) {
    return std::move(*bufferOrErr);
  } else {
    _currentDiagnosticHandler->printDiagnostic(
        std::cout, Diagnostic("Error reading bitcode file: " + filePath + " " +
                                  bufferOrErr.getError().message(),
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Linker,
                              DiagnosticUtils::SourceLocation(0, 0, "")));
    exit(1);
    return nullptr;
  }
}

std::unique_ptr<llvm::Module>
Compiler::createModuleFromIR(const std::string &filePath,
                             std::unique_ptr<llvm::LLVMContext> &TheContext) {
  llvm::SMDiagnostic Err;
  std::unique_ptr<llvm::Module> module =
      llvm::parseIRFile(filePath, Err, *TheContext);

  if (!module) {
    _currentDiagnosticHandler->printDiagnostic(
        std::cout, Diagnostic("Error reading IR file: " + filePath,
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Linker,
                              DiagnosticUtils::SourceLocation(0, 0, "")));
    return nullptr;
  }

  return std::move(module);
}

std::unique_ptr<llvm::Module> Compiler::createModuleFromBitcode(
    const std::string &filePath,
    std::unique_ptr<llvm::LLVMContext> &TheContext) {
  std::unique_ptr<llvm::MemoryBuffer> buffer =

      std::move(getMemoryBuffer(filePath));

  if (auto moduleOrErr =
          llvm::parseBitcodeFile(buffer->getMemBufferRef(), *TheContext)) {
    return std::move(*moduleOrErr);
  } else {
    _currentDiagnosticHandler->printDiagnostic(
        std::cout, Diagnostic("Error reading bitcode file: " + filePath,
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Linker,
                              DiagnosticUtils::SourceLocation(0, 0, "")));
    return nullptr;
  }
}

std::vector<std::string> Compiler::getIRFilePaths() const {
  std::vector<std::string> _userDefinedIRFilePaths = {};

#ifdef DEBUG
  _userDefinedIRFilePaths =
      Utils::getAllFilesInDirectoryWithExtension(".", ".ll", false);
#else
  _userDefinedIRFilePaths =
      Utils::getAllFilesInDirectoryWithExtension(".", ".ll", false);
#endif

  if (_userDefinedIRFilePaths.size() == 0) {
    _currentDiagnosticHandler->printDiagnostic(
        std::cout, Diagnostic("No user defined IR files found.",
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Linker,
                              DiagnosticUtils::SourceLocation(0, 0, "")));
    return {};
  }

  return _userDefinedIRFilePaths;
}

std::unique_ptr<llvm::Module>
Compiler::getLinkedModule(std::unique_ptr<llvm::LLVMContext> &TheContext) {
  std::vector<std::string> _userDefinedIRFilePaths = getIRFilePaths();

  const std::string &filePath = getBuiltInModulePath();

#if defined(RELEASE)
  std::unique_ptr<llvm::Module> TheModule =
      std::make_unique<llvm::Module>("built_in_module", *TheContext);
#else
  std::unique_ptr<llvm::Module> TheModule =
      filePath[filePath.length() - 1] == 'l'
          ? std::move(createModuleFromIR(filePath, TheContext))
          : std::move(createModuleFromBitcode(filePath, TheContext));
#endif
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();

  // TODO: Change the triple to x86_64-unknown-linux-gnu
  // TheModule->setTargetTriple(llvm::Triple::normalize("x86_64-pc-linux-gnu"));

#if defined(__APPLE__)
  TheModule->setTargetTriple("x86_64-apple-macosx14.0.0");
#elif defined(__LINUX__)
  TheModule->setTargetTriple(
      llvm::Triple::normalize("x86_64-unknown-linux-gnu"));
#endif

  for (const std::string &path : _userDefinedIRFilePaths) {
    llvm::SMDiagnostic err;

#if (defined(DEBUG) && defined(JIT_MODE)) ||                                   \
    (defined(DEBUG) && defined(AOT_MODE))

    _currentDiagnosticHandler->printDiagnostic(
        std::cout,
        Diagnostic("Linking " + path, DiagnosticUtils::DiagnosticLevel::Info,
                   DiagnosticUtils::DiagnosticType::Linker,
                   DiagnosticUtils::SourceLocation(0, 0, path)));

#endif

    bool LinkResult = llvm::Linker::linkModules(
        *TheModule.get(), llvm::parseIRFile(path, err, *TheContext.get()),
        llvm::Linker::Flags::OverrideFromSrc);
    if (LinkResult) {
      _currentDiagnosticHandler->printDiagnostic(
          std::cout, Diagnostic("Error linking " + path,
                                DiagnosticUtils::DiagnosticLevel::Error,
                                DiagnosticUtils::DiagnosticType::Linker,
                                DiagnosticUtils::SourceLocation(0, 0, path)));
      return nullptr;
    }
  }

#if (defined(DEBUG) && defined(JIT_MODE)) ||                                   \
    (defined(DEBUG) && defined(AOT_MODE))

  _currentDiagnosticHandler->printDiagnostic(
      std::cout, Diagnostic("Finished linking modules.",
                            DiagnosticUtils::DiagnosticLevel::Info,
                            DiagnosticUtils::DiagnosticType::Linker,
                            DiagnosticUtils::SourceLocation(
                                0, 0, "FLOWWING_GLOBAL_ENTRY_POINT")));

  TheModule->print(llvm::outs(), nullptr);

  // llFileSaveStrategy->saveToFile("../my_module.ll", TheModule.get());

#endif

  return std::move(TheModule);
}

void Compiler::compile(std::vector<std::string> &text,
                       std::ostream &outputStream) {
  std::unique_ptr<FLowWing::DiagnosticHandler> currentDiagnosticHandler =
      std::make_unique<FLowWing::DiagnosticHandler>(this->_filePath);

  std::unique_ptr<Parser> parser =
      std::make_unique<Parser>(text, currentDiagnosticHandler.get());

  parser->setIsFormattedCodeRequired(isFormattedCodeRequired);

  if (currentDiagnosticHandler->hasError(
          DiagnosticUtils::DiagnosticType::Lexical)) {
    currentDiagnosticHandler->logDiagnostics(
        outputStream, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Lexical;
        });
    currentDiagnosticHandler.reset(
        new FLowWing::DiagnosticHandler(this->_filePath));
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
    currentDiagnosticHandler.reset(
        new FLowWing::DiagnosticHandler(this->_filePath));

    return;
  }

#ifdef DEBUG

  std::cout << BLUE << ".............." << YELLOW << "Tree Start" << BLUE
            << ".............." << RESET << std::endl;
  Utils::prettyPrint(compilationUnit.get());
  std::cout << BLUE << ".............." << YELLOW << " Tree End " << BLUE
            << " .............." << RESET << std::endl;

#endif

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

    currentDiagnosticHandler.reset(
        new FLowWing::DiagnosticHandler(this->_filePath));

    return;
  }

#ifdef DEBUG

  std::cout << BLUE << ".............." << YELLOW << "Tree Start" << BLUE
            << ".............." << RESET << std::endl;
  Utils::prettyPrint(globalScope->globalStatement.get());
  std::cout << BLUE << ".............." << YELLOW << " Tree End " << BLUE
            << " .............." << RESET << std::endl;

#endif

  if (isFormattedCodeRequired) {

    std::cout << parser->getFormattedSourceCode() << std::endl;
    return;
  }

  try {

    std::unique_ptr<IRGenerator> _evaluator = std::make_unique<IRGenerator>(
        ENVIRONMENT::SOURCE_FILE, currentDiagnosticHandler.get(),
        globalScope.get()->functions);

    _evaluator->generateEvaluateGlobalStatement(
        globalScope->globalStatement.get());

#ifdef DEBUG
    _evaluator->printIR();
#endif

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

void Compiler::runTests(std::istream &inputStream, std::ostream &outputStream) {
  std::unique_ptr<FLowWing::DiagnosticHandler> currentDiagnosticHandler =
      std::make_unique<FLowWing::DiagnosticHandler>();

  std::unique_ptr<Parser> parser =
      std::make_unique<Parser>(text, currentDiagnosticHandler.get());

  if (currentDiagnosticHandler->hasError(
          DiagnosticUtils::DiagnosticType::Lexical)) {
    currentDiagnosticHandler->logDiagnostics(
        outputStream, [](const Diagnostic &d) {
          return d.getType() == DiagnosticUtils::DiagnosticType::Lexical;
        });
    currentDiagnosticHandler.reset(
        new FLowWing::DiagnosticHandler(this->_filePath));
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
    currentDiagnosticHandler.reset(
        new FLowWing::DiagnosticHandler(this->_filePath));

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

    currentDiagnosticHandler.reset(
        new FLowWing::DiagnosticHandler(this->_filePath));

    return;
  }

  try {
    std::unique_ptr<IRGenerator> _evaluator = std::make_unique<IRGenerator>(
        ENVIRONMENT::SOURCE_FILE, currentDiagnosticHandler.get(),
        globalScope.get()->functions);
    _evaluator->generateEvaluateGlobalStatement(
        globalScope->globalStatement.get());

    if (!_evaluator->hasErrors()) {
      this->execute();
    }
  } catch (const std::exception &e) {
    outputStream << RED << e.what() << RESET << "\n";
  }
}
