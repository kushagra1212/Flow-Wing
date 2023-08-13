#ifndef IRGENERATOR_H
#define IRGENERATOR_H

#include "../IRUtils/IRUtils.h"

class IRGenerator {

  std::unique_ptr<llvm::Module>
  _getModule(const std::vector<std::string> &irFilePaths);

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

  llvm::Function *generateEvaluateExpressionStatement(BoundExpression *node);
  llvm::Function *
  generateEvaluateLiteralExpressionFunction(BoundExpression *node);
  llvm::Function *
  generateEvaluateUnaryExpressionFunction(BoundExpression *node);

  llvm::Function *
  generateEvaluateVariableExpressionFunction(BoundExpression *node);
  llvm::Function *
  generateEvaluateAssignmentExpressionFunction(BoundExpression *node);
  llvm::Function *
  generateEvaluateBinaryExpressionFunction(BoundBinaryExpression *node);
  llvm::Function *generateEvaluateBlockStatement(BoundBlockStatement *node);
  llvm::Function *generateEvaluateStatement(BoundStatement *node);

  void executeGeneratedCode();
  CompilationUnitSyntax *compilation_unit;
  BoundScopeGlobal *getRoot();
  IRGenerator *previous = nullptr;
  BoundScopeGlobal *root = nullptr;

  llvm::Function *getFunction(llvm::Type *Result, std::string name,
                              bool isVarArg);

private:
  std::unique_ptr<llvm::LLVMContext> TheContext;
  std::unique_ptr<llvm::Module> TheModule;
  std::unique_ptr<llvm::IRBuilder<>> Builder;
  std::map<std::string, llvm::Value *> NamedValues;
};

#endif // IRGENERATOR_H
