
#pragma once
#include "../../../LLVMTypeConversion/BoolTypeConverter/BoolTypeConverter.h"
#include "../../../LLVMTypeConversion/ExplicitConverter.h"
#include "../../../strategies/BinaryOperationStrategy/Int32BinaryOperationStrategy/Int32BinaryOperationStrategy.h"
#include "../../CodeGenerationContext.h"
#include "ValueCaster/ValueCaster.h"

namespace DYNAMIC_VALUE_HANDLER {

llvm::Value *assignRHSValueToLHSDynamicValue(llvm::Value *lhsPtr,
                                             const std::string &variableName,
                                             llvm::Value *rhsValue,
                                             CodeGenerationContext *context,
                                             llvm::IRBuilder<> *&Builder);

llvm::Value *
generateDynamicDispatch(llvm::Value *dynamicValue,
                        CodeGenerationContext *context,
                        llvm::IRBuilder<> *&Builder,
                        const std::function<void(llvm::Value *)> &handler);

void assignRHSDynamicValueToLHSDynamicValue(llvm::Value *lhsDynamicValue,
                                            llvm::Value *rhsDynamicValue,
                                            CodeGenerationContext *context,
                                            llvm::IRBuilder<> *&Builder);

std::pair<llvm::Value *, llvm::Value *>
getDynamicStoredValueAndType(llvm::Value *&dynamicValue,
                             CodeGenerationContext *&context,
                             llvm::IRBuilder<> *&Builder);

void assignRHSDynamicValueToLHSVariable(llvm::Value *lhsVariable,
                                        llvm::Type *lhsType,
                                        llvm::Value *rhsDynamicValue,
                                        CodeGenerationContext *context,
                                        llvm::IRBuilder<> *&Builder);

} // namespace DYNAMIC_VALUE_HANDLER
