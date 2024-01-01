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
  Utils::type returnTypeCustomType =
      _codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
          returnType->getType());
  if (returnTypeCustomType != Utils::type::NOTHING && returnStat == nullptr) {

    errorMessage = "Function return type is not Nothing, return "
                   "expression is not found";
  } else if (returnTypeCustomType == Utils::type::NOTHING &&
             returnStat != nullptr) {

    errorMessage = "Function return type is Nothing, return "
                   "expression is found";
  } else if (returnStat != nullptr) {
    returnValue =
        _expressionGenerationFactory->createStrategy(returnStat->getKind())
            ->generateExpression(returnStat);

    if (returnTypeCustomType !=
        _codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
            returnValue->getType())) {

      errorMessage = "Return Type Mismatch " +
                     Utils::typeToString(returnTypeCustomType) +
                     " is expected but " +
                     _codeGenerationContext->getMapper()->getLLVMTypeName(
                         returnValue->getType()) +
                     " is found";
    }
  }

  if (errorMessage != "") {
    _codeGenerationContext->getLogger()->LogError(errorMessage);
  }

  if (returnStat != nullptr && returnTypeCustomType != Utils::type::NOTHING) {

    returnValue =
        _expressionGenerationFactory->createStrategy(returnStat->getKind())
            ->generateExpression(returnStat);

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