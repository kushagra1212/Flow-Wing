#include "DoubleTypeConverter.h"

DoubleTypeConverter::DoubleTypeConverter(CodeGenerationContext *context)
    : TypeConverterBase(context){};

llvm::Value *DoubleTypeConverter::convertExplicit(llvm::Value *value) {

  llvm::Value *res = nullptr;

  CustomLLVMType type =
      this->_mapper->mapLLVMTypeToCustomType(value->getType());

  switch (type) {

  case CustomLLVMType::Int16:
  case CustomLLVMType::Int32:
  case CustomLLVMType::Int64: {
    return _builder->CreateSIToFP(
        value, llvm::Type::getDoubleTy(_builder->getContext()));
  }
  case CustomLLVMType::Float: {
    return _builder->CreateFPTrunc(
        value, llvm::Type::getDoubleTy(_builder->getContext()));
  }
  case CustomLLVMType::Double: {
    return value;
  }
  case CustomLLVMType::Bool: {
    return _builder->CreateUIToFP(
        value, llvm::Type::getDoubleTy(_builder->getContext()));
  }
  case CustomLLVMType::String: {

    return _builder->CreateCall(
        _module->getFunction(INNERS::FUNCTIONS::STRING_TO_DOUBLE), {value});
  }
  default:
    break;
  }

  _logger->logLLVMError(
      llvm::createStringError(llvm::inconvertibleErrorCode(),
                              "Unsupported type for conversion to double"));

  return nullptr;
}

llvm::Value *DoubleTypeConverter::convertImplicit(llvm::Value *value) {
  llvm::Value *res = nullptr;

  CustomLLVMType type =
      this->_mapper->mapLLVMTypeToCustomType(value->getType());

  switch (type) {

  case CustomLLVMType::Int16:
  case CustomLLVMType::Int32:
  case CustomLLVMType::Int64: {
    return _builder->CreateSIToFP(
        value, llvm::Type::getDoubleTy(_builder->getContext()));
  }
  case CustomLLVMType::Float: {
    return _builder->CreateFPTrunc(
        value, llvm::Type::getDoubleTy(_builder->getContext()));
  }
  case CustomLLVMType::Double: {
    return value;
  }
  case CustomLLVMType::Bool: {
    _logger->logLLVMError(llvm::createStringError(
        llvm::inconvertibleErrorCode(),
        "Implicit conversion from bool to double is not "
        "supported for variable with predefined type"));
    return nullptr;
  }
  case CustomLLVMType::String: {
    _logger->logLLVMError(llvm::createStringError(
        llvm::inconvertibleErrorCode(),
        "Implicit conversion from string to double is not "
        "supported for variable with predefined type"));

    return nullptr;
  }
  default:
    break;
  }

  _logger->logLLVMError(
      llvm::createStringError(llvm::inconvertibleErrorCode(),
                              "Unsupported type for conversion to double"));

  return nullptr;
}