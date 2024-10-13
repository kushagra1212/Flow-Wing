#include "MultipleVariableDeclarationStatementGenerationStrategy.h"

#include "../../expressions/AssignmentExpressionGenerationStrategy/AssignmentExpressionGenerationStrategy.h"

MultipleVariableDeclarationStatementGenerationStrategy::
    MultipleVariableDeclarationStatementGenerationStrategy(
        CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *
MultipleVariableDeclarationStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {
  BoundMultipleVariableDeclaration *multipleVariableDeclaration =
      static_cast<BoundMultipleVariableDeclaration *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      multipleVariableDeclaration->getLocation());

  if (this->hasSingleCallExpr(multipleVariableDeclaration)) {
    handleMultipleVarDecCallExprGen(multipleVariableDeclaration);
    return nullptr;
  }

  std::unique_ptr<VariableDeclarationStatementGenerationStrategy>
      varDecGenStrat =
          std::make_unique<VariableDeclarationStatementGenerationStrategy>(
              _codeGenerationContext);

  for (auto &variable :
       multipleVariableDeclaration->getVariableDeclarationListRef()) {
    varDecGenStrat->generateStatement(variable.get());
  }

  return nullptr;
}

bool MultipleVariableDeclarationStatementGenerationStrategy::hasSingleCallExpr(
    BoundMultipleVariableDeclaration *multipleVariableDeclaration) {

  for (uint64_t i = 0;
       i < multipleVariableDeclaration->getVariableDeclarationListRef().size();
       i++) {
    if (i == 0) {
      if (!multipleVariableDeclaration->getVariableDeclarationListRef()[i]
               ->getInitializerPtr()) {
        return false;
      }

      BoundCallExpression *callExpression = BoundUtils::getCallExpression(
          multipleVariableDeclaration->getVariableDeclarationListRef()[i]
              ->getInitializerPtr()
              .get());

      if (!callExpression) {
        return false;
      }
    }

    if (i != 0 &&
        multipleVariableDeclaration->getVariableDeclarationListRef()[i]
            ->getInitializerPtr()) {
      return false;
    }
  }

  return true;
}

void MultipleVariableDeclarationStatementGenerationStrategy::
    handleMultipleVarDecCallExprGen(
        BoundMultipleVariableDeclaration *multipleVariableDeclaration) {
  auto firstVariableDeclaration =
      multipleVariableDeclaration->getVariableDeclarationListRef()[0].get();

  if (!firstVariableDeclaration->getInitializerPtr()) {
    return;
  }

  BoundCallExpression *callExpression = BoundUtils::getCallExpression(
      firstVariableDeclaration->getInitializerPtr().get());

  std::unique_ptr<AssignmentExpressionGenerationStrategy> assignmentEGS =
      std::make_unique<AssignmentExpressionGenerationStrategy>(
          _codeGenerationContext);

  if (callExpression) {

    assignmentEGS->handleAssignExpression(
        callExpression->getArgumentAlloca(0).first,
        callExpression->getArgumentAlloca(0).second, "_retrunArg",
        firstVariableDeclaration->getInitializerPtr().get());

    for (auto &expr :
         multipleVariableDeclaration->getVariableDeclarationListRef()) {

      _codeGenerationContext->getAllocaChain()->setPtr(expr->getVariableName(),
                                                       expr->getLLVMVariable());
    }
  }
}

llvm::Value *
MultipleVariableDeclarationStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  BoundMultipleVariableDeclaration *multipleVariableDeclaration =
      static_cast<BoundMultipleVariableDeclaration *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      multipleVariableDeclaration->getLocation());

  if (this->hasSingleCallExpr(multipleVariableDeclaration)) {
    handleMultipleVarDecCallExprGen(multipleVariableDeclaration);
    return nullptr;
  }

  std::unique_ptr<VariableDeclarationStatementGenerationStrategy>
      varDecGenStrat =
          std::make_unique<VariableDeclarationStatementGenerationStrategy>(
              _codeGenerationContext);

  for (auto &variable :
       multipleVariableDeclaration->getVariableDeclarationListRef()) {
    varDecGenStrat->generateGlobalStatement(variable.get());
  }

  return nullptr;
}

llvm::Value *
MultipleVariableDeclarationStatementGenerationStrategy::declareGlobal(
    BoundStatement *statement) {
  BoundMultipleVariableDeclaration *multipleVariableDeclaration =
      static_cast<BoundMultipleVariableDeclaration *>(statement);
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      multipleVariableDeclaration->getLocation());

  std::unique_ptr<VariableDeclarationStatementGenerationStrategy>
      varDecGenStrat =
          std::make_unique<VariableDeclarationStatementGenerationStrategy>(
              _codeGenerationContext);

  for (auto &variable :
       multipleVariableDeclaration->getVariableDeclarationListRef()) {
    varDecGenStrat->declareGlobal(variable.get());
  }

  if (this->hasSingleCallExpr(multipleVariableDeclaration))
    handleMultipleVarDecReturnCallExprDeclare(multipleVariableDeclaration);

  return nullptr;
}

llvm::Value *
MultipleVariableDeclarationStatementGenerationStrategy::declareLocal(
    BoundStatement *statement) {

  BoundMultipleVariableDeclaration *multipleVariableDeclaration =
      static_cast<BoundMultipleVariableDeclaration *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      multipleVariableDeclaration->getLocation());

  std::unique_ptr<VariableDeclarationStatementGenerationStrategy>
      varDecGenStrat =
          std::make_unique<VariableDeclarationStatementGenerationStrategy>(
              _codeGenerationContext);

  for (auto &variable :
       multipleVariableDeclaration->getVariableDeclarationListRef()) {
    varDecGenStrat->declareLocal(variable.get());
  }

  if (this->hasSingleCallExpr(multipleVariableDeclaration))
    handleMultipleVarDecReturnCallExprDeclare(multipleVariableDeclaration);

  return nullptr;
}

void MultipleVariableDeclarationStatementGenerationStrategy::
    handleMultipleVarDecReturnCallExprDeclare(
        BoundMultipleVariableDeclaration *multipleVariableDeclaration) {

  auto firstVariableDeclaration =
      multipleVariableDeclaration->getVariableDeclarationListRef()[0].get();

  if (!firstVariableDeclaration->getInitializerPtr()) {
    return;
  }

  BoundCallExpression *callExpression = BoundUtils::getCallExpression(
      firstVariableDeclaration->getInitializerPtr().get());

  if (callExpression) {
    std::vector<llvm::Type *> _structElementTypes(
        multipleVariableDeclaration->getVariableDeclarationListRef().size(),
        llvm::Type::getInt8PtrTy(*TheContext));
    llvm::StructType *_structType =
        llvm::StructType::create(*TheContext, _structElementTypes);

    llvm::Value *_stPtr = _codeGenerationContext->createMemoryGetPtr(
        _structType, "rtStructPtr", firstVariableDeclaration->getMemoryKind());
    uint64_t offset = 0;
    for (const auto &var :
         multipleVariableDeclaration->getVariableDeclarationListRef()) {
      auto [ptr, ptrType] = var->getLLVMVariable();
      Builder->CreateStore(
          ptr, Builder->CreateStructGEP(_structType, _stPtr, offset++));
      callExpression->addReturnTypeToList(ptrType);
    }

    callExpression->setArgumentAlloca(0, {_stPtr, _structType});
  }
}
