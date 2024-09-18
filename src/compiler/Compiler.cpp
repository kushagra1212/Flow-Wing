#include "Compiler.h"

Compiler::Compiler(std::string filePath)
    : _filePath(filePath),
      llFileSaveStrategy(std::make_unique<LLFileSaveStrategy>(nullptr)),
      _currentDiagnosticHandler(
          std::make_unique<FLowWing::DiagnosticHandler>(filePath)),
      executionEngine(nullptr) {
  // Define command-line options

  //! Version
  Version = FlowWingCliOptions::OPTIONS::Version;
  ShortVersion = FlowWingCliOptions::OPTIONS::ShortVersion;

  //! File
  File = FlowWingCliOptions::OPTIONS::File;
  ShortFile = FlowWingCliOptions::OPTIONS::ShortFile;

  //! Format
  Format = FlowWingCliOptions::OPTIONS::Format;
  ShortFormat = FlowWingCliOptions::OPTIONS::ShortFormat;

  //! Format Print
  FormatPrint = FlowWingCliOptions::OPTIONS::FormatPrint;
  ShortFormatPrint = FlowWingCliOptions::OPTIONS::ShortFormatPrint;
}

const std::string Compiler::getBuiltInModulePath() const {
  // std::cout << "Executable directory: " << filePath << std::endl;
  return LIB_BUILT_IN_MODULE_PATH;
}

std::unique_ptr<llvm::MemoryBuffer>
Compiler::getMemoryBuffer(std::string filePath) {
  if (auto bufferOrErr = llvm::MemoryBuffer::getFile(filePath)) {
    return std::move(*bufferOrErr);
  } else {
    _currentDiagnosticHandler->printDiagnostic(
        std::cerr, Diagnostic("Error reading bitcode file: " + filePath + " " +
                                  bufferOrErr.getError().message(),
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Linker,
                              DiagnosticUtils::SourceLocation()));
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
        std::cerr, Diagnostic("Error reading IR file: " + filePath,
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Linker,
                              DiagnosticUtils::SourceLocation(0, 0, 0, "")));
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
        std::cerr, Diagnostic("Error reading bitcode file: " + filePath,
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Linker,
                              DiagnosticUtils::SourceLocation(0, 0, 0, "")));
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
      Utils::getAllFilesInDirectoryWithExtension(".", ".bc", false);
#endif

  if (_userDefinedIRFilePaths.size() == 0) {
    _currentDiagnosticHandler->printDiagnostic(
        std::cerr, Diagnostic("No user defined IR files found.",
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Linker,
                              DiagnosticUtils::SourceLocation(0, 0, 0, "")));
    return {};
  }

  return _userDefinedIRFilePaths;
}

std::unique_ptr<llvm::Module>
Compiler::getLinkedModule(std::unique_ptr<llvm::LLVMContext> &TheContext) {
  std::vector<std::string> _userDefinedIRFilePaths = getIRFilePaths();

  const std::string &filePath = getBuiltInModulePath();

#if defined(RELEASE)
  // std::unique_ptr<llvm::Module> TheModule =
  //     std::make_unique<llvm::Module>("built_in_module", *TheContext);
  std::unique_ptr<llvm::Module> TheModule =
      std::move(createModuleFromBitcode(filePath, TheContext));
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
  TheModule->setTargetTriple(getDefaultTargetTriple());
#elif defined(__LINUX__)
  TheModule->setTargetTriple(
      llvm::Triple::normalize(llvm::sys::getDefaultTargetTriple()));
#endif

  for (const std::string &path : _userDefinedIRFilePaths) {
    llvm::SMDiagnostic err;

#if (defined(DEBUG) && defined(JIT_MODE)) ||                                   \
    (defined(DEBUG) && defined(AOT_MODE))

    _currentDiagnosticHandler->printDiagnostic(
        std::cerr,
        Diagnostic("Linking " + path, DiagnosticUtils::DiagnosticLevel::Info,
                   DiagnosticUtils::DiagnosticType::Linker,
                   DiagnosticUtils::SourceLocation(0, 0, 0, path)));

#endif

    bool LinkResult = llvm::Linker::linkModules(
        *TheModule.get(), llvm::parseIRFile(path, err, *TheContext.get()),
        llvm::Linker::Flags::OverrideFromSrc);
    if (LinkResult) {
      _currentDiagnosticHandler->printDiagnostic(
          std::cerr,
          Diagnostic("Error linking " + path,
                     DiagnosticUtils::DiagnosticLevel::Error,
                     DiagnosticUtils::DiagnosticType::Linker,
                     DiagnosticUtils::SourceLocation(0, 0, 0, path)));
      return nullptr;
    }
  }

#if (defined(DEBUG) && defined(JIT_MODE)) ||                                   \
    (defined(DEBUG) && defined(AOT_MODE))

  _currentDiagnosticHandler->printDiagnostic(
      std::cerr, Diagnostic("Finished linking modules.",
                            DiagnosticUtils::DiagnosticLevel::Info,
                            DiagnosticUtils::DiagnosticType::Linker,
                            DiagnosticUtils::SourceLocation(
                                0, 0, 0, "FLOWWING_GLOBAL_ENTRY_POINT")));

  TheModule->print(llvm::outs(), nullptr);

  // llFileSaveStrategy->saveToFile("../my_module.ll", TheModule.get());

#endif

  return std::move(TheModule);
}

