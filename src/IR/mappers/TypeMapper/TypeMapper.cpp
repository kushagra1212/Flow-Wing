#include "TypeMapper.h"

TypeMapper::TypeMapper(llvm::LLVMContext *context, llvm::IRBuilder<> *builder)
    : _context(context), _builder(builder) {
  _typeMappings = {
      {(llvm::Type *)llvm::Type::getInt1Ty(*context),
       SyntaxKindUtils::SyntaxKind::BoolKeyword},
      {(llvm::Type *)llvm::Type::getInt32Ty(*context),
       SyntaxKindUtils::SyntaxKind::Int32Keyword},
      {(llvm::Type *)llvm::Type::getDoubleTy(*context),
       SyntaxKindUtils::SyntaxKind::DeciKeyword},
      {(llvm::Type *)llvm::Type::getInt8PtrTy(*context),
       SyntaxKindUtils::SyntaxKind::StrKeyword},
      {(llvm::Type *)llvm::Type::getVoidTy(*context),
       SyntaxKindUtils::SyntaxKind::NthgKeyword},
  };

  _reverseTypeMappings = {
      {SyntaxKindUtils::SyntaxKind::BoolKeyword,
       (llvm::Type *)llvm::Type::getInt1Ty(*context)},
      {SyntaxKindUtils::SyntaxKind::Int32Keyword,
       (llvm::Type *)llvm::Type::getInt32Ty(*context)},
      {SyntaxKindUtils::SyntaxKind::DeciKeyword,
       (llvm::Type *)llvm::Type::getDoubleTy(*context)},
      {SyntaxKindUtils::SyntaxKind::StrKeyword,
       (llvm::Type *)llvm::Type::getInt8PtrTy(*context)},
      {SyntaxKindUtils::SyntaxKind::NthgKeyword,
       (llvm::Type *)llvm::Type::getVoidTy(*context)},
  };
}

llvm::Type *TypeMapper::mapCustomTypeToLLVMType(
    SyntaxKindUtils::SyntaxKind type) const {
  auto it = _reverseTypeMappings.find(type);
  if (it != _reverseTypeMappings.end()) {
    return it->second;
  } else {
    return nullptr;
  }
}

SyntaxKindUtils::SyntaxKind TypeMapper::mapLLVMTypeToCustomType(
    llvm::Type *type) const {
  auto it = _typeMappings.find(type);
  if (it != _typeMappings.end()) {
    return it->second;
  } else {
    return SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE;
  }
}

const bool TypeMapper::isVoidType(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) ==
         SyntaxKindUtils::SyntaxKind::NthgKeyword;
}

const bool TypeMapper::isStringType(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) ==
         SyntaxKindUtils::SyntaxKind::StrKeyword;
}

const bool TypeMapper::isBoolType(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) ==
         SyntaxKindUtils::SyntaxKind::BoolKeyword;
}

const bool TypeMapper::isDoubleType(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) ==
         SyntaxKindUtils::SyntaxKind::DeciKeyword;
}

const bool TypeMapper::isInt32Type(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) ==
         SyntaxKindUtils::SyntaxKind::Int32Keyword;
}

const bool TypeMapper::isPtrType(llvm::Type *type) const {
  return type->isPointerTy();
}
std::string TypeMapper::getLLVMTypeName(llvm::Type *type) const {
  SyntaxKindUtils::SyntaxKind customType = mapLLVMTypeToCustomType(type);

  return getLLVMTypeName(customType);
}

std::string TypeMapper::getLLVMTypeName(
    SyntaxKindUtils::SyntaxKind customType) const {
  switch (customType) {
    case SyntaxKindUtils::SyntaxKind::BoolKeyword:
      return "Boolean";
    case SyntaxKindUtils::SyntaxKind::Int32Keyword:
      return "Integer32";
    case SyntaxKindUtils::SyntaxKind::DeciKeyword:
      return "Decimal";
    case SyntaxKindUtils::SyntaxKind::StrKeyword:
      return "String";
    case SyntaxKindUtils::SyntaxKind::NthgKeyword:
      return "Nothing";
    default:
      break;
  }

  return "Unknown";
}

llvm::Value *TypeMapper::getDefaultValue(SyntaxKindUtils::SyntaxKind type) {
  llvm::Value *_retVal = nullptr;

  switch (type) {
    case SyntaxKindUtils::SyntaxKind::Int32Keyword:
      _retVal = _builder->getInt32(0);
      break;
    case SyntaxKindUtils::SyntaxKind::DeciKeyword:
      _retVal = llvm::ConstantFP::get(*_context, llvm::APFloat(0.0));
      break;
    case SyntaxKindUtils::SyntaxKind::BoolKeyword:
      _retVal = _builder->getInt1(false);
      break;
    case SyntaxKindUtils::SyntaxKind::StrKeyword:
      _retVal = _builder->CreateGlobalStringPtr("");
      break;
    case SyntaxKindUtils::SyntaxKind::NthgKeyword:
      break;
    case SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE:
      break;
    default:
      break;
  }
  return _retVal;
}

llvm::Value *TypeMapper::getDefaultValue(llvm::Type *type) {
  return getDefaultValue(mapLLVMTypeToCustomType(type));
}

const bool TypeMapper::isPrimitiveType(llvm::Type *type) const {
  return isBoolType(type) || isDoubleType(type) || isInt32Type(type) ||
         isStringType(type);
}

const bool TypeMapper::isPrimitiveType(SyntaxKindUtils::SyntaxKind type) const {
  return isPrimitiveType(mapCustomTypeToLLVMType(type));
}

const bool TypeMapper::isEquivalentType(
    llvm::Type *type, SyntaxKindUtils::SyntaxKind customType) const {
  return type == mapCustomTypeToLLVMType(customType);
}
const bool TypeMapper::isEquivalentType(SyntaxKindUtils::SyntaxKind customType,
                                        llvm::Type *type) const {
  return isEquivalentType(type, customType);
}
const bool TypeMapper::isEquivalentType(llvm::Type *type1,
                                        llvm::Type *type2) const {
  return type1 == type2;
}
const bool TypeMapper::isEquivalentType(
    SyntaxKindUtils::SyntaxKind type1,
    SyntaxKindUtils::SyntaxKind type2) const {
  return type1 == type2;
}