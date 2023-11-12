#include "BringStatementGenerationStrategy.h"

#include "../../../../evaluator/llvm/IRGenerator.h"
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

  std::unique_ptr<FunctionDeclarationGenerationStrategy>
      _functionDeclarationGenerationStrategy =
          std::make_unique<FunctionDeclarationGenerationStrategy>(
              _codeGenerationContext);

  for (const auto &_function : bringStatement->getGlobalScopePtr()->functions) {
    _functionDeclarationGenerationStrategy->generateGlobalStatement(
        _function.second);
  }

  for (const auto &variable : bringStatement->getGlobalScopePtr()->variables) {

    if (variable.second.type == Utils::type::UNKNOWN) {

      _codeGenerationContext->getLogger()->LogError(
          "Multifile UNKOWN type not allowed, Please "
          "specify the type of variable " +
          variable.first);
      continue;
    }

    llvm::Type *type =
        _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
            variable.second.type);

    llvm::GlobalVariable *variableLLVM = new llvm::GlobalVariable(
        *TheModule, type, false, llvm::GlobalValue::ExternalLinkage, nullptr,
        variable.first);
  }

  const std::string onlyFileName = Utils::getNameExtension(
      bringStatement->getDiagnosticHandlerPtr()->getAbsoluteFilePath());
  std::string removedExtenstionFromAbsolutePath =
      Utils::removeExtensionFromString(
          bringStatement->getDiagnosticHandlerPtr()->getAbsoluteFilePath());

  std::replace(removedExtenstionFromAbsolutePath.begin(),
               removedExtenstionFromAbsolutePath.end(), '/', '-');
  std::unique_ptr<IRGenerator> _evaluator = std::make_unique<IRGenerator>(
      ENVIRONMENT::SOURCE_FILE, bringStatement->getDiagnosticHandlerPtr(),
      bringStatement->getGlobalScopePtr()->functions,
      removedExtenstionFromAbsolutePath);

  _evaluator->generateEvaluateGlobalStatement(
      bringStatement->getGlobalScopePtr()->globalStatement.get(), onlyFileName);
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