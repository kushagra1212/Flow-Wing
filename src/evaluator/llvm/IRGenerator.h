#ifndef IRGENERATOR_H
#define IRGENERATOR_H

#include "../IRUtils/IRUtils.h"

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
