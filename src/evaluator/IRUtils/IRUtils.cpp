#include "IRUtils.h"

IRUtils::IRUtils(CodeGenerationContext *codeGenerationContext) {
  _currentSourceLocation = DiagnosticUtils::SourceLocation();
  _initializingGlobals = 1;

  // Code Generation Context
  _codeGenerationContext = codeGenerationContext;

  // Assign logger
  _llvmLogger = _codeGenerationContext->getLogger().get();

  // Assign diagnosticHandler
  _diagnosticHandler = _codeGenerationContext->getDiagnosticHandler();

  _TheContext = _codeGenerationContext->getContext().get();
  _TheModule = _codeGenerationContext->getModule().get();
  _Builder = _codeGenerationContext->getBuilder().get();

  _memberTypesForDynamicTypes = {
      llvm::Type::getInt32Ty(*_TheContext),
      llvm::Type::getDoubleTy(*_TheContext),
      llvm::Type::getInt1Ty(*_TheContext),
      llvm::Type::getInt8PtrTy(*_TheContext),
  };
}

const std::vector<llvm::Type *> IRUtils::getMemberTypesForDynamicTypes() const {
  return this->_memberTypesForDynamicTypes;
}

const int IRUtils::getIndexofMemberType(llvm::Type *type) {
  int index = -1;
  for (int i = 0; i < this->_memberTypesForDynamicTypes.size(); i++) {
    if (this->_memberTypesForDynamicTypes[i] == type) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    std::string typeUsedByUser =
        Utils::getTypeString(this->getReturnType(type));
    this->logError("Unsupported type for dynamic type: " + typeUsedByUser);
    index = 0;
  }

  return index;
}

void IRUtils::handleConditionalBranch(
    llvm::Value *conditionValue, const std::string &trueBlockName,
    const std::string &falseBlockName,
    std::function<void(llvm::BasicBlock *, llvm::IRBuilder<> *_Builder,
                       llvm::LLVMContext *_TheContext, IRUtils *irutils)>
        trueBlockCode,
    std::function<void(llvm::BasicBlock *, llvm::IRBuilder<> *_Builder,
                       llvm::LLVMContext *_TheContext)>
        falseBlockCode) {

  llvm::BasicBlock *currentBlock = _Builder->GetInsertBlock();
  llvm::Function *currentFunction = currentBlock->getParent();

  llvm::BasicBlock *trueBlock = llvm::BasicBlock::Create(
      *_TheContext, trueBlockName, currentFunction, currentBlock);

  llvm::BasicBlock *falseBlock = llvm::BasicBlock::Create(
      *_TheContext, falseBlockName, currentFunction, currentBlock);

  _Builder->CreateCondBr(conditionValue, trueBlock, falseBlock);

  trueBlockCode(trueBlock, _Builder, _TheContext, this);

  falseBlockCode(falseBlock, _Builder, _TheContext);
}

llvm::Constant *IRUtils::createConstantFromValue(llvm::Value *myValue) {
  llvm::Type *valueType = myValue->getType();

  if (auto constant = llvm::dyn_cast<llvm::Constant>(myValue)) {
    return constant;
  }

  if (valueType->isIntegerTy(32)) {
    if (auto intConstant = llvm::dyn_cast<llvm::ConstantInt>(myValue)) {
      llvm::APInt intValue = intConstant->getValue();
      return llvm::ConstantInt::get(valueType, intValue);
    }
  } else if (valueType->isFloatTy() || valueType->isDoubleTy()) {
    if (auto floatConstant = llvm::dyn_cast<llvm::ConstantFP>(myValue)) {
      llvm::APFloat floatValue = floatConstant->getValueAPF();
      return llvm::ConstantFP::get(*_TheContext, floatValue);
    }
  } else if (valueType->isPointerTy()) {
    if (auto ptrConstant = llvm::dyn_cast<llvm::ConstantPointerNull>(myValue)) {
      return llvm::ConstantPointerNull::get(
          llvm::cast<llvm::PointerType>(valueType));
    } else if (auto constArray =
                   llvm::dyn_cast<llvm::ConstantDataArray>(myValue)) {
      if (constArray->isCString()) {
        std::string str = constArray->getAsCString().str();
        llvm::Constant *strConstant =
            llvm::ConstantDataArray::getString(*_TheContext, str, true);
        return strConstant;
      }
    }
  } else if (valueType->isIntegerTy(1)) { // Check if it's a boolean (i1).
    if (auto boolConstant = llvm::dyn_cast<llvm::ConstantInt>(myValue)) {
      return llvm::ConstantInt::get(valueType,
                                    boolConstant->getUniqueInteger());
    }
  }
  // Add more cases for other types if needed.

  // this->logError("Unsupported type for conversion to constant");

  return nullptr; // Return nullptr if the type is not recognized.
}

