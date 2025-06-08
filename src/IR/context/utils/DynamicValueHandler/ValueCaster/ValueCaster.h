#pragma once
#include "../../../../LLVMTypeConversion/ExplicitConverter.h"
#include "../../../CodeGenerationContext.h"

namespace DYNAMIC_VALUE_HANDLER {
namespace VALUE_CASTER {
llvm::Value *toString(llvm::Value *value, CodeGenerationContext *context,
                      llvm::IRBuilder<> *&Builder);

llvm::Value *toInt32(llvm::Value *value, CodeGenerationContext *context,
                     llvm::IRBuilder<> *&Builder);

llvm::Value *toInt64(llvm::Value *value, CodeGenerationContext *context,
                     llvm::IRBuilder<> *&Builder);

llvm::Value *toFloat(llvm::Value *value, CodeGenerationContext *context,
                     llvm::IRBuilder<> *&Builder);

llvm::Value *toDouble(llvm::Value *value, CodeGenerationContext *context,
                      llvm::IRBuilder<> *&Builder);

llvm::Value *toBoolean(llvm::Value *value, CodeGenerationContext *context,
                       llvm::IRBuilder<> *&Builder);

llvm::Value *toInt8(llvm::Value *value, CodeGenerationContext *context,
                    llvm::IRBuilder<> *&Builder);
} // namespace VALUE_CASTER
} // namespace DYNAMIC_VALUE_HANDLER