#include "IRGenerator.h"

IRGenerator::IRGenerator(
    int environment, FLowWing::DiagnosticHandler *diagnosticHandler,
    std::unordered_map<std::string, BoundFunctionDeclaration *>
        boundedUserFunctions,
    std::string outputFilePath, const std::string sourceFileName) {
  // Initialize the code generation context
  _codeGenerationContext = std::make_unique<CodeGenerationContext>(
      diagnosticHandler, sourceFileName);

  // Initialize the BoundUserFunctions
  _codeGenerationContext->getBoundedUserFunctions() = boundedUserFunctions;

  Builder = _codeGenerationContext->getBuilder().get();
  TheModule = _codeGenerationContext->getModule().get();
  TheContext = _codeGenerationContext->getContext().get();
  _llvmLogger = _codeGenerationContext->getLogger().get();

  //? Eg. Output error in JSON format
  _llvmLogger->setOutputFilePath(outputFilePath);

  // Initialize the environment

  _environment = environment;
  _irParser = std::make_unique<IRParser>();

  // LLVM - 16 bit
  // TheContext->setOpaquePointers(false);

  this->declareDependencyFunctions();
  this->initializeGlobalVariables();

  // Initialize IRCodeGenerator (Statement Generation Strategy)

  _irCodeGenerator =
      std::make_unique<IRCodeGenerator>(_codeGenerationContext.get());

  // Statement Generation Strategy

  _functionStatementGenerationStrategy =
      std::make_unique<FunctionStatementGenerationStrategy>(
          this->_codeGenerationContext.get());

  _bringStatementGenerationStrategy =
      std::make_unique<BringStatementGenerationStrategy>(
          this->_codeGenerationContext.get());

  _moduleStatementGenerationStrategy =
      std::make_unique<ModuleStatementGenerationStrategy>(
          this->_codeGenerationContext.get());

  // Initialize the expression generation factory

  _statementGenerationFactory = std::make_unique<StatementGenerationFactory>(
      this->_codeGenerationContext.get());

  // Initialize the file save strategy

  //.ll file save strategy
  llFileSaveStrategy = std::make_unique<LLFileSaveStrategy>(_llvmLogger);

  //.bc file save strategy
  bcFileSaveStrategy = std::make_unique<BCFileSaveStrategy>(_llvmLogger);

  //.o file save strategy
  oFileSaveStrategy = std::make_unique<OFileSaveStrategy>(_llvmLogger);
}

void IRGenerator::declareDependencyFunctions() {
  std::unique_ptr<FunctionDeclarationManager> functionDeclarationManager =
      std::make_unique<FunctionDeclarationManager>(
          _codeGenerationContext.get());

  functionDeclarationManager->declareCompareStringsFn();
  functionDeclarationManager->declareConcatStringsFn();
  functionDeclarationManager->declareDtosFn();
  functionDeclarationManager->declareEqualStringsFn();
  functionDeclarationManager->declareGetInputFn();
  functionDeclarationManager->declareGetMallocPtrofIntConstantFn();
  functionDeclarationManager->declareGetMallocPtrOfStringConstantFn();
  functionDeclarationManager->declareGreaterThanOrEqualStringsFn();
  functionDeclarationManager->declareGreaterThanStringsFn();
  functionDeclarationManager->declareItosFn();
  functionDeclarationManager->declareLessThanOrEqualStringsFn();
  functionDeclarationManager->declareLessThanStringsFn();
  functionDeclarationManager->declarePrintFn();
  functionDeclarationManager->declarePrintfFn();
  functionDeclarationManager->declareStringLengthFn();
  functionDeclarationManager->declareStringToDoubleFn();
  functionDeclarationManager->declareStringToIntFn();
  functionDeclarationManager->declareStringToLongFn();
  functionDeclarationManager->declareRaiseExceptionFn();
  functionDeclarationManager->declareMallocFunctionFn();
  functionDeclarationManager->declarePutChar();
}

void IRGenerator::initializeGlobalVariables() {
  std::unique_ptr<GlobalVariableInitializer> globalVariableInitializer =
      std::make_unique<GlobalVariableInitializer>(_codeGenerationContext.get());

  globalVariableInitializer->initializeTrue();
  globalVariableInitializer->initializeFalse();
  globalVariableInitializer->initializeI8Null();
  globalVariableInitializer->initializeBreakCount();
  globalVariableInitializer->initializeContinueCount();
  globalVariableInitializer->initializeErrorCount();
}

void IRGenerator::setModuleCount(int count) { this->_moduleCount = count; }

