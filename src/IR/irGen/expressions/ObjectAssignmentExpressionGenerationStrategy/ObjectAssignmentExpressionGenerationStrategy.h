#ifndef __FLOWWING_OBJECT_ASSIGNMENT_EXPRESSION_STRATEGY_H__
#define __FLOWWING_OBJECT_ASSIGNMENT_EXPRESSION_STRATEGY_H__

#include "../../../../SemanticAnalyzer/BoundExpressions/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "../../../../SemanticAnalyzer/BoundExpressions/BoundObjectExpression/BoundObjectExpression.h"
#include "../../../../SemanticAnalyzer/BoundExpressions/BoundVariableExpression/BoundVariableExpression.h"
#include "../../statements/CustomTypeStatementGenerationStrategy/CustomTypeStatementGenerationStrategy.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

class ObjectAssignmentExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  ObjectAssignmentExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  llvm::Value *_deprecated_assignObject(llvm::Value *variableElementPtr,
                                        size_t listIndex,
                                        const std::string &parPropertyKey,
                                        bool reachedEnd);

  bool canGenerateAssignmentExpressionAssignment(
      BoundAssignmentExpression *assignmentExpression);

  llvm::Value *copyObject(llvm::StructType *parStructType, llvm::Value *lshPtr,
                          llvm::Value *rhsPtr);

  llvm::Value *assignObject(BoundObjectExpression *parObjectExpression,
                            llvm::Value *variable,
                            llvm::StructType *parStructType,
                            std::string lhsVarName);

private:
  BoundAssignmentExpression *_assignmentExp = nullptr;
  llvm::Value *_lhsVar;
  BoundVariableExpression *_lhsVarExpr = nullptr;
  bool _isGlobal = false;
};

#endif // __FLOWWING_OBJECT_ASSIGNMENT_EXPRESSION_STRATEGY_H__
