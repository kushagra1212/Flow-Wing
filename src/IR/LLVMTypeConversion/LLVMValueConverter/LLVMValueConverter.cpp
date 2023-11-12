#include "LLVMValueConverter.h"

LLVMValueConverter::LLVMValueConverter(CodeGenerationContext *context)
    : _module(context->getModule().get()), _mapper(context->getMapper().get()),
      _logger(context->getLogger().get()),
      _builder(context->getBuilder().get()),
      _llvmContext(context->getContext().get()),
      _codeGenerationContext(context){};

llvm::Value *
LLVMValueConverter::convertToLLVMValue(std::any value,
                                       SyntaxKindUtils::SyntaxKind kind) {
  if (value.type() == typeid(int)) {
    return int32ToLLVMValue(std::any_cast<int32_t>(value));
  } else if (value.type() == typeid(double)) {
    return doubleToLLVMValue(std::any_cast<double>(value));
  } else if (value.type() == typeid(bool)) {
    return boolToLLVMValue(std::any_cast<bool>(value));
  } else if (value.type() == typeid(std::string)) {
    return stringToLLVMValue(std::any_cast<std::string>(value), kind);
  } else {
    return nullptr;
  }
}

llvm::Value *LLVMValueConverter::int32ToLLVMValue(int32_t value) {
  return llvm::ConstantInt::get(*_llvmContext, llvm::APInt(32, value, true));
}

llvm::Value *LLVMValueConverter::doubleToLLVMValue(double value) {
  return llvm::ConstantFP::get(*_llvmContext, llvm::APFloat(value));
}

llvm::Value *LLVMValueConverter::boolToLLVMValue(bool value) {
  if (value) {
    return llvm::ConstantInt::getTrue(*_llvmContext);
  } else {
    return llvm::ConstantInt::getFalse(*_llvmContext);
  }
}

llvm::Value *
LLVMValueConverter::stringToLLVMValue(std::string value,
                                      SyntaxKindUtils::SyntaxKind kind) {
  //  if the string contains only decimal numbers

  if (kind == SyntaxKindUtils::NumberToken) {

    if (Utils::isInteger(value)) {
      // larger integer type
      llvm::APInt llvmLongIntValue(32, value, 10);
      llvm::Constant *llvmValue =
          llvm::ConstantInt::get(*_llvmContext, llvmLongIntValue);

      return llvmValue;
    }

    if (Utils::isDouble(value)) {
      llvm::APFloat llvmDoubleValue(llvm::APFloat::IEEEdouble(), value.c_str());
      llvm::Constant *llvmValue =
          llvm::ConstantFP::get(*_llvmContext, llvmDoubleValue);

      return llvmValue;
    }
  }

  llvm::Constant *strConstant =
      llvm::ConstantDataArray::getString(*_llvmContext, value);

  llvm::GlobalVariable *strVar = new llvm::GlobalVariable(
      *_module, strConstant->getType(),
      true, // isConstant
      llvm::GlobalValue::ExternalLinkage, strConstant, value);

  llvm::Value *zero =
      llvm::ConstantInt::get(llvm::Type::getInt32Ty(*_llvmContext), 0);
  llvm::Value *indices[] = {zero, zero};
  llvm::Value *strPtr = _builder->CreateInBoundsGEP(strConstant->getType(),
                                                    strVar, indices, "str_ptr");

  llvm::Value *elementPtr = _builder->CreateBitCast(
      strPtr, llvm::IntegerType::getInt8PtrTy((*_llvmContext)), "element_ptr");
  return elementPtr;
}
