#include "ModuleStatementGenerationStrategy.h"

ModuleStatementGenerationStrategy::ModuleStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}
llvm::Value *ModuleStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {
  return nullptr;
}

llvm::Value *ModuleStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {

  return nullptr;
}

llvm::Value *
ModuleStatementGenerationStrategy::declare(BoundStatement *statement) {

  BoundModuleStatement *boundModuleStatement =
      static_cast<BoundModuleStatement *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundModuleStatement->getLocation());

  std::unique_ptr<CustomTypeStatementGenerationStrategy>
      customTypeStatementGenerationStrategy =
          std::make_unique<CustomTypeStatementGenerationStrategy>(
              _codeGenerationContext);

  std::unique_ptr<FunctionDeclarationGenerationStrategy>
      functionDeclarationGenerationStrategy =
          std::make_unique<FunctionDeclarationGenerationStrategy>(
              _codeGenerationContext);
  uint64_t count = 0;

  for (int64_t i = 0;
       i < boundModuleStatement->getFunctionStatementsRef().size(); i++) {
    BoundFunctionDeclaration *fd = static_cast<BoundFunctionDeclaration *>(
        boundModuleStatement->getFunctionStatementsRef()[i].get());

    if (!fd->isOnlyDeclared()) {
      llvm::Function *F = functionDeclarationGenerationStrategy->generate(fd);
      count++;
    }
  }

  return nullptr;
}