/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "IRGenerator.h"
#include <string>

IRGenerator::IRGenerator(
    int environment, FlowWing::DiagnosticHandler *diagnosticHandler,
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

  FunctionDeclarationManager functionDeclarationManager(
      _codeGenerationContext.get());
  functionDeclarationManager.initialize();

  GlobalVariableInitializer globalVariableInitializer(
      _codeGenerationContext.get());
  globalVariableInitializer.initialize();

  GlobalTypeInitializer globalTypeInitializer(_codeGenerationContext.get());
  globalTypeInitializer.initialize();

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

  //.o
  objectFile = std::make_unique<ObjectFile>();

  m_hasTempDirectories =
      FLOWWING::IR::UTILS::createTempDirectories(_llvmLogger);
}

void IRGenerator::setModuleCount(int count) { this->_moduleCount = count; }

std::unique_ptr<IRParser> &IRGenerator::getIRParserPtr() {
  return this->_irParser;
}

int32_t IRGenerator::hasErrors() const { return _llvmLogger->getErrorCount(); }

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

  //! REFACTOR BELOW CODE IN SINGLE FUNCTION and DO all
  //! Type, Variable, and Function Declaration at once in order as they
  //! are created

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

  for (size_t i = 0; i < blockStatement->getStatements().size(); i++) {
    BoundStatement *statement = blockStatement->getStatements()[i].get();

    BinderKindUtils::BoundNodeKind kind = statement->getKind();
    bool generateStatement = true;
    if (kind == BinderKindUtils::BoundNodeKind::FunctionDeclaration) {
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

  for (size_t i = 0; i < blockStatement->getStatements().size(); i++) {
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

  char **OutMessage = nullptr;
  // Print LLVM IR to console
  TheModule->print(llvm::outs(), nullptr);
  LLVMVerifyModule(wrap(TheModule),
                   LLVMVerifierFailureAction::LLVMAbortProcessAction,
                   OutMessage);

  if (OutMessage) {
    std::cout << "error: " << *OutMessage << std::endl;
  }

#endif

  if (!this->hasErrors() && m_hasTempDirectories == EXIT_SUCCESS) {
#if defined(DEBUG)
    char **OutMessage = nullptr;
    const std::string Filename = (std::string(
        Utils::getTempDir() + FLOWWING::IR::CONSTANTS::TEMP_BC_FILES_DIR +
        blockName + std::string(".ll")));
    llvm::sys::fs::create_directories(
        Utils::getTempDir() + FLOWWING::IR::CONSTANTS::TEMP_BC_FILES_DIR);
    LLVMPrintModuleToFile(wrap(TheModule), Filename.c_str(), OutMessage);
    objectFile->writeModuleToFile(TheModule, blockName);
#elif defined(AOT_MODE) || defined(AOT_TEST_MODE)
    objectFile->writeModuleToFile(TheModule, blockName);
#elif (defined(JIT_MODE) || defined(JIT_TEST_MODE))
    bcFileSaveStrategy->saveToFile(
        Utils::getTempDir() + FLOWWING::IR::CONSTANTS::TEMP_BC_FILES_DIR +
            blockName + ".bc",
        TheModule);
#endif
  }

#ifdef JIT_MODE
  if (this->hasErrors()) {
    llvm::SMDiagnostic Err;
    Err.print("FlowWing", llvm::errs());
  }
#endif
}

void IRGenerator::defineClass(BoundClassStatement *boundClassStatement) {
  // Add handlers

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
    _functionStatementGenerationStrategy =
        std::make_unique<FunctionStatementGenerationStrategy>(
            this->_codeGenerationContext.get());
    for (auto &variDec : boundClassStatement->getAllMemberVariablesRef()) {
      classVariables.push_back(variDec->getVariableName());
    }

    if (!functionDeclaration->isOnlyDeclared()) {
      _functionStatementGenerationStrategy->generate(
          functionDeclaration, {"self"}, classType, classVariables);
    }
  }
  // Rest
  _codeGenerationContext->resetCurrentClassName();
  // Remove handlers
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
