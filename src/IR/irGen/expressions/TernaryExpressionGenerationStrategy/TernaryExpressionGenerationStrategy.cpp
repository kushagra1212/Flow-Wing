#include "TernaryExpressionGenerationStrategy.h"
#include <cstdlib>

TernaryExpressionGenerationStrategy::TernaryExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *TernaryExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      expression->getLocation());

  auto ternaryExpression = static_cast<BoundTernaryExpression *>(expression);

  _codeGenerationContext->getValueStackHandler()->popAll();

  llvm::Value *conditionValue =
      _expressionGenerationFactory
          ->createStrategy(
              ternaryExpression->getConditionExpressionRef().get()->getKind())
          ->generateExpression(
              ternaryExpression->getConditionExpressionRef().get());

  if (_codeGenerationContext->getValueStackHandler()->isStructType()) {
    if (!_codeGenerationContext->isValidClassType(llvm::cast<llvm::StructType>(
            _codeGenerationContext->getValueStackHandler()->getLLVMType()))) {
      _codeGenerationContext->getLogger()->LogError(
          "Using Objects in If Statement is not allowed");
      return nullptr;
    }

    conditionValue = Builder->CreateIsNotNull(Builder->CreateLoad(
        llvm::Type::getInt8PtrTy(*TheContext), conditionValue));
  }
  if (_codeGenerationContext->getValueStackHandler()->isPrimaryType()) {
    conditionValue = Builder->CreateLoad(
        _codeGenerationContext->getValueStackHandler()->getLLVMType(),
        _codeGenerationContext->getValueStackHandler()->getValue());
    _codeGenerationContext->getValueStackHandler()->popAll();
  }

  if (conditionValue == nullptr) {

    _codeGenerationContext->getLogger()->LogError(
        "Condition value is not found in if statement");

    return nullptr;
  }

  llvm::Type *trueType = llvm::Type::getInt8Ty(*TheContext);
  llvm::Type *falseType = llvm::Type::getInt8Ty(*TheContext);

  llvm::BasicBlock *trueBlock = llvm::BasicBlock::Create(
      *TheContext, "trueBranch", Builder->GetInsertBlock()->getParent());
  llvm::BasicBlock *falseBlock = llvm::BasicBlock::Create(
      *TheContext, "falseBranch", Builder->GetInsertBlock()->getParent());
  llvm::BasicBlock *mergeBlock = llvm::BasicBlock::Create(
      *TheContext, "merge", Builder->GetInsertBlock()->getParent());

  Builder->CreateCondBr(_boolTypeConverter->convertExplicit(conditionValue),
                        trueBlock, falseBlock);

  // True branch logic
  Builder->SetInsertPoint(trueBlock);
  llvm::Value *trueValue =
      _expressionGenerationFactory
          ->createStrategy(
              ternaryExpression->getTrueExpressionRef().get()->getKind())
          ->generateExpression(ternaryExpression->getTrueExpressionRef().get());
  trueValue = _codeGenerationContext->getValueStackHandler()->getValue();
  trueType = _codeGenerationContext->getValueStackHandler()->getLLVMType();

  if (!_codeGenerationContext->getValueStackHandler()->isLLVMConstant()) {
    trueValue = Builder->CreateLoad(
        _codeGenerationContext->getValueStackHandler()->getLLVMType(),
        _codeGenerationContext->getValueStackHandler()->getValue());
  }

  _codeGenerationContext->getValueStackHandler()->popAll();

  Builder->CreateBr(mergeBlock);

  Builder->SetInsertPoint(falseBlock);

  llvm::Value *falseValue =
      _expressionGenerationFactory
          ->createStrategy(
              ternaryExpression->getFalseExpressionRef().get()->getKind())
          ->generateExpression(
              ternaryExpression->getFalseExpressionRef().get());
  falseValue = _codeGenerationContext->getValueStackHandler()->getValue();

  falseType = _codeGenerationContext->getValueStackHandler()->getLLVMType();

  if (!_codeGenerationContext->getValueStackHandler()->isLLVMConstant()) {
    falseValue = Builder->CreateLoad(
        _codeGenerationContext->getValueStackHandler()->getLLVMType(),
        _codeGenerationContext->getValueStackHandler()->getValue());
  }

  _codeGenerationContext->getValueStackHandler()->popAll();

  Builder->CreateBr(mergeBlock);

  Builder->SetInsertPoint(mergeBlock);

  if (trueType != falseType) {

    trueValue =
        llvm::Constant::getNullValue(llvm::Type::getInt8PtrTy(*TheContext));
    falseValue = trueValue;

    trueType = trueValue->getType();
    falseType = trueValue->getType();
  }

  llvm::PHINode *phiNode = Builder->CreatePHI(trueType, 2, "result");
  phiNode->addIncoming(trueValue, trueBlock);
  phiNode->addIncoming(falseValue, falseBlock);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      ternaryExpression->getLocation());

  _codeGenerationContext->getValueStackHandler()->push("", phiNode, "constant",
                                                       phiNode->getType());
  return phiNode;
}

llvm::Value *TernaryExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  return generateExpression(expression);
}