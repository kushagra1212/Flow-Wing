#include "BringStatementGenerationStrategy.h"

#include "../../../IRGenerator.h"
#include "../FunctionDeclarationGenerationStrategy/FunctionDeclarationGenerationStrategy.h"

BringStatementGenerationStrategy::BringStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *BringStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  BoundBringStatement *bringStatement =
      static_cast<BoundBringStatement *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      bringStatement->getLocation());

  const std::string onlyFileName = Utils::getNameExtension(
      bringStatement->getDiagnosticHandlerPtr()->getAbsoluteFilePath());

  std::string absoluteFilePathWithoutExtension =
      Utils::removeExtensionFromString(
          bringStatement->getDiagnosticHandlerPtr()->getAbsoluteFilePath());

  std::replace(absoluteFilePathWithoutExtension.begin(),
               absoluteFilePathWithoutExtension.end(), '/', 'i');

  llvm::FunctionType *FT =
      llvm::FunctionType::get(llvm::Type::getInt32Ty(*TheContext),
                              llvm::ArrayRef<llvm::Type *>(), false);

  llvm::Function *F =
      llvm::Function::Create(FT, llvm::Function::ExternalLinkage,
                             absoluteFilePathWithoutExtension, *TheModule);

  // Custom Object Type Declaration
  std::unique_ptr<CustomTypeStatementGenerationStrategy> custTypeGenStrat =
      std::make_unique<CustomTypeStatementGenerationStrategy>(
          _codeGenerationContext);

  for (const auto &customType :
       bringStatement->getGlobalScopePtr()->customTypes) {

    if (bringStatement->isChoosyImport()) {
      if (bringStatement->isImported(customType.first) &&
          !customType.second->isExposed()) {
        _codeGenerationContext->getLogger()->LogError(
            "Object Type " + customType.first + " is not exposed in the file " +
            onlyFileName);
        return nullptr;
      }

      custTypeGenStrat->generateGlobalStatement(customType.second);

    } else {
      custTypeGenStrat->generateGlobalStatement(customType.second);
    }
  }

  // Variable Declaration
  std::unique_ptr<VariableDeclarationStatementGenerationStrategy>
      varDecGenStrat =
          std::make_unique<VariableDeclarationStatementGenerationStrategy>(
              _codeGenerationContext);

  for (const auto &variable : bringStatement->getGlobalScopePtr()->variables) {
    if (variable.second->getTypeExpression()->getSyntaxType() ==
        SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE) {
      _codeGenerationContext->getLogger()->LogError(
          "Multifile UNKOWN type not allowed, Please "
          "specify the type of variable " +
          variable.first);
      return nullptr;
    }

    if (bringStatement->isChoosyImport()) {
      if (bringStatement->isImported(variable.first) &&
          !variable.second->isExposed()) {
        _codeGenerationContext->getLogger()->LogError(
            "Varibale " + variable.first + " is not exposed in the file " +
            onlyFileName);
        return nullptr;
      }

      if (bringStatement->isImported(variable.first))
        varDecGenStrat->generateGlobalStatement(variable.second);

    } else {

      varDecGenStrat->generateGlobalStatement(variable.second);
    }
  }

  // Function Declaration
  std::unique_ptr<FunctionDeclarationGenerationStrategy>
      _functionDeclarationGenerationStrategy =
          std::make_unique<FunctionDeclarationGenerationStrategy>(
              _codeGenerationContext);

  for (const auto &_function : bringStatement->getGlobalScopePtr()->functions) {

    if (bringStatement->isChoosyImport()) {
      if (bringStatement->isImported(_function.first) &&
          !_function.second->isExposed()) {
        _codeGenerationContext->getLogger()->LogError(
            "Function " + _function.first + " is not exposed in the file " +
            onlyFileName);
        return nullptr;
      }

      if (bringStatement->isImported(_function.first))
        _functionDeclarationGenerationStrategy->generateGlobalStatement(
            _function.second);

    } else {
      _functionDeclarationGenerationStrategy->generateGlobalStatement(
          _function.second);
    }
  }

  Builder->CreateCall(F, {});

  std::unique_ptr<IRGenerator> _evaluator = std::make_unique<IRGenerator>(
      ENVIRONMENT::SOURCE_FILE, bringStatement->getDiagnosticHandlerPtr(),
      bringStatement->getGlobalScopePtr()->functions,
      absoluteFilePathWithoutExtension);

  _evaluator->generateEvaluateGlobalStatement(
      bringStatement->getGlobalScopePtr()->globalStatement.get(),
      absoluteFilePathWithoutExtension);
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      bringStatement->getLocation());
  if (_evaluator->hasErrors()) {
    _codeGenerationContext->getLogger()->LogError(
        "Error in importing file " +
        bringStatement->getDiagnosticHandlerPtr()->getAbsoluteFilePath());
  }
  return nullptr;
}

// TODO: Refactor This Later
llvm::Value *
BringStatementGenerationStrategy::generateStatement(BoundStatement *statement) {
  BoundBringStatement *bringStatement =
      static_cast<BoundBringStatement *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      bringStatement->getLocation());

  // TODO: Allow bring statement in local scope as well
  _codeGenerationContext->getLogger()->LogError(
      "Bring statement not allowed here as of now");

  return nullptr;
}