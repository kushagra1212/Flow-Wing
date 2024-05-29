#ifndef __FLOWWING__LLVM_PRIMITIVE_TYPE_H__
#define __FLOWWING__LLVM_PRIMITIVE_TYPE_H__

#include <llvm/IR/DerivedTypes.h>

#include "../LLVMType.h"

class LLVMPrimitiveType : public LLVMType {
public:
  LLVMPrimitiveType(llvm::Type *type, llvm::Type *primitiveType);

  virtual inline const bool isPointerToPrimitive() const override {
    return true;
  }

  inline llvm::Type *getPrimitiveType() const { return _primitiveType; }

  virtual inline llvm::Type *getLLVMType() const override {
    return _primitiveType;
  }

private:
  llvm::Type *_type;
  llvm::Type *_primitiveType;
};

#endif // __FLOWWING__LLVM_PRIMITIVE_TYPE_H__