const int IRUtils::isInitializingGlobals() const {
  return this->_initializingGlobals;
}
void IRUtils::setInitializingGlobals(int value) {
  this->_initializingGlobals = value;
}

llvm::Value *IRUtils::getLLVMValue(std::any value,
                                   SyntaxKindUtils::SyntaxKind kind) {
  if (value.type() == typeid(int)) {
    return llvm::ConstantInt::get(
        *_TheContext, llvm::APInt(32, std::any_cast<int>(value), true));
  } else if (value.type() == typeid(double)) {
    return llvm::ConstantFP::get(*_TheContext,
                                 llvm::APFloat(std::any_cast<double>(value)));
  } else if (value.type() == typeid(bool)) {
    bool boolValue = std::any_cast<bool>(value);

    if (boolValue) {
      return llvm::ConstantInt::getTrue(*_TheContext);
    } else {
      return llvm::ConstantInt::getFalse(*_TheContext);
    }

  } else if (value.type() == typeid(std::string)) {

    std::string strValue = std::any_cast<std::string>(value);

    //  if the string contains only decimal numbers

    if (kind == SyntaxKindUtils::NumberToken) {

      if (Utils::isInteger(strValue)) {
        // larger integer type
        llvm::APInt llvmLongIntValue(32, strValue, 10);
        llvm::Constant *llvmValue =
            llvm::ConstantInt::get(*_TheContext, llvmLongIntValue);

        return llvmValue;
      }

      if (Utils::isDouble(strValue)) {
        llvm::APFloat llvmDoubleValue(llvm::APFloat::IEEEdouble(),
                                      strValue.c_str());
        llvm::Constant *llvmValue =
            llvm::ConstantFP::get(*_TheContext, llvmDoubleValue);

        return llvmValue;
      }
    }

    llvm::Constant *strConstant =
        llvm::ConstantDataArray::getString(*_TheContext, strValue);

    // if (this->isInitializingGlobals()) {
    //   return strConstant;
    // }

    llvm::GlobalVariable *strVar = new llvm::GlobalVariable(
        *_TheModule, strConstant->getType(),
        true, // isConstant
        llvm::GlobalValue::ExternalLinkage, strConstant, strValue);

    llvm::Value *zero =
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*_TheContext), 0);
    llvm::Value *indices[] = {zero, zero};
    llvm::Value *strPtr = _Builder->CreateInBoundsGEP(
        strConstant->getType(), strVar, indices, "str_ptr");

    llvm::Value *elementPtr = _Builder->CreateBitCast(
        strPtr, llvm::IntegerType::getInt8PtrTy((*_TheContext)), "element_ptr");

    // llvm::Value *strVarPtr = _Builder->CreatePointerCast(
    //     strVar, llvm::Type::getInt8PtrTy(*_TheContext), "str_var_ptr");

    return elementPtr;
  } else {
    return nullptr;
  }
}

