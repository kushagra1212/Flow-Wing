#ifndef __FLOWWING_CALL_EXPRESSION_STRATEGY_H__
#define __FLOWWING_CALL_EXPRESSION_STRATEGY_H__

#include "../../../../bind/BoundCallExpression/BoundCallExpression.h"
#include "../../../../bind/BoundFunctionDeclaration/BoundFunctionDeclaration.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

class CallExpressionGenerationStrategy : public ExpressionGenerationStrategy {
public:
  CallExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  llvm::Value *buildInFunctionCall(BoundCallExpression *callExpression);
  llvm::Value *userDefinedFunctionCall(BoundCallExpression *callExpression);

  void handleArrayArgs(const std::vector<llvm::Type *> &paramTypes,
                       const int &i, const std::vector<llvm::Value *> &args,
                       BoundCallExpression *callExpression, int &retFlag);

  llvm::Value *printArray(llvm::ArrayType *arrayType, llvm::Type *elementType,
                          llvm::Value *v);

  llvm::Value *printArrayAtom(llvm::ArrayType *&arrayType, llvm::Value *&v,
                              const std::vector<size_t> &sizes,
                              std::vector<llvm::Value *> &indices, int64_t i,
                              llvm::Type *&elementType);
  llvm::Type *isGlobalArray(llvm::Value *value);

  llvm::Type *isLocalArray(llvm::Value *value);
  void printUnit(const std::string &unit, const std::string &unitName);

  llvm::Value *getUnit(const std::string &unit, const std::string &unitName);
};

#endif // __FLOWWING_CALL_EXPRESSION_STRATEGY_H__
