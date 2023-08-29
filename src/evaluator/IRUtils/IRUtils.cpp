#include "IRUtils.h"

namespace IRUtils {

// GET VALUES

llvm::Value *getNamedValue(
    const std::string &name,
    std::stack<std::map<std::string, llvm::Value *>> NamedValuesStack) {
  llvm::Value *value = nullptr;
  while (!NamedValuesStack.empty()) {
    std::map<std::string, llvm::Value *> &NamedValues = NamedValuesStack.top();
    if (NamedValues.find(name) != NamedValues.end()) {
      value = NamedValues[name];
      break;
    }
    NamedValuesStack.pop();
  }
  return value;
}

llvm::AllocaInst *
getNamedValueAlloca(const std::string &name,
                    std::stack<std::map<std::string, llvm::AllocaInst *>>
                        NamedValuesAllocaStack) {
  llvm::AllocaInst *value = nullptr;
  while (!NamedValuesAllocaStack.empty()) {
    std::map<std::string, llvm::AllocaInst *> &NamedValues =
        NamedValuesAllocaStack.top();
    if (NamedValues.find(name) != NamedValues.end()) {
      value = NamedValues[name];
      break;
    }
    NamedValuesAllocaStack.pop();
  }
  return value;
}

// CHECK VALUES

bool isVariableDeclared(
    const std::string &name,
    std::stack<std::map<std::string, llvm::Value *>> NamedValuesStack) {
  bool isDeclared = false;
  while (!NamedValuesStack.empty()) {
    std::map<std::string, llvm::Value *> &NamedValues = NamedValuesStack.top();
    if (NamedValues.find(name) != NamedValues.end()) {
      isDeclared = true;
      break;
    }
    NamedValuesStack.pop();
  }
  return isDeclared;
}

void handleReplLastExpression(
    int _environment, llvm::Module *TheModule, llvm::IRBuilder<> *Builder,
    llvm::LLVMContext *TheContext,
    std::function<void(llvm::Module *TheModule, llvm::IRBuilder<> *Builder,
                       llvm::LLVMContext *TheContext)>
        printContent,
    std::function<void(llvm::Module *TheModule, llvm::IRBuilder<> *Builder,
                       llvm::LLVMContext *TheContext)>
        errorContent) {

  llvm::BasicBlock *lastBlock = Builder->GetInsertBlock();
  llvm::Function *lastFunction = lastBlock->getParent();

  llvm::BasicBlock *printBlock = llvm::BasicBlock::Create(
      *TheContext, "printBlock", lastFunction, lastBlock);

  llvm::BasicBlock *errorBlock = llvm::BasicBlock::Create(
      *TheContext, "errorBlock", lastFunction, lastBlock);

  llvm::BasicBlock *exitBlock = llvm::BasicBlock::Create(
      *TheContext, "exitBlock", lastFunction, lastBlock);

  llvm::Value *isErrorZero = IRUtils::isCountZero(
      ELANG_GLOBAL_ERROR, llvm::Type::getInt32Ty(*TheContext), TheModule,
      Builder, TheContext);

  Builder->CreateCondBr(isErrorZero, printBlock, errorBlock);

  Builder->SetInsertPoint(printBlock);

  printContent(TheModule, Builder, TheContext);

  Builder->CreateBr(exitBlock);

  Builder->SetInsertPoint(errorBlock);

  errorContent(TheModule, Builder, TheContext);

  Builder->CreateBr(exitBlock);

  Builder->SetInsertPoint(exitBlock);

} // UPDATE VALUES

bool updateNamedValue(
    const std::string &name, llvm::Value *value,
    std::stack<std::map<std::string, llvm::Value *>> &NamedValuesStack) {

  std::stack<std::map<std::string, llvm::Value *>> tempStack;

  bool isSet = false;
  while (!NamedValuesStack.empty()) {
    std::map<std::string, llvm::Value *> &NamedValues = NamedValuesStack.top();
    if (NamedValues.find(name) != NamedValues.end()) {
      NamedValues[name] = value;
      isSet = true;
      break;
    }
    tempStack.push(NamedValues);
    NamedValuesStack.pop();
  }

  while (!tempStack.empty()) {
    NamedValuesStack.push(tempStack.top());
    tempStack.pop();
  }

  return isSet;
}

bool updateNamedValueAlloca(
    const std::string &name, llvm::AllocaInst *value,
    std::stack<std::map<std::string, llvm::AllocaInst *>>
        &NamedValuesAllocaStack) {

  std::stack<std::map<std::string, llvm::AllocaInst *>> tempStack;

  bool isSet = false;
  while (!NamedValuesAllocaStack.empty()) {
    std::map<std::string, llvm::AllocaInst *> &NamedValues =
        NamedValuesAllocaStack.top();
    if (NamedValues.find(name) != NamedValues.end()) {
      NamedValues[name] = value;
      isSet = true;
      break;
    }
    tempStack.push(NamedValues);
    NamedValuesAllocaStack.pop();
  }

  while (!tempStack.empty()) {
    NamedValuesAllocaStack.push(tempStack.top());
    tempStack.pop();
  }

  return isSet;
}

// SET VALUES

void setNamedValue(
    const std::string &name, llvm::Value *value,
    std::stack<std::map<std::string, llvm::Value *>> &NamedValuesStack) {
  std::stack<std::map<std::string, llvm::Value *>> tempStack;

  std::map<std::string, llvm::Value *> &NamedValues = NamedValuesStack.top();
  NamedValues[name] = value;
}

void setNamedValueAlloca(const std::string &name, llvm::AllocaInst *value,
                         std::stack<std::map<std::string, llvm::AllocaInst *>>
                             &NamedValuesAllocaStack) {

  std::map<std::string, llvm::AllocaInst *> &NamedValues =
      NamedValuesAllocaStack.top();
  NamedValues[name] = value;
}

llvm::Value *addNewLineCharacter(llvm::Value *value, llvm::IRBuilder<> *Builder,
                                 bool isNewLine) {
  llvm::Value *i8Value = IRUtils::convertToString(value, Builder);

  if (!isNewLine)
    return i8Value;

  std::string strValue = IRUtils::valueToString(i8Value);
  strValue += '\n';

  return IRUtils::convertStringToi8Ptr(strValue, Builder);
}

void printFunction(llvm::Value *value, llvm::Module *TheModule,
                   llvm::IRBuilder<> *Builder, llvm::LLVMContext *TheContext,
                   bool isNewLine) {

  if (value && llvm::isa<llvm::Instruction>(value)) {
    // The value is an instruction or a derived class of Instruction
    llvm::Instruction *instruction = llvm::cast<llvm::Instruction>(value);
    if (instruction->getType()->isIntegerTy(1)) {
      llvm::Value *resultStr = Builder->CreateSelect(
          value, TheModule->getGlobalVariable("true_string"),
          TheModule->getGlobalVariable("false_string"));
      Builder->CreateCall(TheModule->getFunction("print"),
                          {resultStr, Builder->getInt1(isNewLine)});
    } else {

      llvm::ArrayRef<llvm::Value *> Args = {
          IRUtils::convertToString(value, Builder),
          Builder->getInt1(isNewLine)};

      Builder->CreateCall(TheModule->getFunction("print"), Args);
    }
  } else if (value) {
    llvm::ArrayRef<llvm::Value *> Args = {
        IRUtils::convertToString(value, Builder), Builder->getInt1(isNewLine)};

    Builder->CreateCall(TheModule->getFunction("print"), Args);
  }
}

llvm::Value *getLLVMValue(std::any value, llvm::Module *TheModule,
                          llvm::LLVMContext *TheContext,
                          llvm::IRBuilder<> *Builder) {
  if (value.type() == typeid(int)) {
    return llvm::ConstantInt::get(
        *TheContext, llvm::APInt(32, std::any_cast<int>(value), true));
  } else if (value.type() == typeid(double)) {
    return llvm::ConstantFP::get(*TheContext,
                                 llvm::APFloat(std::any_cast<double>(value)));
  } else if (value.type() == typeid(bool)) {
    return llvm::ConstantInt::get(
        *TheContext, llvm::APInt(1, std::any_cast<bool>(value), true));
  } else if (value.type() == typeid(std::string)) {

    std::string strValue = std::any_cast<std::string>(value);

    llvm::Constant *strConstant =
        llvm::ConstantDataArray::getString(*TheContext, strValue);

    llvm::GlobalVariable *strVar = new llvm::GlobalVariable(
        *TheModule, strConstant->getType(),
        true, // isConstant
        llvm::GlobalValue::ExternalLinkage, strConstant, "string_constant");

    llvm::Value *zero =
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*TheContext), 0);
    llvm::Value *indices[] = {zero, zero};
    llvm::Value *strPtr = Builder->CreateInBoundsGEP(
        strConstant->getType(), strVar, indices, "str_ptr");

