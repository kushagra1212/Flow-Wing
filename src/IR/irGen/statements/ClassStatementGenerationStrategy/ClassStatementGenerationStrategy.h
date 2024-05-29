#ifndef __FLOWWING_CLASS_STATEMENT_STRATEGY_H__
#define __FLOWWING_CLASS_STATEMENT_STRATEGY_H__

#include "../../../../bind/BoundClassStatement/BoundClassStatement.h"
#include "../../Types/Class.h"
#include "../../Types/LLVMType/LLVMObjectType/LLVMObjectType.h"
#include "../CustomTypeStatementGenerationStrategy/CustomTypeStatementGenerationStrategy.h"
#include "../FunctionDeclarationGenerationStrategy/FunctionDeclarationGenerationStrategy.h"
#include "../FunctionStatementGenerationStrategy/FunctionStatementGenerationStrategy.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"

class ClassStatementGenerationStrategy : public StatementGenerationStrategy {
public:
  ClassStatementGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;
};

#endif //__FLOWWING_CLASS_STATEMENT_STRATEGY_H__
