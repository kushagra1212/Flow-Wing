#ifndef __FLOWWING_VARIABLE_EXPRESSION_STRATEGY_H__
#define __FLOWWING_VARIABLE_EXPRESSION_STRATEGY_H__

#include "../../../../bind/BoundCallExpression/BoundCallExpression.h"
#include "../../../../bind/BoundTypeExpression/BoundObjectTypeExpression/BoundObjectTypeExpression.h"
#include "../../../../bind/BoundVariableExpression/BoundVariableExpression.h"
#include "../CallExpressionGenerationStrategy/CallExpressionGenerationStrategy.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"
#include "../IndexExpressionGenerationStrategy/IndexExpressionGenerationStrategy.h"

class VariableExpressionGenerationStrategy
    : public ExpressionGenerationStrategy {
public:
  VariableExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  llvm::Value *getVariableValue(const std::string &variableName);

  llvm::Value *getGlobalVariableValue(const std::string &variableName,
                                      llvm::GlobalVariable *variable);

  // Get Primitive Local Variable Value

  llvm::Value *getUnTypedLocalVariableValue(llvm::Value *variableValue,
                                            llvm::Value *v,
                                            const std::string &variableName);

  llvm::Value *getObjectValueNF(llvm::Value *variableElementPtr,
                                size_t listIndex,
                                const std::string &parPropertyKey,
                                llvm::StructType *type, bool itsClass = false);

  llvm::Value *handleVariableGet(llvm::StructType *parObjType, bool itsClass,
                                 std::string &dotPropertyName, size_t listIndex,
                                 const std::string &parPropertyName,
                                 bool isNested, llvm::Value *outerElementPtr);

  llvm::Value *handleIndexExpression(size_t listIndex,
                                     llvm::Value *innerElementPtr,
                                     llvm::ArrayType *arrayType);

  std::string getPropertyName(size_t listIndex);

  llvm::Value *getVariable(llvm::Value *v, llvm::Type *variableType,
                           const std::string &variableName, int64_t pos = 0);

  llvm::Value *handleSingleVariable(llvm::Type *&variableType, llvm::Value *v,
                                    const std::string &variableName);

  llvm::Value *getClassMember(int64_t pos, std::string &className,
                              llvm::Value *v);

  llvm::Value *getClassMemberFunctionValue(std::string className,
                                           std::string memberName,
                                           llvm::Value *classPtr);
  inline auto
  setVariableExpression(BoundVariableExpression *variableExpression) {
    _variableExpression = variableExpression;
  }

private:
  BoundVariableExpression *_variableExpression;
  BoundTypeExpression *_typeExpression;
  llvm::StructType *parObjTypeType = nullptr;
  bool _isGlobal = false;
};

#endif // __FLOWWING_VARIABLE_EXPRESSION_STRATEGY_H__
