#ifndef __FLOW_WING_VALUE_STACK_HANDLE
#define __FLOW_WING_VALUE_STACK_HANDLE

#include "ValueStack.h"

class ValueStackHandler {
public:
  std::stack<ValueStack *> vs;

  auto inline push(const std::string &typeName, llvm::Value *value,
                   const std::string &type, llvm::Type *llvmType) {
    vs.push(new ValueStack(typeName, value, type, llvmType));
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

  auto inline isStructType() -> bool {
    if (vs.empty()) {
      return false;
    }

    ValueStack *valueStack = vs.top();
    return valueStack->getType() == "struct";
  }

  auto inline getLLVMType() -> llvm::Type * {
    if (vs.empty()) {
      return nullptr;
    }

    ValueStack *valueStack = vs.top();
    return valueStack->getLLVMType();
  }

  auto inline isPrimaryType() -> bool {
    if (vs.empty()) {
      return false;
    }

    ValueStack *valueStack = vs.top();
    return valueStack->getType() == "primary";
  }

  auto inline isArrayType() -> bool {
    if (vs.empty()) {
      return false;
    }

    ValueStack *valueStack = vs.top();
    return valueStack->getType() == "array";
  }
};

#endif