#include "IRGenerator.h"

IRGenerator::IRGenerator(
    int environment, DiagnosticHandler *diagnosticHandler,
    std::map<std::string, BoundFunctionDeclaration *> boundedUserFunctions,
    const std::string sourceFileName) {

  // Initialize the code generation context
  _codeGenerationContext = std::make_unique<CodeGenerationContext>(
      diagnosticHandler, sourceFileName);

  // Initialize the BoundUserFunctions
  _codeGenerationContext->getBoundedUserFunctions() = boundedUserFunctions;

  Builder = _codeGenerationContext->getBuilder().get();
  TheModule = _codeGenerationContext->getModule().get();
  TheContext = _codeGenerationContext->getContext().get();
  _llvmLogger = _codeGenerationContext->getLogger().get();

  _environment = environment;
  _irParser = std::make_unique<IRParser>();

  this->declareDependencyFunctions();
  this->initializeGlobalVariables();

  // Statement Generation Strategy

  _functionStatementGenerationStrategy =
      std::make_unique<FunctionStatementGenerationStrategy>(
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
  functionDeclarationManager->declareStringLengthFn();
  functionDeclarationManager->declareStringToDoubleFn();
  functionDeclarationManager->declareStringToIntFn();
  functionDeclarationManager->declareStringToLongFn();
  functionDeclarationManager->declareRaiseExceptionFn();
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
      llvm::FunctionType::get(llvm::Type::getInt32Ty(*TheContext), false);

  llvm::Function *F = llvm::Function::Create(
      FT, llvm::Function::ExternalLinkage, blockName, *TheModule);

  llvm::BasicBlock *entryBlock =
      llvm::BasicBlock::Create(*TheContext, "entry", F);

  llvm::BasicBlock *returnBlock =
      llvm::BasicBlock::Create(*TheContext, "returnBlock", F);

  // Entry Block

  Builder->SetInsertPoint(entryBlock);

  for (int i = 0; i < blockStatement->getStatements().size(); i++) {
    BoundStatement *statement = blockStatement->getStatements()[i].get();

    BinderKindUtils::BoundNodeKind kind = statement->getKind();
    _statementGenerationFactory->createStrategy(kind)->generateGlobalStatement(
        statement);
  }

  Builder->CreateBr(returnBlock);
  Builder->SetInsertPoint(returnBlock);
  Builder->CreateRet(
      llvm::ConstantInt::get(llvm::Type::getInt32Ty(*TheContext), 0, true));

  for (int i = 0; i < blockStatement->getStatements().size(); i++) {
    BinderKindUtils::BoundNodeKind kind =
        blockStatement->getStatements()[i].get()->getKind();
    if (kind == BinderKindUtils::BoundNodeKind::FunctionDeclaration) {

      _functionStatementGenerationStrategy->generateGlobalStatement(
          blockStatement->getStatements()[i].get());
    }
  }

#ifdef DEBUG
  llFileSaveStrategy->saveToFile(
      _codeGenerationContext->getSourceFileName() + ".ll", TheModule);
#else
  bcFileSaveStrategy->saveToFile(
      _codeGenerationContext->getSourceFileName() + ".bc", TheModule);
#endif

  // this->_irParser->mergeIR(TheModule.get());

  // this->_irParser->removeDuplicates();

#ifdef JIT_MODE
  if (this->hasErrors()) {
    llvm::SMDiagnostic Err;
    Err.print("FLowWing", llvm::errs());
  }
#endif
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
