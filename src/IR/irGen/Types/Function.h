#ifndef __FUNCTION_TYPE_H__
#define __FUNCTION_TYPE_H__

#include "../../../bind/BoundVariableDeclaration/BoundVariableDeclaration.h"
#include "llvm/IR/Module.h"
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>

namespace FlowWing {
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

  inline auto addParameter(BoundVariableDeclaration *parameter) -> void {
    _parameters.push_back(parameter);
  }

  inline auto getParameterListRef() const
      -> const std::vector<BoundVariableDeclaration *> & {
    return _parameters;
  }
  inline auto getParameterListSize() const { return _parameters.size(); }

  inline auto setOptionalParameterStartIndex(int64_t index) -> void {
    _optionalParameterStartIndex = index;
  }

  inline auto getOptionalParameterStartIndex() -> int64_t {
    return _optionalParameterStartIndex;
  }

  inline auto hasOptionalParameters() -> bool {
    return _optionalParameterStartIndex != -1;
  }
  inline auto addAsParam(bool hasAsParam) -> void {
    _hasAsParams.push_back(hasAsParam);
  }

  inline auto hasAsParamsRef() { return _hasAsParams; }

private:
  std::string _functionName;
  llvm::Type *_returnType;
  bool _hasAsReturnType = false;
  std::vector<BoundVariableDeclaration *> _parameters;
  int64_t _optionalParameterStartIndex = -1;
  std::vector<bool> _hasAsParams;
};
} // namespace FlowWing

#endif