llvm::PHINode *IRUtils::handleForLoopCondition(llvm::Value *stepValue,
                                               llvm::Value *value,
                                               llvm::Value *upperBound) {
  llvm::Value *isStepNegative =
      _Builder->CreateICmpSLT(stepValue, _Builder->getInt32(0));

  llvm::BasicBlock *trueBlock =
      llvm::BasicBlock::Create(value->getContext(), "trueBlock",
                               _Builder->GetInsertBlock()->getParent());
  llvm::BasicBlock *falseBlock =
      llvm::BasicBlock::Create(value->getContext(), "falseBlock",
                               _Builder->GetInsertBlock()->getParent());
  llvm::BasicBlock *mergeBlock =
      llvm::BasicBlock::Create(value->getContext(), "mergeBlock",
                               _Builder->GetInsertBlock()->getParent());

  _Builder->CreateCondBr(isStepNegative, trueBlock, falseBlock);

  _Builder->SetInsertPoint(trueBlock);

  llvm::Value *oppositeCondition = _Builder->CreateICmpSGE(value, upperBound);

  _Builder->CreateBr(mergeBlock);

  _Builder->SetInsertPoint(falseBlock);

  llvm::Value *normalCondition = _Builder->CreateICmpSLE(value, upperBound);

  _Builder->CreateBr(mergeBlock);

  _Builder->SetInsertPoint(mergeBlock);

  llvm::PHINode *conditionPHI = _Builder->CreatePHI(_Builder->getInt1Ty(), 2);
  conditionPHI->addIncoming(oppositeCondition, trueBlock);
  conditionPHI->addIncoming(normalCondition, falseBlock);

  return conditionPHI;
}

std::string IRUtils::getString(BoundExpression *node) {
  std::any value = ((BoundLiteralExpression<std::any> *)node)->getValue();
  if (value.type() == typeid(std::string)) {
    return std::any_cast<std::string>(value);
  }
  return "";
}

std::string IRUtils::valueToString(llvm::Value *val) {
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
      this->logError("Unsupported integer type for conversion to string");
      return "";
    }
  }

  llvm::ConstantFP *constFP = llvm::dyn_cast<llvm::ConstantFP>(val);

  if (constFP) {
    if (constFP->getType()->isDoubleTy()) {
      return std::to_string(constFP->getValueAPF().convertToDouble());
    } else {
      this->logError(
          "Unsupported floating point type for conversion to string");
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
        this->logError("Unsupported type for conversion to string");
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

llvm::Value *IRUtils::convertStringToi8Ptr(std::string stringValue) {
  llvm::Constant *stringConstant =
      llvm::ConstantDataArray::getString(_Builder->getContext(), stringValue);
  llvm::GlobalVariable *globalVar = new llvm::GlobalVariable(
      *_TheModule, stringConstant->getType(), true,
      llvm::GlobalValue::ExternalLinkage, stringConstant);

  // load global variable
  llvm::Value *i8Ptr = _Builder->CreateBitCast(
      globalVar, llvm::Type::getInt8PtrTy(_Builder->getContext()));
  return i8Ptr;
}

llvm::Value *IRUtils::convertToString(llvm::Value *val) {

  llvm::Type *type = val->getType();
  if (isStringType(type)) {
    return val;
  }

  if (isBoolType(type)) {
    return _Builder->CreateSelect(
        val,
        _TheModule->getGlobalVariable(
            _codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_TRUE)),
        _TheModule->getGlobalVariable(
            _codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_FALSE)));
  }

  if (isIntType(type)) {
    return _Builder->CreateCall(
        _TheModule->getFunction(INNERS::FUNCTIONS::ITOS), {val});
  }

  if (isDoubleType(type)) {
    return _Builder->CreateCall(
        _TheModule->getFunction(INNERS::FUNCTIONS::DTOS), {val});
  }

  // Attempt to convert the value to string
  std::string stringValue = this->valueToString(val);

  // Create a global constant string and return its pointer
  if (!stringValue.empty()) {
    return convertStringToi8Ptr(stringValue);
  }

  this->logError("Unsupported type for conversion to string");

  return nullptr; // Return nullptr for other types or unrecognized cases
}

