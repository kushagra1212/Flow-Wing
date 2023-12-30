#ifndef __FLOWWING_CONTAINER_STATEMENT_STRATEGY_H__
#define __FLOWWING_CONTAINER_STATEMENT_STRATEGY_H__

#include "../../../../bind/BoundContainerStatement/BoundContainerStatement.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"

class ContainerStatementGenerationStrategy
    : public StatementGenerationStrategy {

  std::vector<uint64_t>
  getActualContainerSize(BoundContainerStatement *containerStatement);

public:
  ContainerStatementGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;
};

#endif //__FLOWWING_CONTAINER_STATEMENT_STRATEGY_H__
