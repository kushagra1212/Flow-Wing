#include "StringTypeConverter.h"

StringTypeConverter::StringTypeConverter(CodeGenerationContext *context)
    : TypeConverterBase(context){};

llvm::Value *StringTypeConverter::convertExplicit(llvm::Value *value) {

  if (auto globalString = llvm::dyn_cast<llvm::GlobalVariable>(value)) {
    std::unique_ptr<GStringTypeConverter> gStringConverter =
        std::make_unique<GStringTypeConverter>(this->_codeGenerationContext);

    return gStringConverter->convertExplicit(globalString);
  }

  if (auto dataArr = llvm::dyn_cast<llvm::ConstantDataArray>(value)) {

    // bitcast to i8*
    // Define a global variable for the string
    llvm::GlobalVariable *str = new llvm::GlobalVariable(
        *_module, dataArr->getType(), true, llvm::GlobalValue::PrivateLinkage,
        dataArr, ".str");

    return _builder->CreateBitCast(
        str, llvm::Type::getInt8PtrTy(*this->_llvmContext));
  }

  llvm::Value *res = nullptr;

  CustomLLVMType type =
      this->_mapper->mapLLVMTypeToCustomType(value->getType());

  switch (type) {
  case CustomLLVMType::Int32:
  case CustomLLVMType::Int16:
  case CustomLLVMType::Int64: {
    return _builder->CreateCall(_module->getFunction(INNERS::FUNCTIONS::ITOS),
                                {value});
  }
  case CustomLLVMType::Float:
  case CustomLLVMType::Double: {
    return _builder->CreateCall(_module->getFunction(INNERS::FUNCTIONS::DTOS),
                                {value});
  }
  case CustomLLVMType::Bool: {
    llvm::Value *str = _builder->CreateSelect(
        value,
        _module->getGlobalVariable(
            _codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_TRUE)),

        _module->getGlobalVariable(
            _codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_FALSE)));

    return this->convertExplicit(str);
  }
  case CustomLLVMType::String: {
    return value;
  }
  default:
    break;
  }

  _logger->logLLVMError(
      llvm::createStringError(llvm::inconvertibleErrorCode(),
                              "Unsupported type for conversion to string"));

  return res;
}

llvm::Value *StringTypeConverter::convertImplicit(llvm::Value *value) {

  if (auto globalString = llvm::dyn_cast<llvm::GlobalVariable>(value)) {
    std::unique_ptr<GStringTypeConverter> gStringConverter =
        std::make_unique<GStringTypeConverter>(this->_codeGenerationContext);

    return gStringConverter->convertExplicit(globalString);
  }

  if (auto dataArr = llvm::dyn_cast<llvm::ConstantDataArray>(value)) {

    // bitcast to i8*
    // Define a global variable for the string
    llvm::GlobalVariable *str = new llvm::GlobalVariable(
        *_module, dataArr->getType(), true, llvm::GlobalValue::PrivateLinkage,
        dataArr, ".str");

    return _builder->CreateBitCast(
        str, llvm::Type::getInt8PtrTy(*this->_llvmContext));
  }

  llvm::Value *res = nullptr;

  CustomLLVMType type =
      this->_mapper->mapLLVMTypeToCustomType(value->getType());

  switch (type) {
  case CustomLLVMType::Int32:
  case CustomLLVMType::Int16:
  case CustomLLVMType::Int64: {
    _logger->logLLVMError(
        llvm::createStringError(llvm::inconvertibleErrorCode(),
                                "Implicit conversion from int to string is not "
                                "supported for variable with predefined type"));

    return nullptr;
  }
  case CustomLLVMType::Float:
  case CustomLLVMType::Double: {
    _logger->logLLVMError(
        llvm::createStringError(llvm::inconvertibleErrorCode(),
                                "Implicit conversion from float/double to "
                                "string is not supported for variable with "
                                "predefined type"));

    return nullptr;
  }
  case CustomLLVMType::Bool: {
    _logger->logLLVMError(
        llvm::createStringError(llvm::inconvertibleErrorCode(),
                                "Implicit conversion from bool to string is "
                                "not supported for variable with predefined "
                                "type"));

    return nullptr;
  }
  case CustomLLVMType::String: {
    return value;
  }
  default:
    break;
  }

  _logger->logLLVMError(
      llvm::createStringError(llvm::inconvertibleErrorCode(),
                              "Unsupported type for conversion to string"));

  return res;
}