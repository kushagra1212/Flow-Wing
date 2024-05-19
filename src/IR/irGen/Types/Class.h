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
  std::unordered_map<std::string, llvm::FunctionType *>
      _classMemberFunctionTypeMap;
  std::unordered_map<std::string,
                     std::tuple<llvm::FunctionType *, uint64_t, std::string>>
      _vTableElementsMap;
  std::unordered_map<std::string, llvm::Function *> _classFunctionMap;

  llvm::StructType *_classType;
  llvm::StructType *_vTableType;
  std::string _vTableName;
  std::string _parentClassName;

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

  inline auto doesElementExist(std::string key) -> bool {
    return _classElementsIndexMap.find(key) != _classElementsIndexMap.end();
  }

  inline auto setVTableType(llvm::StructType *type) { _vTableType = type; }

  inline auto setParentClassName(std::string name) { _parentClassName = name; }

  inline auto hasParent() -> bool { return _parentClassName != ""; }

  inline auto getParentClassName() -> std::string { return _parentClassName; }

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

  inline auto insertFunctionType(std::string key,
                                 llvm::FunctionType *functionType) -> void {
    _classMemberFunctionTypeMap[key] = functionType;
  }

  inline auto getFunctionType(std::string key) -> llvm::FunctionType * {
    return _classMemberFunctionTypeMap[key];
  }

  inline auto getClassMemberFunctionTypeMap()
      -> std::unordered_map<std::string, llvm::FunctionType *> & {
    return _classMemberFunctionTypeMap;
  }

  inline auto getVTableElementsMap() -> std::unordered_map<
      std::string, std::tuple<llvm::FunctionType *, uint64_t, std::string>> & {
    return _vTableElementsMap;
  }

  inline auto createVTable(std::string className, llvm::Module *TheModule)
      -> void {
    _vTableName = "vtable." + className + "." + "fg";
    new llvm::GlobalVariable(
        *TheModule, _vTableType, false, llvm::GlobalValue::ExternalLinkage,
        llvm::ConstantAggregateZero::get(_vTableType), _vTableName);
  }

  inline auto getVTableName() -> std::string { return _vTableName; }
  inline auto getVTableType() -> llvm::StructType * { return _vTableType; }

  inline auto populateVTable(llvm::IRBuilder<> *builder,
                             llvm::Module *TheModule,
                             llvm::LLVMContext *context, llvm::Value *ptr)
      -> void {

    llvm::Value *vTablePtr = builder->CreateLoad(
        llvm::PointerType::getInt8PtrTy(*context),
        builder->CreateStructGEP(_classType, ptr,
                                 _classType->getNumElements() - 1));

    for (auto &element : _vTableElementsMap) {

      std::string className = std::get<2>(element.second);

      std::string fName = className +
                          FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX +
                          element.first;
      llvm::Function *f = TheModule->getFunction(fName);

      llvm::Value *vTableElementPtr = builder->CreateStructGEP(
          _vTableType, vTablePtr, std::get<1>(element.second));

      builder->CreateStore(f, vTableElementPtr);
    }
  }

  inline auto getFunctionPtr(llvm::IRBuilder<> *builder,
                             llvm::Module *TheModule,
                             llvm::LLVMContext *context,
                             std::string functionName, llvm::Value *ptr)
      -> llvm::Value * {

    llvm::Value *vTablePtr = builder->CreateLoad(
        llvm::PointerType::getInt8PtrTy(*context),
        builder->CreateStructGEP(_classType, ptr,
                                 _classType->getNumElements() - 1));
    std::string fName = functionName.substr(functionName.find(".") + 1);
    if (!_vTableElementsMap.count(fName)) {

      return nullptr;
    }

    uint64_t index = std::get<1>(_vTableElementsMap[fName]);

    return builder->CreateLoad(
        llvm::PointerType::getInt8PtrTy(*context),
        builder->CreateStructGEP(_vTableType, vTablePtr, index));
  }
};

#endif