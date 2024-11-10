#pragma once

#include "../../../../../common/CrossPlatformMacros.h"
#include <llvm/IR/DerivedTypes.h>
#include "../LLVMType.h"

class LLVMFunctionType : public LLVMType {
public:
  LLVMFunctionType(llvm::Type *type, llvm::FunctionType *fType);

  virtual inline const bool isPointerToFunction() const override {
    return true;
  }

  inline llvm::FunctionType *getFunctionType() const { return _fType; }

  virtual inline llvm::Type *getLLVMType() const override { return _fType; }

private:
  llvm::Type *_type;
  llvm::FunctionType *_fType;
};