std::unique_ptr<IRParser> &IRGenerator::getIRParserPtr() {
  return this->_irParser;
}

void IRGenerator::printIR() {
  // Print LLVM IR to console
  TheModule->print(llvm::outs(), nullptr);
}

void IRGenerator::mergeModules(llvm::Module *sourceModule,
                               llvm::Module *destinationModule) {
  llvm::LLVMContext &context = destinationModule->getContext();
  llvm::ValueToValueMapTy vmap;

  // Iterate through functions in the source module and clone them to the
  // destination module
  for (llvm::Function &sourceFunction : *sourceModule) {
    llvm::Function *clonedFunction = llvm::CloneFunction(&sourceFunction, vmap);
    clonedFunction->setName(sourceFunction.getName() + ".clone");
    destinationModule->getFunctionList().push_back(clonedFunction);
  }
}

const int32_t IRGenerator::hasErrors() const {
  return _llvmLogger->getErrorCount();
}

void IRGenerator::generateEvaluateGlobalStatement(
    BoundBlockStatement *blockStatement, std::string blockName) {
  llvm::FunctionType *FT =
      llvm::FunctionType::get(llvm::Type::getInt32Ty(*TheContext),
                              {llvm::Type::getInt32Ty(*TheContext),
                               llvm::Type::getInt8PtrTy(*TheContext)},
                              false);

  llvm::Function *F = llvm::Function::Create(
      FT, llvm::Function::ExternalLinkage, blockName, *TheModule);

  llvm::BasicBlock *entryBlock =
      llvm::BasicBlock::Create(*TheContext, "entry", F);

  llvm::BasicBlock *returnBlock =
      llvm::BasicBlock::Create(*TheContext, "returnBlock", F);

  // Entry Block

  Builder->SetInsertPoint(entryBlock);

  _irCodeGenerator->declareCustomType(blockStatement);
  for (auto &children : blockStatement->getStatements()) {
    if (children->getKind() ==
        BinderKindUtils::BoundNodeKind::FunctionDeclaration) {
      BoundFunctionDeclaration *functionDeclaration =
          static_cast<BoundFunctionDeclaration *>(children.get());
      if (functionDeclaration->isOnlyDeclared())
        _statementGenerationFactory->createStrategy(children->getKind())
            ->generateGlobalStatement(children.get());
    } else if (children->getKind() ==
               BinderKindUtils::BoundNodeKind::BringStatement) {

      _bringStatementGenerationStrategy->declare(children.get());
    } else if (children->getKind() ==
               BinderKindUtils::BoundNodeKind::BoundModuleStatement) {
      _moduleStatementGenerationStrategy->declare(children.get());
    }
  }

  _irCodeGenerator->declareVariables(blockStatement, true);

  // Declare All Global Variables

  for (int i = 0; i < blockStatement->getStatements().size(); i++) {
    BoundStatement *statement = blockStatement->getStatements()[i].get();

    BinderKindUtils::BoundNodeKind kind = statement->getKind();
    bool generateStatement = true;
    if (kind == BinderKindUtils::BoundNodeKind::FunctionDeclaration) {
      BoundFunctionDeclaration *functionDeclaration =
          static_cast<BoundFunctionDeclaration *>(
              blockStatement->getStatements()[i].get());
      generateStatement = false;
    }

    if (generateStatement)
      _statementGenerationFactory->createStrategy(kind)
          ->generateGlobalStatement(statement);
  }

  Builder->CreateBr(returnBlock);
  Builder->SetInsertPoint(returnBlock);

  Builder->CreateRet(
      llvm::ConstantInt::get(llvm::Type::getInt32Ty(*TheContext), 0, true));

  for (int i = 0; i < blockStatement->getStatements().size(); i++) {
    BinderKindUtils::BoundNodeKind kind =
        blockStatement->getStatements()[i].get()->getKind();
    if (kind == BinderKindUtils::BoundNodeKind::FunctionDeclaration) {

      BoundFunctionDeclaration *functionDeclaration =
          static_cast<BoundFunctionDeclaration *>(
              blockStatement->getStatements()[i].get());

      if (!functionDeclaration->isOnlyDeclared())
        _functionStatementGenerationStrategy->generateGlobalStatement(
            functionDeclaration);

    } else if (kind == BinderKindUtils::BoundNodeKind::ClassStatement) {

      BoundClassStatement *boundClassStatement =
          static_cast<BoundClassStatement *>(
              blockStatement->getStatements()[i].get());

      defineClass(boundClassStatement);
    } else if (kind == BinderKindUtils::BoundNodeKind::BoundModuleStatement) {

      BoundModuleStatement *boundModuleStatement =
          static_cast<BoundModuleStatement *>(
              blockStatement->getStatements()[i].get());

      for (const auto &fun : boundModuleStatement->getFunctionStatementsRef()) {
        BoundFunctionDeclaration *functionDeclaration =
            static_cast<BoundFunctionDeclaration *>(fun.get());

        if (!functionDeclaration->isOnlyDeclared())
          _functionStatementGenerationStrategy->generateGlobalStatement(
              functionDeclaration);
      }

      for (const auto &classStatement :
           boundModuleStatement->getClassStatementsRef()) {
        BoundClassStatement *boundClassStatement =
            static_cast<BoundClassStatement *>(classStatement.get());

        defineClass(boundClassStatement);
      }
    }
  }
#if DEBUG
  this->printIR();
  _codeGenerationContext->verifyModule(TheModule);
#endif

  if (!this->hasErrors()) {
#ifdef DEBUG
    llFileSaveStrategy->saveToFile(blockName + ".ll", TheModule);

    std::unique_ptr<ObjectFile> objectFile =
        std::make_unique<ObjectFile>(blockName);
    objectFile->writeModuleToFile(TheModule);
#elif defined(RELEASE) && (defined(JIT_MODE) || defined(JIT_TEST_MODE))
    bcFileSaveStrategy->saveToFile(blockName + ".bc", TheModule);
#elif RELEASE
    std::unique_ptr<ObjectFile> objectFile =
        std::make_unique<ObjectFile>(blockName);
    objectFile->writeModuleToFile(*TheModule,
                                  _codeGenerationContext->getTargetMachine());
#endif
  }

#ifdef JIT_MODE
  if (this->hasErrors()) {
    llvm::SMDiagnostic Err;
    Err.print("FLowWing", llvm::errs());
  }
#endif
}

