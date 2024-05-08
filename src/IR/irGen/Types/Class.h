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
  std::vector<std::string> _classFunctionNames;
  std::vector<llvm::FunctionType *> _classFunctionTypes;
  llvm::StructType *_classType;
  llvm::StructType *_vTableType;
  llvm::Value *_objectPtr;

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

  inline auto setObjectPtr(llvm::Value *ptr) { _objectPtr = ptr; }
  inline auto getObjectPtr() -> llvm::Value * { return _objectPtr; }

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

  inline auto addFunctionName(std::string name) {
    _classFunctionNames.push_back(name);
  }

  inline auto addFunctionType(llvm::FunctionType *type) {
    _classFunctionTypes.push_back(type);
  }

  inline auto addVTablePtr(llvm::Value *vTablePtr, llvm::Module *module,
                           llvm::IRBuilder<> *builder) {
    uint64_t i = 0;
    for (auto name : _classFunctionNames) {
      llvm::Function *function = module->getFunction(name);
      builder->CreateStore(
          function,
          builder->CreateGEP(_vTableType, vTablePtr,
                             {builder->getInt32(0), builder->getInt32(i)}));
      i++;
    }
  }
  inline auto getFunctionPtr(std::string name, llvm::IRBuilder<> *builder,
                             llvm::Value *objPtr) -> llvm::Function * {

    llvm::Value *vTablePtr = builder->CreateGEP(
        _classType, objPtr,
        {builder->getInt32(0),
         builder->getInt32(_classType->getStructNumElements() - 1)});

    llvm::Value *load = builder->CreateLoad(_vTableType, vTablePtr);

    for (uint64_t i = 0; i < _classFunctionNames.size(); i++) {

      if (_classFunctionNames[i] == name) {
        auto *F = builder->CreateGEP(
            _vTableType, load, {builder->getInt32(0), builder->getInt32(i)});

        if (F && llvm::isa<llvm::Function>(F))
          return llvm::cast<llvm::Function>(F);
      }
    }

    return nullptr;
  }
};

#endif