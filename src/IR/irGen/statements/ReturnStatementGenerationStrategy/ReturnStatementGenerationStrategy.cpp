#include "ReturnStatementGenerationStrategy.h"

#include "../../expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

ReturnStatementGenerationStrategy::ReturnStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *ReturnStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {
  BoundReturnStatement *returnStatement =
      static_cast<BoundReturnStatement *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      returnStatement->getLocation());

  llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
  llvm::Function *function = currentBlock->getParent();

  llvm::BasicBlock *returnBlock =
      llvm::BasicBlock::Create(*TheContext, "returnBlock", function);

  llvm::BasicBlock *mergeBlock =
      llvm::BasicBlock::Create(*TheContext, "mergeBlock", function);

  Builder->CreateBr(returnBlock);

  Builder->SetInsertPoint(returnBlock);

  llvm::Value *returnValue = nullptr; // default return value

  llvm::Value *hasError = Builder->getFalse();
  std::string errorMessage = "";
  BoundExpression *returnStat = returnStatement->getReturnExpressionPtr().get();

  llvm::Function *currentFunction = Builder->GetInsertBlock()->getParent();

  std::string functionName = currentFunction->getName().str();

  LLVMType *returnType = _codeGenerationContext->getReturnTypeHandler()
                             ->getReturnType(functionName)
                             .get();

  SyntaxKindUtils::SyntaxKind returnTypeCustomType =
      _codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
          returnType->getType());
  if (returnTypeCustomType != SyntaxKindUtils::SyntaxKind::NthgKeyword &&
      returnStat == nullptr) {
    errorMessage = "Function return type is not Nothing, return "
                   "expression is not found";
  } else if (returnTypeCustomType == SyntaxKindUtils::SyntaxKind::NthgKeyword &&
             returnStat != nullptr) {
    errorMessage = "Function return type is Nothing, return "
                   "expression is found";
  } else if (returnStat != nullptr) {
    _codeGenerationContext->getValueStackHandler()->popAll();
    returnValue =
        _expressionGenerationFactory->createStrategy(returnStat->getKind())
            ->generateExpression(returnStat);

    if (returnType->isPointerToObject()) {
      LLVMObjectType *llvmObjectType =
          static_cast<LLVMObjectType *>(returnType);

      if (!_codeGenerationContext->getValueStackHandler()->isStructType()) {
        errorMessage = "Return Type Mismatch " +
                       _codeGenerationContext->getMapper()->getLLVMTypeName(
                           returnType->getType()) +
                       " is expected but " +
                       _codeGenerationContext->getMapper()->getLLVMTypeName(
                           returnValue->getType()) +
                       " is found";
      }

      if (llvmObjectType->getStructType()->getStructName() !=
          _codeGenerationContext->getValueStackHandler()->getTypeName()) {
        errorMessage =
            "Return Type Mismatch " +
            llvmObjectType->getStructType()->getStructName().str() +
            " is expected but " +

            _codeGenerationContext->getValueStackHandler()->getTypeName() +
            " is found";
      }

    } else if (returnTypeCustomType !=
               _codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
                   returnValue->getType())) {
      errorMessage = "Return Type Mismatch " +
                     _codeGenerationContext->getMapper()->getLLVMTypeName(
                         returnTypeCustomType) +
                     " is expected but " +
                     _codeGenerationContext->getMapper()->getLLVMTypeName(
                         returnValue->getType()) +
                     " is found";
    }
  }
  if (errorMessage != "") {
    _codeGenerationContext->getLogger()->LogError(errorMessage);
  }

  if (returnStat != nullptr &&
      returnTypeCustomType != SyntaxKindUtils::SyntaxKind::NthgKeyword) {
    if (!returnValue) {
      returnValue =
          _expressionGenerationFactory->createStrategy(returnStat->getKind())
              ->generateExpression(returnStat);
    }

    // create alloca for return value

    Builder->CreateRet(returnValue);

  } else {
    Builder->CreateRetVoid();
  }

  _codeGenerationContext->getReturnAllocaStack().top() = 1;

  Builder->SetInsertPoint(mergeBlock);

  return returnValue;
}

llvm::Value *ReturnStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  BoundReturnStatement *returnStatement =
      static_cast<BoundReturnStatement *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      returnStatement->getLocation());

  _codeGenerationContext->getLogger()->LogError(
      "Return Statement is not allowed in global scope ");

  return nullptr;
}