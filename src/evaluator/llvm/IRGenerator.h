#ifndef IRGENERATOR_H
#define IRGENERATOR_H

#include "../IRUtils/IRUtils.h"

class IRGenerator {

  std::unique_ptr<llvm::Module>
  _getModule(const std::vector<std::string> &irFilePaths);

public:
  IRGenerator();
  void printIR();
  //   void generateIR();
  //   void verifyIR();
  //   void optimizeIR();
  //   void runIR();

  void defineStandardFunctions();

  void define_StringLength();

  llvm::Function *
  generateEvaluateExpressionStatement(std::shared_ptr<BoundExpression> node);
  llvm::Function *generateEvaluateLiteralExpressionFunction(
      std::shared_ptr<BoundExpression> node);
  llvm::Function *generateEvaluateUnaryExpressionFunction(
      std::shared_ptr<BoundExpression> node);

  llvm::Function *generateEvaluateVariableExpressionFunction(
      std::shared_ptr<BoundExpression> node);
  llvm::Function *generateEvaluateAssignmentExpressionFunction(
      std::shared_ptr<BoundExpression> node);
  llvm::Function *generateEvaluateBinaryExpressionFunction(
      std::shared_ptr<BoundBinaryExpression> node);
  llvm::Function *
  generateEvaluateBlockStatement(std::shared_ptr<BoundBlockStatement> node);
  llvm::Function *
  generateEvaluateStatement(std::shared_ptr<BoundStatement> node);

  void executeGeneratedCode();
  std::shared_ptr<BoundScopeGlobal> getRoot();

  std::shared_ptr<BoundScopeGlobal> _previousGlobalScope = nullptr;

  llvm::Function *getFunction(llvm::Type *Result, std::string name,
                              bool isVarArg);

private:
  std::unique_ptr<llvm::LLVMContext> TheContext;
  std::unique_ptr<llvm::Module> TheModule;
  std::unique_ptr<llvm::IRBuilder<>> Builder;
  std::map<std::string, llvm::Value *> NamedValues;
};

#endif // IRGENERATOR_H
