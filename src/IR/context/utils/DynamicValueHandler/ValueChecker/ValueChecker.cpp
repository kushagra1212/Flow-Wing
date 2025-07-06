#include "ValueChecker.h"

namespace DYNAMIC_VALUE_HANDLER {
namespace VALUE_CHECKER {

int8_t isDynamicType(llvm::Type *type, CodeGenerationContext *ctx) {
  return llvm::StructType::getTypeByName(
             *ctx->getContext(), DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE) ==
         type;
}

int8_t isDynamicCompatibleType(llvm::Type *rhsType,
                               CodeGenerationContext *ctx) {
  if (ctx->getMapper()->isPrimitiveType(rhsType) ||
      rhsType == llvm::Type::getVoidTy(*ctx->getContext())) {
    return 1;
  }
  return 0;
}

} // namespace VALUE_CHECKER
} // namespace DYNAMIC_VALUE_HANDLER