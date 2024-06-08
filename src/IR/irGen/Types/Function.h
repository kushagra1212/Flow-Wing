#ifndef __FUNCTION_TYPE_H__
#define __FUNCTION_TYPE_H__

#include "llvm/IR/Module.h"
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>

class Function {
public:
  inline auto setFunctionName(std::string functionName) -> void {
    this->_functionName = functionName;
  }

  inline auto getFunctionName() -> std::string { return _functionName; }

  inline auto getReturnType() -> llvm::Type * { return _returnType; }

  inline auto setReturnType(llvm::Type *returnType, bool hasAsReturnType)
      -> void {
    this->_returnType = returnType;
    this->_hasAsReturnType = hasAsReturnType;
  }

  inline auto isHavingReturnTypeAsParamater() -> bool {

    if (_hasAsReturnType)
      return false;

    if (_returnType->isVoidTy())
      return false;

    return true;
  }

private:
  std::string _functionName;
  llvm::Type *_returnType;
  bool _hasAsReturnType = false;
};

#endif