    llvm::Value *elementPtr = Builder->CreateBitCast(
        strPtr, llvm::IntegerType::getInt8PtrTy((*TheContext)), "element_ptr");

    llvm::LoadInst *elementLoad = Builder->CreateLoad(
        llvm::IntegerType::getInt8PtrTy(*TheContext), elementPtr, "element");

    // llvm::Value *strVarPtr = Builder->CreatePointerCast(
    //     strVar, llvm::Type::getInt8PtrTy(*TheContext), "str_var_ptr");

    return elementPtr;
  } else {
    return nullptr;
  }
}

llvm::PHINode *
handleForLoopCondition(llvm::Value *stepValue, llvm::Value *value,
                       llvm::Value *upperBound, llvm::IRBuilder<> *Builder,
                       llvm::LLVMContext *TheContext, llvm::Module *TheModule) {
  llvm::Value *isStepNegative =
      Builder->CreateICmpSLT(stepValue, Builder->getInt32(0));

  llvm::BasicBlock *trueBlock = llvm::BasicBlock::Create(
      value->getContext(), "trueBlock", Builder->GetInsertBlock()->getParent());
  llvm::BasicBlock *falseBlock =
      llvm::BasicBlock::Create(value->getContext(), "falseBlock",
                               Builder->GetInsertBlock()->getParent());
  llvm::BasicBlock *mergeBlock =
      llvm::BasicBlock::Create(value->getContext(), "mergeBlock",
                               Builder->GetInsertBlock()->getParent());

  Builder->CreateCondBr(isStepNegative, trueBlock, falseBlock);

  Builder->SetInsertPoint(trueBlock);

  llvm::Value *oppositeCondition = Builder->CreateICmpSGE(value, upperBound);

  Builder->CreateBr(mergeBlock);

  Builder->SetInsertPoint(falseBlock);

  llvm::Value *normalCondition = Builder->CreateICmpSLE(value, upperBound);

  Builder->CreateBr(mergeBlock);

  Builder->SetInsertPoint(mergeBlock);

  llvm::PHINode *conditionPHI = Builder->CreatePHI(Builder->getInt1Ty(), 2);
  conditionPHI->addIncoming(oppositeCondition, trueBlock);
  conditionPHI->addIncoming(normalCondition, falseBlock);

  return conditionPHI;
}

