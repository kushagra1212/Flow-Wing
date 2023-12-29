#include "LLVMArrayType.h"

LLVMArrayType::LLVMArrayType(llvm::Type *type, llvm::Type *elementType)
    : LLVMType(type), _elementType(elementType) {}