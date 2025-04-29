#include "Int8TypeConverter.h"

Int8TypeConverter::Int8TypeConverter(CodeGenerationContext *context)
    : TypeConverterBase(context){};

llvm::Value *Int8TypeConverter::convertExplicit(llvm::Value *&value) {
  llvm::Value *res = nullptr;

  llvm::LLVMContext *TheContext = _codeGenerationContext->getContext().get();

  SyntaxKindUtils::SyntaxKind type =
      this->_mapper->mapLLVMTypeToCustomType(value->getType());

  switch (type) {
  case SyntaxKindUtils::SyntaxKind::Int8Keyword: {
    return value;
  }
  case SyntaxKindUtils::SyntaxKind::Int32Keyword:
  case SyntaxKindUtils::SyntaxKind::Int64Keyword: {
    return _builder->CreateTrunc(value, llvm::Type::getInt8Ty(*TheContext));
  }
  case SyntaxKindUtils::SyntaxKind::DeciKeyword:
  case SyntaxKindUtils::SyntaxKind::Deci32Keyword: {
    return _builder->CreateFPToSI(value, llvm::Type::getInt8Ty(*TheContext));
  }
  case SyntaxKindUtils::SyntaxKind::BoolKeyword: {
    return _builder->CreateZExt(value, llvm::Type::getInt8Ty(*TheContext));
  }
  case SyntaxKindUtils::SyntaxKind::StrKeyword: {
    // TODO: Implement explicit conversion from string to int
    llvm::Value *int32Val = _builder->CreateCall(
        _module->getFunction(INNERS::FUNCTIONS::STRING_TO_INT), {value});
    return this->convertExplicit(int32Val);
  }
  default:
    break;
  }

  _logger->LogError(("Unsupported type for conversion to int8"));

  return res;
}

llvm::Value *Int8TypeConverter::convertImplicit(llvm::Value *&value) {
  llvm::Value *res = nullptr;

  SyntaxKindUtils::SyntaxKind type =
      this->_mapper->mapLLVMTypeToCustomType(value->getType());

  switch (type) {
  case SyntaxKindUtils::SyntaxKind::Int8Keyword: {
    return value;
  }
  case SyntaxKindUtils::SyntaxKind::Int32Keyword:
  case SyntaxKindUtils::SyntaxKind::Int64Keyword: {
    this->_logger->LogError(("Implicit conversion from int64 or int32 to int8 "
                             "is not supported for variable with "
                             "predefined type"));
    return nullptr;
  }

  case SyntaxKindUtils::SyntaxKind::DeciKeyword: {
    this->_logger->LogError(("Implicit conversion from deci to int8 "
                             "is not supported for variable with "
                             "predefined type"));

    return nullptr;
  }
  case SyntaxKindUtils::SyntaxKind::Deci32Keyword: {
    this->_logger->LogError(("Implicit conversion from deci32 to int8 "
                             "is not supported for variable with "
                             "predefined type"));

    return nullptr;
  }
  case SyntaxKindUtils::SyntaxKind::BoolKeyword: {

    return _builder->CreateZExt(value,
                                llvm::Type::getInt8Ty(_builder->getContext()));
  }

  case SyntaxKindUtils::SyntaxKind::StrKeyword: {
    this->_logger->LogError(("Implicit conversion from string to int8 is "
                             "not supported for variable with predefined "
                             "type"));

    return nullptr;
  }
  default:
    break;
  }

  _logger->LogError(("Unsupported type for conversion to int8"));

  return res;
}