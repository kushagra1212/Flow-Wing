#ifndef __FLOWWING__CONTAINER_EXPRESSION_GENERATION_STRATEGY_H__
#define __FLOWWING__CONTAINER_EXPRESSION_GENERATION_STRATEGY_H__

#include "../../../../SemanticAnalyzer/BoundExpressions/BoundContainerExpression/BoundContainerExpression.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

class ContainerExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  ContainerExpressionGenerationStrategy(CodeGenerationContext *context,
                                        std::vector<uint64_t> actualSizes,
                                        llvm::Type *elementType,
                                        const std::string &containerName);

  llvm::Value *generateExpression(BoundExpression *expression) override;

  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  // Specialized for BoundContainerExpression
  llvm::Value *
  createGlobalExpression(llvm::Type *arrayType,
                         llvm::GlobalVariable *_globalVariable,
                         BoundContainerExpression *containerExpression);

  llvm::Value *
  createLocalExpression(llvm::Type *arrayType, llvm::AllocaInst *v,
                        BoundContainerExpression *containerExpression);

  llvm::Value *createExpression(llvm::Type *arrayType, llvm::Value *v,
                                BoundContainerExpression *containerExpression);

  const bool
  canGenerateExpression(BoundContainerExpression *containerExpression);

  llvm::Value *
  createExpressionAtom(llvm::Type *&arrayType, llvm::Value *&v,
                       BoundContainerExpression *containerExpression,
                       std::vector<llvm::Value *> &indices, uint64_t index);

  inline auto setAllocaInst(llvm::Value *allocaInst) {
    _allocaInst = allocaInst;
  }

private:
  uint64_t _totalSize;
  std::vector<uint64_t> _actualSizes;
  llvm::Type *_elementType = nullptr;
  std::string _containerName;
  uint64_t _sizeToFill;
  bool _isGlobal;
  llvm::Value *_allocaInst = nullptr;
};

#endif // __FLOWWING__CONTAINER_EXPRESSION_GENERATION_STRATEGY_H__
