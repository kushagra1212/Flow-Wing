#ifndef IRGENERATOR_H
#define IRGENERATOR_H

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
#include "../IR/irGen/statements/BringStatementGenerationStrategy/BringStatementGenerationStrategy.h"
#include "../IR/irGen/statements/ClassStatementGenerationStrategy/ClassStatementGenerationStrategy.h"
#include "../IR/irGen/statements/FunctionStatementGenerationStrategy/FunctionStatementGenerationStrategy.h"
#include "../IR/irGen/statements/ModuleStatementGenerationStrategy/ModuleStatementGenerationStrategy.h"
#include "../IR/irGen/statements/StatementGenerationFactory.h"
#include "../IR/irGen/statements/VariableDeclarationStatementGenerationStrategy/VariableDeclarationStatementGenerationStrategy.h"
#include "../IR/logger/LLVMLogger.h"
#include "../SemanticAnalyzer/BinderKindUtils.h"
#include "../SemanticAnalyzer/BoundExpressions/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "../SemanticAnalyzer/BoundExpressions/BoundBinaryExpression/BoundBinaryExpression.h"
#include "../SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "../SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundLiteralExpression.h"
#include "../SemanticAnalyzer/BoundExpressions/BoundParenthesizedExpression/BoundParenthesizedExpression.h"
#include "../SemanticAnalyzer/BoundExpressions/BoundUnaryExpression/BoundUnaryExpression.h"
#include "../SemanticAnalyzer/BoundExpressions/BoundVariableExpression/BoundVariableExpression.h"
#include "../SemanticAnalyzer/BoundStatements/BoundBlockStatement/BoundBlockStatement.h"
#include "../SemanticAnalyzer/BoundStatements/BoundBringStatement/BoundBringStatement.h"
#include "../SemanticAnalyzer/BoundStatements/BoundExpressionStatement/BoundExpressionStatement.h"
#include "../SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "../SemanticAnalyzer/SemanticAnalyzer.h"
#include "../SemanticAnalyzer/SyntaxBinder/BoundGlobalScope/BoundGlobalScope.h"
#include "../common/Common.h"
#include "../compiler/AOTCompiler/ObjectFile/ObjectFile.h"
#include "../syntax/CompilationUnitSyntax.h"
#include "../utils/Utils.h"
#include "IRParser/IRParser.h"
#include "irGen/declaration/IRCodeGenerator/IRCodeGenerator.h"
#include "utils/fileSaver/bc-file/BCFileSaveStrategy.h"
#include "utils/fileSaver/ll-file/LLFileSaveStrategy.h"
#include "utils/fileSaver/o-file/OFileSaveStrategy.h"

using namespace FLOWWING::IR::CONSTANTS;

// LLVM Imports
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
#include <llvm/Support/Error.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Transforms/Utils/Cloning.h>

#include "llvm/IR/Instruction.h"
#include "llvm/IR/Type.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
// ExecutionEngine
#include "llvm//IR/Value.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/PassManager.h"
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
#include <llvm/Linker/Linker.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/SourceMgr.h>
// JIT
#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/Support/raw_ostream.h>

#include <sstream>

class IRGenerator {
public:
  IRGenerator(int environment, FlowWing::DiagnosticHandler *diagnosticHandler,
              std::unordered_map<std::string, BoundFunctionDeclaration *>
                  boundedUserFunctions,
              std::string outputFilePath,
              const std::string sourceFileName = FLOWWING_GLOBAL_ENTRY_POINT);
  void printIR();

  void mergeModules(llvm::Module *sourceFunction,
                    llvm::Module *destinationModule);
  void declareDependencyFunctions();
  void initializeGlobalVariables();

  int executeGeneratedCode();

  std::shared_ptr<BoundGlobalScope> _previousGlobalScope = nullptr;

  void generateEvaluateGlobalStatement(
      BoundBlockStatement *blockStatement,
      std::string blockName = FLOWWING_GLOBAL_ENTRY_POINT);

  void defineClass(BoundClassStatement *boundClassStatement);

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

  std::unique_ptr<BringStatementGenerationStrategy>
      _bringStatementGenerationStrategy;

  std::unique_ptr<StatementGenerationFactory> _statementGenerationFactory;

  std::unique_ptr<ModuleStatementGenerationStrategy>
      _moduleStatementGenerationStrategy;

  // File Save Strategy

  std::unique_ptr<LLFileSaveStrategy> llFileSaveStrategy;
  std::unique_ptr<BCFileSaveStrategy> bcFileSaveStrategy;
  std::unique_ptr<OFileSaveStrategy> oFileSaveStrategy;
  std::unique_ptr<ObjectFile> objectFile;
  // IRCodeGenerator Instance

  std::unique_ptr<IRCodeGenerator> _irCodeGenerator;
};

#endif // IRGENERATOR_H
