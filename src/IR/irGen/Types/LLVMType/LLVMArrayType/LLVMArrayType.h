#ifndef __FLOWWING__LLVM_ARRAY_TYPE_H__
#define __FLOWWING__LLVM_ARRAY_TYPE_H__

#include "../LLVMType.h"

class LLVMArrayType : public LLVMType {

public:
  LLVMArrayType(llvm::Type *type, llvm::Type *elementType);

  inline const bool isPointerToArray() const override { return true; }

  inline llvm::Type *getElementType() const { return _elementType; }

private:
  llvm::Type *_type;
  llvm::Type *_elementType;
};

#endif // __FLOWWING__LLVM_ARRAY_TYPE_H__