size_t calculateStringLength(llvm::Value *strPtr, llvm::Module *TheModule,
                             llvm::IRBuilder<> *Builder) {
  llvm::Function *stringLengthFunc = TheModule->getFunction("stringLength");

  if (!stringLengthFunc) {
    // Function not found, handle error
    return 0;
  }

  llvm::Value *length = Builder->CreateCall(stringLengthFunc, strPtr);
  return std::any_cast<size_t>(length);
}

llvm::Value *itos(llvm::Value *num, llvm::Module *TheModule,
                  llvm::IRBuilder<> *Builder) {
  llvm::Function *itosFunc = TheModule->getFunction("itos");

  if (!itosFunc) {
    // Function not found, handle error
    return 0;
  }

  llvm::Value *strValue = Builder->CreateCall(itosFunc, num);
  return strValue;
}

std::string getString(BoundExpression *node) {
  std::any value = ((BoundLiteralExpression<std::any> *)node)->getValue();
  if (value.type() == typeid(std::string)) {
    return std::any_cast<std::string>(value);
  }
  return "";
}

std::string valueToString(llvm::Value *val) {
  if (!val)
    return "";

  llvm::ConstantInt *constInt = llvm::dyn_cast<llvm::ConstantInt>(val);
  if (constInt) {

    if (constInt->getType()->isIntegerTy(32)) {
      return std::to_string(constInt->getSExtValue());
    } else if (constInt->getType()->isIntegerTy(1)) {
      return constInt->getSExtValue() ? "true" : "false";
    } else {
      llvm::errs() << "Unsupported integer type for conversion to string";
      return "";
    }
  }

  llvm::ConstantFP *constFP = llvm::dyn_cast<llvm::ConstantFP>(val);

  if (constFP) {
    if (constFP->getType()->isDoubleTy()) {
      return std::to_string(constFP->getValueAPF().convertToDouble());
    } else {
      llvm::errs() << "Unsupported floating point type for conversion to "
                      "string";
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
        llvm::errs() << "Unexpected comparison result type\n";
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
    llvm::GlobalVariable *globalVar = new llvm::GlobalVariable(
        *module, i8PtrType, true, llvm::GlobalValue::PrivateLinkage, constExpr);

    std::string str;
    llvm::raw_string_ostream rso(str);
    globalVar->printAsOperand(rso, true, module);
    return rso.str();
  }

  if (val->getType()->isPointerTy() &&
      val->getType()->getPointerElementType()->isIntegerTy(8)) {
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

llvm::Value *convertStringToi8Ptr(std::string stringValue,
                                  llvm::IRBuilder<> *Builder) {
  llvm::Constant *stringConstant =
      llvm::ConstantDataArray::getString(Builder->getContext(), stringValue);
  llvm::GlobalVariable *globalVar = new llvm::GlobalVariable(
      *Builder->GetInsertBlock()->getParent()->getParent(),
      stringConstant->getType(), true, llvm::GlobalValue::PrivateLinkage,
      stringConstant);

  llvm::Value *i8Ptr = Builder->CreateBitCast(
      globalVar, llvm::Type::getInt8PtrTy(Builder->getContext()));
  return i8Ptr;
}

llvm::Value *convertToString(llvm::Value *val, llvm::IRBuilder<> *Builder) {
  llvm::Type *type = val->getType();

  if (isIntType(type)) {
    return itos(val, Builder->GetInsertBlock()->getParent()->getParent(),
                Builder);
  }

  if (isStringType(type)) {
    return val;
  }

  // Attempt to convert the value to string
  std::string stringValue = IRUtils::valueToString(val);

  // Create a global constant string and return its pointer
  if (!stringValue.empty()) {
    return convertStringToi8Ptr(stringValue, Builder);
  }

  return nullptr; // Return nullptr for other types or unrecognized cases
}

llvm::Value *concatenateStrings(llvm::Value *lhs, llvm::Value *rhs,
                                llvm::Module *TheModule,
                                llvm::IRBuilder<> *Builder) {

  llvm::Function *stringConcatenateFunc =
      TheModule->getFunction("concat_strings");

  if (!stringConcatenateFunc) {
    // Function not found, handle error
    return nullptr;

  } else {

    llvm::Value *args[] = {lhs, rhs};

    llvm::Value *res = Builder->CreateCall(stringConcatenateFunc, args);
    return res;
  }
}

llvm::Type *getTypeFromAny(std::any value, llvm::LLVMContext *TheContext) {
  if (value.type() == typeid(int)) {
    return llvm::Type::getInt32Ty(*TheContext);
  } else if (value.type() == typeid(double)) {
    return llvm::Type::getDoubleTy(*TheContext);
  } else if (value.type() == typeid(bool)) {
    return llvm::Type::getInt1Ty(*TheContext);
  } else if (value.type() == typeid(std::string)) {
    return llvm::Type::getInt8PtrTy(*TheContext);
  } else {
    return nullptr;
  }
}

bool isStringType(llvm::Type *type) {
  return type->isPointerTy() && type->getPointerElementType()->isIntegerTy(8);
}
bool isDoubleType(llvm::Type *type) { return type->isDoubleTy(); }

bool isIntType(llvm::Type *type) { return type->isIntegerTy(32); }

bool isBoolType(llvm::Type *type) { return type->isIntegerTy(1); }

llvm::Value *convertToDouble(llvm::Value *val, llvm::IRBuilder<> *Builder) {
  llvm::Type *type = val->getType();

  if (type->isDoubleTy()) {
    return val;
  } else if (type->isIntegerTy(32)) {
    return Builder->CreateSIToFP(
        val, llvm::Type::getDoubleTy(Builder->getContext()));
  } else if (type->isIntegerTy(1)) {
    return Builder->CreateUIToFP(
        val, llvm::Type::getDoubleTy(Builder->getContext()));
  } else if (isStringType(type)) {
    llvm::errs()
        << "Implicit conversion from string to double is not supported";
    return nullptr;
  } else {
    llvm::errs() << "Unsupported type for conversion to double";
    return nullptr;
  }
  return nullptr;
}

llvm::Value *convertToInt(llvm::Value *val, llvm::IRBuilder<> *Builder) {
  llvm::Type *type = val->getType();

  if (type->isIntegerTy(32)) {
    return val;
  } else if (type->isDoubleTy()) {
    llvm::errs() << "Implicit conversion from double to int is not supported";
    return nullptr;
  } else if (type->isIntegerTy(1)) {
    return Builder->CreateZExt(val,
                               llvm::Type::getInt32Ty(Builder->getContext()));
  } else if (isStringType(type)) {
    llvm::errs() << "Implicit conversion from string to int is not supported";
    return nullptr;
  } else {
    llvm::errs() << "Unsupported type for conversion to int";
    return nullptr;
  }
  return nullptr;
}

llvm::Value *convertToBool(llvm::Value *val, llvm::IRBuilder<> *Builder) {
  llvm::Type *type = val->getType();

  if (type->isIntegerTy(1)) {
    return val;
  } else if (type->isDoubleTy()) {
    llvm::errs() << "Implicit conversion from double to bool is not supported";
    return nullptr;
  } else if (type->isIntegerTy(32)) {
    return Builder->CreateICmpNE(
        val, llvm::ConstantInt::get(Builder->getInt32Ty(), 0));
  } else if (isStringType(type)) {
    llvm::errs() << "Implicit conversion from string to bool is not supported";
    return nullptr;
  } else {
    return nullptr;
  }
  return nullptr;
}
llvm::Value *checkBitSet(llvm::Value *result, unsigned int bitPosition,
                         llvm::IRBuilder<> *Builder) {
  llvm::Value *bitMask = Builder->getInt32(1 << bitPosition);
  llvm::Value *bitIsSet = Builder->CreateAnd(result, bitMask);
  llvm::Value *bitIsNonZero =
      Builder->CreateICmpNE(bitIsSet, Builder->getInt32(0));
  return bitIsNonZero;
}
llvm::Value *
createStringComparison(llvm::Value *lhsValue, llvm::Value *rhsValue,
                       llvm::Module *TheModule, llvm::IRBuilder<> *Builder,
                       llvm::LLVMContext *TheContext,
                       const std::string functionName, std::string operand) {

  llvm::Function *stringComparison = TheModule->getFunction(functionName);

  if (!stringComparison) {
    llvm::errs() << functionName + "function not found";
    return nullptr;
  }

  // / Get the Global Variable using the name

  llvm::GlobalVariable *globalTrueStr =
      TheModule->getGlobalVariable(ELANG_GLOBAL_TRUE);

  if (!globalTrueStr) {
    llvm::errs() << "true_string global variable not found";
    return nullptr;
  }

  llvm::GlobalVariable *globalFalseStr =
      TheModule->getGlobalVariable(ELANG_GLOBAL_FALSE);

  if (!globalFalseStr) {
    llvm::errs() << "false_string global variable not found";
    return nullptr;
  }

  llvm::Value *args[] = {lhsValue, rhsValue};
  llvm::CallInst *stringsCall = Builder->CreateCall(stringComparison, args);
  llvm::Value *resultStr =
      operand == "!="
          ? Builder->CreateSelect(stringsCall, globalFalseStr, globalTrueStr)
          : Builder->CreateSelect(stringsCall, globalTrueStr, globalFalseStr);

  return Builder->CreateBitCast(resultStr,
                                llvm::Type::getInt8PtrTy(*TheContext));
}

llvm::GlobalVariable *getNullValue(llvm::Module *TheModule,
                                   llvm::LLVMContext *TheContext,
                                   llvm::IRBuilder<> *Builder) {

  return TheModule->getGlobalVariable(ELANG_GLOBAL_NULL);
}

llvm::Value *getResultFromBinaryOperationOnString(
    llvm::Value *lhsValue, llvm::Value *rhsValue, llvm::IRBuilder<> *Builder,
    llvm::Module *TheModule, llvm::LLVMContext *TheContext,
    BoundBinaryExpression *binaryExpression) {
  llvm::Value *result = nullptr;
  switch (binaryExpression->getOperator()) {

  case BinderKindUtils::BoundBinaryOperatorKind::Addition: {

    result = concatenateStrings(lhsValue, rhsValue, TheModule, Builder);
    break;
  }

  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    result = createStringComparison(lhsValue, rhsValue, TheModule, Builder,
                                    TheContext, "equal_strings");
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    result = createStringComparison(lhsValue, rhsValue, TheModule, Builder,
                                    TheContext, "equal_strings", "!=");
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    result = createStringComparison(lhsValue, rhsValue, TheModule, Builder,
                                    TheContext, "less_than_strings");
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:

    result = createStringComparison(lhsValue, rhsValue, TheModule, Builder,
                                    TheContext, "less_than_or_equal_strings");
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    result = createStringComparison(lhsValue, rhsValue, TheModule, Builder,
                                    TheContext, "greater_than_strings");
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    result =
        createStringComparison(lhsValue, rhsValue, TheModule, Builder,
                               TheContext, "greater_than_or_equal_strings");
    break;

  // Add more cases for other binary operators
  default:
    llvm::errs() << "Unsupported binary operator for string type";
    return nullptr;
  }
  return result;
}
llvm::ConstantInt *getConstantIntFromValue(llvm::Value *value) {
  if (llvm::ConstantInt *constInt = llvm::dyn_cast<llvm::ConstantInt>(value)) {
    return constInt;
  }
  return nullptr;
}

llvm::Value *getGlobalVarAndLoad(const std::string name, llvm::Type *Ty,
                                 llvm::Module *TheModule,
                                 llvm::IRBuilder<> *Builder,
                                 llvm::LLVMContext *TheContext) {

  llvm::Value *ptr = TheModule->getGlobalVariable(name);

  // Assuming that zeroPtr is of type i32*
  llvm::Value *var = Builder->CreateLoad(Ty, ptr);

  return var;
}
llvm::Value *isCountZero(const std::string name, llvm::Type *ty,
                         llvm::Module *TheModule, llvm::IRBuilder<> *Builder,
                         llvm::LLVMContext *TheContext) {
  llvm::Value *count =
      getGlobalVarAndLoad(name, ty, TheModule, Builder, TheContext);
  llvm::Value *loadZero = getGlobalVarAndLoad(ELANG_GLOBAL_ZERO, ty, TheModule,
                                              Builder, TheContext);

  llvm::Value *isZero = Builder->CreateICmpEQ(count, loadZero);
  return isZero;
}

void incrementCount(const std::string name, llvm::Module *TheModule,
                    llvm::IRBuilder<> *Builder, llvm::LLVMContext *TheContext) {
  llvm::Value *count =
      getGlobalVarAndLoad(name, llvm::Type::getInt32Ty(*TheContext), TheModule,
                          Builder, TheContext);
  llvm::Value *newCount = Builder->CreateAdd(
      count, llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 1, true)));
  Builder->CreateStore(newCount, TheModule->getGlobalVariable(name));
}

void decrementCountIfNotZero(const std::string name, llvm::Module *TheModule,
                             llvm::IRBuilder<> *Builder,
                             llvm::LLVMContext *TheContext) {

  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
  llvm::BasicBlock *decrementBlock = llvm::BasicBlock::Create(
      *TheContext, "decrement_block", currentBlock->getParent());
  llvm::BasicBlock *endBlock = llvm::BasicBlock::Create(
      *TheContext, "end_block", currentBlock->getParent());

  llvm::Value *isZero = isCountZero(name, llvm::Type::getInt32Ty(*TheContext),
                                    TheModule, Builder, TheContext);
  Builder->CreateCondBr(isZero, endBlock, decrementBlock);

  Builder->SetInsertPoint(decrementBlock);
  llvm::Value *count =
      getGlobalVarAndLoad(name, llvm::Type::getInt32Ty(*TheContext), TheModule,
                          Builder, TheContext);
  llvm::Value *newCount = Builder->CreateSub(
      count, llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 1, true)));
  Builder->CreateStore(newCount, TheModule->getGlobalVariable(name));
  Builder->CreateBr(endBlock);

  Builder->SetInsertPoint(endBlock);
}

