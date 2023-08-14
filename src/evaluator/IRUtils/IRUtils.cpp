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

std::string getString(std::shared_ptr<BoundExpression> node) {
  std::any value =
      std::static_pointer_cast<BoundLiteralExpression<std::any>>(node)
          ->getValue();
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

llvm::Value *getResultFromBinaryOperationOnDouble(
    llvm::Value *lhsValue, llvm::Value *rhsValue, llvm::IRBuilder<> *Builder,
    llvm::Module *TheModule,
    std::shared_ptr<BoundBinaryExpression> binaryExpression) {
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
    result = Builder->CreateAnd(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    result = Builder->CreateOr(lhsValue, rhsValue);
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
    // Handle unsupported binary operator
    return nullptr;
  }
  return result;
}

llvm::Value *getResultFromBinaryOperationOnInt(
    llvm::Value *lhsValue, llvm::Value *rhsValue, llvm::IRBuilder<> *Builder,
    llvm::Module *TheModule,
    std::shared_ptr<BoundBinaryExpression> binaryExpression) {
  llvm::Value *result = nullptr;
  switch (binaryExpression->getOperator()) {

  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    result = Builder->CreateAdd(lhsValue, rhsValue);

    break;
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    result = Builder->CreateSub(lhsValue, rhsValue);
    break;
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    result = Builder->CreateMul(lhsValue, rhsValue);
    break;
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
    result = Builder->CreateSDiv(lhsValue, rhsValue);
    break;

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
    result = Builder->CreateAnd(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    result = Builder->CreateOr(lhsValue, rhsValue);
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

  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    result = Builder->CreateICmpSGT(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:

    result = Builder->CreateICmpSGE(lhsValue, rhsValue);
    break;

    // Add more cases for other binary operators

  default:
    // Handle unsupported binary operator
    return nullptr;
  }
  return result;
}

llvm::Value *getResultFromBinaryOperationOnBool(
    llvm::Value *lhsValue, llvm::Value *rhsValue, llvm::IRBuilder<> *Builder,
    llvm::Module *TheModule,
    std::shared_ptr<BoundBinaryExpression> binaryExpression) {
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
    result = convertToBool(
        getResultFromBinaryOperationOnInt(convertToInt(lhsValue, Builder),
                                          convertToInt(rhsValue, Builder),
                                          Builder, TheModule, binaryExpression),
        Builder);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    result = Builder->CreateAnd(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    result = Builder->CreateOr(lhsValue, rhsValue);
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
    // Handle unsupported binary operator
    return nullptr;
  }
  return result;
}

} // namespace IRUtils
