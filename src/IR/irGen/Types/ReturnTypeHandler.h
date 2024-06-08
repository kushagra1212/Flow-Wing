#ifndef __FLOWWING__RETURN__TYPE_HANLDER_H__
#define __FLOWWING__RETURN__TYPE_HANLDER_H__

#include "LLVMType/LLVMArrayType/LLVMArrayType.h"

class ReturnType {
private:
  std::unique_ptr<LLVMType> _returnType;
  bool _hasAsReturnType = false;

public:
  ReturnType(std::unique_ptr<LLVMType> returnType, bool hasAsReturnType) {
    _returnType = (std::move(returnType));
    _hasAsReturnType = (hasAsReturnType);
  }

  inline std::unique_ptr<LLVMType> &getReturnType() { return _returnType; }

  inline bool hasAsReturnType() const { return _hasAsReturnType; }
};

class ReturnTypeHandler {
private:
  std::unordered_map<std::string, std::unique_ptr<ReturnType>> _returnTypeMap;

public:
  inline void addReturnType(const std::string &funcName,
                            std::unique_ptr<LLVMType> returnType,
                            bool hasAsReturnType) {
    _returnTypeMap[funcName] =
        std::make_unique<ReturnType>(std::move(returnType), hasAsReturnType);
  }

  inline std::unique_ptr<LLVMType> &getReturnType(const std::string &funcName) {
    return _returnTypeMap[funcName]->getReturnType();
  }

  inline bool hasAsReturnType(const std::string &funcName) {
    return _returnTypeMap[funcName]->hasAsReturnType();
  }

  inline auto isHavingReturnTypeAsParameter(const std::string &funcName)
      -> bool {
    if (this->hasAsReturnType(funcName))
      return false;

    if (this->getReturnType(funcName)->getLLVMType()->isVoidTy())
      return false;

    return true;
  }
};

#endif // __FLOWWING__RETURN__TYPE_HANLDER_H__