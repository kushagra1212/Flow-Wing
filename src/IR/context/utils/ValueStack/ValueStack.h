#ifndef __FLOW__WING_VALUE_STACK
#define __FLOW__WING_VALUE_STACK

#include "string"
#include "llvm/IR/Value.h"

class ValueStack {
public:
  std::string typeName;
  llvm::Value *value;
  std::string type;
  llvm::Type *llvmType;
  llvm::Value *dynamicValue;
  ValueStack(const std::string &typeName, llvm::Value *value,
             const std::string &type, llvm::Type *llvmType,
             llvm::Value *dynamicValue)
      : typeName(typeName), value(value), type(type), llvmType(llvmType),
        dynamicValue(dynamicValue) {}

  auto inline getValue() -> llvm::Value * { return value; }
  auto inline getTypeName() -> std::string { return typeName; }
  auto inline getType() -> std::string { return type; }

  auto inline getLLVMType() -> llvm::Type * { return llvmType; }
  auto inline getDynamicValue() -> llvm::Value * { return dynamicValue; }
};

#endif