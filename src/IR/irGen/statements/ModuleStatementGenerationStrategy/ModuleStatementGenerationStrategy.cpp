#include "ModuleStatementGenerationStrategy.h"
#include <memory>

ModuleStatementGenerationStrategy::ModuleStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}
llvm::Value *ModuleStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {
  return nullptr;
}

llvm::Value *ModuleStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  BoundModuleStatement *boundModuleStatement =
      static_cast<BoundModuleStatement *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundModuleStatement->getLocation());

  for (const auto &varDec :
       boundModuleStatement->getVariableDeclarationStatementsRef()) {
  }

  for (auto &stat : boundModuleStatement->getStatementsRef()) {
    switch (stat->getKind()) {
    case BinderKindUtils::BoundNodeKind::VariableDeclaration: {
      std::unique_ptr<VariableDeclarationStatementGenerationStrategy>
          variableDeclarationStatementGenerationStrategy =
              std::make_unique<VariableDeclarationStatementGenerationStrategy>(
                  _codeGenerationContext);
      BoundVariableDeclaration *varDec =
          static_cast<BoundVariableDeclaration *>(stat);
      variableDeclarationStatementGenerationStrategy->generateGlobalStatement(
          varDec);

      break;
    }

    case BinderKindUtils::BoundNodeKind::CallExpression: {

      std::unique_ptr<CallExpressionGenerationStrategy>
          callExpressionGenerationStrategy =
              std::make_unique<CallExpressionGenerationStrategy>(
                  _codeGenerationContext);

      callExpressionGenerationStrategy->generateGlobalExpression(
          static_cast<BoundCallExpression *>(stat));
      break;
    }

    default: {
      break;
    }
    }
  }

  return nullptr;
}

llvm::Value *
ModuleStatementGenerationStrategy::declare(BoundStatement *statement) {

  BoundModuleStatement *boundModuleStatement =
      static_cast<BoundModuleStatement *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundModuleStatement->getLocation());

  std::unique_ptr<FunctionDeclarationGenerationStrategy>
      functionDeclarationGenerationStrategy =
          std::make_unique<FunctionDeclarationGenerationStrategy>(
              _codeGenerationContext);

  for (int64_t i = 0;
       i < boundModuleStatement->getFunctionStatementsRef().size(); i++) {
    BoundFunctionDeclaration *fd = static_cast<BoundFunctionDeclaration *>(
        boundModuleStatement->getFunctionStatementsRef()[i].get());
    if (fd->isOnlyDeclared())
      functionDeclarationGenerationStrategy->generate(fd);
  }

  return nullptr;
}