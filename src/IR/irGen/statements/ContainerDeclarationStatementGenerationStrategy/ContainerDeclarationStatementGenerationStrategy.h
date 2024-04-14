#ifndef __FLOWWING_CONTAINER_STATEMENT_STRATEGY_H__
#define __FLOWWING_CONTAINER_STATEMENT_STRATEGY_H__

#include "../../../../bind/BoundBracketedExpression/BoundBracketedExpression.h"
#include "../../../../bind/BoundContainerStatement/BoundContainerStatement.h"
#include "../../../../bind/BoundTypeExpression/BoundArrayTypeExpression/BoundArrayTypeExpression.h"
#include "../../../../bind/BoundTypeExpression/BoundObjectTypeExpression/BoundObjectTypeExpression.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"

class ContainerDeclarationStatementGenerationStrategy
    : public StatementGenerationStrategy {
  void calcActualContainerSize(BoundArrayTypeExpression *arrayTypeExpression);

public:
  ContainerDeclarationStatementGenerationStrategy(
      CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;

  llvm::Value *generateBracketGlobalExpression(
      BoundBracketedExpression *bracketedExpression);

  llvm::Value *
  generateBracketLocalExpression(BoundBracketedExpression *bracketedExpression);

  llvm::Value *generateCommonStatement(std ::vector<uint64_t> actualSizes,
                                       llvm::Type *arrayElementType,
                                       const std::string &containerName,
                                       BoundExpression *initializer);

  const bool canGenerateCallExpression(BoundExpression *callExp);

  llvm::Value *
  generateCommonStatement(BoundArrayTypeExpression *arrayTypeExpression,
                          const std::string &containerName,
                          BoundExpression *initializer);

  const bool canGenerateVariableExpression(BoundExpression *callExp);

  inline auto setAllocaInst(llvm::Value *allocaInst) {
    _allocaInst = allocaInst;
  }

  inline auto setElementType(llvm::Type *elementType) {
    _elementType = elementType;
  }

private:
  std::vector<uint64_t> _actualSizes;
  llvm::Type *_elementType;
  std::string _containerName;
  llvm::LoadInst *_loadedValue;
  llvm::Value *_allocaInst;
};

#endif //__FLOWWING_CONTAINER_STATEMENT_STRATEGY_H__
