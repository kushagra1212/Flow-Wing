#include "LLVMFunctionType.h"

LLVMFunctionType::LLVMFunctionType(llvm::Type *type, llvm::FunctionType *fType)
    : LLVMType(type), _fType(fType) {}