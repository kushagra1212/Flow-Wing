#include "MultipleVariableDeclarationStatementGenerationStrategy.h"

MultipleVariableDeclarationStatementGenerationStrategy::
    MultipleVariableDeclarationStatementGenerationStrategy(
        CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *
MultipleVariableDeclarationStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {
  std::unique_ptr<VariableDeclarationStatementGenerationStrategy>
      varDecGenStrat =
          std::make_unique<VariableDeclarationStatementGenerationStrategy>(
              _codeGenerationContext);

  BoundMultipleVariableDeclaration *multipleVariableDeclaration =
      static_cast<BoundMultipleVariableDeclaration *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      multipleVariableDeclaration->getLocation());

  for (const auto &variable :
       multipleVariableDeclaration->getVariableDeclarationListRef()) {
    varDecGenStrat->generateStatement(variable.get());
  }
  return nullptr;
}

llvm::Value *
MultipleVariableDeclarationStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  std::unique_ptr<VariableDeclarationStatementGenerationStrategy>
      varDecGenStrat =
          std::make_unique<VariableDeclarationStatementGenerationStrategy>(
              _codeGenerationContext);

  BoundMultipleVariableDeclaration *multipleVariableDeclaration =
      static_cast<BoundMultipleVariableDeclaration *>(statement);
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      multipleVariableDeclaration->getLocation());
  for (const auto &variable :
       multipleVariableDeclaration->getVariableDeclarationListRef()) {
    varDecGenStrat->generateGlobalStatement(variable.get());
  }
  return nullptr;
}

llvm::Value *
MultipleVariableDeclarationStatementGenerationStrategy::declareGlobal(
    BoundStatement *statement) { //! Declare when RHS is Call Expression
  std::unique_ptr<VariableDeclarationStatementGenerationStrategy>
      varDecGenStrat =
          std::make_unique<VariableDeclarationStatementGenerationStrategy>(
              _codeGenerationContext);

  BoundMultipleVariableDeclaration *multipleVariableDeclaration =
      static_cast<BoundMultipleVariableDeclaration *>(statement);
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      multipleVariableDeclaration->getLocation());
  for (const auto &variable :
       multipleVariableDeclaration->getVariableDeclarationListRef()) {
    varDecGenStrat->declareGlobal(variable.get());
  }

  return nullptr;
}

llvm::Value *
MultipleVariableDeclarationStatementGenerationStrategy::declareLocal(
    BoundStatement *statement) {
  //! Declare when RHS is Call Expression
  std::unique_ptr<VariableDeclarationStatementGenerationStrategy>
      varDecGenStrat =
          std::make_unique<VariableDeclarationStatementGenerationStrategy>(
              _codeGenerationContext);

  BoundMultipleVariableDeclaration *multipleVariableDeclaration =
      static_cast<BoundMultipleVariableDeclaration *>(statement);
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      multipleVariableDeclaration->getLocation());
  for (const auto &variable :
       multipleVariableDeclaration->getVariableDeclarationListRef()) {
    varDecGenStrat->declareLocal(variable.get());
  }
  return nullptr;
}