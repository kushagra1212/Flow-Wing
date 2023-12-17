#ifndef __FLOWWING__FILL_EXPRESSION_GENERATION_STRATEGY_H__
#define __FLOWWING__FILL_EXPRESSION_GENERATION_STRATEGY_H__

#include "../../../../bind/BoundFillExpression/BoundFillExpression.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

class FillExpressionGenerationStrategy : public ExpressionGenerationStrategy {
public:
  FillExpressionGenerationStrategy(CodeGenerationContext *context,
                                   uint64_t actualSize, llvm::Type *elementType,
                                   const std::string &containerName);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  llvm::Value *createGlobalExpression(llvm::Type *arrayType,
                                      llvm::GlobalVariable *_globalVariable,
                                      BoundFillExpression *fillExpression);

  bool canGenerateExpression(BoundExpression *expression);

private:
  uint64_t _actualSize;
  llvm::Type *_elementType;
  std::string _containerName;

  //  Variables for the fill expression
  uint64_t _sizeToFill;
  llvm::Value *_elementToFill;
};

#endif // __FLOWWING__FILL_EXPRESSION_GENERATION_STRATEGY_H__