llvm::Value *IRUtils::loadGlobalValue(llvm::Value *val) {
  if (auto globalVar = llvm::dyn_cast<llvm::GlobalVariable>(val)) {
    if (globalVar->getValueType()->isIntegerTy(32)) {

      return _Builder->CreateLoad(llvm::Type::getInt32Ty(*_TheContext),
                                  globalVar);

    } else if (globalVar->getValueType()->isIntegerTy(1)) {

      return _Builder->CreateLoad(llvm::Type::getInt1Ty(*_TheContext),
                                  globalVar);

    } else if (globalVar->getValueType()->isDoubleTy()) {
      return _Builder->CreateLoad(llvm::Type::getDoubleTy(*_TheContext),
                                  globalVar);

    } else if (globalVar->getValueType()->isPointerTy()) {

      return _Builder->CreateLoad(llvm::Type::getInt8PtrTy(*_TheContext),
                                  globalVar);

    } else if (globalVar->getValueType()->isIntegerTy(8)) {

      return _Builder->CreateLoad(llvm::Type::getInt8Ty(*_TheContext),
                                  globalVar);

    } else if (globalVar->getValueType()->isIntegerTy(64)) {

      return _Builder->CreateLoad(llvm::Type::getInt64Ty(*_TheContext),
                                  globalVar);
    }
  }

  this->logError("Value is not a global variable");

  return nullptr;
}

llvm::Value *IRUtils::explicitConvertToString(llvm::Value *val) {
  llvm::Type *type = val->getType();

  // check if it a global variable i32

  if (auto globalVar = llvm::dyn_cast<llvm::GlobalVariable>(val)) {
    if (globalVar->getValueType()->isIntegerTy(32)) {
      llvm::Value *val =
          _Builder->CreateLoad(llvm::Type::getInt32Ty(*_TheContext), globalVar);

      return _Builder->CreateCall(
          _TheModule->getFunction(INNERS::FUNCTIONS::ITOS), {val});
    } else if (globalVar->getValueType()->isIntegerTy(1)) {
      llvm::Value *val =
          _Builder->CreateLoad(llvm::Type::getInt1Ty(*_TheContext), globalVar);

      return _Builder->CreateCall(
          _TheModule->getFunction(INNERS::FUNCTIONS::ITOS), {val});
    } else if (globalVar->getValueType()->isDoubleTy()) {
      llvm::Value *val = _Builder->CreateLoad(
          llvm::Type::getDoubleTy(*_TheContext), globalVar);

      return _Builder->CreateCall(
          _TheModule->getFunction(INNERS::FUNCTIONS::DTOS), {val});
    } else if (globalVar->getValueType()->isPointerTy()) {
      llvm::Value *val = _Builder->CreateLoad(
          llvm::Type::getInt8PtrTy(*_TheContext), globalVar);

      // bitcast to i8*

      return val;

    } else if (globalVar->getValueType()->isIntegerTy(8)) {
      llvm::Value *val =
          _Builder->CreateLoad(llvm::Type::getInt8Ty(*_TheContext), globalVar);

      // bitcast to i8*

      return val;
    } else if (globalVar->getValueType()->isIntegerTy(64)) {
      llvm::Value *val =
          _Builder->CreateLoad(llvm::Type::getInt64Ty(*_TheContext), globalVar);

      return _Builder->CreateCall(
          _TheModule->getFunction(INNERS::FUNCTIONS::DTOS), {val});
    }
  }

  if (auto dataArr = llvm::dyn_cast<llvm::ConstantDataArray>(val)) {

    // bitcast to i8*
    // Define a global variable for the string
    llvm::GlobalVariable *str = new llvm::GlobalVariable(
        *_TheModule, dataArr->getType(), true,
        llvm::GlobalValue::PrivateLinkage, dataArr, ".str");

    return _Builder->CreateBitCast(str, llvm::Type::getInt8PtrTy(*_TheContext));
  }

  if (isStringType(type)) {
    return val;
  }

  if (isBoolType(type)) {

    llvm::Value *str = _Builder->CreateSelect(
        val,
        _TheModule->getGlobalVariable(
            _codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_TRUE)),

        _TheModule->getGlobalVariable(
            _codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_FALSE)));

    return explicitConvertToString(str);
  }

  if (isIntType(type)) {
    return _Builder->CreateCall(
        _TheModule->getFunction(INNERS::FUNCTIONS::ITOS), {val});
  }

  if (isDoubleType(type)) {
    return _Builder->CreateCall(
        _TheModule->getFunction(INNERS::FUNCTIONS::DTOS), {val});
  }

  // Attempt to convert the value to string
  std::string stringValue = this->valueToString(val);

  // Create a global constant string and return its pointer
  if (!stringValue.empty()) {
    return convertStringToi8Ptr(stringValue);
  }

  this->logError("Unsupported type for conversion to string");

  return nullptr; // Return nullptr for other types or unrecognized cases
}
llvm::Value *IRUtils::concatenateStrings(llvm::Value *lhs, llvm::Value *rhs) {

  llvm::Function *stringConcatenateFunc =
      _TheModule->getFunction(INNERS::FUNCTIONS::CONCAT_STRINGS);

  if (!stringConcatenateFunc) {
    // Function not found, handle error
    return nullptr;

  } else {

    llvm::Value *args[] = {this->explicitConvertToString(lhs),
                           this->explicitConvertToString(rhs)};

    llvm::Value *res = _Builder->CreateCall(stringConcatenateFunc, args);
    return res;
  }
}

