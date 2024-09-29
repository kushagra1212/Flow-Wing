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

  if (bringStatement->isAlreadyImported()) {
    return nullptr;
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

  if (bringStatement->isAlreadyImported()) {
    return nullptr;
  }

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

  auto processVarDec = [&](BoundVariableDeclaration *varDec) {
    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        varDec->getLocation());

    std::unique_ptr<VariableDeclarationStatementGenerationStrategy>
        varDecGenStrat =
            std::make_unique<VariableDeclarationStatementGenerationStrategy>(
                _codeGenerationContext);

    if (bringStatement->isChoosyImport()) {
      if (bringStatement->isImported(varDec->getVariableName())) {
        _codeGenerationContext->getLogger()->setCurrentSourceLocation(
            bringStatement->getExpressionRef(varDec->getVariableName())
                ->getLocation());
      }

      if (bringStatement->isImported(varDec->getVariableName()) &&
          !varDec->isExposed()) {
        _codeGenerationContext->getLogger()->LogError(
            "Variable " + varDec->getVariableName() +
            " is not exposed in the file " + onlyFileName);
        return EXIT_FAILURE;
      }

      if (bringStatement->isImported(varDec->getVariableName())) {
        if (varDec->getTypeExpression()->getSyntaxType() ==
            SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE) {
          _codeGenerationContext->getLogger()->LogError(
              "Multi file UNKOWN type not allowed, Please "
              "specify the type of variable " +
              varDec->getVariableName());
          return EXIT_FAILURE;
        }

        varDecGenStrat->declareGlobal(varDec);
      }

    } else {
      if (varDec->getTypeExpression()->getSyntaxType() !=
          SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE) {
        varDecGenStrat->declareGlobal(varDec);
      }
    }

    return EXIT_SUCCESS;
  };

  auto processFuncDecl = [&](BoundFunctionDeclaration *func) {
    std::unique_ptr<FunctionDeclarationGenerationStrategy>
        _functionDeclarationGenerationStrategy =
            std::make_unique<FunctionDeclarationGenerationStrategy>(
                _codeGenerationContext);

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        func->getLocation());
    if (bringStatement->isChoosyImport()) {
      if (bringStatement->isImported(func->getFunctionNameRef())) {
        _codeGenerationContext->getLogger()->setCurrentSourceLocation(
            bringStatement->getExpressionRef(func->getFunctionNameRef())
                ->getLocation());
      }

      if (bringStatement->isImported(func->getFunctionNameRef()) &&
          !func->isExposed()) {

        _codeGenerationContext->getLogger()->LogError(
            "Function " + func->getFunctionNameRef() +
            " is not exposed in the file " + onlyFileName);
        return EXIT_FAILURE;
      }

      if (func->isOnlyDeclared() &&
          bringStatement->isImported(func->getFunctionNameRef()))
        _functionDeclarationGenerationStrategy->generateGlobalStatement(func);

    } else {
      if (func->isOnlyDeclared())
        _functionDeclarationGenerationStrategy->generateGlobalStatement(func);
    }

    return EXIT_SUCCESS;
  };

  auto processCustomType = [&](BoundCustomTypeStatement *customType) {
    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        customType->getLocation());

    std::unique_ptr<CustomTypeStatementGenerationStrategy> custTypeGenStrat =
        std::make_unique<CustomTypeStatementGenerationStrategy>(
            _codeGenerationContext);

    if (bringStatement->isChoosyImport()) {
      if (bringStatement->isImported(customType->getTypeNameAsString())) {
        _codeGenerationContext->getLogger()->setCurrentSourceLocation(
            bringStatement->getExpressionRef(customType->getTypeNameAsString())
                ->getLocation());
      }

      if (bringStatement->isImported(customType->getTypeNameAsString()) &&
          !customType->isExposed()) {

        _codeGenerationContext->getLogger()->LogError(
            "Type " + customType->getTypeNameAsString() +
            " is not exposed in the file " + onlyFileName);
        return EXIT_FAILURE;
      }

      custTypeGenStrat->generateGlobalStatement(customType);

    } else {
      custTypeGenStrat->generateGlobalStatement(customType);
    }

    return EXIT_SUCCESS;
  };

  auto processClassDecl = [&](BoundClassStatement *classDecl) {
    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        classDecl->getLocation());

    std::unique_ptr<ClassStatementGenerationStrategy> classGenStrat =
        std::make_unique<ClassStatementGenerationStrategy>(
            _codeGenerationContext);

    if (bringStatement->isChoosyImport()) {
      if (bringStatement->isImported(classDecl->getClassName()) &&
          !classDecl->isExposed()) {

        _codeGenerationContext->getLogger()->LogError(
            "Class " + classDecl->getClassName() +
            " is not exposed in the file " + onlyFileName);

        return EXIT_FAILURE;
      }
      if (_codeGenerationContext->_classTypes.find(classDecl->getClassName()) ==
          _codeGenerationContext->_classTypes.end()) {

        classGenStrat->generateClassType(classDecl);
      }
    } else {
      DEBUG_LOG("Bring Statement Class ", classDecl->getClassName());
      if (_codeGenerationContext->_classTypes.find(classDecl->getClassName()) ==
          _codeGenerationContext->_classTypes.end()) {

        classGenStrat->generateClassType(classDecl);
      }
    }

    return EXIT_SUCCESS;
  };

  auto processModule = [&](BoundModuleStatement *module) {
    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        module->getLocation());

    std::unique_ptr<ModuleStatementGenerationStrategy> moduleGenStrat =
        std::make_unique<ModuleStatementGenerationStrategy>(
            _codeGenerationContext);

    if (bringStatement->isChoosyImport()) {
      if (bringStatement->isImported(module->getModuleName())) {
        _codeGenerationContext->getLogger()->setCurrentSourceLocation(
            bringStatement->getExpressionRef(module->getModuleName())
                ->getLocation());
      }

      if (bringStatement->isImported(module->getModuleName())) {

        _codeGenerationContext->getLogger()->LogError(
            "Module " + module->getModuleName() +
            " is import like this is not allowed " + onlyFileName);
        return EXIT_FAILURE;
      }

      if (bringStatement->isImported(module->getModuleName()))
        moduleGenStrat->declare(module);

    } else {
      moduleGenStrat->declare(module);
    }

    for (auto &_stat : module->getStatementsRef()) {
      switch (_stat->getKind()) {
      case BinderKindUtils::BoundNodeKind::VariableDeclaration: {
        if (processVarDec(static_cast<BoundVariableDeclaration *>(_stat)) !=
            EXIT_SUCCESS) {
          return EXIT_FAILURE;
        }
        break;
      }
      case BinderKindUtils::BoundNodeKind::CustomTypeStatement: {
        if (processCustomType(static_cast<BoundCustomTypeStatement *>(_stat)) !=
            EXIT_SUCCESS) {
          return EXIT_FAILURE;
        }
        break;
      }

      case BinderKindUtils::BoundNodeKind::FunctionDeclaration: {
        if (processFuncDecl(static_cast<BoundFunctionDeclaration *>(_stat)) !=
            EXIT_SUCCESS) {
          return EXIT_FAILURE;
        }
        break;
      }

      case BinderKindUtils::BoundNodeKind::ClassStatement: {
        if (processClassDecl(static_cast<BoundClassStatement *>(_stat)) !=
            EXIT_SUCCESS) {
          return EXIT_FAILURE;
        }
        break;
      }

      default: {

        //? Skipping for CallExpression and other expressions in Bring

        break;
      }
      }
    }

    return EXIT_SUCCESS;
  };

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      bringStatement->getLocation());
  for (const auto &stat :
       bringStatement->getGlobalScopePtr()->globalStatement->getStatements()) {

    switch (stat->getKind()) {
    case BinderKindUtils::BoundNodeKind::FunctionDeclaration: {

      if (processFuncDecl(static_cast<BoundFunctionDeclaration *>(
              stat.get())) != EXIT_SUCCESS) {
        return nullptr;
      }

      break;
    }
    case BinderKindUtils::BoundNodeKind::VariableDeclaration: {

      if (processVarDec(static_cast<BoundVariableDeclaration *>(stat.get())) !=
          EXIT_SUCCESS) {
        return nullptr;
      }
      break;
    }
    case BinderKindUtils::BoundNodeKind::CustomTypeStatement: {

      if (processCustomType(static_cast<BoundCustomTypeStatement *>(
              stat.get())) != EXIT_SUCCESS) {
        return nullptr;
      }

      break;
    }
    case BinderKindUtils::BoundNodeKind::ClassStatement: {

      if (processClassDecl(static_cast<BoundClassStatement *>(stat.get())) !=
          EXIT_SUCCESS) {
        return nullptr;
      }

      break;
    }
    case BinderKindUtils::BoundNodeKind::BoundModuleStatement: {

      if (processModule(static_cast<BoundModuleStatement *>(stat.get())) !=
          EXIT_SUCCESS) {
        return nullptr;
      }
    }

    default: {
      // DEBUG_LOG(BinderKindUtils::to_string(stat->getKind()));
      // _codeGenerationContext->getLogger()->LogError(
      //     "Invalid Statement in Bring Statement");
      // return nullptr;
      break;
    }
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