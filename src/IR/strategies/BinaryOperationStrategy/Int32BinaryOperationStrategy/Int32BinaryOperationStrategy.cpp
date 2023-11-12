
#include "Int32BinaryOperationStrategy.h"

Int32BinaryOperationStrategy::Int32BinaryOperationStrategy(
    CodeGenerationContext *context)
    : BinaryOperationStrategy(context){};

llvm::Value *Int32BinaryOperationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BoundBinaryExpression *binaryExpression) {

  llvm::Value *result = Builder->getInt32(1);

  std::string errorMessage = "";
  switch (binaryExpression->getOperator()) {

  case BinderKindUtils::BoundBinaryOperatorKind::Addition: {
    return result = Builder->CreateAdd(lhsValue, rhsValue);
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    return result = Builder->CreateSub(lhsValue, rhsValue);
    break;
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    return result = Builder->CreateMul(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::IntegerDivision: {

    llvm::Value *isZero = Builder->CreateICmpEQ(rhsValue, Builder->getInt32(0));

    llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
    llvm::BasicBlock *ifBlock =
        llvm::BasicBlock::Create(*TheContext, "if", currentBlock->getParent());
    llvm::BasicBlock *elseBlock = llvm::BasicBlock::Create(
        *TheContext, "else", currentBlock->getParent());

    // Create a conditional branch
    Builder->CreateCondBr(isZero, ifBlock, elseBlock);

    // Set up the 'if' block
    Builder->SetInsertPoint(ifBlock);
    Builder->CreateCall(
        TheModule->getFunction(INNERS::FUNCTIONS::RAISE_EXCEPTION),
        {Builder->CreateGlobalStringPtr(
            _codeGenerationContext->getLogger()->getLLVMErrorMsg(
                "Division by zero is not allowed",
                binaryExpression->getLocation()))});

    Builder->CreateBr(elseBlock);

    Builder->SetInsertPoint(elseBlock);

    llvm::Value *divisionResult = Builder->CreateSDiv(lhsValue, rhsValue);
    return divisionResult;
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::Division: {

    llvm::Value *isZero = Builder->CreateICmpEQ(rhsValue, Builder->getInt32(0));

    llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
    llvm::BasicBlock *ifBlock =
        llvm::BasicBlock::Create(*TheContext, "if", currentBlock->getParent());
    llvm::BasicBlock *elseBlock = llvm::BasicBlock::Create(
        *TheContext, "else", currentBlock->getParent());

    // Create a conditional branch
    Builder->CreateCondBr(isZero, ifBlock, elseBlock);

    // Set up the 'if' block
    Builder->SetInsertPoint(ifBlock);
    Builder->CreateCall(
        TheModule->getFunction(INNERS::FUNCTIONS::RAISE_EXCEPTION),
        {Builder->CreateGlobalStringPtr(
            _codeGenerationContext->getLogger()->getLLVMErrorMsg(
                "Division by zero is not allowed",
                binaryExpression->getLocation()))});

    Builder->CreateBr(elseBlock);

    Builder->SetInsertPoint(elseBlock);

    llvm::Value *divisionResult =
        Builder->CreateFDiv(_doubleTypeConverter->convertExplicit(lhsValue),
                            _doubleTypeConverter->convertExplicit(rhsValue));
    return divisionResult;
    break;
  }

  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    return Builder->CreateSRem(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    return Builder->CreateAnd(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    return Builder->CreateOr(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    return Builder->CreateXor(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    return Builder->CreateLogicalAnd(
        _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), lhsValue),
        _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), rhsValue));
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    return Builder->CreateLogicalOr(
        _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), lhsValue),
        _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), rhsValue));
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return _typeSpecificValueVisitor->visit(
        _boolTypeConverter.get(), Builder->CreateICmpEQ(lhsValue, rhsValue));
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return _typeSpecificValueVisitor->visit(
        _boolTypeConverter.get(), Builder->CreateICmpNE(lhsValue, rhsValue));
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Less: {
    return _typeSpecificValueVisitor->visit(
        _boolTypeConverter.get(), Builder->CreateICmpSLT(lhsValue, rhsValue));
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals: {
    return _typeSpecificValueVisitor->visit(
        _boolTypeConverter.get(), Builder->CreateICmpSLE(lhsValue, rhsValue));
    break;
  }

  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    return _typeSpecificValueVisitor->visit(
        _boolTypeConverter.get(), Builder->CreateICmpSGT(lhsValue, rhsValue));
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:

    return _typeSpecificValueVisitor->visit(
        _boolTypeConverter.get(), Builder->CreateICmpSGE(lhsValue, rhsValue));
    break;
  default: {

    errorMessage = "Unsupported binary operator for int type ";
    break;
  }
  }

  this->_codeGenerationContext->getLogger()->logLLVMError(
      llvm::createStringError(llvm::inconvertibleErrorCode(), errorMessage));

  return nullptr;
}