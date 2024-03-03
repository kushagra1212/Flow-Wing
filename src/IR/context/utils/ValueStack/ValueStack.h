#ifndef __FLOW__WING_VALUE_STACK
#define __FLOW__WING_VALUE_STACK

#include "llvm/IR/Value.h"
#include "string"

class ValueStack {
 public:
  std::string typeName;
  llvm::Value *value;
  std::string type;
  llvm::Type *llvmType;
  ValueStack(const std::string &typeName, llvm::Value *value,
             const std::string &type, llvm::Type *llvmType)
      : typeName(typeName), value(value), type(type), llvmType(llvmType) {}

  auto inline getValue() -> llvm::Value * { return value; }
  auto inline getTypeName() -> std::string { return typeName; }
  auto inline getType() -> std::string { return type; }

  auto inline getLLVMType() -> llvm::Type * { return llvmType; }
};

#endif