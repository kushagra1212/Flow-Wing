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

  if (_codeGenerationContext->getReturnAllocaStack().top().first !=
          Utils::type::NOTHING &&
      returnStat == nullptr) {

    errorMessage = "Function return type is not Nothing, return "
                   "expression is not found";
  } else if (_codeGenerationContext->getReturnAllocaStack().top().first ==
                 Utils::type::NOTHING &&
             returnStat != nullptr) {

    errorMessage = "Function return type is Nothing, return "
                   "expression is found";
  } else if (returnStat != nullptr) {
    returnValue =
        _expressionGenerationFactory->createStrategy(returnStat->getKind())
            ->generateExpression(returnStat);

    if (_codeGenerationContext->getReturnAllocaStack().top().first !=
        _codeGenerationContext->getMapper()->mapLLVMTypeToCustomType(
            returnValue->getType())) {

      errorMessage =
          "Return Type Mismatch " +
          Utils::typeToString(
              _codeGenerationContext->getReturnAllocaStack().top().first) +
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
      _codeGenerationContext->getReturnAllocaStack().top().first !=
          Utils::type::NOTHING) {

    returnValue =
        _expressionGenerationFactory->createStrategy(returnStat->getKind())
            ->generateExpression(returnStat);

    _codeGenerationContext->getReturnAllocaStack().top().second += 1;

    // create alloca for return value

    Builder->CreateRet(returnValue);

  } else {
    Builder->CreateRetVoid();
  }

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