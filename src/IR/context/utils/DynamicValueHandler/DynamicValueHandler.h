
#pragma once
#include "../../CodeGenerationContext.h"

namespace DYNAMIC_VALUE_HANDLER {

llvm::Value *handleAssignmentToDynamicValueVariable(
    llvm::Value *lhsPtr, const std::string &variableName, llvm::Value *rhsValue,
    CodeGenerationContext *context, llvm::IRBuilder<> *&Builder);

llvm::Value *
generateDynamicDispatch(llvm::Value *dynamicValue,
                        CodeGenerationContext *context,
                        llvm::IRBuilder<> *&Builder,
                        const std::function<void(llvm::Value *)> &handler);
} // namespace DYNAMIC_VALUE_HANDLER
