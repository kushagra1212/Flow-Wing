#ifndef __FLOWWING_CUSTOM_TYPE_STATEMENT_STRATEGY_H__
#define __FLOWWING_CUSTOM_TYPE_STATEMENT_STRATEGY_H__

#include "../../../../bind/BoundCustomTypeStatement/BoundCustomTypeStatement.h"
#include "../../../../bind/BoundTypeExpression/BoundObjectTypeExpression/BoundObjectTypeExpression.h"
#include "../../expressions/LiteralExpressionGenerationStrategy/LiteralExpressionGenerationStrategy.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"
class CustomTypeStatementGenerationStrategy
    : public StatementGenerationStrategy {
public:
  CustomTypeStatementGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;

  llvm::Type *getType(BoundTypeExpression *btE);
  llvm::Type *getClassElementType(BoundTypeExpression *bTE,
                                  std::string className);

  llvm::Value *generateForClassElement(BoundStatement *statement,
                                       std::string className);

private:
  bool _isGlobal = false;
  std::string _className = "";
};

#endif // __FLOWWING_CUSTOM_TYPE_STATEMENT_STRATEGY_H__
