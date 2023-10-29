#ifndef IRGENERATOR_H
#define IRGENERATOR_H

#include "../IRUtils/IRUtils.h"
using namespace ELANG::EVALUATOR::CONSTANTS;

class IRGenerator {

public:
  IRGenerator(
      int environment, DiagnosticHandler *diagnosticHandler,
      std::map<std::string, BoundFunctionDeclaration *> boundedUserFunctions,
      const std::string sourceFileName = ELANG_GLOBAL_ENTRY_POINT);
  void printIR();
  //   void generateIR();
  //   void verifyIR();
  //   void optimizeIR();
  //   void runIR();

  void mergeModules(llvm::Module *sourceFunction,
                    llvm::Module *destinationModule);
  void declareDependencyFunctions();
  void initializeGlobalVariables();
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
  llvm::Value *generateEvaluateBlockStatement(BoundBlockStatement *node);
  llvm::Value *generateEvaluateStatement(BoundStatement *node);

  llvm::Value *
  generateEvaluateVariableDeclaration(BoundVariableDeclaration *node);

  int executeGeneratedCode();

  std::shared_ptr<BoundScopeGlobal> _previousGlobalScope = nullptr;

  void generateEvaluateGlobalStatement(
      BoundBlockStatement *blockStatement,
      std::string blockName = ELANG_GLOBAL_ENTRY_POINT);

  llvm::Value *evaluateIfStatement(BoundStatement *node);

  llvm::Value *evaluateWhileStatement(BoundWhileStatement *node);

  llvm::Value *evaluateForStatement(BoundForStatement *node);
  llvm::Value *generateEvaluateCallExpression(BoundCallExpression *node);
  llvm::Value *handleBuiltInfuntions(BoundCallExpression *callExpression);

  void
  generateUserDefinedFunction(BoundFunctionDeclaration *functionDeclaration);
  void generateUserDefinedFunctionOnFly(
      BoundFunctionDeclaration *functionDeclaration,
      std::vector<llvm::Value *> args);
  llvm::Value *generateCallExpressionForUserDefinedFunction(
      BoundCallExpression *callExpression);

  std::unique_ptr<llvm::Module> &getModulePtr();
  std::unique_ptr<IRParser> &getIRParserPtr();
  void setModuleCount(int count);
  const int hasErrors() const;

  // Globals

  // Global Functions
  void handleGlobalFunctionDefinition(BoundFunctionDeclaration *userFunction);
  // Global Fuction Declaration
  void handleGlobalFunctionDeclaration(BoundFunctionDeclaration *node);

  // Global Bring Statements
  void handleGlobalBringStatement(BoundBringStatement *bringStatement);

  // Global Expression Statements
  void handleGlobalExpressionStatement(BoundExpressionStatement *node);
  // - Assignment Expression
  void handleGlobalAssignmentExpression(BoundAssignmentExpression *node);
  // - Variable Declaration
  void handleGlobalVariableDeclaration(BoundVariableDeclaration *node);

private:
  std::unique_ptr<llvm::LLVMContext> TheContext;
  std::unique_ptr<llvm::Module> TheModule;
  std::unique_ptr<llvm::IRBuilder<>> Builder;

  std::stack<std::map<std::string, llvm::Value *>> _NamedValuesStack;
  std::stack<std::map<std::string, llvm::AllocaInst *>> _NamedValuesAllocaStack;
  std::stack<std::pair<Utils::type, int>> _returnAllocaStack;

  std::map<std::string, BoundFunctionDeclaration *> _boundedUserFunctions;

  std::map<std::string,
           std::vector<std::pair<llvm::AllocaInst *, llvm::Value *>>>
      _functionsParameters;
  std::map<std::string, bool> _recursiveFunctionsMap;
  std::unique_ptr<IRUtils> _irUtils;
  std::unique_ptr<IRParser> _irParser;

  DiagnosticHandler *_diagnosticHandler;

  int showNewLineForRepl = 0;
  int _moduleCount = 0;
  int _environment;
  std::string _sourceFileName;
};

#endif // IRGENERATOR_H
