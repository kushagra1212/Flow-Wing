

#include "ValueCaster.h"

namespace DYNAMIC_VALUE_HANDLER {
namespace VALUE_CASTER {

llvm::Value *toString(llvm::Value *value, CodeGenerationContext *context,
                      llvm::IRBuilder<> *&Builder) {
  return Builder->CreateIntToPtr(
      value, llvm::Type::getInt8PtrTy(*context->getContext()),
      "loadedStringPtr");
}

llvm::Value *toInt32(llvm::Value *value, CodeGenerationContext *context,
                     llvm::IRBuilder<> *&Builder) {
  return Builder->CreateIntCast(value,
                                llvm::Type::getInt32Ty(*context->getContext()),
                                true, "int32Value");
}

llvm::Value *toInt64(llvm::Value *value, CodeGenerationContext *context,
                     llvm::IRBuilder<> *&Builder) {
  return Builder->CreateIntCast(value,
                                llvm::Type::getInt64Ty(*context->getContext()),
                                true, "int64Value");
}

llvm::Value *toFloat(llvm::Value *value, CodeGenerationContext *context,
                     llvm::IRBuilder<> *&Builder) {
  llvm::Value *bitsAsInt32 = Builder->CreateTrunc(
      value,
      llvm::Type::getInt32Ty(
          *context->getContext())); // Truncate to get lower 32 bits
  llvm::Value *float32Value = Builder->CreateBitCast(
      bitsAsInt32, llvm::Type::getFloatTy(*context->getContext()));

  return float32Value;
}

llvm::Value *toDouble(llvm::Value *value, CodeGenerationContext *context,
                      llvm::IRBuilder<> *&Builder) {
  return Builder->CreateBitCast(
      value, llvm::Type::getDoubleTy(*context->getContext()));
}

llvm::Value *toBoolean(llvm::Value *value, CodeGenerationContext *context,
                       llvm::IRBuilder<> *&Builder) {
  return Builder->CreateICmpNE(value,
                               llvm::ConstantInt::get(value->getType(), 0));
}

llvm::Value *toInt8(llvm::Value *value, CodeGenerationContext *context,
                    llvm::IRBuilder<> *&Builder) {
  return Builder->CreateIntCast(
      value, llvm::Type::getInt8Ty(*context->getContext()), true, "int8Value");
}

} // namespace VALUE_CASTER
} // namespace DYNAMIC_VALUE_HANDLER