void IRGenerator::defineClass(BoundClassStatement *boundClassStatement) {
  // Add handlers
  _codeGenerationContext->getNamedValueChain()->addHandler(
      new NamedValueTable());
  _codeGenerationContext->getAllocaChain()->addHandler(
      std::make_unique<AllocaTable>());

  llvm::StructType *classType =
      _codeGenerationContext->_classTypes[boundClassStatement->getClassName()]
          ->getClassType();

  if (!classType) {
    _codeGenerationContext->getLogger()->LogError(
        "Class " + boundClassStatement->getClassName() + " not found");
    return;
  }
  _codeGenerationContext->setCurrentClassName(
      boundClassStatement->getClassName());

  for (auto &funDec : boundClassStatement->getMemberFunctionsRef()) {
    BoundFunctionDeclaration *functionDeclaration =
        static_cast<BoundFunctionDeclaration *>(funDec.get());
    std::vector<std::string> classVariables = {};

    for (auto &variDec : boundClassStatement->getAllMemberVariablesRef()) {
      classVariables.push_back(variDec->getVariableName());
    }

    if (!functionDeclaration->isOnlyDeclared()) {
      llvm::Value *F = _functionStatementGenerationStrategy->generate(
          functionDeclaration, {"self"}, classType, classVariables);
    }
  }
  // Rest
  _codeGenerationContext->resetCurrentClassName();
  // Remove handlers
  _codeGenerationContext->getNamedValueChain()->removeHandler();
  _codeGenerationContext->getAllocaChain()->removeHandler();
}

int IRGenerator::executeGeneratedCode() {
  llvm::Function *evaluateBlockStatement =
      TheModule->getFunction(FLOWWING_GLOBAL_ENTRY_POINT);

  std::string errorMessage;
  llvm::ExecutionEngine *executionEngine =
      llvm::EngineBuilder(std::move(_codeGenerationContext->getModule()))
          .setErrorStr(&errorMessage)
          .setEngineKind(llvm::EngineKind::JIT)
          .create();
  if (!executionEngine) {
    llvm::errs() << "Failed to create Execution Engine: " << errorMessage
                 << "\n";
  }

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
  return hasError;
}

bool IRGenerator::saveLLVMModuleToFile(llvm::Module *module,
                                       const std::string &path) {
  // Create an output stream for the .ll file
  std::error_code EC;
  llvm::raw_fd_ostream OS(path, EC, llvm::sys::fs::OF_None);

  if (!EC) {
    // Write the LLVM module to the .ll file
    module->print(OS, nullptr);
    OS.flush();
    return true;
  } else {
    _llvmLogger->LogError("Error opening " + Utils::getFileName(path) +
                          " for writing: " + EC.message());

    return false;
  }
}
