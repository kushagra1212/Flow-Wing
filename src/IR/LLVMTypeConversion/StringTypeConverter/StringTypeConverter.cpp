#include "StringTypeConverter.h"

StringTypeConverter::StringTypeConverter(CodeGenerationContext *context)
    : TypeConverterBase(context){};

llvm::Value *StringTypeConverter::convertExplicit(llvm::Value *&value) {
  if (llvm::isa<llvm::PointerType>(value->getType())) {
    return value;
  }

  if (auto globalString = llvm::dyn_cast<llvm::GlobalVariable>(value)) {
    std::unique_ptr<GStringTypeConverter> gStringConverter =
        std::make_unique<GStringTypeConverter>(this->_codeGenerationContext);

    llvm::Value *response = gStringConverter->convertExplicit(value);

    if (response) {
      return response;
    }
  }

  if (auto dataArr = llvm::dyn_cast<llvm::ConstantDataArray>(value)) {
    // bitcast to i8*
    // Define a global variable for the string
    llvm::GlobalVariable *str = new llvm::GlobalVariable(
        *_module, dataArr->getType(), true, llvm::GlobalValue::ExternalLinkage,
        dataArr, ".str");

    return _builder->CreateBitCast(
        str, llvm::Type::getInt8PtrTy(*this->_llvmContext));
  }

  llvm::Value *res = nullptr;

  SyntaxKindUtils::SyntaxKind type =
      this->_mapper->mapLLVMTypeToCustomType(value->getType());

  switch (type) {
  case SyntaxKindUtils::SyntaxKind::Int32Keyword: {
    return _builder->CreateCall(_module->getFunction(INNERS::FUNCTIONS::ITOS),
                                {value});
  }
  case SyntaxKindUtils::SyntaxKind::DeciKeyword: {
    return _builder->CreateCall(_module->getFunction(INNERS::FUNCTIONS::DTOS),
                                {value});
  }
  case SyntaxKindUtils::SyntaxKind::BoolKeyword: {
    llvm::Value *str = _builder->CreateSelect(
        value,
        _module->getGlobalVariable(
            _codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_TRUE)),

        _module->getGlobalVariable(
            _codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_FALSE)));

    return this->convertExplicit(str);
  }
  case SyntaxKindUtils::SyntaxKind::StrKeyword: {
    return value;
  }
  default:
    break;
  }

  // Attempt to convert the value to string
  std::string stringValue = valueToString(value);

  // Create a global constant string and return its pointer
  if (!stringValue.empty()) {
    return convertStringToi8Ptr(stringValue);
  }

  _logger->logLLVMError(
      llvm::createStringError(llvm::inconvertibleErrorCode(),
                              "Unsupported type for conversion to string"));

  return res;
}