void Compiler::compile(std::vector<std::string> &text,
                       std::ostream &outputStream) {
  std::unique_ptr<FLowWing::DiagnosticHandler> currentDiagnosticHandler =
      std::make_unique<FLowWing::DiagnosticHandler>(
          Utils::getAbsoluteFilePath(this->_filePath));

  currentDiagnosticHandler->setOutputFilePath(_outputFilePath);
  logNoErrorJSONIfAsked();
  std::unique_ptr<Parser> parser =
      std::make_unique<Parser>(text, currentDiagnosticHandler.get());

  if (Utils::getExtension(_outputFilePath) == ".json") {
    JSON jsonObject = Utils::outJSON(parser->getTokensRef());
    Utils::logJSON(jsonObject, _outputFilePath.substr(
                                   0, _outputFilePath.find_last_of(".")) +
                                   ".tokens.json");
  }

  parser->setIsFormattedCodeRequired(this->Format.getValue() ||
                                     this->ShortFormat.getValue());

  if (currentDiagnosticHandler->hasError(
          DiagnosticUtils::DiagnosticType::Lexical)) {
    currentDiagnosticHandler->logDiagnostics(
        std::cerr, [](const Diagnostic &d) {
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
        std::cerr, [](const Diagnostic &d) {
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
  if (Utils::getExtension(_outputFilePath) == ".json") {
    JSON jsonObject = Utils::outJSON(compilationUnit.get());
    Utils::logJSON(jsonObject, _outputFilePath);
  }
  std::unique_ptr<BoundScopeGlobal> globalScope =
      std::move(Binder::bindGlobalScope(nullptr, compilationUnit.get(),
                                        currentDiagnosticHandler.get()));
  const bool &hasSemanticError = currentDiagnosticHandler->hasError(
      DiagnosticUtils::DiagnosticType::Semantic);

  if (hasSemanticError) {
    currentDiagnosticHandler->logDiagnostics(
        std::cerr, [](const Diagnostic &d) {
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

  if (Utils::getExtension(_outputFilePath) == ".json") {
    //! Disable for now
    // JSON jsonObject = Utils::outJSON(globalScope->globalStatement.get(),
    // false); Utils::logJSON(jsonObject, _outputFilePath);

  } else if (this->Format.getValue() || this->ShortFormat.getValue()) {
    //? format and Save to file
    std::ofstream file(currentDiagnosticHandler->getAbsoluteFilePath(),
                       std::ios::out);

    // Check if the file is opened successfully
    if (!file.is_open()) {
      _currentDiagnosticHandler->printDiagnostic(
          std::cerr,
          Diagnostic(
              "Error opening file: formatting failed " +
                  currentDiagnosticHandler->getAbsoluteFilePath(),
              DiagnosticUtils::DiagnosticLevel::Error,
              DiagnosticUtils::DiagnosticType::Linker,
              DiagnosticUtils::SourceLocation(
                  0, 0, 0, currentDiagnosticHandler->getAbsoluteFilePath())));
      return;
    }

    // Replace the content of the file with text
    file << parser->getFormattedSourceCode();
    return;
  } else if (this->FormatPrint.getValue() ||
             this->ShortFormatPrint.getValue()) {
    std::cout << parser->getFormattedSourceCode() << std::endl;
    return;
  }

  try {
    std::unique_ptr<IRGenerator> _evaluator = std::make_unique<IRGenerator>(
        ENVIRONMENT::SOURCE_FILE, currentDiagnosticHandler.get(),
        globalScope.get()->functions, _outputFilePath);

    _evaluator->generateEvaluateGlobalStatement(
        globalScope->globalStatement.get());

    // _evaluator->executeGeneratedCode();

    //_evaluator->getIRParserPtr()->printIR();

    // _evaluator.reset(nullptr);

    if (!_evaluator->hasErrors()) {
      logNoErrorJSONIfAsked();
      this->execute();
    }
    outputStream << std::endl;
  } catch (const std::exception &e) {
    outputStream << RED << e.what() << RESET << "\n";
  }
}

void Compiler::logNoErrorJSONIfAsked() {
  if (Utils::getExtension(_outputFilePath) == ".json") {
    JSON jsonObj = {{"error", false}};
    Utils::logJSON(
        jsonObj, _outputFilePath.substr(0, _outputFilePath.find_last_of(".")) +
                     ".err.json");
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
        globalScope.get()->functions, _outputFilePath);
    _evaluator->generateEvaluateGlobalStatement(
        globalScope->globalStatement.get());

    if (!_evaluator->hasErrors()) {
      this->execute();
    }
  } catch (const std::exception &e) {
    outputStream << RED << e.what() << RESET << "\n";
  }
}
