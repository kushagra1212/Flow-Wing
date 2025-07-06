#include "LLVMDynamicType.h"

LLVMDynamicType::LLVMDynamicType(llvm::Type *type, llvm::Type *dynamicType)
    : LLVMType(type), _dynamicType(dynamicType) {}