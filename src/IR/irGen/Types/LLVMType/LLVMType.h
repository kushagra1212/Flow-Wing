#ifndef __FLOWWING__ARG_TYPE_H__
#define __FLOWWING__ARG_TYPE_H__

#include <llvm/IR/Type.h>

class LLVMType {
public:
  LLVMType(llvm::Type *type);

  inline llvm::Type *getType() const { return _type; }

  inline const bool isPointer() const { return _type->isPointerTy(); }

  inline const bool operator==(const LLVMType &other) const {
    return _type == other._type;
  }

  inline const bool operator!=(const LLVMType &other) const {
    return !(*this == other);
  }

  virtual inline llvm::Type *getLLVMType() const { return _type; }

  virtual inline const bool isPointerToArray() const { return false; }

  virtual inline const bool isPointerToObject() const { return false; }

  virtual inline const bool isPointerToPrimitive() const { return false; }

private:
  llvm::Type *_type;
};

#endif // __FLOWWING__ARG_TYPE_H__
