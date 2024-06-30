#include "FloatTypeConverter.h"

FloatTypeConverter::FloatTypeConverter(CodeGenerationContext *context)
    : TypeConverterBase(context){};

llvm::Value *FloatTypeConverter::convertExplicit(llvm::Value *&value) {
  llvm::Value *res = nullptr;

  SyntaxKindUtils::SyntaxKind type =
      this->_mapper->mapLLVMTypeToCustomType(value->getType());

  switch (type) {
  case SyntaxKindUtils::SyntaxKind::Int32Keyword:
  case SyntaxKindUtils::SyntaxKind::Int64Keyword:
  case SyntaxKindUtils::SyntaxKind::Int8Keyword: {
    return _builder->CreateSIToFP(
        value, llvm::Type::getFloatTy(_builder->getContext()));
  }
  case SyntaxKindUtils::SyntaxKind::DeciKeyword: {
    return _builder->CreateFPTrunc(
        value, llvm::Type::getFloatTy(_builder->getContext()));
  }
  case SyntaxKindUtils::SyntaxKind::Deci32Keyword: {
    return value;
  }
  case SyntaxKindUtils::SyntaxKind::BoolKeyword: {
    return _builder->CreateUIToFP(
        value, llvm::Type::getFloatTy(_builder->getContext()));
  }
  case SyntaxKindUtils::SyntaxKind::StrKeyword: {
    llvm::Value *val = _builder->CreateCall(
        _module->getFunction(INNERS::FUNCTIONS::STRING_TO_DOUBLE), {value});
    return this->convertExplicit(val);
  }
  default:
    break;
  }

  _logger->logLLVMError(
      llvm::createStringError(llvm::inconvertibleErrorCode(),
                              "Unsupported type for conversion to double"));

  return nullptr;
}

llvm::Value *FloatTypeConverter::convertImplicit(llvm::Value *&value) {
  llvm::Value *res = nullptr;

  SyntaxKindUtils::SyntaxKind type =
      this->_mapper->mapLLVMTypeToCustomType(value->getType());

  switch (type) {
  case SyntaxKindUtils::SyntaxKind::Int32Keyword:
  case SyntaxKindUtils::SyntaxKind::Int8Keyword: {
    return _builder->CreateSIToFP(
        value, llvm::Type::getDoubleTy(_builder->getContext()));
  }
  case SyntaxKindUtils::SyntaxKind::Int64Keyword: {
    _logger->logLLVMError(llvm::createStringError(
        llvm::inconvertibleErrorCode(),
        "Implicit conversion from int64 to deci32 is not "
        "supported for variable with predefined type"));
    return nullptr;
  }
  case SyntaxKindUtils::SyntaxKind::DeciKeyword: {
    _logger->logLLVMError(llvm::createStringError(
        llvm::inconvertibleErrorCode(),
        "Implicit conversion from deci to deci32 is not "
        "supported for variable with predefined type"));
    return nullptr;
  }
  case SyntaxKindUtils::SyntaxKind::Deci32Keyword: {
    return value;
  }
  case SyntaxKindUtils::SyntaxKind::BoolKeyword: {
    _logger->logLLVMError(llvm::createStringError(
        llvm::inconvertibleErrorCode(),
        "Implicit conversion from bool to double is not "
        "supported for variable with predefined type"));
    return nullptr;
  }
  case SyntaxKindUtils::SyntaxKind::StrKeyword: {
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