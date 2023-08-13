#include "IRUtils.h"

namespace IRUtils {
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

    const std::string &strValue = std::any_cast<std::string>(value);

    // Create a global constant data array for the string
    llvm::Constant *strConstant =
        llvm::ConstantDataArray::getString(*TheContext, strValue);

    // Create a global variable to hold the string constant
    llvm::GlobalVariable *strGlobal = new llvm::GlobalVariable(
        *TheModule, strConstant->getType(), true,
        llvm::GlobalValue::PrivateLinkage, strConstant, "string_constant");

    // Get a pointer to the string global variable
    return Builder->CreateBitCast(strGlobal,
                                  llvm::Type::getInt8PtrTy(*TheContext));

  } else {
    return nullptr;
  }
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

std::string getString(BoundExpression *node) {
  std::any value = ((BoundLiteralExpression<std::any> *)node)->getValue();
  if (value.type() == typeid(std::string)) {
    return std::any_cast<std::string>(value);
  }
  return "";
}

std::string valueToString(llvm::Value *val) {
  if (!val)
    return "nullptr";

  llvm::ConstantInt *constInt = llvm::dyn_cast<llvm::ConstantInt>(val);
  if (constInt) {

    if (constInt->getType()->isIntegerTy(32)) {
      return std::to_string(constInt->getSExtValue());
    } else if (constInt->getType()->isIntegerTy(1)) {
      return constInt->getSExtValue() ? "true" : "false";
    } else {
      return std::to_string(constInt->getZExtValue());
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

llvm::Value *convertToI8Pointer(llvm::Value *val, llvm::IRBuilder<> *Builder) {
  llvm::Type *type = val->getType();

  if (type->isPointerTy() && type->getPointerElementType()->isIntegerTy(8)) {
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
            llvm::Type *i8Type =
                llvm::Type::getInt8PtrTy(Builder->getContext());
            llvm::Value *result = Builder->CreateBitCast(basePtr, i8Type);
            return result;
          }
        }
      }
    }
  }

  // Attempt to convert the value to string
  std::string stringValue = IRUtils::valueToString(val);

  // Create a global constant string and return its pointer
  if (!stringValue.empty()) {
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

  return nullptr; // Return nullptr for other types or unrecognized cases
}

bool isStringType(llvm::Type *type) {
  return type->isPointerTy() && type->getPointerElementType()->isIntegerTy(8);
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

} // namespace IRUtils
