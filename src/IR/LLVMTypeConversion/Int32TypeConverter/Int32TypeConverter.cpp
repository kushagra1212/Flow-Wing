#include "Int32TypeConverter.h"

Int32TypeConverter::Int32TypeConverter(CodeGenerationContext *context)
    : TypeConverterBase(context){};

llvm::Value *Int32TypeConverter::convertExplicit(llvm::Value *&value) {
  llvm::Value *res = nullptr;

  llvm::LLVMContext *TheContext = _codeGenerationContext->getContext().get();

  SyntaxKindUtils::SyntaxKind type =
      this->_mapper->mapLLVMTypeToCustomType(value->getType());

  switch (type) {
  case SyntaxKindUtils::SyntaxKind::Int32Keyword: {
    return value;
  }
  case SyntaxKindUtils::SyntaxKind::Int8Keyword: {
    return _builder->CreateSExt(value, llvm::Type::getInt32Ty(*TheContext));
  }
  case SyntaxKindUtils::SyntaxKind::Int64Keyword: {
    return _builder->CreateTrunc(value, llvm::Type::getInt32Ty(*TheContext));
  }
  case SyntaxKindUtils::SyntaxKind::DeciKeyword:
  case SyntaxKindUtils::SyntaxKind::Deci32Keyword: {
    return _builder->CreateFPToSI(value, llvm::Type::getInt32Ty(*TheContext));
  }
  case SyntaxKindUtils::SyntaxKind::BoolKeyword: {
    return _builder->CreateZExt(value, llvm::Type::getInt32Ty(*TheContext));
  }
  case SyntaxKindUtils::SyntaxKind::StrKeyword: {
    // TODO: Implement explicit conversion from string to int

    return _builder->CreateCall(
        _module->getFunction(INNERS::FUNCTIONS::STRING_TO_INT), {value});
  }
  default:
    break;
  }

  _logger->logLLVMError(
      llvm::createStringError(llvm::inconvertibleErrorCode(),
                              "Unsupported type for conversion to int32"));

  return res;
}

llvm::Value *Int32TypeConverter::convertImplicit(llvm::Value *&value) {
  llvm::Value *res = nullptr;

  SyntaxKindUtils::SyntaxKind type =
      this->_mapper->mapLLVMTypeToCustomType(value->getType());

  switch (type) {
  case SyntaxKindUtils::SyntaxKind::Int32Keyword: {
    return value;
  }
  case SyntaxKindUtils::SyntaxKind::Int8Keyword: {
    return _builder->CreateSExt(value,
                                llvm::Type::getInt32Ty(_builder->getContext()));
  }
  case SyntaxKindUtils::SyntaxKind::Int64Keyword: {
    this->_logger->logLLVMWarning(
        llvm::createStringError(llvm::inconvertibleErrorCode(),
                                "Implicit conversion from int64 to int32 "
                                "is not supported for variable with "
                                "predefined type"));
    return nullptr;
  }

  case SyntaxKindUtils::SyntaxKind::DeciKeyword: {
    this->_logger->logLLVMWarning(
        llvm::createStringError(llvm::inconvertibleErrorCode(),
                                "Implicit conversion from deci to int32 "
                                "is not supported for variable with "
                                "predefined type"));

    return nullptr;
  }
  case SyntaxKindUtils::SyntaxKind::Deci32Keyword: {
    this->_logger->logLLVMWarning(
        llvm::createStringError(llvm::inconvertibleErrorCode(),
                                "Implicit conversion from deci32 to int32 "
                                "is not supported for variable with "
                                "predefined type"));

    return nullptr;
  }
  case SyntaxKindUtils::SyntaxKind::BoolKeyword: {
    this->_logger->logLLVMWarning(
        llvm::createStringError(llvm::inconvertibleErrorCode(),
                                "Implicit conversion from bool to int32"));

    return _builder->CreateZExt(value,
                                llvm::Type::getInt32Ty(_builder->getContext()));
  }

  case SyntaxKindUtils::SyntaxKind::StrKeyword: {
    this->_logger->logLLVMWarning(
        llvm::createStringError(llvm::inconvertibleErrorCode(),
                                "Implicit conversion from string to int32 is "
                                "not supported for variable with predefined "
                                "type"));

    return nullptr;
  }
  default:
    break;
  }

  _logger->logLLVMError(
      llvm::createStringError(llvm::inconvertibleErrorCode(),
                              "Unsupported type for conversion to int32"));

  return res;
}