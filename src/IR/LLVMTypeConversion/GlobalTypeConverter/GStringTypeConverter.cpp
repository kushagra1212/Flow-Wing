#include "GStringTypeConverter.h"

GStringTypeConverter::GStringTypeConverter(CodeGenerationContext *context)
    : TypeConverterBase(context){};

llvm::Value *
GStringTypeConverter::convertExplicit(llvm::Value *possibleGlobalVariable) {
  return convertImplicit(possibleGlobalVariable);
}

llvm::Value *
GStringTypeConverter::convertImplicit(llvm::Value *possibleGlobalVariable) {

  llvm::Value *res = nullptr;
  auto globalVar = llvm::dyn_cast<llvm::GlobalVariable>(possibleGlobalVariable);

  if (!globalVar) {
    _logger->logLLVMError(llvm::createStringError(
        llvm::inconvertibleErrorCode(),
        "Unsupported type for conversion to String (not a global variable)"));
    return res;
  }

  llvm::Type *llvmType = globalVar->getValueType();
  llvm::Value *value = _builder->CreateLoad(llvmType, globalVar);

  std::unique_ptr<StringTypeConverter> stringConverter =
      std::make_unique<StringTypeConverter>(this->_codeGenerationContext);

  return stringConverter->convertExplicit(value);
}