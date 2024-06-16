#ifndef __FLOWWING_FUNCTION_STATEMENT_STRATEGY_H__
#define __FLOWWING_FUNCTION_STATEMENT_STRATEGY_H__

#include "../../../../bind/BoundFunctionDeclaration/BoundFunctionDeclaration.h"
#include "../../Types/LLVMType/LLVMObjectType/LLVMObjectType.h"
#include "../../Types/LLVMType/LLVMPrimitiveType/LLVMPrimitiveType.h"
#include "../../expressions/ContainerAssignmentExpressionGenerationStrategy/ContainerAssignmentExpressionGenerationStrategy.h"
#include "../../expressions/ObjectExpressionGenerationStrategy/ObjectExpressionGenerationStrategy.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"
#include "../VariableDeclarationStatementGenerationStrategy/VariableDeclarationStatementGenerationStrategy.h"

class FunctionStatementGenerationStrategy : public StatementGenerationStrategy {
public:
  FunctionStatementGenerationStrategy(CodeGenerationContext *context);
  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;

  llvm::Value *generateStatementOnFly(BoundFunctionDeclaration *node,
                                      std::vector<llvm::Value *> callArgs);

  void declareVariables(BoundStatement *statement);
  void declareVariables(BoundNode *statement);

  llvm::Value *generate(BoundStatement *statement,
                        std::vector<std::string> classParams = {},
                        llvm::Type *classType = nullptr,
                        std::vector<std::string> classVariables = {});

private:
  std::unique_ptr<VariableDeclarationStatementGenerationStrategy>
      _variableDeclarationStatementGenerationStrategy;
};

#endif // __FLOWWING_VARIABLE_EXPRESSION_STRATEGY_H__
