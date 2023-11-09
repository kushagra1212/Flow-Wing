#ifndef IRGENERATOR_H
#define IRGENERATOR_H

#include "../../IR/handlers/alloca/AllocaChain/AllocaChain.h"
#include "../../IR/handlers/alloca/AllocaHandler.h"
#include "../../IR/handlers/alloca/AllocaTable/AllocaTable.h"
#include "../../IR/handlers/value/NamedValueTable/NamedValueTable.h"
#include "../../IR/handlers/value/ValueChain/ValueChain.h"
#include "../../IR/handlers/value/ValueHandler.h"
#include "../../IR/mappers/TypeMapper/TypeMapper.h"
#include "../../IR/strategies/BinaryOperationStrategy/BinaryOperationStrategy.h"
#include "../../IR/strategies/BinaryOperationStrategy/BoolBinaryOperationStrategy/BoolBinaryOperationStrategy.h"
#include "../../IR/strategies/BinaryOperationStrategy/DoubleBinaryOperationStrategy/DoubleBinaryOperationStrategy.h"
#include "../../IR/strategies/BinaryOperationStrategy/Int32BinaryOperationStrategy/Int32BinaryOperationStrategy.h"
#include "../../IR/strategies/BinaryOperationStrategy/StringBinaryOperationStrategy/StringBinaryOperationStrategy.h"
#include "../IRUtils/IRUtils.h"
using namespace FLOWWING::IR::CONSTANTS;

class IRGenerator {

public:
  IRGenerator(
      int environment, DiagnosticHandler *diagnosticHandler,
      std::map<std::string, BoundFunctionDeclaration *> boundedUserFunctions,
      const std::string sourceFileName = FLOWWING_GLOBAL_ENTRY_POINT);
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
      std::string blockName = FLOWWING_GLOBAL_ENTRY_POINT);

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

  llvm::Value *handleGlobalVariableExpression(const std::string &variableName,
                                              llvm::GlobalVariable *variable);

private:
  llvm::LLVMContext *TheContext;
  llvm::Module *TheModule;
  llvm::IRBuilder<> *Builder;

  TypeMapper *_typeMapper;
  LLVMLogger *_llvmLogger;

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
  llvm::StructType *_dynamicType;

  std::unique_ptr<ValueChain> _namedValueChain;
  std::unique_ptr<AllocaChain> _allocaChain;

  std::unique_ptr<CodeGenerationContext> _codeGenerationContext;

  std::unique_ptr<Int32BinaryOperationStrategy> _int32BinaryOperationStrategy;
  std::unique_ptr<BoolBinaryOperationStrategy> _boolBinaryOperationStrategy;
  std::unique_ptr<DoubleBinaryOperationStrategy> _doubleBinaryOperationStrategy;
  std::unique_ptr<StringBinaryOperationStrategy> _stringBinaryOperationStrategy;
  std::unique_ptr<Int32TypeConverter> _int32TypeConverter;
  std::unique_ptr<DoubleTypeConverter> _doubleTypeConverter;
  std::unique_ptr<StringTypeConverter> _stringTypeConverter;
  std::unique_ptr<BoolTypeConverter> _boolTypeConverter;
  std::unique_ptr<TypeSpecificValueVisitor> _typeSpecificValueVisitor;
};

#endif // IRGENERATOR_H
