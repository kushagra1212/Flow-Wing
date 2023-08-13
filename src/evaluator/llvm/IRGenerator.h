#ifndef IRGENERATOR_H
#define IRGENERATOR_H

#include "../../Common.h"
#include "../../bind/Binder/Binder.h"
#include "../../bind/Binder/BoundScopeGlobal/BoundScopeGlobal.h"
#include "../../bind/BinderKindUtils.h"
#include "../../bind/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "../../bind/BoundBinaryExpression/BoundBinaryExpression.h"
#include "../../bind/BoundBlockStatement/BoundBlockStatement.h"
#include "../../bind/BoundExpression.h"
#include "../../bind/BoundExpressionStatement/BoundExpressionStatement.h"
#include "../../bind/BoundLiteralExpression/BoundLiteralExpression.h"
#include "../../bind/BoundParenthesizedExpression/BoundParenthesizedExpression.h"
#include "../../bind/BoundStatement/BoundStatement.h"
#include "../../bind/BoundUnaryExpression/BoundUnaryExpression.h"
#include "../../bind/BoundVariableExpression/BoundVariableExpression.h"
#include "../../syntax/CompilationUnitSyntax.h"
#include "llvm-14/llvm/IR/Type.h"
#include <llvm-14/llvm/ADT/APInt.h>
#include <llvm-14/llvm/ADT/StringRef.h>
#include <llvm-14/llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm-14/llvm/ExecutionEngine/GenericValue.h>
#include <llvm-14/llvm/IR/IRBuilder.h>
#include <llvm-14/llvm/IR/IRPrintingPasses.h>
#include <llvm-14/llvm/IR/InstrTypes.h>
#include <llvm-14/llvm/IR/Instruction.h>
#include <llvm-14/llvm/IR/Instructions.h>
#include <llvm-14/llvm/IR/LLVMContext.h>
#include <llvm-14/llvm/IR/Module.h>
#include <llvm-14/llvm/IR/Verifier.h>
#include <llvm-14/llvm/IRReader/IRReader.h>
#include <llvm-14/llvm/Support/MemoryBuffer.h>
#include <llvm-14/llvm/Support/raw_ostream.h>
#include <llvm-14/llvm/Transforms/Utils/Cloning.h>

#include <llvm-14/llvm/Support/Error.h>
#include <llvm-14/llvm/Support/SourceMgr.h>

#include <llvm-14/llvm/IRReader/IRReader.h>
// ExecutionEngine
#include <llvm-14/llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm-14/llvm/ExecutionEngine/GenericValue.h>
#include <llvm-14/llvm/ExecutionEngine/Interpreter.h>
#include <llvm-14/llvm/ExecutionEngine/MCJIT.h>
#include <llvm-14/llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm-14/llvm/IR/LegacyPassManager.h>
#include <llvm-14/llvm/IR/Module.h>
#include <llvm-14/llvm/Support/SourceMgr.h>
#include <llvm-14/llvm/Support/TargetSelect.h>

#include "llvm-14/llvm/IR/Constants.h"
#include "llvm/IR/Value.h"
class IRGenerator {

  std::unique_ptr<llvm::Module> _getModule();

public:
  IRGenerator(IRGenerator *previousEvaluator,
              CompilationUnitSyntax *compilationUnit);
  void printIR();
  //   void generateIR();
  //   void verifyIR();
  //   void optimizeIR();
  //   void runIR();

  void defineStandardFunctions();

  void define_StringLength();

  llvm::Value *generateEvaluateExpressionStatement(BoundExpression *node);
  llvm::Value *generateEvaluateLiteralExpressionFunction(BoundExpression *node);
  llvm::Value *generateEvaluateUnaryExpressionFunction(BoundExpression *node);

  llvm::Value *
  generateEvaluateVariableExpressionFunction(BoundExpression *node);
  llvm::Value *
  generateEvaluateAssignmentExpressionFunction(BoundExpression *node);
  llvm::Value *
  generateEvaluateBinaryExpressionFunction(BoundBinaryExpression *node);
  llvm::Value *generateEvaluateBlockStatement(BoundBlockStatement *node);
  llvm::Value *generateEvaluateStatement(BoundStatement *node);

  void executeGeneratedCode();
  CompilationUnitSyntax *compilation_unit;
  BoundScopeGlobal *getRoot();
  IRGenerator *previous = nullptr;
  BoundScopeGlobal *root = nullptr;

private:
  std::unique_ptr<llvm::LLVMContext> TheContext;
  std::unique_ptr<llvm::Module> TheModule;
  std::unique_ptr<llvm::IRBuilder<>> Builder;
  std::map<std::string, llvm::Value *> NamedValues;
};

#endif // IRGENERATOR_H