llvm::Type *IRUtils::getTypeFromAny(std::any value) {
  if (value.type() == typeid(int)) {
    return llvm::Type::getInt32Ty(*_TheContext);
  } else if (value.type() == typeid(double)) {
    return llvm::Type::getDoubleTy(*_TheContext);
  } else if (value.type() == typeid(bool)) {
    return llvm::Type::getInt1Ty(*_TheContext);
  } else if (value.type() == typeid(std::string)) {
    return llvm::Type::getInt8PtrTy(*_TheContext);
  } else {
    return nullptr;
  }
}

bool IRUtils::isStringType(llvm::Type *type) { return type->isPointerTy(); }
bool IRUtils::isDoubleType(llvm::Type *type) { return type->isDoubleTy(); }

bool IRUtils::isIntType(llvm::Type *type) { return type->isIntegerTy(32); }

bool IRUtils::isBoolType(llvm::Type *type) { return type->isIntegerTy(1); }

bool IRUtils::saveLLVMModuleToFile(llvm::Module *module,
                                   const std::string &path) {

  // Create an output stream for the .ll file
  std::error_code EC;
  llvm::raw_fd_ostream OS(path, EC, llvm::sys::fs::OF_None);

  if (!EC) {
    // Write the LLVM module to the .ll file
    module->print(OS, nullptr);
    OS.flush();
    return true;
  } else {

    this->logError("Error opening " + Utils::getFileName(path) +
                   " for writing: " + EC.message());

    return false;
  }
}

llvm::Constant *IRUtils::getNull() {

  llvm::PointerType *charPointerType = llvm::Type::getInt8PtrTy(*_TheContext);

  // Create a null pointer to i8.
  llvm::Constant *nullCharPointer =
      llvm::ConstantPointerNull::get(charPointerType);

  return nullCharPointer;
}

