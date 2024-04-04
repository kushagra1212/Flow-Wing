#ifndef TYPEMAPPER_H
#define TYPEMAPPER_H

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

#include "../../../Common.h"
#include "../../../utils/Utils.h"
#include "../../constants/FlowWingIRConstants.h"
using namespace FLOWWING::IR::CONSTANTS;

class TypeMapper {
  llvm::LLVMContext *_context;
  llvm::IRBuilder<> *_builder;
  std::unordered_map<llvm::Type *, SyntaxKindUtils::SyntaxKind> _typeMappings;
  std::unordered_map<SyntaxKindUtils::SyntaxKind, llvm::Type *>
      _reverseTypeMappings;

public:
  TypeMapper(llvm::LLVMContext *context, llvm::IRBuilder<> *builder);

  SyntaxKindUtils::SyntaxKind mapLLVMTypeToCustomType(llvm::Type *type) const;
  llvm::Type *mapCustomTypeToLLVMType(SyntaxKindUtils::SyntaxKind type) const;
  const bool isVoidType(llvm::Type *type) const;
  const bool isStringType(llvm::Type *type) const;
  const bool isBoolType(llvm::Type *type) const;
  const bool isDoubleType(llvm::Type *type) const;
  const bool isInt32Type(llvm::Type *type) const;
  const bool isInt8Type(llvm::Type *type) const;
  const bool isPtrType(llvm::Type *type) const;
  const bool isPrimitiveType(llvm::Type *type) const;
  const bool isPrimitiveType(SyntaxKindUtils::SyntaxKind type) const;
  const bool isEquivalentType(llvm::Type *type,
                              SyntaxKindUtils::SyntaxKind customType) const;
  const bool isEquivalentType(SyntaxKindUtils::SyntaxKind customType,
                              llvm::Type *type) const;
  const bool isEquivalentType(llvm::Type *type1, llvm::Type *type2) const;
  const bool isEquivalentType(SyntaxKindUtils::SyntaxKind type1,
                              SyntaxKindUtils::SyntaxKind type2) const;

  llvm::Value *getDefaultValue(SyntaxKindUtils::SyntaxKind type);
  llvm::Value *getDefaultValue(llvm::Type *type);

  std::string getLLVMTypeName(llvm::Type *type) const;
  std::string getLLVMTypeName(SyntaxKindUtils::SyntaxKind customType) const;
};

#endif // TYPEMAPPER_H
