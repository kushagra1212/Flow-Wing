#include "LLVMPrimitiveType.h"

LLVMPrimitiveType::LLVMPrimitiveType(llvm::Type *type,
                                     llvm::Type *primitiveType)
    : LLVMType(type), _primitiveType(primitiveType) {}