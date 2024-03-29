#ifndef __FLOWWING_OBJECT_EXPRESSION_STRATEGY_H__
#define __FLOWWING_OBJECT_EXPRESSION_STRATEGY_H__

#include "../../../../bind/BoundObjectExpression/BoundObjectExpression.h"
#include "../../../../bind/BoundTypeExpression/BoundObjectTypeExpression/BoundObjectTypeExpression.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"
#include "../ObjectAssignmentExpressionGenerationStrategy/ObjectAssignmentExpressionGenerationStrategy.h"

class ObjectExpressionGenerationStrategy : public ExpressionGenerationStrategy {
public:
  ObjectExpressionGenerationStrategy(CodeGenerationContext *context);
  llvm::Value *generateExpression(BoundExpression *expression) override;

  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;
  llvm::Value *generateCallExp(BoundExpression *expression);
  llvm::Value *generateVariableExp(BoundExpression *expression);
  llvm::Value *createExpression(BoundExpression *expression,
                                llvm::Value *variable,
                                const std::string &typeName);

  llvm::Value *createExpressionNP(BoundExpression *expression,
                                  llvm::Value *variable,
                                  const std::string &typeName);

  llvm::Value *generateVariable(llvm::Value *variable,
                                const std::string &typeName,
                                llvm::Value *fromVar, const bool isGlobal);

  llvm::Value *generateVariableAccessThroughPtr(llvm::Value *variable,
                                                const std::string &typeName,
                                                llvm::Value *fromVar);

  llvm::Value *createExpressionNPDefault(llvm::Value *variable,
                                         const std::string &typeName);

  inline auto setVariable(llvm::Value *variable) { _variable = variable; }

  inline auto setTypeName(std::string typeName) { _typeName = typeName; }

private:
  llvm::Value *_variable;
  std::string _typeName;
  bool _variableIsGlobal = false;
};

#endif // __FLOWWING_OBJECT_EXPRESSION_STRATEGY_H__