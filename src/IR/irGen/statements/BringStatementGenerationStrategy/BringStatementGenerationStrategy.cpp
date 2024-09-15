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

  // Variable Declaration
  std::unique_ptr<VariableDeclarationStatementGenerationStrategy>
      varDecGenStrat =
          std::make_unique<VariableDeclarationStatementGenerationStrategy>(
              _codeGenerationContext);
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      bringStatement->getLocation());
  for (const auto &variable : bringStatement->getGlobalScopePtr()->variables) {
    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        variable.second->getLocation());
    if (bringStatement->isChoosyImport()) {

      if (bringStatement->isImported(variable.first)) {
        _codeGenerationContext->getLogger()->setCurrentSourceLocation(
            bringStatement->getExpressionRef(variable.first)->getLocation());
      }

      if (bringStatement->isImported(variable.first) &&
          !variable.second->isExposed()) {
        _codeGenerationContext->getLogger()->LogError(
            "Variable " + variable.first + " is not exposed in the file " +
            onlyFileName);
        return nullptr;
      }

      if (bringStatement->isImported(variable.first)) {
        if (variable.second->getTypeExpression()->getSyntaxType() ==
            SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE) {
          _codeGenerationContext->getLogger()->LogError(
              "Multi file UNKOWN type not allowed, Please "
              "specify the type of variable " +
              variable.first);
          return nullptr;
        }
        varDecGenStrat->generateGlobalStatement(variable.second);
      }

    } else {
      if (variable.second->getTypeExpression()->getSyntaxType() ==
          SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE) {
        continue;
      }
      varDecGenStrat->generateGlobalStatement(variable.second);
    }
  }

  Builder->CreateCall(
      TheModule->getFunction(bringStatement->getRootCallerName()), {});

  return nullptr;
}

llvm::Value *
BringStatementGenerationStrategy::declare(BoundStatement *statement) {
  BoundBringStatement *bringStatement =
      static_cast<BoundBringStatement *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      bringStatement->getLocation());

  std::map<std::string, int8_t> importMap;

  const std::string onlyFileName = Utils::getNameExtension(
      bringStatement->getDiagnosticHandlerPtr()->getAbsoluteFilePath());

  std::string absoluteFilePathWithoutExtension =
      Utils::removeExtensionFromString(
          bringStatement->getDiagnosticHandlerPtr()->getAbsoluteFilePath());

  std::replace(absoluteFilePathWithoutExtension.begin(),
               absoluteFilePathWithoutExtension.end(), '/', '-');

  std::unique_ptr<IRGenerator> _evaluator = std::make_unique<IRGenerator>(
      ENVIRONMENT::SOURCE_FILE, bringStatement->getDiagnosticHandlerPtr(),
      bringStatement->getGlobalScopePtr()->functions,
      bringStatement->getDiagnosticHandlerPtr()->getOutputFilePath(),
      absoluteFilePathWithoutExtension);

  CODEGEN_DEBUG_LOG("absoluteFilePathWithoutExtension",
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

  llvm::FunctionType *FT =
      llvm::FunctionType::get(llvm::Type::getInt32Ty(*TheContext),
                              llvm::ArrayRef<llvm::Type *>(), false);

  llvm::Function *F =
      llvm::Function::Create(FT, llvm::Function::ExternalLinkage,
                             absoluteFilePathWithoutExtension, *TheModule);

  bringStatement->setRootCallerName(absoluteFilePathWithoutExtension);

  // Custom Object Type Declaration
  std::unique_ptr<CustomTypeStatementGenerationStrategy> custTypeGenStrat =
      std::make_unique<CustomTypeStatementGenerationStrategy>(
          _codeGenerationContext);
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      bringStatement->getLocation());
  for (const auto &customType :
       bringStatement->getGlobalScopePtr()->customTypes) {
    importMap[customType.first] = 1;

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        customType.second->getLocation());

    if (bringStatement->isChoosyImport()) {
      if (bringStatement->isImported(customType.first)) {
        _codeGenerationContext->getLogger()->setCurrentSourceLocation(
            bringStatement->getExpressionRef(customType.first)->getLocation());
      }

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

  //
  std::unique_ptr<ClassStatementGenerationStrategy> classGenStrat =
      std::make_unique<ClassStatementGenerationStrategy>(
          _codeGenerationContext);
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      bringStatement->getLocation());
  for (const auto &_class : bringStatement->getGlobalScopePtr()->classes) {
    importMap[_class.first] = 1;
    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        _class.second->getLocation());

    if (bringStatement->isChoosyImport()) {
      if (bringStatement->isImported(_class.first) &&
          !_class.second->isExposed()) {

        _codeGenerationContext->getLogger()->LogError(
            "Object Type " + _class.first + " is not exposed in the file " +
            onlyFileName);
        return nullptr;
      }

      classGenStrat->generateGlobalStatement(_class.second);

    } else {
      classGenStrat->generateGlobalStatement(_class.second);
    }
  }

  // Variable Declaration
  std::unique_ptr<VariableDeclarationStatementGenerationStrategy>
      varDecGenStrat =
          std::make_unique<VariableDeclarationStatementGenerationStrategy>(
              _codeGenerationContext);
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      bringStatement->getLocation());
  for (const auto &variable : bringStatement->getGlobalScopePtr()->variables) {
    importMap[variable.first] = 1;
    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        variable.second->getLocation());
    if (bringStatement->isChoosyImport()) {
      if (bringStatement->isImported(variable.first)) {
        _codeGenerationContext->getLogger()->setCurrentSourceLocation(
            bringStatement->getExpressionRef(variable.first)->getLocation());
      }

      if (bringStatement->isImported(variable.first) &&
          !variable.second->isExposed()) {
        _codeGenerationContext->getLogger()->LogError(
            "Variable " + variable.first + " is not exposed in the file " +
            onlyFileName);
        return nullptr;
      }

      if (bringStatement->isImported(variable.first)) {
        if (variable.second->getTypeExpression()->getSyntaxType() ==
            SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE) {
          _codeGenerationContext->getLogger()->LogError(
              "Multi file UNKOWN type not allowed, Please "
              "specify the type of variable " +
              variable.first);
          return nullptr;
        }

        varDecGenStrat->declareGlobal(variable.second);
      }

    } else {
      if (variable.second->getTypeExpression()->getSyntaxType() ==
          SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE) {
        continue;
      }
      varDecGenStrat->declareGlobal(variable.second);
    }
  }

  // Function Declaration
  std::unique_ptr<FunctionDeclarationGenerationStrategy>
      _functionDeclarationGenerationStrategy =
          std::make_unique<FunctionDeclarationGenerationStrategy>(
              _codeGenerationContext);

  for (const auto &_function : bringStatement->getGlobalScopePtr()->functions) {

    importMap[_function.first] = 1;
    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        _function.second->getLocation());
    if (bringStatement->isChoosyImport()) {
      if (bringStatement->isImported(_function.first)) {
        _codeGenerationContext->getLogger()->setCurrentSourceLocation(
            bringStatement->getExpressionRef(_function.first)->getLocation());
      }

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