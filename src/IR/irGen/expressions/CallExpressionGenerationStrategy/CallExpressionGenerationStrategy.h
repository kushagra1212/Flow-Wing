#ifndef __FLOWWING_CALL_EXPRESSION_STRATEGY_H__
#define __FLOWWING_CALL_EXPRESSION_STRATEGY_H__

#include "../../../../bind/BoundCallExpression/BoundCallExpression.h"
#include "../../../../bind/BoundFunctionDeclaration/BoundFunctionDeclaration.h"
#include "../../../../bind/BoundTypeExpression/BoundArrayTypeExpression/BoundArrayTypeExpression.h"
#include "../../../../bind/BoundTypeExpression/BoundObjectTypeExpression/BoundObjectTypeExpression.h"
#include "../../statements/ContainerDeclarationStatementGenerationStrategy/ContainerDeclarationStatementGenerationStrategy.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"
#include "../LiteralExpressionGenerationStrategy/LiteralExpressionGenerationStrategy.h"
class CallExpressionGenerationStrategy : public ExpressionGenerationStrategy {
public:
  CallExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  llvm::Value *buildInFunctionCall(BoundCallExpression *callExpression);
  llvm::Value *
  handleInBuiltFunctionReturnValue(llvm::Value *res,
                                   BoundCallExpression *callExpression);
  void handleInBuiltFunctionCall(BoundCallExpression *callExpression,
                                 llvm::Value *&val);
  llvm::Value *handlePrintFunction(llvm::Value *&value);
  llvm::Value *userDefinedFunctionCall(BoundCallExpression *callExpression);
  void declare(BoundExpression *expression);

  llvm::Value *generateCommonCallExpression(
      BoundCallExpression *callExpression, llvm::Function *calleeFunction,
      std::__1::vector<llvm::Value *> &classArg, llvm::Type *_classType,
      llvm::Value *_classPtr, llvm::Value *calleeValue = nullptr);

  llvm::Value *
  handleExpression(llvm::Function *calleeFunction, uint64_t callArgIndex,
                   uint64_t llvmArgsIndex, BoundCallExpression *callExpression,
                   llvm::Value *&rhsValue, llvm::FunctionType *functionType,
                   const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs,
                   bool &retFlag);

  llvm::Value *
  handlePremitive(llvm::Value *&rhsValue, BoundCallExpression *callExpression,
                  uint64_t callArgIndex, uint64_t llvmArgsIndex,
                  const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs,
                  llvm::Argument *arg, bool &retFlag);

  llvm::Value *handleBracketExpression(
      const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs,
      uint64_t callArgIndex, uint64_t llvmArgsIndex,
      BoundCallExpression *callExpression, llvm::Argument *arg,
      llvm::Value *&rhsValue, bool &retFlag);

  llvm::Value *handleObjectExpression(
      const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs,
      uint64_t callArgIndex, uint64_t llvmArgsIndex,
      BoundCallExpression *callExpression, llvm::Argument *arg,
      llvm::Value *&rhsValue, bool &retFlag);
  llvm::Value *handleIndexExpression(
      llvm::Value *&rhsValue, BoundCallExpression *callExpression,
      uint64_t callArgIndex, uint64_t llvmArgsIndex,
      llvm::FunctionType *functionType,
      const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs,
      llvm::Argument *arg, bool &retFlag);
  llvm::Value *handleVariableExpression(
      llvm::Value *&rhsValue, BoundCallExpression *callExpression,
      uint64_t callArgIndex, uint64_t llvmArgsIndex,
      llvm::FunctionType *functionType,
      const std::vector<std::unique_ptr<LLVMType>> &llvmArrayArgs,
      llvm::Argument *arg, bool &retFlag);

  void handleArrayArgs(const std::vector<llvm::Type *> &paramTypes,
                       const int &i, const std::vector<llvm::Value *> &args,
                       BoundCallExpression *callExpression, int &retFlag);

  llvm::Value *printArray(llvm::ArrayType *arrayType, llvm::Type *elementType,
                          llvm::Value *v, llvm::IRBuilder<> &Builder);

  llvm::Value *printArrayAtom(llvm::ArrayType *&arrayType, llvm::Value *&v,
                              const std::vector<uint64_t> &actualSizes,
                              llvm::Type *&elementType,
                              llvm::IRBuilder<> &Builder);

  llvm::Value *printObject(llvm::Value *outerElementPtr,
                           llvm::StructType *parObjType,
                           llvm::IRBuilder<> &Builder);

  llvm::Type *isGlobalArray(llvm::Value *value);

  llvm::Type *isLocalArray(llvm::Value *value);
  void printUnit(const std::string &unit, const std::string &unitName,
                 llvm::IRBuilder<> &Builder);

  llvm::Value *getUnit(const std::string &unit, const std::string &unitName,
                       llvm::IRBuilder<> &Builder);

  void printString(llvm::Value *value, llvm::Type *elementType,
                   llvm::IRBuilder<> &Builder);
  void printPremitives(llvm::Value *&value, llvm::IRBuilder<> &Builder);

private:
  bool _isGlobal = false;
  bool _isDeclarationNeeded = false;
};

#endif // __FLOWWING_CALL_EXPRESSION_STRATEGY_H__
