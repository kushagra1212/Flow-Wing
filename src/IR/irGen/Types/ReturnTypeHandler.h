#ifndef __FLOWWING__RETURN__TYPE_HANLDER_H__
#define __FLOWWING__RETURN__TYPE_HANLDER_H__

#include "LLVMType/LLVMArrayType/LLVMArrayType.h"

class ReturnTypeHandler {

private:
  std::unordered_map<std::string, std::unique_ptr<LLVMType>> _returnTypeMap;

public:
  inline void addReturnType(const std::string &funcName,
                            std::unique_ptr<LLVMType> returnType) {
    _returnTypeMap[funcName] = (std::move(returnType));
  }

  inline std::unique_ptr<LLVMType> &getReturnType(const std::string &funcName) {
    return _returnTypeMap[funcName];
  }
};

#endif // __FLOWWING__RETURN__TYPE_HANLDER_H__