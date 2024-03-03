#ifndef __FLOWWING_RETURN_STATEMENT_STRATEGY_H__
#define __FLOWWING_RETURN_STATEMENT_STRATEGY_H__

#include "../../../../bind/BoundReturnStatement/BoundReturnStatement.h"
#include "../../Types/LLVMType/LLVMObjectType/LLVMObjectType.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"

class ReturnStatementGenerationStrategy : public StatementGenerationStrategy {
 public:
  ReturnStatementGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;
};

#endif  //__FLOWWING_RETURN_STATEMENT_STRATEGY_H__
