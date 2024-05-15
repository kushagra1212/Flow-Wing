#ifndef __FLOWWING_ASSIGNMENT_EXPRESSION_STRATEGY_H__
#define __FLOWWING_ASSIGNMENT_EXPRESSION_STRATEGY_H__

#include "../../../../bind/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "../../../../bind/BoundBracketedExpression/BoundBracketedExpression.h"
#include "../../../../bind/BoundIndexExpression/BoundIndexExpression.h"
#include "../../../../bind/BoundObjectExpression/BoundObjectExpression.h"
#include "../BracketedExpressionGenerationStrategy/BracketedExpressionGenerationStrategy.h"
#include "../ContainerAssignmentExpressionGenerationStrategy/ContainerAssignmentExpressionGenerationStrategy.h"
#include "../ContainerExpressionGenerationStrategy/ContainerExpressionGenerationStrategy.h"
#include "../ObjectAssignmentExpressionGenerationStrategy/ObjectAssignmentExpressionGenerationStrategy.h"
#include "../ObjectExpressionGenerationStrategy/ObjectExpressionGenerationStrategy.h"

class AssignmentExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  AssignmentExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  // Specialized for BoundAssignmentExpression
  //   llvm::Value *handleLiteralExpressionAssignment(
  //       BoundAssignmentExpression *assignmentExpression);

  //   llvm::Value *handleIndexExpressionAssignment(
  //       BoundAssignmentExpression *assignmentExpression);

  // Global Specialized for BoundAssignmentExpression
  //   llvm::Value *handleGlobalLiteralExpressionAssignment(
  //       BoundAssignmentExpression *assignmentExpression);

  // bool canGenerateLiteralExpressionAssignment(
  //     BoundAssignmentExpression *assignmentExpression);

  // Primitve Local Variable Assignment

  //   llvm::Value *handleTypedPrmitiveLocalVariableAssignment(
  //       const std::string &variableName,
  //       const SyntaxKindUtils::SyntaxKind &variableType, llvm::Value
  //       *rhsValue);

  //   llvm::Value *
  //   handleUnTypedPrmitiveLocalVariableAssignment(const std::string
  //   &variableName,
  //                                                llvm::Value *rhsValue);

  //   llvm::Value *handlePrimitiveLocalVariableAssignment(
  //       const std::string &variableName,
  //       const SyntaxKindUtils::SyntaxKind &variableType, llvm::Value
  //       *rhsValue);

  // Primitive Global Variable Assignment

  //   llvm::Value *handleTypedPrmitiveGlobalVariableAssignment(
  //       llvm::GlobalVariable *variable, const std::string &variableName,
  //       const SyntaxKindUtils::SyntaxKind &variableType, llvm::Value
  //       *rhsValue);

  llvm::Value *
  handleDynamicPrimitiveVariableAssignment(llvm::Value *variable,
                                           const std::string &variableName,
                                           llvm::Value *rhsValue);

  //   llvm::Value *handlePrimitiveGlobalVariableAssignment(
  //       llvm::GlobalVariable *variable, const std::string &variableName,
  //       const SyntaxKindUtils::SyntaxKind &variableType, llvm::Value
  //       *rhsValue);

  llvm::Value *
  handleAssignmentExpression(BoundAssignmentExpression *assignmentExpression);
  llvm::Value *handleRHSExpression(BoundExpression *expression);
  llvm::Value *handleAssignExpression(llvm::Value *lshPtr, llvm::Type *lhsType,
                                      std::string lhsVarName,
                                      BoundExpression *expression);
  llvm::Value *handleAssignmentByVariable(BoundExpression *exp);

  int8_t populateLHS(BoundAssignmentExpression *&assignmentExpression);

  int8_t handleWhenRHSIsConstant(BoundExpression *expression);

  llvm::Value *handleAssignmentByBracketedExpression(
      BoundBracketedExpression *bracketedExpression);
  llvm::Value *
  handleAssignmentByObjectExpression(BoundObjectExpression *boundObjExp);

  // Default Initialize
  void initObjectWithDefaultValue(llvm::StructType *type, llvm::Value *alloca);
  void initArrayWithDefaultValue(llvm::ArrayType *arrayType,
                                 llvm::Value *alloca);
  void initDefaultValue(llvm::Type *type, llvm::Value *alloca);

private:
  std::string _variableName;
  llvm::Value *_allocaInst;
  llvm::GlobalVariable *_previousGlobalVariable;
  SyntaxKindUtils::SyntaxKind _variableType;
  bool _isGlobal;
  std::vector<llvm::Value *> _indices;
  BoundVariableExpression *_variableExpression;
  BoundExpression *_rhsExpression;

  // Complete Assignment
  std::string _lhsVariableName;
  llvm::Type *_lhsType, *_rhsType;
  llvm::Value *_lhsPtr, *_rhsPtr;
  SyntaxKindUtils::SyntaxKind _lhsTypeKind;

  llvm::Value *_lhsDynamicPtr;
};

#endif // __FLOWWING_ASSIGNMENT_EXPRESSION_STRATEGY_H__
