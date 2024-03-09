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
  case SyntaxKindUtils::SyntaxKind::DeciKeyword: {
    return _builder->CreateFPToSI(value, llvm::Type::getInt32Ty(*TheContext));
  }
  case SyntaxKindUtils::SyntaxKind::BoolKeyword: {
    return _builder->CreateZExt(value, llvm::Type::getInt32Ty(*TheContext));
  }
  case SyntaxKindUtils::SyntaxKind::StrKeyword: {
    // TODO: Implement explicit conversion from string to int

    // llvm::ArrayRef<llvm::Value *> Args =
    // {this->explicitConvertToString(val)};
    llvm::ArrayRef<llvm::Value *> Args = {value};

    return _builder->CreateCall(
        _module->getFunction(INNERS::FUNCTIONS::STRING_TO_INT), Args);
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
  case SyntaxKindUtils::SyntaxKind::DeciKeyword: {
    this->_logger->logLLVMWarning(llvm::createStringError(
        llvm::inconvertibleErrorCode(),
        "Implicit conversion from float/double to int32 "
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