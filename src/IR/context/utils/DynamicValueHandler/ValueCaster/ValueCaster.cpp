

#include "ValueCaster.h"

namespace DYNAMIC_VALUE_HANDLER {
namespace VALUE_CASTER {

llvm::Value *castToType(llvm::Value *value,
                        DYNAMIC_VALUE::TYPE::VALUE_TYPE type,
                        CodeGenerationContext *context,
                        llvm::IRBuilder<> *&Builder) {
  switch (type) {
  case DYNAMIC_VALUE::TYPE::VALUE_TYPE::INT8:
    return toInt8(value, context, Builder);
  case DYNAMIC_VALUE::TYPE::VALUE_TYPE::INT32:
    return toInt32(value, context, Builder);
  case DYNAMIC_VALUE::TYPE::VALUE_TYPE::INT64:
    return toInt64(value, context, Builder);
  case DYNAMIC_VALUE::TYPE::VALUE_TYPE::FLOAT32:
    return toFloat(value, context, Builder);
  case DYNAMIC_VALUE::TYPE::VALUE_TYPE::FLOAT64:
    return toDouble(value, context, Builder);
  case DYNAMIC_VALUE::TYPE::VALUE_TYPE::BOOLEAN:
    return toBoolean(value, context, Builder);
  case DYNAMIC_VALUE::TYPE::VALUE_TYPE::STRING:
    return toString(value, context, Builder);
  case DYNAMIC_VALUE::TYPE::VALUE_TYPE::NIRAST:
    return toNirast(value, context, Builder);
  }

  return nullptr;
}

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

llvm::Value *toNirast(llvm::Value *value, CodeGenerationContext *context,
                      llvm::IRBuilder<> *&Builder) {
  return llvm::ConstantPointerNull::get(
      llvm::Type::getInt8PtrTy(*context->getContext()));
}

} // namespace VALUE_CASTER
} // namespace DYNAMIC_VALUE_HANDLER