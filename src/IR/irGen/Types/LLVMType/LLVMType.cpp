#include "LLVMType.h"

LLVMType::LLVMType(llvm::Type *type) : _type(type) {}
LLVMType::LLVMType(llvm::Type *type, std::vector<llvm::Type *> structTypeList)
    : _type(type), _structTypeList(structTypeList) {}