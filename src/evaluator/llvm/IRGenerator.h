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
  void updateModule();

  llvm::Value *generateEvaluateExpressionStatement(BoundExpression *node);
  llvm::Value *generateEvaluateLiteralExpressionFunction(BoundExpression *node);
  llvm::Value *generateEvaluateUnaryExpressionFunction(BoundExpression *node);

  llvm::Value *
  generateEvaluateVariableExpressionFunction(BoundExpression *node);
  llvm::Value *
  generateEvaluateAssignmentExpressionFunction(BoundExpression *node);
  llvm::Value *
  generateEvaluateBinaryExpressionFunction(BoundBinaryExpression *node);
  llvm::Value *generateEvaluateBlockStatement(llvm::BasicBlock *basicBlock,
                                              llvm::BasicBlock *returnBlock,
                                              BoundBlockStatement *node);
  llvm::Value *generateEvaluateStatement(llvm::BasicBlock *basicBlock,
                                         llvm::BasicBlock *returnBlock,
                                         BoundStatement *node);

  llvm::Value *
  generateEvaluateVariableDeclaration(BoundVariableDeclaration *node);

  std::string executeGeneratedCode();
  std::shared_ptr<BoundScopeGlobal> getRoot();

  std::shared_ptr<BoundScopeGlobal> _previousGlobalScope = nullptr;

  void generateEvaluateGlobalStatement(BoundStatement *node);

  llvm::Value *evaluateIfStatement(llvm::BasicBlock *basicBlock,
                                   llvm::BasicBlock *returnBlock,
                                   BoundStatement *node);

  llvm::Value *evaluateWhileStatement(llvm::BasicBlock *basicBlock,
                                      llvm::BasicBlock *returnBlock,
                                      BoundWhileStatement *node);
  llvm::Value *generateEvaluateCallExpression(BoundCallExpression *node);
  llvm::Constant *getNull();
  llvm::Value *handleBuiltInfuntions(BoundCallExpression *callExpression);

private:
  std::unique_ptr<llvm::LLVMContext> TheContext;
  std::unique_ptr<llvm::Module> TheModule;
  std::unique_ptr<llvm::IRBuilder<>> Builder;

  std::stack<std::map<std::string, llvm::Value *>> _NamedValuesStack;
  std::stack<std::map<std::string, llvm::AllocaInst *>> _NamedValuesAllocaStack;
};

#endif // IRGENERATOR_H
