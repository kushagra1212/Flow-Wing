
#include "../../context/CodeGenerationContext.h"
#include "ExpressionGenerationFactory.h"
#include "ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"
#include "llvm/IR/IRBuilder.h"

namespace ExpressionSupport {
llvm::Value *getExpressionValue(CodeGenerationContext *context,
                                BoundExpression *expression, bool &isClassType,
                                int8_t &isDynamicValue);
} // namespace ExpressionSupport