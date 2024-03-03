#include "LLVMObjectType.h"

LLVMObjectType::LLVMObjectType(llvm::Type *type, llvm::StructType *structType)
    : LLVMType(type), _structType(structType) {}