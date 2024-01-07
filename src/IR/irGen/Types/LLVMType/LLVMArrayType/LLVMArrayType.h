#ifndef __FLOWWING__LLVM_ARRAY_TYPE_H__
#define __FLOWWING__LLVM_ARRAY_TYPE_H__

#include "../LLVMType.h"

class LLVMArrayType : public LLVMType {
 public:
  LLVMArrayType(llvm::Type *type, llvm::Type *elementType,
                llvm::Type *arrayElementType,
                const std::vector<uint64_t> &dimensions);

  inline const bool isPointerToArray() const override { return true; }

  inline llvm::Type *getElementType() const { return _elementType; }

  inline const std::vector<uint64_t> &getDimensions() const {
    return _dimensions;
  }

  inline llvm::Type *getArrayElementType() const { return _arrayElementType; }

 private:
  llvm::Type *_type;
  llvm::Type *_elementType;
  std::vector<uint64_t> _dimensions;
  llvm::Type *_arrayElementType;
};

#endif  // __FLOWWING__LLVM_ARRAY_TYPE_H__