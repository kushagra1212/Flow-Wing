#pragma once

#include <llvm/IR/DerivedTypes.h>

#include "../LLVMType.h"

class LLVMDynamicType : public LLVMType {
public:
  LLVMDynamicType(llvm::Type *type, llvm::Type *dynamicType);

  virtual inline const bool isPointerToDynamic() const override { return true; }

  inline llvm::Type *getDynamicType() const { return _dynamicType; }

  virtual inline llvm::Type *getLLVMType() const override {
    return _dynamicType;
  }

private:
  llvm::Type *_type;
  llvm::Type *_dynamicType;
};