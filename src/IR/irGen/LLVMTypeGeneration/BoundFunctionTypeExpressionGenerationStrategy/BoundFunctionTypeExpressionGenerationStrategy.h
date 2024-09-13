#pragma once

#include "../../../../bind/BoundTypeExpression/BoundFunctionTypeExpression/BoundFunctionTypeExpression.h"
#include "../../Types/LLVMType/LLVMObjectType/LLVMObjectType.h"
#include "../../Types/LLVMType/LLVMPrimitiveType/LLVMPrimitiveType.h"
#include "../../expressions/LiteralExpressionGenerationStrategy/LiteralExpressionGenerationStrategy.h"
#include "../../statements/CustomTypeStatementGenerationStrategy/CustomTypeStatementGenerationStrategy.h"
#include "../LLVMTypeGenerationStrategy.h"

class BoundFunctionTypeExpressionGenerationStrategy
    : public LLVMTypeGenerationStrategy {
  std::vector<std::unique_ptr<LLVMType>> _paramsLLVMType;
  std::vector<std::unique_ptr<LLVMType>> _llvmArgsList;
  std::unique_ptr<LLVMType> _llvmReturnType = nullptr;
  bool _hasAsReturnType = false;

 public:
  BoundFunctionTypeExpressionGenerationStrategy(CodeGenerationContext *context)
      : LLVMTypeGenerationStrategy(context) {}

  llvm::Type *getType(BoundTypeExpression *expression) override;
};
