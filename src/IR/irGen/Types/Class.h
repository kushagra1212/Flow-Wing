#ifndef __FLOWING_CLASS_H__
#define __FLOWING_CLASS_H__

#include "LLVMType/LLVMArrayType/LLVMArrayType.h"
#include <llvm/IR/DerivedTypes.h>

class Class {
private:
  std::string _className;
  //   std::vector<llvm::Type *> _vTableElements;
  //   std::vector<llvm::Type *> _classElements;
  std::unordered_map<std::string, uint64_t> _classElementsIndexMap;
  std::unordered_map<std::string, uint64_t> _vTableElementsIndexMap;
  llvm::StructType *_classType;
  llvm::StructType *_vTableType;

public:
  Class(std::string className) : _className(className) {}
  inline auto setClassType(llvm::StructType *type) { _classType = type; }
  inline auto setVTableType(llvm::StructType *type) { _vTableType = type; }
  inline auto getClassType() -> llvm::StructType * { return _classType; }
  inline auto getVTableType() -> llvm::StructType * { return _vTableType; }
  inline auto setElementIndex(std::string key, uint64_t index) {
    _classElementsIndexMap[key] = index;
  }

  inline auto setVTableElementIndex(std::string key, uint64_t index) {
    _vTableElementsIndexMap[key] = index;
  }

  inline auto doesElementExist(std::string key) -> bool {
    return _classElementsIndexMap.find(key) != _classElementsIndexMap.end();
  }

  inline auto getElement(std::string key)
      -> std::tuple<llvm::Type *, uint64_t, std::string, llvm::StructType *> {
    uint64_t index = _classElementsIndexMap[key];
    llvm::Type *elementType = _classType->getElementType(index);
    std::string elementName = "primitive";

    if (llvm::isa<llvm::StructType>(elementType)) {
      elementName = "struct";
    } else if (llvm::isa<llvm::ArrayType>(elementType)) {
      elementName = "array";
    }

    return {elementType, index, elementName, _classType};
  }
  inline auto getvTableElement(std::string key)
      -> std::tuple<llvm::Type *, uint64_t, llvm::StructType *> {
    uint64_t index = _vTableElementsIndexMap[key];
    llvm::Type *elementType = _vTableType->getElementType(index);

    return {elementType, index, _vTableType};
  }
};

#endif