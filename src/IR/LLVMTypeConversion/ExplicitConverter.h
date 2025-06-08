#pragma once

#include "../context/CodeGenerationContext.h"
#include "../irGen/GenerationStrategy.h"
#include <llvm/IR/Value.h>

namespace FlowWing {

namespace EXPLICIT_CONVERTER {

llvm::Value *explicitConvertLLVMValueTo(llvm::Value *value, llvm::Type *type,
                                        CodeGenerationContext *context);

} // namespace EXPLICIT_CONVERTER

} // namespace FlowWing