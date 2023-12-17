#include "TypeMapper.h"

TypeMapper::TypeMapper(llvm::LLVMContext *context, llvm::IRBuilder<> *builder)
    : _context(context), _builder(builder) {
  _typeMappings = {
      {(llvm::Type *)llvm::Type::getInt1Ty(*context), Utils::type::BOOL},
      {(llvm::Type *)llvm::Type::getInt8Ty(*context), Utils::type::INT8},
      {(llvm::Type *)llvm::Type::getInt16Ty(*context), Utils::type::INT16},
      {(llvm::Type *)llvm::Type::getInt32Ty(*context), Utils::type::INT32},
      {(llvm::Type *)llvm::Type::getInt64Ty(*context), Utils::type::INT64},
      {(llvm::Type *)llvm::Type::getDoubleTy(*context), Utils::type::DECIMAL},
      {(llvm::Type *)llvm::Type::getInt8PtrTy(*context), Utils::type::STRING},
      {(llvm::Type *)llvm::Type::getVoidTy(*context), Utils::type::NOTHING},
  };

  _reverseTypeMappings = {
      {Utils::type::BOOL, (llvm::Type *)llvm::Type::getInt1Ty(*context)},
      {Utils::type::INT8, (llvm::Type *)llvm::Type::getInt8Ty(*context)},
      {Utils::type::INT16, (llvm::Type *)llvm::Type::getInt16Ty(*context)},
      {Utils::type::INT32, (llvm::Type *)llvm::Type::getInt32Ty(*context)},
      {Utils::type::INT64, (llvm::Type *)llvm::Type::getInt64Ty(*context)},
      {Utils::type::DECIMAL, (llvm::Type *)llvm::Type::getDoubleTy(*context)},
      {Utils::type::STRING, (llvm::Type *)llvm::Type::getInt8PtrTy(*context)},
      {Utils::type::NOTHING, (llvm::Type *)llvm::Type::getVoidTy(*context)},
  };
}

llvm::Type *TypeMapper::mapCustomTypeToLLVMType(Utils::type type) const {
  auto it = _reverseTypeMappings.find(type);
  if (it != _reverseTypeMappings.end()) {
    return it->second;
  } else {
    return nullptr;
  }
}

Utils::type TypeMapper::mapLLVMTypeToCustomType(llvm::Type *type) const {
  auto it = _typeMappings.find(type);
  if (it != _typeMappings.end()) {
    return it->second;
  } else {
    return Utils::type::UNKNOWN;
  }
}

const bool TypeMapper::isVoidType(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) == Utils::type::NOTHING;
}

const bool TypeMapper::isStringType(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) == Utils::type::STRING;
}

const bool TypeMapper::isBoolType(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) == Utils::type::BOOL;
}

const bool TypeMapper::isDoubleType(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) == Utils::type::DECIMAL;
}

const bool TypeMapper::isInt64Type(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) == Utils::type::INT64;
}

const bool TypeMapper::isInt32Type(llvm::Type *type) const {
  return mapLLVMTypeToCustomType(type) == Utils::type::INT32;
}
std::string TypeMapper::getLLVMTypeName(llvm::Type *type) const {

  Utils::type customType = mapLLVMTypeToCustomType(type);

  return getLLVMTypeName(customType);
}

std::string TypeMapper::getLLVMTypeName(Utils::type customType) const {

  switch (customType) {
  case Utils::type::BOOL:
    return "Boolean";
  case Utils::type::INT8:
  case Utils::type::INT16:
  case Utils::type::INT32:
  case Utils::type::INT64:
    return "Integer";
  case Utils::type::DECIMAL:
    return "Decimal";
  case Utils::type::STRING:
    return "String";
  case Utils::type::NOTHING:
    return "Nothing";
  default:
    break;
  }

  return "Unknown";
}

llvm::Value *TypeMapper::getDefaultValue(Utils::type type) {
  llvm::Value *_retVal = nullptr;

  switch (type) {
  case Utils::type::INT32:
    _retVal = _builder->getInt32(0);
    break;
  case Utils::type::DECIMAL:
    _retVal = llvm::ConstantFP::get(*_context, llvm::APFloat(0.0));
    break;
  case Utils::type::BOOL:
    _retVal = _builder->getInt1(false);
    break;
  case Utils::type::STRING:
    _retVal = _builder->CreateGlobalStringPtr("");
    break;
  case Utils::type::NOTHING:
    break;
  case Utils::type::UNKNOWN:
    break;
  default:
    break;
  }
  return _retVal;
}

llvm::Value *TypeMapper::getDefaultValue(llvm::Type *type) {
  return getDefaultValue(mapLLVMTypeToCustomType(type));
}
