#ifndef __FLOWWING_FUNCTION_DECLARATION_STRATEGY_H__
#define __FLOWWING_FUNCTION_DECLARATION_STRATEGY_H__

#include "../../../../bind/BoundFunctionDeclaration/BoundFunctionDeclaration.h"
#include "../../../../bind/BoundTypeExpression/BoundArrayTypeExpression/BoundArrayTypeExpression.h"
#include "../../../../bind/BoundTypeExpression/BoundObjectTypeExpression/BoundObjectTypeExpression.h"
#include "../../../../bind/BoundTypeExpression/BoundTypeExpression.h"
#include "../../../../bind/BoundVariableExpression/BoundArrayVariableExpression/BoundArrayVariableExpression.h"
#include "../../Types/LLVMType/LLVMObjectType/LLVMObjectType.h"
#include "../../Types/LLVMType/LLVMPrimitiveType/LLVMPrimitiveType.h"
#include "../CustomTypeStatementGenerationStrategy/CustomTypeStatementGenerationStrategy.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"

class FunctionDeclarationGenerationStrategy
    : public StatementGenerationStrategy {
public:
  FunctionDeclarationGenerationStrategy(CodeGenerationContext *context);
  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;
  llvm::Function *generate(BoundStatement *statement,
                           std::vector<llvm::Type *> classArgs = {},
                           std::string className = "");

  llvm::StructType *
  getStructType(BoundObjectTypeExpression *objectTypeExpression,
                std::__1::string &className);
};

#endif // __FLOWWING_FUNCTION_DECLARATION_STRATEGY_H__
