#ifndef __FLOWWING_OBJECT_STATEMENT_STRATEGY_H__
#define __FLOWWING_OBJECT_STATEMENT_STRATEGY_H__

#include "../../../../bind/BoundTypeExpression/BoundArrayTypeExpression/BoundArrayTypeExpression.h"
#include "../../../../bind/BoundTypeExpression/BoundObjectTypeExpression/BoundObjectTypeExpression.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"

class ObjectDeclarationStatementGenerationStrategy
    : public StatementGenerationStrategy {

public:
  // public methods
  ObjectDeclarationStatementGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;

  llvm::Value *declareLocal(BoundStatement *statement);
  llvm::Value *declareGlobal(BoundStatement *statement);

private:
  // private members
  std::string _variableName;

  BoundExpression *_initializer;
  BinderKindUtils::MemoryKind _memoryKind;
  BoundObjectTypeExpression *_objectTypeExpr;
  BoundVariableDeclaration *_variableDeclExpr;
  bool _isGlobal = false;

  // private methods
  void initialize(BoundStatement *statement,
                  BinderKindUtils::MemoryKind memoryKind =
                      BinderKindUtils::MemoryKind::None);
  llvm::Value *declare();
  llvm::Value *assignExpression();
};

#endif //__FLOWWING_OBJECT_STATEMENT_STRATEGY_H__
