#ifndef __FLOWWING_CONTAINER_STATEMENT_STRATEGY_H__
#define __FLOWWING_CONTAINER_STATEMENT_STRATEGY_H__

#include "../../../../bind/BoundContainerStatement/BoundContainerStatement.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"

class ContainerStatementGenerationStrategy
    : public StatementGenerationStrategy {

  size_t getActualContainerSize(BoundContainerStatement *containerStatement);
  void generateContainerItems(BoundContainerExpression *containerExpression,
                              std::vector<llvm::Constant *> &items,
                              llvm::Type *elementType,
                              const std::string &containerName);

public:
  ContainerStatementGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;
};

#endif //__FLOWWING_CONTAINER_STATEMENT_STRATEGY_H__
