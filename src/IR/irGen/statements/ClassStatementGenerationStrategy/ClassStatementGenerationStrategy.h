#ifndef __FLOWWING_CLASS_STATEMENT_STRATEGY_H__
#define __FLOWWING_CLASS_STATEMENT_STRATEGY_H__

#include "../../../../SemanticAnalyzer/BoundStatements/BoundClassStatement/BoundClassStatement.h"
#include "../../Types/FlowWingClass.h"
#include "../../Types/LLVMType/LLVMObjectType/LLVMObjectType.h"
#include "../CustomTypeStatementGenerationStrategy/CustomTypeStatementGenerationStrategy.h"
#include "../FunctionDeclarationGenerationStrategy/FunctionDeclarationGenerationStrategy.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"

class ClassStatementGenerationStrategy : public StatementGenerationStrategy {
public:
  ClassStatementGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;
  llvm::Value *generateClassType(BoundStatement *statement);
  llvm::Value *generateClassTypeForBring(BoundStatement *statement);
};

#endif //__FLOWWING_CLASS_STATEMENT_STRATEGY_H__
