#ifndef __FLOWWING__CONTAINER_EXPRESSION_GENERATION_STRATEGY_H__
#define __FLOWWING__CONTAINER_EXPRESSION_GENERATION_STRATEGY_H__

#include "../../../../bind/BoundContainerExpression/BoundContainerExpression.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

class ContainerExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  ContainerExpressionGenerationStrategy(CodeGenerationContext *context,
                                        uint64_t actualSize,
                                        llvm::Type *elementType,
                                        const std::string &containerName);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  // Specialized for BoundContainerExpression
  llvm::Value *
  createGlobalExpression(llvm::Type *arrayType,
                         llvm::GlobalVariable *_globalVariable,
                         BoundContainerExpression *containerExpression);

  llvm::Value *createExpression(llvm::Type *arrayType,
                                llvm::AllocaInst *_allocaInst,
                                BoundContainerExpression *containerExpression);

  const bool
  canGenerateExpression(BoundContainerExpression *containerExpression);

private:
  uint64_t _actualSize;
  llvm::Type *_elementType;
  std::string _containerName;
  uint64_t _sizeToFill;
};

#endif // __FLOWWING__CONTAINER_EXPRESSION_GENERATION_STRATEGY_H__
