#ifndef __FLOWWING_CONTAINER_STATEMENT_STRATEGY_H__
#define __FLOWWING_CONTAINER_STATEMENT_STRATEGY_H__

#include "../../../../bind/BoundBracketedExpression/BoundBracketedExpression.h"
#include "../../../../bind/BoundContainerStatement/BoundContainerStatement.h"
#include "../../../../bind/BoundTypeExpression/BoundArrayTypeExpression/BoundArrayTypeExpression.h"
#include "../../../../bind/BoundTypeExpression/BoundObjectTypeExpression/BoundObjectTypeExpression.h"

#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"

class ContainerDeclarationStatementGenerationStrategy
    : public StatementGenerationStrategy {

public:
  // public methods
  ContainerDeclarationStatementGenerationStrategy(
      CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;

  llvm::Value *declareLocal(BoundStatement *statement);
  llvm::Value *declareGlobal(BoundStatement *statement);

private:
  // private members
  std::vector<uint64_t> _actualSizes;
  llvm::Type *_elementType = nullptr;
  std::string _containerName;

  BoundExpression *_initializer;
  BinderKindUtils::MemoryKind _memoryKind;
  BoundArrayTypeExpression *_arrayTypeExpression;
  BoundVariableDeclaration *_variableDeclExpr;

  // private methods
  void calcActualContainerSize(BoundArrayTypeExpression *arrayTypeExpression);
  void initialize(BoundStatement *statement,
                  BinderKindUtils::MemoryKind memoryKind =
                      BinderKindUtils::MemoryKind::None);
  llvm::Value *declare();
  llvm::Value *assignExpression();
};

#endif //__FLOWWING_CONTAINER_STATEMENT_STRATEGY_H__
