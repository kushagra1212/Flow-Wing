
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
    // llvm::Value *divisionResult = nullptr;
    // llvm::Value *isZero = Builder->CreateICmpEQ(rhsValue,
    // Builder->getInt32(0));

    // llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
    // llvm::BasicBlock *ifBlock =
    //     llvm::BasicBlock::Create(*TheContext, "if",
    //     currentBlock->getParent());
    // llvm::BasicBlock *elseBlock = llvm::BasicBlock::Create(
    //     *TheContext, "else", currentBlock->getParent());
    // llvm::BasicBlock *mergeBlock = llvm::BasicBlock::Create(
    //     *TheContext, "merge", currentBlock->getParent());
    // // Create a conditional branch
    // Builder->CreateCondBr(isZero, ifBlock, elseBlock);

    // // Set up the 'if' block
    // Builder->SetInsertPoint(ifBlock);

    // _codeGenerationContext->getLogger()->LogError("Division by zero is not
    // allowed");

    // Builder->CreateBr(mergeBlock);

    // Builder->SetInsertPoint(elseBlock);
    // divisionResult = Builder->CreateSDiv(lhsValue, rhsValue);
    // Builder->CreateBr(mergeBlock);

    // Builder->SetInsertPoint(mergeBlock);

    return Builder->CreateSDiv(lhsValue, rhsValue);
    ;
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::Division: {

    // llvm::Value *divisionResult = nullptr;
    // llvm::Value *isZero = Builder->CreateICmpEQ(rhsValue,
    // Builder->getInt32(0));

    // llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
    // llvm::BasicBlock *ifBlock =
    //     llvm::BasicBlock::Create(*TheContext, "if",
    //     currentBlock->getParent());
    // llvm::BasicBlock *elseBlock = llvm::BasicBlock::Create(
    //     *TheContext, "else", currentBlock->getParent());
    // llvm::BasicBlock *mergeBlock = llvm::BasicBlock::Create(
    //     *TheContext, "merge", currentBlock->getParent());
    // // Create a conditional branch
    // Builder->CreateCondBr(isZero, ifBlock, elseBlock);

    // // Set up the 'if' block
    // Builder->SetInsertPoint(ifBlock);

    // _codeGenerationContext->getLogger()->LogError("Division by zero is not
    // allowed");

    // Builder->CreateBr(mergeBlock);

    // Builder->SetInsertPoint(elseBlock);

    // divisionResult =
    //     Builder->CreateFDiv(_doubleTypeConverter->convertExplicit(lhsValue),
    //                         _doubleTypeConverter->convertExplicit(rhsValue));
    // Builder->CreateBr(mergeBlock);
    // Builder->SetInsertPoint(mergeBlock);
    return Builder->CreateFDiv(_doubleTypeConverter->convertExplicit(lhsValue),
                               _doubleTypeConverter->convertExplicit(rhsValue));
    ;
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

  case BinderKindUtils::BoundBinaryOperatorKind::Equals: {
    llvm::Value *_val = Builder->CreateICmpEQ(lhsValue, rhsValue);
    return _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), _val);
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals: {

    llvm::Value *_val = Builder->CreateICmpNE(lhsValue, rhsValue);
    return _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), _val);
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::Less: {
    llvm::Value *_val = Builder->CreateICmpSLT(lhsValue, rhsValue);
    return _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), _val);
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals: {
    llvm::Value *_val = Builder->CreateICmpSLE(lhsValue, rhsValue);
    return _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), _val);
    break;
  }

  case BinderKindUtils::BoundBinaryOperatorKind::Greater: {
    llvm::Value *_val = Builder->CreateICmpSGT(lhsValue, rhsValue);
    return _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), _val);
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals: {
    llvm::Value *_val = Builder->CreateICmpSGE(lhsValue, rhsValue);

    return _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), _val);
    break;
  }
  default: {

    errorMessage = "Unsupported binary operator for int type ";
    break;
  }
  }

  _codeGenerationContext->getLogger()->LogError(errorMessage);
  return nullptr;
}