llvm::Value *IRUtils::checkBitSet(llvm::Value *result,
                                  unsigned int bitPosition) {
  llvm::Value *bitMask = _Builder->getInt32(1 << bitPosition);
  llvm::Value *bitIsSet = _Builder->CreateAnd(result, bitMask);
  llvm::Value *bitIsNonZero =
      _Builder->CreateICmpNE(bitIsSet, _Builder->getInt32(0));
  return bitIsNonZero;
}
llvm::Value *IRUtils::createStringComparison(llvm::Value *lhsValue,
                                             llvm::Value *rhsValue,
                                             const std::string functionName,
                                             std::string operand) {

  llvm::Function *stringComparison = _TheModule->getFunction(functionName);

  if (!stringComparison) {

    this->logError("Function " + functionName + " not found");

    return nullptr;
  }

  // / Get the Global Variable using the name

  llvm::GlobalVariable *globalTrueStr = _TheModule->getGlobalVariable(
      _codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_TRUE));

  if (!globalTrueStr) {

    this->logError("FLOWWING_GLOBAL_TRUE global variable not found");

    return nullptr;
  }

  llvm::GlobalVariable *globalFalseStr = _TheModule->getGlobalVariable(
      _codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_FALSE));

  if (!globalFalseStr) {

    this->logError("FLOWWING_GLOBAL_FALSE global variable not found");

    return nullptr;
  }

  llvm::Value *args[] = {lhsValue, rhsValue};
  llvm::CallInst *stringsCall = _Builder->CreateCall(stringComparison, args);
  llvm::Value *resultStr =
      operand == "!="
          ? _Builder->CreateSelect(stringsCall, globalFalseStr, globalTrueStr)
          : _Builder->CreateSelect(stringsCall, globalTrueStr, globalFalseStr);

  return _Builder->CreateBitCast(resultStr,
                                 llvm::Type::getInt8PtrTy(*_TheContext));
}

llvm::ConstantInt *IRUtils::getConstantIntFromValue(llvm::Value *value) {
  if (llvm::ConstantInt *constInt = llvm::dyn_cast<llvm::ConstantInt>(value)) {
    return constInt;
  }

  return nullptr;
}

llvm::ConstantFP *IRUtils::getConstantFPFromValue(llvm::Value *value) {
  if (llvm::ConstantFP *constFP = llvm::dyn_cast<llvm::ConstantFP>(value)) {
    return constFP;
  }

  return nullptr;
}

llvm::StringRef IRUtils::getConstantStringFromValue(llvm::Value *value) {
  if (llvm::ConstantDataArray *constDataArray =
          llvm::dyn_cast<llvm::ConstantDataArray>(value)) {
    if (constDataArray->isString()) {
      return constDataArray->getAsString();
    }
  }

  return "";
}

llvm::Value *IRUtils::getGlobalVarAndLoad(const std::string name,
                                          llvm::Type *Ty) {

  llvm::Value *ptr = _TheModule->getGlobalVariable(name);

  // Assuming that zeroPtr is of type i32*
  llvm::Value *var = _Builder->CreateLoad(Ty, ptr);

  return var;
}
llvm::Value *IRUtils::isCountZero(const std::string name, llvm::Type *ty) {
  llvm::Value *count = getGlobalVarAndLoad(name, ty);
  llvm::Value *loadZero =
      llvm::ConstantInt::get(*_TheContext, llvm::APInt(32, 0, true));

  llvm::Value *isZero = _Builder->CreateICmpEQ(count, loadZero);
  return isZero;
}

void IRUtils::incrementCount(const std::string name) {
  llvm::Value *count =
      getGlobalVarAndLoad(name, llvm::Type::getInt32Ty(*_TheContext));
  llvm::Value *newCount = _Builder->CreateAdd(
      count, llvm::ConstantInt::get(*_TheContext, llvm::APInt(32, 1, true)));
  _Builder->CreateStore(newCount, _TheModule->getGlobalVariable(name));
}

void IRUtils::decrementCountIfNotZero(const std::string name) {

  llvm::BasicBlock *currentBlock = _Builder->GetInsertBlock();
  llvm::BasicBlock *decrementBlock = llvm::BasicBlock::Create(
      *_TheContext, "decrement_block", currentBlock->getParent());
  llvm::BasicBlock *endBlock = llvm::BasicBlock::Create(
      *_TheContext, "end_block", currentBlock->getParent());

  llvm::Value *isZero = isCountZero(name, llvm::Type::getInt32Ty(*_TheContext));
  _Builder->CreateCondBr(isZero, endBlock, decrementBlock);

  _Builder->SetInsertPoint(decrementBlock);
  llvm::Value *count =
      getGlobalVarAndLoad(name, llvm::Type::getInt32Ty(*_TheContext));
  llvm::Value *newCount = _Builder->CreateSub(
      count, llvm::ConstantInt::get(*_TheContext, llvm::APInt(32, 1, true)));
  _Builder->CreateStore(newCount, _TheModule->getGlobalVariable(name));
  _Builder->CreateBr(endBlock);

  _Builder->SetInsertPoint(endBlock);
}

