#ifndef __FLOWWING_INDEX_EXPRESSION_STRATEGY_H__
#define __FLOWWING_INDEX_EXPRESSION_STRATEGY_H__

#include "../../../../bind/BoundIndexExpression/BoundIndexExpression.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

class IndexExpressionGenerationStrategy : public ExpressionGenerationStrategy {
public:
  IndexExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  llvm::Value *handleGlobalVariable(llvm::GlobalVariable *variable,
                                    std::string variableName);

  llvm::Value *handleArrayTypeIndexing();

  void verifyBounds(llvm::Value *index, llvm::ConstantInt *actualSize);

  const bool canGenerateExpression(const std::string &variableName);

private:
  std::vector<llvm::Value *> _indices;
  std::vector<llvm::ConstantInt *> _actualSizes;
  std::string _variableName;
  llvm::Type *_arrayElementType;
  llvm::Value *_variable;
  llvm::ArrayType *_arrayType;
};

#endif // __FLOWWING_INDEX_EXPRESSION_STRATEGY_H__
