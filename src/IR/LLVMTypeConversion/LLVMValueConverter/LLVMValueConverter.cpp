#include "LLVMValueConverter.h"
#include <llvm-14/llvm/IR/Constants.h>

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
  }

  else if (value.type() == typeid(double)) {
    return doubleToLLVMValue(std::any_cast<double>(value));
  }

  else if (value.type() == typeid(bool)) {
    return boolToLLVMValue(std::any_cast<bool>(value));
  }

  else if (value.type() == typeid(std::string)) {

    return stringToLLVMValue(std::any_cast<std::string>(value), kind);
  }

  else {
    return nullptr;
  }
}

llvm::Value *LLVMValueConverter::int32ToLLVMValue(int value) {
  return llvm::ConstantInt::get(*_llvmContext, llvm::APInt(32, value, true));
}

llvm::Value *LLVMValueConverter::doubleToLLVMValue(double value) {
  return llvm::ConstantFP::get(*_llvmContext, llvm::APFloat(value));
}

llvm::Value *LLVMValueConverter::boolToLLVMValue(bool value) {
  if (value)
    return llvm::ConstantInt::getTrue(*_llvmContext);
  else
    return llvm::ConstantInt::getFalse(*_llvmContext);
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
    char endChar = ' ';
    if (value.size() > 1 && value[value.size() - 1] == 'd') {
      endChar = 'd';
      value.pop_back();
    }
    if (Utils::isDouble(value)) {
      if (endChar == 'd') {
        llvm::APFloat llvmDoubleValue(llvm::APFloat::IEEEsingle(),
                                      value.c_str());
        return llvm::ConstantFP::get(*_llvmContext, llvmDoubleValue);
      }

      llvm::APFloat llvmDoubleValue(llvm::APFloat::IEEEdouble(), value.c_str());
      llvm::Constant *llvmValue =
          llvm::ConstantFP::get(*_llvmContext, llvmDoubleValue);

      return llvmValue;
    }
  } else if (kind == SyntaxKindUtils::SyntaxKind::CharacterToken) {
    if (value == "\\0") {
      return llvm::ConstantInt::get(_builder->getInt8Ty(), 0);
    }

    if (value.length() == 1) {
      return llvm::ConstantInt::get(_builder->getInt8Ty(), value[0]);
    } else if (value.length() == 2 && value[0] == '\\' && value[1] == 'n') {
      return llvm::ConstantInt::get(_builder->getInt8Ty(), '\n');
    } else if (value.length() == 2 && value[0] == '\\' && value[1] == 't') {
      return llvm::ConstantInt::get(_builder->getInt8Ty(), '\t');
    } else if (value.length() == 2 && value[0] == '\\' && value[1] == 'r') {
      return llvm::ConstantInt::get(_builder->getInt8Ty(), '\r');
    } else if (value.length() == 2 && value[0] == '\\' && value[1] == '0') {
      return llvm::ConstantInt::get(_builder->getInt8Ty(), '\0');
    } else if (value.length() == 2 && value[0] == '\\' && value[1] == '\\') {
      return llvm::ConstantInt::get(_builder->getInt8Ty(), '\\');
    } else if (value.length() == 2 && value[0] == '\\' && value[1] == '\'') {
      return llvm::ConstantInt::get(_builder->getInt8Ty(), '\'');
    } else if (value.length() == 2 && value[0] == '\\' && value[1] == '\"') {
      return llvm::ConstantInt::get(_builder->getInt8Ty(), '\"');
    } else {
      _codeGenerationContext->getLogger()->LogError(
          "Invalid character Constant, " +
          COLORED_STRING::GET("<" + value + ">", YELLOW, RED));
      return nullptr;
    }
  }

  // if (value.length() == 0) {
  //   return llvm::ConstantInt::getNullValue(_builder->getInt8PtrTy());
  // }

  // return _builder->CreateGlobalStringPtr(value);

  llvm::Constant *strConstant =
      llvm::ConstantDataArray::getString(*_llvmContext, value);

  return _codeGenerationContext->createMemoryGetPtr(
      strConstant->getType(), "", BinderKindUtils::MemoryKind::Global,
      strConstant);

  // llvm::GlobalVariable *strVar = new llvm::GlobalVariable(
  //     *_module, strConstant->getType(),
  //     true, // isConstant
  //     llvm::GlobalValue::ExternalLinkage, strConstant, value + ".str");

  // llvm::Value *elementPtr = _builder->CreateBitCast(
  //     _builder->CreateInBoundsGEP(
  //         strConstant->getType(), strVar,
  //         {_builder->getInt32(0), _builder->getInt32(0)}),
  //     llvm::IntegerType::getInt8PtrTy((*_llvmContext)));

  // return strPtr;
}

