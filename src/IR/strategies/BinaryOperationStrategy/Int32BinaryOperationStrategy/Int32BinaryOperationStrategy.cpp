
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
    llvm::Value *divisionResult = nullptr;
    llvm::Value *isZero = Builder->CreateICmpEQ(rhsValue, Builder->getInt32(0));

    llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
    llvm::BasicBlock *ifBlock =
        llvm::BasicBlock::Create(*TheContext, "if", currentBlock->getParent());
    llvm::BasicBlock *elseBlock = llvm::BasicBlock::Create(
        *TheContext, "else", currentBlock->getParent());
    llvm::BasicBlock *mergeBlock = llvm::BasicBlock::Create(
        *TheContext, "merge", currentBlock->getParent());
    // Create a conditional branch
    Builder->CreateCondBr(isZero, ifBlock, elseBlock);

    // Set up the 'if' block
    Builder->SetInsertPoint(ifBlock);

    _codeGenerationContext->callREF("Division by zero is not allowed");

    Builder->CreateBr(mergeBlock);

    Builder->SetInsertPoint(elseBlock);
    divisionResult = Builder->CreateSDiv(lhsValue, rhsValue);
    Builder->CreateBr(mergeBlock);

    Builder->SetInsertPoint(mergeBlock);

    return divisionResult;
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::Division: {

    llvm::Value *divisionResult = nullptr;
    llvm::Value *isZero = Builder->CreateICmpEQ(rhsValue, Builder->getInt32(0));

    llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
    llvm::BasicBlock *ifBlock =
        llvm::BasicBlock::Create(*TheContext, "if", currentBlock->getParent());
    llvm::BasicBlock *elseBlock = llvm::BasicBlock::Create(
        *TheContext, "else", currentBlock->getParent());
    llvm::BasicBlock *mergeBlock = llvm::BasicBlock::Create(
        *TheContext, "merge", currentBlock->getParent());
    // Create a conditional branch
    Builder->CreateCondBr(isZero, ifBlock, elseBlock);

    // Set up the 'if' block
    Builder->SetInsertPoint(ifBlock);

    _codeGenerationContext->callREF("Division by zero is not allowed");

    Builder->CreateBr(mergeBlock);

    Builder->SetInsertPoint(elseBlock);

    divisionResult =
        Builder->CreateFDiv(_doubleTypeConverter->convertExplicit(lhsValue),
                            _doubleTypeConverter->convertExplicit(rhsValue));
    Builder->CreateBr(mergeBlock);
    Builder->SetInsertPoint(mergeBlock);
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

  this->_codeGenerationContext->callREF(errorMessage);
  return nullptr;
}