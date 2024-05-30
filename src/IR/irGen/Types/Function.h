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

  inline auto setReturnType(llvm::Type *returnType) -> void {
    this->_returnType = returnType;
  }

  inline auto isNonPrimitiveReturnType() -> bool {
    return llvm::isa<llvm::StructType>(_returnType) ||
           llvm::isa<llvm::ArrayType>(_returnType);
  }

private:
  std::string _functionName;
  llvm::Type *_returnType;
};

#endif
