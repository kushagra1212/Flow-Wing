#ifndef __FLOW_WING_VALUE_STACK_HANDLE
#define __FLOW_WING_VALUE_STACK_HANDLE

#include "../../../constants/FlowWingIRConstants.h"
#include "ValueStack.h"
#include <stack>

class ValueStackHandler {
  auto inline isType(const std::string type) -> bool {
    if (vs.empty()) {
      return false;
    }

    ValueStack *valueStack = vs.top();
    return valueStack->getType() == type;
  }

public:
  std::stack<ValueStack *> vs;

  auto inline push(const std::string &typeName, llvm::Value *value,
                   const std::string &type, llvm::Type *llvmType,
                   llvm::Value *dynamicValue = nullptr) {
    vs.push(new ValueStack(typeName, value, type, llvmType, dynamicValue));
  }

  auto inline getTypeName() -> std::string {
    if (vs.empty()) {
      return "";
    }

    ValueStack *valueStack = vs.top();
    return valueStack->getTypeName();
  }

  auto inline getValue() -> llvm::Value * {
    if (vs.empty()) {
      return nullptr;
    }

    ValueStack *valueStack = vs.top();
    return valueStack->getValue();
  }

  auto inline pop() {
    ValueStack *valueStack = vs.top();
    vs.pop();
    delete valueStack;
  }

  auto inline popAll() {
    while (!vs.empty()) {
      pop();
    }
  }

  auto inline isStructType() -> bool { return isType("struct"); }

  auto inline getLLVMType() -> llvm::Type * {
    if (vs.empty()) {
      return nullptr;
    }

    ValueStack *valueStack = vs.top();
    return valueStack->getLLVMType();
  }

  auto inline isPrimaryType() -> bool { return isType("primary"); }

  auto inline isNothingType() -> bool { return isType("nothing"); }

  auto inline isFunctionType() -> bool { return isType("function"); }

  auto inline isArrayType() -> bool { return isType("array"); }

  auto inline isDynamicValueType() -> bool {
    return isType(
        FLOWWING::IR::CONSTANTS::DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE);
  }

  auto inline isDynamicType() -> bool { return isType("dynamic"); }

  auto inline isLLVMConstant() -> bool { return isType("constant"); }

  auto inline isEmpty() -> bool { return vs.empty(); }

  auto inline getDynamicValue() -> llvm::Value * {
    if (vs.empty()) {
      return nullptr;
    }

    ValueStack *valueStack = vs.top();
    return valueStack->getDynamicValue();
  }
};

#endif