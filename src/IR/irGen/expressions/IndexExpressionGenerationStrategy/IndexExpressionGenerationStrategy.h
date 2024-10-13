#ifndef __FLOWWING_INDEX_EXPRESSION_STRATEGY_H__
#define __FLOWWING_INDEX_EXPRESSION_STRATEGY_H__

#include "../../../../SemanticAnalyzer/BoundExpressions/BoundIndexExpression/BoundIndexExpression.h"
#include "../../../../SemanticAnalyzer/BoundExpressions/BoundVariableExpression/BoundVariableExpression.h"
#include "../ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

class IndexExpressionGenerationStrategy : public ExpressionGenerationStrategy {
public:
  IndexExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  llvm::Value *handleGlobalVariable(llvm::GlobalVariable *variable,
                                    std::string variableName);

  llvm::Value *handleStringIndexing();

  llvm::Value *handleArrayTypeIndexing();

  void verifyBounds(llvm::Value *index, llvm::ConstantInt *actualSize);

  const bool canGenerateExpression(const std::string &variableName);

  inline auto setIndexExpression(BoundIndexExpression *indexExpression) {
    _indexExpression = indexExpression;
  }
  int8_t populateIndices();
  int8_t populateVariableName();
  inline auto setArrayType(llvm::Type *arrayType) -> void {
    _arrayType = llvm::cast<llvm::ArrayType>(arrayType);
  }
  inline auto populateArraySize() -> void {
    _arrayElementType = _arrayType;
    std::vector<uint64_t> sizes;
    _codeGenerationContext->createArraySizesAndArrayElementType(
        sizes, _arrayElementType);
    for (int i = 0; i < sizes.size(); i++) {
      _actualSizes.push_back(Builder->getInt32(sizes[i]));
    }
  }

  inline auto setVariable(llvm::Value *variable) { _variable = variable; }

private:
  std::vector<llvm::Value *> _indices;
  std::vector<llvm::ConstantInt *> _actualSizes;
  std::string _variableName;
  llvm::Type *_arrayElementType = nullptr;
  llvm::Value *_variable = nullptr;
  llvm::ArrayType *_arrayType = nullptr;
  BoundIndexExpression *_indexExpression = nullptr;
};

#endif // __FLOWWING_INDEX_EXPRESSION_STRATEGY_H__