llvm::Value *
LLVMValueConverter::convertToTypedLLVMValue(std::any value,
                                            SyntaxKindUtils::SyntaxKind kind,
                                            SyntaxKindUtils::SyntaxKind type) {

  if (value.type() == typeid(bool))
    return boolToLLVMValue(std::any_cast<bool>(value));

  if (value.type() == typeid(std::string))
    return stringToTypedLLVMValue(std::any_cast<std::string>(value), kind,
                                  type);

  return nullptr;
}

llvm::Value *
LLVMValueConverter::stringToTypedLLVMValue(std::string value,
                                           SyntaxKindUtils::SyntaxKind kind,
                                           SyntaxKindUtils::SyntaxKind type) {
  //  if the string contains only decimal numbers

  if (kind == SyntaxKindUtils::NumberToken) {

    if (Utils::isInteger(value)) {
      // larger integer type
      switch (type) {
      case SyntaxKindUtils::SyntaxKind::Int32Keyword: {
        llvm::APInt llvmLongIntValue(32, value, 10);
        return llvm::ConstantInt::get(*_llvmContext, llvmLongIntValue);
      }
      case SyntaxKindUtils::SyntaxKind::Int8Keyword: {
        llvm::APInt llvmLongIntValue(8, value, 10);
        return llvm::ConstantInt::get(*_llvmContext, llvmLongIntValue);
      }
      case SyntaxKindUtils::SyntaxKind::Int64Keyword: {
        llvm::APInt llvmLongIntValue(64, value, 10);
        return llvm::ConstantInt::get(*_llvmContext, llvmLongIntValue);
      }
      default:
        break;
      }
    }

    char endChar = ' ';
    if (value.size() > 1 && value[value.size() - 1] == 'd') {
      endChar = 'd';
      value.pop_back();
    }
    if (Utils::isDouble(value)) {
      if (endChar == 'd') {
        llvm::APFloat llvmDoubleValue(llvm::APFloat::IEEEsingle(),
                                      value.c_str());
        llvm::Constant *llvmValue =
            llvm::ConstantFP::get(*_llvmContext, llvmDoubleValue);

        return llvmValue;
      }

      llvm::APFloat llvmDoubleValue(llvm::APFloat::IEEEdouble(), value.c_str());
      llvm::Constant *llvmValue =
          llvm::ConstantFP::get(*_llvmContext, llvmDoubleValue);

      return llvmValue;
    }
    if (Utils::isDouble(value)) {
      switch (type) {
      case SyntaxKindUtils::SyntaxKind::DeciKeyword: {
        llvm::APFloat llvmDoubleValue(llvm::APFloat::IEEEdouble(),
                                      value.c_str());
        return llvm::ConstantFP::get(*_llvmContext, llvmDoubleValue);
      }
      case SyntaxKindUtils::SyntaxKind::Deci32Keyword: {
        llvm::APFloat llvmDoubleValue(llvm::APFloat::IEEEsingle(),
                                      value.c_str());
        return llvm::ConstantFP::get(*_llvmContext, llvmDoubleValue);
      }
      default:
        break;
      }
    }
  }

  DEBUG_LOG("value: " + value);

  return _builder->CreateGlobalStringPtr(value);
}
