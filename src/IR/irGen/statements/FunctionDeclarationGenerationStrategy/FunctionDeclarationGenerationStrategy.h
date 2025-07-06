#ifndef __FLOWWING_FUNCTION_DECLARATION_STRATEGY_H__
#define __FLOWWING_FUNCTION_DECLARATION_STRATEGY_H__

#include "../../../../SemanticAnalyzer/BoundExpressions/BoundTypeExpression/BoundArrayTypeExpression/BoundArrayTypeExpression.h"
#include "../../../../SemanticAnalyzer/BoundExpressions/BoundTypeExpression/BoundFunctionTypeExpression/BoundFunctionTypeExpression.h"
#include "../../../../SemanticAnalyzer/BoundExpressions/BoundTypeExpression/BoundObjectTypeExpression/BoundObjectTypeExpression.h"
#include "../../../../SemanticAnalyzer/BoundExpressions/BoundTypeExpression/BoundTypeExpression.h"
#include "../../../../SemanticAnalyzer/BoundExpressions/BoundVariableExpression/BoundArrayVariableExpression/BoundArrayVariableExpression.h"
#include "../../../../SemanticAnalyzer/BoundStatements/BoundFunctionDeclaration/BoundFunctionDeclaration.h"
#include "../../Types/LLVMType/LLVMDynamicType/LLVMDynamicType.h"
#include "../../Types/LLVMType/LLVMFunctionType/LLVMFunctionType.h"
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
};

#endif // __FLOWWING_FUNCTION_DECLARATION_STRATEGY_H__
