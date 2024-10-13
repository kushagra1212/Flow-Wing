#pragma once

#include "../../../../SemanticAnalyzer/BoundExpressions/BoundTypeExpression/BoundFunctionTypeExpression/BoundFunctionTypeExpression.h"
#include "../../Types/LLVMType//LLVMFunctionType/LLVMFunctionType.h"
#include "../../Types/LLVMType/LLVMObjectType/LLVMObjectType.h"
#include "../../Types/LLVMType/LLVMPrimitiveType/LLVMPrimitiveType.h"
#include "../../expressions/LiteralExpressionGenerationStrategy/LiteralExpressionGenerationStrategy.h"
#include "../../statements/CustomTypeStatementGenerationStrategy/CustomTypeStatementGenerationStrategy.h"
#include "../LLVMTypeGenerationStrategy.h"

class BoundFunctionTypeExpressionGenerationStrategy
    : public LLVMTypeGenerationStrategy {
  std::unique_ptr<LLVMType> _llvmReturnType = nullptr;
  bool _hasAsReturnType = false;

public:
  BoundFunctionTypeExpressionGenerationStrategy(CodeGenerationContext *context)
      : LLVMTypeGenerationStrategy(context) {}

  llvm::Type *getType(BoundTypeExpression *expression) override;
};
