#include "LLVMArrayType.h"

LLVMArrayType::LLVMArrayType(llvm::Type *type, llvm::Type *elementType,
                             llvm::Type *arrayElementType,
                             const std::vector<uint64_t> &dimensions,
                             BoundArrayTypeExpression *arrayTypeExpression)
    : LLVMType(type),
      _elementType(elementType),
      _dimensions(dimensions),
      _arrayElementType(arrayElementType),
      _arrayTypeExpression(arrayTypeExpression) {}