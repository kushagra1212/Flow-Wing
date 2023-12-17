#ifndef TYPEMAPPER_H
#define TYPEMAPPER_H

#include "../../../Common.h"
#include "../../../utils/Utils.h"
#include "../../constants/FlowWingIRConstants.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
using namespace FLOWWING::IR::CONSTANTS;

class TypeMapper {
  llvm::LLVMContext *_context;
  llvm::IRBuilder<> *_builder;
  std::unordered_map<llvm::Type *, Utils::type> _typeMappings;
  std::unordered_map<Utils::type, llvm::Type *> _reverseTypeMappings;

public:
  TypeMapper(llvm::LLVMContext *context, llvm::IRBuilder<> *builder);

  Utils::type mapLLVMTypeToCustomType(llvm::Type *type) const;
  llvm::Type *mapCustomTypeToLLVMType(Utils::type type) const;
  const bool isVoidType(llvm::Type *type) const;
  const bool isStringType(llvm::Type *type) const;
  const bool isBoolType(llvm::Type *type) const;
  const bool isDoubleType(llvm::Type *type) const;
  const bool isInt64Type(llvm::Type *type) const;
  const bool isInt32Type(llvm::Type *type) const;
  llvm::Value *getDefaultValue(Utils::type type);
  llvm::Value *getDefaultValue(llvm::Type *type);

  std::string getLLVMTypeName(llvm::Type *type) const;
  std::string getLLVMTypeName(Utils::type customType) const;
};

#endif // TYPEMAPPER_H