llvm::Value *getResultFromBinaryOperationOnDouble(
    llvm::Value *lhsValue, llvm::Value *rhsValue, llvm::IRBuilder<> *Builder,
    llvm::Module *TheModule, BoundBinaryExpression *binaryExpression) {
  llvm::Value *result = nullptr;
  switch (binaryExpression->getOperator()) {

  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    result = Builder->CreateFAdd(lhsValue, rhsValue);
    break;
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    result = Builder->CreateFSub(lhsValue, rhsValue);
    break;
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    result = Builder->CreateFMul(lhsValue, rhsValue);
    break;
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    result = Builder->CreateFDiv(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    result = Builder->CreateFRem(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    llvm::errs() << "Bitwise And is not supported for double type";
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    llvm::errs() << "Bitwise Or is not supported for double type";
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    llvm::errs() << "Bitwise Xor is not supported for double type";
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    llvm::errs() << "Logical And is not supported for double type";
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    llvm::errs() << "Logical Or is not supported for double type";
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    result = Builder->CreateFCmpOEQ(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    result = Builder->CreateFCmpONE(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    result = Builder->CreateFCmpOLT(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:

    result = Builder->CreateFCmpOLE(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    result = Builder->CreateFCmpOGT(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    result = Builder->CreateFCmpOGE(lhsValue, rhsValue);
    break;

  // Add more cases for other binary operators
  default:
    llvm::errs() << "Unsupported binary operator for double type";
    return nullptr;
  }
  return result;
}

llvm::Value *getResultFromBinaryOperationOnInt(
    llvm::Value *lhsValue, llvm::Value *rhsValue, llvm::IRBuilder<> *Builder,
    llvm::Module *TheModule, BoundBinaryExpression *binaryExpression,
    llvm::LLVMContext *TheContext) {
  llvm::Value *result = Builder->getInt32(1);
  switch (binaryExpression->getOperator()) {

  case BinderKindUtils::BoundBinaryOperatorKind::Addition: {
    result = Builder->CreateAdd(lhsValue, rhsValue);

    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    result = Builder->CreateSub(lhsValue, rhsValue);
    break;
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    result = Builder->CreateMul(lhsValue, rhsValue);
    break;
  case BinderKindUtils::BoundBinaryOperatorKind::Division: {

    // Check if rhsValue is zero
    llvm::Value *zeroCheck = IRUtils::convertToBool(rhsValue, Builder);

    // Basic block for the error case
    llvm::BasicBlock *errorBlock = llvm::BasicBlock::Create(
        *TheContext, "error", Builder->GetInsertBlock()->getParent());
    llvm::BasicBlock *continueBlock = llvm::BasicBlock::Create(
        *TheContext, "continueBlock", Builder->GetInsertBlock()->getParent());

    llvm::BasicBlock *opExitBlock = llvm::BasicBlock::Create(
        *TheContext, "opExitBlock", Builder->GetInsertBlock()->getParent());

    // Conditional branch based on zeroCheck
    Builder->CreateCondBr(zeroCheck, continueBlock, errorBlock);

    // Set insert point to the error block
    Builder->SetInsertPoint(errorBlock);
    // Emit error message or handling code here

    // Create call to print function

    std::string error = "\x1b[31mDivision by zero";

    llvm::Value *errorStr = IRUtils::convertStringToi8Ptr(error, Builder);

    IRUtils::incrementCount(ELANG_GLOBAL_ERROR, TheModule, Builder, TheContext);

    IRUtils::printFunction(errorStr, TheModule, Builder, TheContext, false);

    llvm::Type *int8PtrType = llvm::Type::getInt8PtrTy(*TheContext);
    result = llvm::ConstantExpr::getBitCast(
        getNullValue(TheModule, TheContext, Builder), int8PtrType);
    Builder->CreateBr(opExitBlock);

    Builder->SetInsertPoint(continueBlock);
    result = Builder->CreateSDiv(lhsValue, rhsValue);
    Builder->CreateBr(opExitBlock);

    Builder->SetInsertPoint(opExitBlock);
    break;
  }

  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    result = Builder->CreateSRem(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    result = Builder->CreateAnd(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    result = Builder->CreateOr(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    result = Builder->CreateXor(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    result =
        Builder->CreateLogicalAnd(IRUtils::convertToBool(lhsValue, Builder),
                                  IRUtils::convertToBool(rhsValue, Builder));
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    result =
        Builder->CreateLogicalOr(IRUtils::convertToBool(lhsValue, Builder),
                                 IRUtils::convertToBool(rhsValue, Builder));
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    result = IRUtils::convertToBool(Builder->CreateICmpEQ(lhsValue, rhsValue),
                                    Builder);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    result = IRUtils::convertToBool(Builder->CreateICmpNE(lhsValue, rhsValue),
                                    Builder);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Less: {

    result = IRUtils::convertToBool(Builder->CreateICmpSLT(lhsValue, rhsValue),
                                    Builder);

    return result;
    break;
  }

  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals: {

    result = IRUtils::convertToBool(Builder->CreateICmpSLE(lhsValue, rhsValue),
                                    Builder);

    break;
  }

  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    result = IRUtils::convertToBool(Builder->CreateICmpSGT(lhsValue, rhsValue),
                                    Builder);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:

    result = IRUtils::convertToBool(Builder->CreateICmpSGE(lhsValue, rhsValue),
                                    Builder);
    break;

    // Add more cases for other binary operators

  default:

    llvm::errs() << "Unsupported binary operator for int type";
    return nullptr;
  }
  return result;
}

llvm::Value *getResultFromBinaryOperationOnBool(
    llvm::Value *lhsValue, llvm::Value *rhsValue, llvm::IRBuilder<> *Builder,
    llvm::Module *TheModule, BoundBinaryExpression *binaryExpression,
    llvm::LLVMContext *TheContext) {
  llvm::Value *result = nullptr;
  switch (binaryExpression->getOperator()) {

  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    result = convertToBool(getResultFromBinaryOperationOnInt(
                               convertToInt(lhsValue, Builder),
                               convertToInt(rhsValue, Builder), Builder,
                               TheModule, binaryExpression, TheContext),
                           Builder);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    result = Builder->CreateLogicalAnd(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    result = Builder->CreateLogicalOr(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    result = Builder->CreateICmpEQ(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    result = Builder->CreateICmpNE(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    result = Builder->CreateICmpSLT(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:

    result = Builder->CreateICmpSLE(lhsValue, rhsValue);
    break;

  case BinderKindUtils ::BoundBinaryOperatorKind::Greater:
    result = Builder->CreateICmpSGT(lhsValue, rhsValue);
    break;

  case BinderKindUtils ::BoundBinaryOperatorKind::GreaterOrEquals:

    result = Builder->CreateICmpSGE(lhsValue, rhsValue);
    break;

  // Add more cases for other binary operators
  default:

    llvm::errs() << "Unsupported binary operator for bool type";
    return nullptr;
  }
  return result;
}

} // namespace IRUtils