llvm::Value *StringTypeConverter::convertImplicit(llvm::Value *&value) {
  if (auto globalString = llvm::isa<llvm::GlobalVariable>(value)) {
    std::unique_ptr<GStringTypeConverter> gStringConverter =
        std::make_unique<GStringTypeConverter>(this->_codeGenerationContext);

    return gStringConverter->convertExplicit(value);
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

  SyntaxKindUtils::SyntaxKind type =
      this->_mapper->mapLLVMTypeToCustomType(value->getType());

  switch (type) {
  case SyntaxKindUtils::SyntaxKind::Int32Keyword: {
    _logger->logLLVMError(llvm::createStringError(
        llvm::inconvertibleErrorCode(),
        "Implicit conversion from int32 to string is not "
        "supported for variable with predefined type"));

    return nullptr;
  }
  case SyntaxKindUtils::SyntaxKind::Int8Keyword: {
    _logger->logLLVMError(llvm::createStringError(
        llvm::inconvertibleErrorCode(),
        "Implicit conversion from int8 to string is not "
        "supported for variable with predefined type"));
  }
  case SyntaxKindUtils::SyntaxKind::DeciKeyword: {
    _logger->logLLVMError(
        llvm::createStringError(llvm::inconvertibleErrorCode(),
                                "Implicit conversion from float/double to "
                                "string is not supported for variable with "
                                "predefined type"));

    return nullptr;
  }
  case SyntaxKindUtils::SyntaxKind::BoolKeyword: {
    _logger->logLLVMError(
        llvm::createStringError(llvm::inconvertibleErrorCode(),
                                "Implicit conversion from bool to string is "
                                "not supported for variable with predefined "
                                "type"));

    return nullptr;
  }
  case SyntaxKindUtils::SyntaxKind::StrKeyword: {
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

llvm::Value *
StringTypeConverter::convertStringToi8Ptr(std::string stringValue) {
  llvm::Constant *stringConstant =
      llvm::ConstantDataArray::getString(_builder->getContext(), stringValue);
  llvm::GlobalVariable *globalVar = new llvm::GlobalVariable(
      *_module, stringConstant->getType(), true,
      llvm::GlobalValue::ExternalLinkage, stringConstant);

  // load global variable
  llvm::Value *i8Ptr = _builder->CreateBitCast(
      globalVar, llvm::Type::getInt8PtrTy(_builder->getContext()));
  return i8Ptr;
}

std::string StringTypeConverter::valueToString(llvm::Value *val) {
  if (!val)
    return "";

  llvm::ConstantInt *constInt = llvm::dyn_cast<llvm::ConstantInt>(val);
  if (constInt) {
    if (constInt->getType()->isIntegerTy(32)) {
      return std::to_string(constInt->getSExtValue());
    } else if (constInt->getType()->isIntegerTy(64)) {
      return std::to_string(constInt->getSExtValue());
    } else if (constInt->getType()->isIntegerTy(1)) {
      return constInt->getSExtValue() ? "true" : "false";
    } else {
      _logger->logLLVMError(llvm::createStringError(
          llvm::inconvertibleErrorCode(),
          "Unsupported integer type for conversion to string"));
      return "";
    }
  }

  llvm::ConstantFP *constFP = llvm::dyn_cast<llvm::ConstantFP>(val);

  if (constFP) {
    if (constFP->getType()->isDoubleTy()) {
      return std::to_string(constFP->getValueAPF().convertToDouble());
    } else {
      _logger->logLLVMError(llvm::createStringError(
          llvm::inconvertibleErrorCode(),
          "Unsupported floating point type for conversion to string"));
      return "";
    }
  }

  llvm::Instruction *instr = llvm::dyn_cast<llvm::Instruction>(val);

  if (instr && instr->getOpcode() == llvm::Instruction::Call) {
    llvm::CallInst *callInst = llvm::cast<llvm::CallInst>(instr);
    llvm::Function *calledFunc = callInst->getCalledFunction();
    if (calledFunc) {
      llvm::Type *i1Type = llvm::Type::getInt1Ty(val->getContext());
      llvm::IRBuilder<> builder(val->getContext());

      // Compare the result of the function call with 0 using an ICmpInst
      llvm::Value *cmpResult =
          builder.CreateICmpNE(val, llvm::ConstantInt::get(i1Type, 1));

      // Convert the i1 comparison result to "true" or "false" string
      if (cmpResult->getType() == i1Type) {
        return cmpResult == llvm::ConstantInt::get(i1Type, 1) ? "true"
                                                              : "false";
      } else {
        _logger->logLLVMError(llvm::createStringError(
            llvm::inconvertibleErrorCode(),
            "Unsupported type for conversion to string"));
        return "";
      }
    }
  }

  llvm::IRBuilder<> builder(val->getContext());
  llvm::Type *i8PtrType = llvm::Type::getInt8PtrTy(builder.getContext());
  llvm::Constant *constVal = llvm::dyn_cast<llvm::Constant>(val);

  if (constVal) {
    llvm::Module *module = builder.GetInsertBlock()->getParent()->getParent();
    llvm::ConstantExpr *constExpr = llvm::dyn_cast<llvm::ConstantExpr>(val);
    llvm::GlobalVariable *globalVar =
        new llvm::GlobalVariable(*module, i8PtrType, true,
                                 llvm::GlobalValue::ExternalLinkage, constExpr);

    std::string str;
    llvm::raw_string_ostream rso(str);
    globalVar->printAsOperand(rso, true, module);
    return rso.str();
  }
  if (val->getType()->isPointerTy() && val->getType()->isIntegerTy(8)) {
    llvm::ConstantExpr *constExpr = llvm::dyn_cast<llvm::ConstantExpr>(val);
    if (constExpr &&
        constExpr->getOpcode() == llvm::Instruction::GetElementPtr) {
      llvm::User::op_iterator it = constExpr->op_begin();
      if (it != constExpr->op_end()) {
        llvm::Value *basePtr = *it;
        llvm::GlobalVariable *globalVar =
            llvm::dyn_cast<llvm::GlobalVariable>(basePtr);
        if (globalVar && globalVar->isConstant() &&
            globalVar->hasInitializer()) {
          llvm::ConstantDataArray *dataArray =
              llvm::dyn_cast<llvm::ConstantDataArray>(
                  globalVar->getInitializer());
          if (dataArray && dataArray->isCString()) {
            return dataArray->getAsCString().str();
          }
        }
      }
    }
  }

  std::string str;
  llvm::raw_string_ostream rso(str);
  val->print(rso);
  return rso.str();
}