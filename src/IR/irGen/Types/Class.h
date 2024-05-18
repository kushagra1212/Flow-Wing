#ifndef __FLOWING_CLASS_H__
#define __FLOWING_CLASS_H__

#include "LLVMType/LLVMArrayType/LLVMArrayType.h"
#include "llvm/IR/Module.h"
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>

class Class {
private:
  std::string _className;
  //   std::vector<llvm::Type *> _vTableElements;
  //   std::vector<llvm::Type *> _classElements;
  std::unordered_map<std::string, uint64_t> _classElementsIndexMap;
  std::unordered_map<std::string, uint64_t> _vTableElementsIndexMap;
  std::unordered_map<std::string, llvm::Function *> _classFunctionMap;
  llvm::StructType *_classType;
  llvm::Value *_objectPtr;
  std::vector<
      std::pair<BoundLiteralExpression<std::any> *, BoundTypeExpression *>>
      _key_type_pairs;

public:
  Class(std::string className) : _className(className) {}
  inline auto setClassType(llvm::StructType *type) { _classType = type; }
  inline auto getClassType() -> llvm::StructType * { return _classType; }
  inline auto setElementIndex(std::string key, uint64_t index) {
    _classElementsIndexMap[key] = index;
  }

  inline auto setVTableElementIndex(std::string key, uint64_t index) {
    _vTableElementsIndexMap[key] = index;
  }

  inline auto doesElementExist(std::string key) -> bool {
    return _classElementsIndexMap.find(key) != _classElementsIndexMap.end();
  }

  inline auto addKeyTypePair(BoundLiteralExpression<std::any> *key,
                             BoundTypeExpression *type) -> void {
    _key_type_pairs.push_back(std::make_pair(key, type));
  }
  inline auto getKeyTypePairs() -> std::vector<
      std::pair<BoundLiteralExpression<std::any> *, BoundTypeExpression *>> & {
    return _key_type_pairs;
  }

  inline auto getKeyValue(std::string key)
      -> std::tuple<BoundLiteralExpression<std::any> *, BoundTypeExpression *,
                    uint64_t> {
    uint64_t index = 0;
    for (auto &pair : this->_key_type_pairs) {
      std::string name = std::any_cast<std::string>(pair.first->getValue());
      if (name == key) {
        return {pair.first, pair.second, index};
      }
      index++;
    }

    return {nullptr, nullptr, -1};
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

  inline auto insertFunctionType(std::string key, llvm::Function *functionType)
      -> void {
    _classFunctionMap[key] = functionType;
  }
};

#endif