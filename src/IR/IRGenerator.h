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

#pragma once

#include "IRParser/IRParser.h"
#include "irGen/declaration/IRCodeGenerator/IRCodeGenerator.h"
#include "src/IR/constants/FlowWingIRConstants.h"
#include "src/IR/context/CodeGenerationContext.h"
#include "src/IR/declarations/FunctionDeclarationManager/FunctionDeclarationManager.h"
#include "src/IR/handlers/alloca/AllocaChain/AllocaChain.h"
#include "src/IR/handlers/alloca/AllocaHandler.h"
#include "src/IR/handlers/alloca/AllocaTable/AllocaTable.h"
#include "src/IR/initializers/GlobalTypeInitializer/GlobalTypeInitializer.h"
#include "src/IR/initializers/GlobalVariableInitializer/GlobalVariableInitializer.h"
#include "src/IR/irGen/statements/BringStatementGenerationStrategy/BringStatementGenerationStrategy.h"
#include "src/IR/irGen/statements/ClassStatementGenerationStrategy/ClassStatementGenerationStrategy.h"
#include "src/IR/irGen/statements/FunctionStatementGenerationStrategy/FunctionStatementGenerationStrategy.h"
#include "src/IR/irGen/statements/ModuleStatementGenerationStrategy/ModuleStatementGenerationStrategy.h"
#include "src/IR/irGen/statements/StatementGenerationFactory.h"
#include "src/IR/irGen/statements/VariableDeclarationStatementGenerationStrategy/VariableDeclarationStatementGenerationStrategy.h"
#include "src/IR/logger/LLVMLogger.h"
#include "src/SemanticAnalyzer/BinderKindUtils.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundBinaryExpression/BoundBinaryExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundLiteralExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundParenthesizedExpression/BoundParenthesizedExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundUnaryExpression/BoundUnaryExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundVariableExpression/BoundVariableExpression.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundBlockStatement/BoundBlockStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundBringStatement/BoundBringStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundExpressionStatement/BoundExpressionStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/SemanticAnalyzer/SemanticAnalyzer.h"
#include "src/SemanticAnalyzer/SyntaxBinder/BoundGlobalScope/BoundGlobalScope.h"
#include "src/common/Common.h"
#include "src/compiler/AOTCompiler/ObjectFile/ObjectFile.h"
#include "src/syntax/CompilationUnitSyntax.h"
#include "src/utils/Utils.h"
#include "utils/fileSaver/bc-file/BCFileSaveStrategy.h"
#include "utils/fileSaver/ll-file/LLFileSaveStrategy.h"
#include "utils/fileSaver/o-file/OFileSaveStrategy.h"

using namespace FLOWWING::IR::CONSTANTS;

// clang-format off
#include "src/diagnostics/Diagnostic/diagnostic_push.h"
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
#include "utils/DirectoryUtils.h"
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
#include <llvm/Linker/Linker.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/SourceMgr.h>

// JIT
#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/Support/raw_ostream.h>
#include "src/diagnostics/Diagnostic/diagnostic_pop.h"
// clang-format on

#include <sstream>

class IRGenerator {
public:
  IRGenerator(int environment, FlowWing::DiagnosticHandler *diagnosticHandler,
              std::unordered_map<std::string, BoundFunctionDeclaration *>
                  boundedUserFunctions,
              std::string outputFilePath,
              const std::string sourceFileName = FLOWWING_GLOBAL_ENTRY_POINT);

  int executeGeneratedCode();
  std::shared_ptr<BoundGlobalScope> _previousGlobalScope = nullptr;

  void generateEvaluateGlobalStatement(
      BoundBlockStatement *blockStatement,
      std::string blockName = FLOWWING_GLOBAL_ENTRY_POINT);

  void defineClass(BoundClassStatement *boundClassStatement);

  std::unique_ptr<IRParser> &getIRParserPtr();
  void setModuleCount(int count);
  int32_t hasErrors() const;

private:
  llvm::LLVMContext *TheContext;
  llvm::Module *TheModule;
  llvm::IRBuilder<> *Builder;

  int8_t m_hasTempDirectories = EXIT_SUCCESS;

  LLVMLogger *_llvmLogger;

  std::unique_ptr<IRParser> _irParser;

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
