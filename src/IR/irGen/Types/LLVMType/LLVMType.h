#ifndef __FLOWWING__ARG_TYPE_H__
#define __FLOWWING__ARG_TYPE_H__

#include <llvm/IR/Type.h>

class LLVMType {
public:
  LLVMType(llvm::Type *type);
  LLVMType(llvm::Type *type, std::vector<llvm::Type *> structTypeList);

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
  virtual inline const bool isPointerToFunction() const { return false; }

  virtual inline const bool isPointerToPrimitive() const { return false; }

  inline auto getStructTypeListRef() const
      -> const std::vector<llvm::Type *> & {
    return _structTypeList;
  }

private:
  llvm::Type *_type;
  std::vector<llvm::Type *> _structTypeList;
};

#endif // __FLOWWING__ARG_TYPE_H__
