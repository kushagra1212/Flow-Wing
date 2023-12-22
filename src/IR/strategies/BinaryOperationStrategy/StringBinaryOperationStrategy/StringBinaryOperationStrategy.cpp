
#include "StringBinaryOperationStrategy.h"

StringBinaryOperationStrategy::StringBinaryOperationStrategy(
    CodeGenerationContext *context)
    : BinaryOperationStrategy(context){};

llvm::Value *StringBinaryOperationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BoundBinaryExpression *binaryExpression) {

  std::string errorMessage = "";

  switch (binaryExpression->getOperator()) {

  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    return concatenateStrings(lhsValue, rhsValue);

  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return createStringComparison(lhsValue, rhsValue,
                                  INNERS::FUNCTIONS::EQUAL_STRINGS);

  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return createStringComparison(lhsValue, rhsValue,
                                  INNERS::FUNCTIONS::EQUAL_STRINGS, "!=");

  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    return createStringComparison(lhsValue, rhsValue,
                                  INNERS::FUNCTIONS::LESS_THAN_STRINGS);

  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
    return createStringComparison(
        lhsValue, rhsValue, INNERS::FUNCTIONS::LESS_THAN_OR_EQUAL_STRINGS);

  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    return createStringComparison(lhsValue, rhsValue,
                                  INNERS::FUNCTIONS::GREATER_THAN_STRINGS);

  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    return createStringComparison(
        lhsValue, rhsValue, INNERS::FUNCTIONS::GREATER_THAN_OR_EQUAL_STRINGS);

  default: {
    errorMessage = "Unsupported binary operator for string type ";
    break;
  }
  }

  this->_codeGenerationContext->getLogger()->logLLVMError(
      llvm::createStringError(llvm::inconvertibleErrorCode(), errorMessage));

  return nullptr;
}

llvm::Value *StringBinaryOperationStrategy::createStringComparison(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    const std::string functionName, std::string operand) {

  llvm::Function *stringComparison = TheModule->getFunction(functionName);

  if (!stringComparison) {

    this->_codeGenerationContext->getLogger()->logLLVMError(
        llvm::createStringError(llvm::inconvertibleErrorCode(),
                                "Function " + functionName + " not found"));

    return nullptr;
  }

  llvm::GlobalVariable *globalTrueStr = TheModule->getGlobalVariable(
      this->_codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_TRUE));

  if (!globalTrueStr) {

    this->_codeGenerationContext->getLogger()->logLLVMError(
        llvm::createStringError(llvm::inconvertibleErrorCode(),

                                this->_codeGenerationContext->getPrefixedName(
                                    FLOWWING_GLOBAL_TRUE) +
                                    " variable not found"));

    return nullptr;
  }

  llvm::GlobalVariable *globalFalseStr = TheModule->getGlobalVariable(
      this->_codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_FALSE));

  if (!globalFalseStr) {

    this->_codeGenerationContext->getLogger()->logLLVMError(
        llvm::createStringError(llvm::inconvertibleErrorCode(),
                                this->_codeGenerationContext->getPrefixedName(
                                    FLOWWING_GLOBAL_FALSE) +
                                    " variable not found"));

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

llvm::Value *
StringBinaryOperationStrategy::concatenateStrings(llvm::Value *lhs,
                                                  llvm::Value *rhs) {

  llvm::Function *stringConcatenateFunc =
      TheModule->getFunction(INNERS::FUNCTIONS::CONCAT_STRINGS);

  if (!stringConcatenateFunc) {
    // Function not found, handle error
    return nullptr;
  } else {

    llvm::Value *args[] = {_stringTypeConverter->convertExplicit(lhs),
                           _stringTypeConverter->convertExplicit(rhs)};

    llvm::Value *res = Builder->CreateCall(stringConcatenateFunc, args);
    return res;
  }
}