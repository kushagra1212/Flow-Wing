#ifndef __FLOWWING__BRACKETED_EXPRESSION_GENERATION_STRATEGY_H__
#define __FLOWWING__BRACKETED_EXPRESSION_GENERATION_STRATEGY_H__

#include "../../../../bind/BoundBracketedExpression/BoundBracketedExpression.h"
#include "../../../../bind/BoundContainerExpression/BoundContainerExpression.h"
#include "../../../../bind/BoundFillExpression/BoundFillExpression.h"
#include "../ContainerExpressionGenerationStrategy/ContainerExpressionGenerationStrategy.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"
#include "../FillExpressionGenerationStrategy/FillExpressionGenerationStrategy.h"

class BracketedExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  BracketedExpressionGenerationStrategy(CodeGenerationContext *context);

  void setPreviousGlobalVariable(llvm::GlobalVariable *previousGlobalVariable);
  void setAllocatedVariable(llvm::AllocaInst *allocaInst);
  void setContainerName(const std::string &containerName);

  llvm::Value *
  assignBracketExpression(BoundBracketedExpression *&bracketedExpression,
                          llvm::Value *&lhsPtr, llvm::ArrayType *lhsType,
                          std::string &containerName);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  // Specialized for BoundBracketedExpression

private:
  llvm::GlobalVariable *_previousGlobalVariable = nullptr;
  std::string _containerName;
  llvm::AllocaInst *_allocaInst = nullptr;
};

#endif // __FLOWWING__BRACKETED_EXPRESSION_GENERATION_STRATEGY_H__
