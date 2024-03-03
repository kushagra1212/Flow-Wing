#ifndef __FLOWWING__FILL_EXPRESSION_GENERATION_STRATEGY_H__
#define __FLOWWING__FILL_EXPRESSION_GENERATION_STRATEGY_H__

#include "../../../../bind/BoundFillExpression/BoundFillExpression.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

class FillExpressionGenerationStrategy : public ExpressionGenerationStrategy {
 public:
  FillExpressionGenerationStrategy(CodeGenerationContext *context,
                                   std::vector<uint64_t> actualSizes,
                                   llvm::Type *elementType,
                                   const std::string &containerName);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  llvm::Value *createGlobalExpression(llvm::Type *arrayType,
                                      llvm::GlobalVariable *_globalVariable);

  llvm::Value *createLocalExpression(llvm::Type *arrayType,
                                     llvm::AllocaInst *arrayAlloca);

  llvm::Value *createExpression(llvm::Type *arrayType, llvm::Value *v,
                                llvm::Value *elementToFill,
                                uint64_t sizeToFillVal);

  bool canGenerateExpression(BoundExpression *expression);
  llvm::Value *createExpressionAtom(llvm::Type *arrayType, llvm::Value *v,
                                    llvm::Value *elementToFill,
                                    uint64_t &sizeToFillVal,
                                    std::vector<llvm::Value *> &indices,
                                    uint64_t index);

 private:
  std::vector<uint64_t> _actualSizes;

  uint64_t _totalSize;

  llvm::Type *_elementType;
  std::string _containerName;

  //  Variables for the fill expression

  llvm::Value *_elementToFill;
  uint64_t _sizeToFillInt;
  llvm::AllocaInst *_allocaInst;
};

#endif  // __FLOWWING__FILL_EXPRESSION_GENERATION_STRATEGY_H__
