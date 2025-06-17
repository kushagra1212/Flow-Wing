#ifndef __FLOWWING__UNARY_EXPRESSION_GENERATION_STRATEGY_H__
#define __FLOWWING__UNARY_EXPRESSION_GENERATION_STRATEGY_H__

#include "../../../context/utils/DynamicValueHandler/DynamicValueHandler.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"
#include "../utility.h"

class UnaryExpressionGenerationStrategy : public ExpressionGenerationStrategy {
public:
  UnaryExpressionGenerationStrategy(CodeGenerationContext *context);

  SyntaxKindUtils::SyntaxKind selectOperationStrategy(llvm::Value *value,
                                                      int8_t isClassType);

  void declare(BoundExpression *expression);
  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  llvm::Value *performOperation(llvm::Value *value,
                                BinderKindUtils::BoundUnaryOperatorKind unaryOp,
                                bool isClassType = false,
                                bool skipUnsupportedOperation = false);
};

#endif // __FLOWWING__UNARY_EXPRESSION_GENERATION_STRATEGY_H__
