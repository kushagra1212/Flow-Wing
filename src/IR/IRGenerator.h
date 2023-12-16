#ifndef IRGENERATOR_H
#define IRGENERATOR_H

#include "../Common.h"
#include "../IR/constants/FlowWingIRConstants.h"
#include "../IR/context/CodeGenerationContext.h"
#include "../IR/declarations/FunctionDeclarationManager/FunctionDeclarationManager.h"
#include "../IR/handlers/alloca/AllocaChain/AllocaChain.h"
#include "../IR/handlers/alloca/AllocaHandler.h"
#include "../IR/handlers/alloca/AllocaTable/AllocaTable.h"
#include "../IR/handlers/value/NamedValueTable/NamedValueTable.h"
#include "../IR/handlers/value/ValueChain/ValueChain.h"
#include "../IR/handlers/value/ValueHandler.h"
#include "../IR/initializers/GlobalVariableInitializer/GlobalVariableInitializer.h"
#include "../IR/irGen/statements/FunctionStatementGenerationStrategy/FunctionStatementGenerationStrategy.h"
#include "../IR/irGen/statements/StatementGenerationFactory.h"
#include "../IR/irGen/statements/VariableDeclarationStatementGenerationStrategy/VariableDeclarationStatementGenerationStrategy.h"
#include "../IR/logger/LLVMLogger.h"
#include "../bind/Binder/Binder.h"
#include "../bind/Binder/BoundScopeGlobal/BoundScopeGlobal.h"
#include "../bind/BinderKindUtils.h"
#include "../bind/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "../bind/BoundBinaryExpression/BoundBinaryExpression.h"
#include "../bind/BoundBlockStatement/BoundBlockStatement.h"
#include "../bind/BoundBringStatement/BoundBringStatement.h"
#include "../bind/BoundExpression.h"
#include "../bind/BoundExpressionStatement/BoundExpressionStatement.h"
#include "../bind/BoundLiteralExpression/BoundLiteralExpression.h"
#include "../bind/BoundParenthesizedExpression/BoundParenthesizedExpression.h"
#include "../bind/BoundStatement/BoundStatement.h"
#include "../bind/BoundUnaryExpression/BoundUnaryExpression.h"
#include "../bind/BoundVariableExpression/BoundVariableExpression.h"
#include "../syntax/CompilationUnitSyntax.h"
#include "../utils/Utils.h"
#include "IRGenerator.h"
#include "IRParser/IRParser.h"
#include "utils/fileSaver/ll-file/LLFileSaveStrategy.h"

using namespace FLOWWING::IR::CONSTANTS;

// LLVM Imports
#include "llvm/IR/Type.h"
#include "llvm/Pass.h"
#include <llvm/ADT/APInt.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Transforms/Utils/Cloning.h>

#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"
#include <llvm/Support/Error.h>
#include <llvm/Support/SourceMgr.h>

#include <llvm/IRReader/IRReader.h>
// ExecutionEngine
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/Signals.h"
#include "llvm/Support/raw_ostream.h"
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/SourceMgr.h>

#include "llvm//IR/Value.h"
#include "llvm/IR/Constants.h"

#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include <llvm/Linker/Linker.h>
#include <llvm/Support/FileSystem.h>
// JIT
#include <llvm/ExecutionEngine/Orc/LLJIT.h>

#include <llvm/Support/raw_ostream.h>
#include <sstream>

class IRGenerator {

public:
  IRGenerator(
      int environment, DiagnosticHandler *diagnosticHandler,
      std::map<std::string, BoundFunctionDeclaration *> boundedUserFunctions,
      const std::string sourceFileName = FLOWWING_GLOBAL_ENTRY_POINT);
  void printIR();

  void mergeModules(llvm::Module *sourceFunction,
                    llvm::Module *destinationModule);
  void declareDependencyFunctions();
  void initializeGlobalVariables();

  int executeGeneratedCode();

  std::shared_ptr<BoundScopeGlobal> _previousGlobalScope = nullptr;

  void generateEvaluateGlobalStatement(
      BoundBlockStatement *blockStatement,
      std::string blockName = FLOWWING_GLOBAL_ENTRY_POINT);

  std::unique_ptr<IRParser> &getIRParserPtr();
  void setModuleCount(int count);
  const int32_t hasErrors() const;
  bool saveLLVMModuleToFile(llvm::Module *module, const std::string &path);

private:
  llvm::LLVMContext *TheContext;
  llvm::Module *TheModule;
  llvm::IRBuilder<> *Builder;

  LLVMLogger *_llvmLogger;

  std::unique_ptr<IRParser> _irParser;

  int showNewLineForRepl = 0;
  int _moduleCount = 0;
  int _environment;

  std::unique_ptr<CodeGenerationContext> _codeGenerationContext;

  // Statement Generation Strategy

  std::unique_ptr<FunctionStatementGenerationStrategy>
      _functionStatementGenerationStrategy;

  std::unique_ptr<StatementGenerationFactory> _statementGenerationFactory;

  // File Save Strategy

  std::unique_ptr<LLFileSaveStrategy> llFileSaveStrategy;
};

#endif // IRGENERATOR_H
