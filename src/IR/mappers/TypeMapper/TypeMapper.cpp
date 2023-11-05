#include "TypeMapper.h"

TypeMapper::TypeMapper(llvm::LLVMContext *context) : _context(context) {
  _typeMappings = {
      {(llvm::Type *)llvm::Type::getInt1Ty(*context), CustomLLVMType::Bool},
      {(llvm::Type *)llvm::Type::getInt8Ty(*context), CustomLLVMType::Int8},
      {(llvm::Type *)llvm::Type::getInt16Ty(*context), CustomLLVMType::Int16},
      {(llvm::Type *)llvm::Type::getInt32Ty(*context), CustomLLVMType::Int32},
      {(llvm::Type *)llvm::Type::getInt64Ty(*context), CustomLLVMType::Int64},
      {(llvm::Type *)llvm::Type::getFloatTy(*context), CustomLLVMType::Float},
      {(llvm::Type *)llvm::Type::getDoubleTy(*context), CustomLLVMType::Double},
      {(llvm::Type *)llvm::Type::getInt8PtrTy(*context),
       CustomLLVMType::String},
      {(llvm::Type *)llvm::Type::getVoidTy(*context), CustomLLVMType::Void},
  };

  _reverseTypeMappings = {
      {CustomLLVMType::Bool, (llvm::Type *)llvm::Type::getInt1Ty(*context)},
      {CustomLLVMType::Int8, (llvm::Type *)llvm::Type::getInt8Ty(*context)},
      {CustomLLVMType::Int16, (llvm::Type *)llvm::Type::getInt16Ty(*context)},
      {CustomLLVMType::Int32, (llvm::Type *)llvm::Type::getInt32Ty(*context)},
      {CustomLLVMType::Int64, (llvm::Type *)llvm::Type::getInt64Ty(*context)},
      {CustomLLVMType::Float, (llvm::Type *)llvm::Type::getFloatTy(*context)},
      {CustomLLVMType::Double, (llvm::Type *)llvm::Type::getDoubleTy(*context)},
      {CustomLLVMType::String,
       (llvm::Type *)llvm::Type::getInt8PtrTy(*context)},
      {CustomLLVMType::Void, (llvm::Type *)llvm::Type::getVoidTy(*context)},
  };
}

const llvm::Type *
TypeMapper::mapCustomTypeToLLVMType(CustomLLVMType type) const {
  auto it = _reverseTypeMappings.find(type);
  if (it != _reverseTypeMappings.end()) {
    return it->second;
  } else {
    return nullptr;
  }
}

const CustomLLVMType
TypeMapper::mapLLVMTypeToCustomType(llvm::Type *type) const {
  auto it = _typeMappings.find(type);
  if (it != _typeMappings.end()) {
    return it->second;
  } else {
    return CustomLLVMType::Unknown;
  }
}

const bool TypeMapper::isVoidType(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) == CustomLLVMType::Void;
}

const bool TypeMapper::isStringType(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) == CustomLLVMType::String;
}

const bool TypeMapper::isBoolType(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) == CustomLLVMType::Bool;
}

const bool TypeMapper::isDoubleType(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) == CustomLLVMType::Double;
}

const bool TypeMapper::isFloatType(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) == CustomLLVMType::Float;
}

const bool TypeMapper::isInt64Type(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) == CustomLLVMType::Int64;
}

const bool TypeMapper::isInt32Type(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) == CustomLLVMType::Int32;
}