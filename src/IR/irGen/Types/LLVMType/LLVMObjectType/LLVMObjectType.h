#ifndef __FLOWWING__LLVM_OBJECT_TYPE_H__
#define __FLOWWING__LLVM_OBJECT_TYPE_H__

#include <llvm/IR/DerivedTypes.h>

#include "../LLVMType.h"

class LLVMObjectType : public LLVMType {
public:
  LLVMObjectType(llvm::Type *type, llvm::StructType *structType);

  virtual inline const bool isPointerToObject() const override { return true; }

  inline llvm::StructType *getStructType() const { return _structType; }

  virtual inline llvm::Type *getLLVMType() const override {
    return _structType;
  }

private:
  llvm::Type *_type;
  llvm::StructType *_structType;
};

#endif // __FLOWWING__LLVM_OBJECT_TYPE_H__