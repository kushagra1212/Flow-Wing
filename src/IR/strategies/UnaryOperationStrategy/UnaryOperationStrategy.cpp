#include "UnaryOperationStrategy.h"

llvm::Value *UnaryOperationStrategy::performOperation(
    llvm::Value *val, BoundUnaryExpression *unaryExpression) {

  if (_codeGenerationContext->getValueStackHandler()->isStructType() &&
      _codeGenerationContext->isValidClassType(llvm::cast<llvm::StructType>(
          _codeGenerationContext->getValueStackHandler()->getLLVMType()))) {

    val = Builder->CreateIsNotNull(Builder->CreateLoad(
        llvm::Type::getInt8PtrTy(*TheContext),
        _codeGenerationContext->getValueStackHandler()->getValue()));
  }

  llvm::Type *type = val->getType();

  TypeMapper *typeMapper = this->_codeGenerationContext->getMapper().get();
  switch (unaryExpression->getOperatorPtr()) {
  case BinderKindUtils::BoundUnaryOperatorKind::Identity: {

    return Builder->CreateAdd(
        val, llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true)));
  }
  case BinderKindUtils::BoundUnaryOperatorKind::Negation: {

    return Builder->CreateSub(
        llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true)), val);
  }
  case BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation: {

    if (typeMapper->isInt32Type(type) || typeMapper->isDoubleType(type) ||
        typeMapper->isFloatType(type)) {
      // Convert non-boolean values to boolean (true if zero, false if non-zero)
      return Builder->CreateICmpEQ(
          val, llvm::Constant::getNullValue(val->getType()));
    } else if (typeMapper->isStringType(type)) {
      llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
      llvm::BasicBlock *nullBlock =
          llvm::BasicBlock::Create(val->getContext(), "UnaryOP::NullBlock",
                                   Builder->GetInsertBlock()->getParent());
      llvm::BasicBlock *notNullBlock =
          llvm::BasicBlock::Create(val->getContext(), "UnaryOP::NotNullBlock",
                                   Builder->GetInsertBlock()->getParent());
      llvm::BasicBlock *mergeBlock =
          llvm::BasicBlock::Create(val->getContext(), "UnaryOP::MergeBlock",
                                   Builder->GetInsertBlock()->getParent());

      Builder->CreateCondBr(Builder->CreateIsNull(val), nullBlock,
                            notNullBlock);

      Builder->SetInsertPoint(nullBlock);
      // true if null [ BoundUnaryOperatorKind::LogicalNegation ]
      llvm::Value *resultFromNullBlock = Builder->getTrue();

      Builder->CreateBr(mergeBlock);

      Builder->SetInsertPoint(notNullBlock);
      // Get the string length
      // Compare the string Length to Zero

      //! For String

      llvm::Value *strLen = Builder->CreateCall(
          TheModule->getFunction(INNERS::FUNCTIONS::STRING_LENGTH),
          {_stringTypeConverter->convertExplicit(val)});

      llvm::Value *strLenIsZero =
          Builder->CreateICmpEQ(strLen, Builder->getInt32(0));

      llvm::Value *resultFromNotNullBlock = Builder->CreateSelect(
          strLenIsZero, llvm::ConstantInt::get(Builder->getInt1Ty(), 1),
          llvm::ConstantInt::get(Builder->getInt1Ty(), 0));
      Builder->CreateBr(mergeBlock);

      Builder->SetInsertPoint(mergeBlock);
      llvm::PHINode *conditionPHI = Builder->CreatePHI(Builder->getInt1Ty(), 2);
      conditionPHI->addIncoming(resultFromNullBlock, nullBlock);
      conditionPHI->addIncoming(resultFromNotNullBlock, notNullBlock);

      return conditionPHI;
    } else if (typeMapper->isBoolType(type)) {
      // For boolean values, perform logical NOT
      return Builder->CreateNot(val);
    } else if (typeMapper->isNirastValue(val)) {
      return Builder->CreateICmpNE(
          val, llvm::Constant::getNullValue(val->getType()));
    }
    break;
  }
  case BinderKindUtils::BoundUnaryOperatorKind::BitwiseNegation: {

    return Builder->CreateXor(
        val, llvm::ConstantInt::get(*TheContext, llvm::APInt(32, -1, true)));
  }
  default: {
    break;
  }
  }

  this->_codeGenerationContext->getLogger()->LogError(
      "Unsupported Unary Expression Type ");

  return nullptr;
}
