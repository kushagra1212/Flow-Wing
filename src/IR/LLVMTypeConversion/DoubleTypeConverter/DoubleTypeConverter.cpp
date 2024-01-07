#include "DoubleTypeConverter.h"

DoubleTypeConverter::DoubleTypeConverter(CodeGenerationContext *context)
    : TypeConverterBase(context){};

llvm::Value *DoubleTypeConverter::convertExplicit(llvm::Value *value) {
  llvm::Value *res = nullptr;

  SyntaxKindUtils::SyntaxKind type =
      this->_mapper->mapLLVMTypeToCustomType(value->getType());

  switch (type) {
    case SyntaxKindUtils::SyntaxKind::Int32Keyword: {
      return _builder->CreateSIToFP(
          value, llvm::Type::getDoubleTy(_builder->getContext()));
    }
    case SyntaxKindUtils::SyntaxKind::DeciKeyword: {
      return value;
    }
    case SyntaxKindUtils::SyntaxKind::BoolKeyword: {
      return _builder->CreateUIToFP(
          value, llvm::Type::getDoubleTy(_builder->getContext()));
    }
    case SyntaxKindUtils::SyntaxKind::StrKeyword: {
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

  SyntaxKindUtils::SyntaxKind type =
      this->_mapper->mapLLVMTypeToCustomType(value->getType());

  switch (type) {
    case SyntaxKindUtils::SyntaxKind::Int32Keyword: {
      return _builder->CreateSIToFP(
          value, llvm::Type::getDoubleTy(_builder->getContext()));
    }
    case SyntaxKindUtils::SyntaxKind::DeciKeyword: {
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