#ifndef TYPEMAPPER_H
#define TYPEMAPPER_H

#include "../../../Common.h"
#include "../../constants/FlowWingIRConstants.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

using namespace FLOWWING::IR::CONSTANTS;

class TypeMapper {
  llvm::LLVMContext *_context;
  std::unordered_map<llvm::Type *, CustomLLVMType> _typeMappings;
  std::unordered_map<CustomLLVMType, llvm::Type *> _reverseTypeMappings;

public:
  TypeMapper(llvm::LLVMContext *context);

  const CustomLLVMType mapLLVMTypeToCustomType(llvm::Type *type) const;
  const llvm::Type *mapCustomTypeToLLVMType(CustomLLVMType type) const;
  const bool isVoidType(llvm::Type *type) const;
  const bool isStringType(llvm::Type *type) const;
  const bool isBoolType(llvm::Type *type) const;
  const bool isDoubleType(llvm::Type *type) const;
  const bool isFloatType(llvm::Type *type) const;
  const bool isInt64Type(llvm::Type *type) const;
  const bool isInt32Type(llvm::Type *type) const;
};

#endif // TYPEMAPPER_H