llvm::Type *IRUtils::getReturnType(Utils::type type) {
  switch (type) {
  case Utils::type::INT32:
    return llvm::Type::getInt32Ty(*_TheContext);
    break;
  case Utils::type::DECIMAL:
    return llvm::Type::getDoubleTy(*_TheContext);
    break;
  case Utils::type::BOOL:
    return llvm::Type::getInt1Ty(*_TheContext);
    break;
  case Utils::type::STRING:
    return llvm::Type::getInt8PtrTy(*_TheContext);
    break;
  case Utils::type::NOTHING:
    return llvm::Type::getVoidTy(*_TheContext);
    break;
  default:
    break;
  }
  return llvm::Type::getVoidTy(*_TheContext);
}

llvm::Value *IRUtils::getDefaultValue(Utils::type type) {
  llvm::Value *_retVal = nullptr;

  switch (type) {
  case Utils::type::INT32:
    _retVal = _Builder->getInt32(0);
    break;
  case Utils::type::DECIMAL:
    _retVal = llvm::ConstantFP::get(*_TheContext, llvm::APFloat(0.0));
    break;
  case Utils::type::BOOL:
    _retVal = _Builder->getInt1(false);
    break;
  case Utils::type::STRING:
    _retVal = _Builder->CreateGlobalStringPtr("");
    break;
  case Utils::type::NOTHING:
    break;
  case Utils::type::UNKNOWN:
    break;
  default:
    break;
  }
  return _retVal;
}

Utils::type IRUtils::getReturnType(llvm::Type *type) {

  if (type->isIntegerTy(32)) {
    return (Utils::type::INT32);
  } else if (type->isDoubleTy()) {
    return (Utils::type::DECIMAL);
  } else if (type->isIntegerTy(1)) {
    return (Utils::type::BOOL);
  } else if (type->isPointerTy()) {
    return (Utils::type::STRING);
  } else if (type->isVoidTy()) {
    return (Utils::type::NOTHING);
  } else {
    return Utils::type::UNKNOWN;
  }
}

void IRUtils::setCurrentSourceLocation(
    DiagnosticUtils::SourceLocation sourceLocation) {
  this->_currentSourceLocation = sourceLocation;
}

DiagnosticUtils::SourceLocation IRUtils::getCurrentSourceLocation() {
  return this->_currentSourceLocation;
}
void IRUtils::logError(std::string errorMessgae) {
  if (errorMessgae != "") {
    _hasError = 1;
    std::string errorString = _diagnosticHandler->getLogString(
        Diagnostic(errorMessgae, DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Runtime,
                   this->getCurrentSourceLocation()));

    llvm::Error error =
        llvm::createStringError(llvm::inconvertibleErrorCode(), errorString);
    _llvmLogger->logLLVMError(std::move(error));
  }
}

const int IRUtils::hasError() const { return _hasError; }

void IRUtils::errorGuard(std::function<void()> code) {
  llvm::Value *isZero = this->isCountZero(
      _codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_ERROR_COUNT),
      llvm::Type::getInt32Ty(*_TheContext));

  llvm::BasicBlock *printBlock =
      llvm::BasicBlock::Create(*_TheContext, "printBlock",
                               this->_Builder->GetInsertBlock()->getParent());

  llvm::BasicBlock *afterPrintBlock =
      llvm::BasicBlock::Create(*_TheContext, "afterPrintBlock",
                               this->_Builder->GetInsertBlock()->getParent());

  this->_Builder->CreateCondBr(isZero, printBlock, afterPrintBlock);

  this->_Builder->SetInsertPoint(printBlock);

  code();

  this->_Builder->CreateBr(afterPrintBlock);

  this->_Builder->SetInsertPoint(afterPrintBlock);
}
