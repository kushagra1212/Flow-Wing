#ifndef __FLOWWING__ARG__TYPE_HANLDER_H__
#define __FLOWWING__ARG__TYPE_HANLDER_H__

#include "LLVMType/LLVMArrayType/LLVMArrayType.h"

class ArgsTypeHandler {
 private:
  std::unordered_map<std::string, std::vector<std::unique_ptr<LLVMType>>>
      _argsTypeMap;

 public:
  inline void addArgsType(const std::string &funcName,
                          std::unique_ptr<LLVMType> argsType) {
    _argsTypeMap[funcName].push_back(std::move(argsType));
  }

  inline const std::vector<std::unique_ptr<LLVMType>> &getArgsType(
      const std::string &funcName) {
    return _argsTypeMap[(funcName)];
  }
};

#endif  // __FLOWWING__ARG__TYPE_HANLDER_H__