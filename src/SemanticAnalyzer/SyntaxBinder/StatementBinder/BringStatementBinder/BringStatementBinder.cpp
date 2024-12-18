
#include "BringStatementBinder.h"
#include <memory>

std::unique_ptr<BoundStatement>
BringStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                    StatementSyntax *statement) {

  BringStatementSyntax *bringStatement =
      static_cast<BringStatementSyntax *>(statement);

  if (!Utils::Node::isPathExists(bringStatement->getAbsoluteFilePath())) {
    ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
        "File <" + bringStatement->getRelativeFilePathPtr() + "> not found",
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic,
        Utils::getSourceLocation(bringStatement->getBringKeywordPtr().get())));
    return std::make_unique<BoundBringStatement>(
        bringStatement->getSourceLocation(),
        bringStatement->getDiagnosticHandlerPtr().get());
  }
  //! Need this Check (Skip for now)
  // if (Utils::Node::isCycleDetected(bringStatement->getAbsoluteFilePath())) {
  //       ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
  //       "Found Circular Dependency <" +
  //           bringStatement->getRelativeFilePathPtr() + "> ",
  //       DiagnosticUtils::DiagnosticLevel::Error,
  //       DiagnosticUtils::DiagnosticType::Semantic,
  //       Utils::getSourceLocation(bringStatement->getBringKeywordPtr().get())));

  //   return std::make_unique<BoundBringStatement>(
  //       bringStatement->getSourceLocation(),
  //       bringStatement->getDiagnosticHandlerPtr().get());
  // }
  bool isAlreadyImported = false;
  //! Need this Check (Skip for now)
  // if (Utils::Node::isPathVisited(bringStatement->getAbsoluteFilePathPtr())) {

  //   auto boundBringStatement = std::make_unique<BoundBringStatement>(
  //       bringStatement->getSourceLocation(),
  //       bringStatement->getDiagnosticHandlerPtr().get());

  //   if (!bringStatement->getIsModuleImport()) {
  //     //     ctx->getDiagnosticHandler()->addDiagnostic(
  //     //     Diagnostic("File <" + bringStatement->getRelativeFilePathPtr() +
  //     //                    "> already included ",
  //     //                DiagnosticUtils::DiagnosticLevel::Error,
  //     //                DiagnosticUtils::DiagnosticType::Semantic,
  //     //                Utils::getSourceLocation(
  //     //                    bringStatement->getBringKeywordPtr().get())));
  //   }
  //   isAlreadyImported = true;
  // }
  // Utils::Node::addPath(bringStatement->getAbsoluteFilePathPtr());

  auto boundBringStatement = std::make_unique<BoundBringStatement>(
      bringStatement->getSourceLocation(),
      bringStatement->getDiagnosticHandlerPtr().get());

  boundBringStatement->setIsAlreadyImported(isAlreadyImported);
  boundBringStatement->setIsModuleImport(bringStatement->getIsModuleImport());

  std::unordered_map<std::string, int> memberMap =
      getMemberMap(bringStatement->getCompilationUnitPtr()->getMembers(),
                   bringStatement->getCompilationUnitPtr().get());

  if (bringStatement->getIsChoosyImportPtr()) {

    for (auto &expression : bringStatement->getExpressionsPtr()) {
      if (expression->getKind() !=
          SyntaxKindUtils::SyntaxKind::LiteralExpression) {
        ctx->getDiagnosticHandler()->addDiagnostic(
            Diagnostic("Unexpected Token <" +
                           SyntaxKindUtils::to_string(expression->getKind()) +
                           ">, Expected <" +
                           SyntaxKindUtils::to_string(
                               SyntaxKindUtils::SyntaxKind::IdentifierToken) +
                           ">",
                       DiagnosticUtils::DiagnosticLevel::Error,
                       DiagnosticUtils::DiagnosticType::Semantic,
                       (expression->getSourceLocation())));
        continue;
      }

      const bool notFound =
          memberMap.find(expression->getTokenPtr()->getText().substr(
              0, expression->getTokenPtr()->getText().find_last_of("."))) ==
          memberMap.end();

      if (notFound) {
        ctx->getDiagnosticHandler()->addDiagnostic(
            Diagnostic("Identifier <" + expression->getTokenPtr()->getText() +
                           "> not found in <" +
                           bringStatement->getRelativeFilePathPtr() + ">",
                       DiagnosticUtils::DiagnosticLevel::Error,
                       DiagnosticUtils::DiagnosticType::Semantic,
                       (expression->getSourceLocation())));
        continue;
      }

      std::unique_ptr<BoundLiteralExpression<std::any>> bLitExpr(
          static_cast<BoundLiteralExpression<std::any> *>(
              ExpressionBinderFactory::create(expression->getKind())
                  ->bindExpression(ctx, expression.get())
                  .release()));

      boundBringStatement->setExpression(expression->getTokenPtr()->getText(),
                                         std::move(bLitExpr));
    }
  }
  // Utils::Node::removePath(bringStatement->getAbsoluteFilePathPtr());

  ctx->getDiagnosticHandler()->addParentDiagnostics(
      bringStatement->getDiagnosticHandlerPtr().get());

  std::unique_ptr<BoundGlobalScope> globalScope =
      std::move(SemanticAnalyzer::analyzeGlobalScope(
          nullptr, bringStatement->getCompilationUnitPtr().get(),
          bringStatement->getDiagnosticHandlerPtr().get()));

  const auto LOG_ERROR = [&](const std::string &msg) {
    ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
        msg, DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic,
        Utils::getSourceLocation(bringStatement->getBringKeywordPtr().get())));
  };

  if (bringStatement->getModuleName().size() &&
      ctx->doesModuleAlreadyExist(bringStatement->getModuleName())) {
    LOG_ERROR("Module " + bringStatement->getModuleName() +
              " Already Declared");
  }

  if (bringStatement->getModuleName().size()) {
    ctx->updateModuleDependencyMap(bringStatement->getModuleName(), true);
  }

  for (auto &stat : globalScope->globalStatement->getStatements()) {

    switch (stat->getKind()) {
    case BinderKindUtils::BoundNodeKind::FunctionDeclaration: {
      auto func = static_cast<BoundFunctionDeclaration *>(stat.get());
      if (func->isOnlyDeclared() &&
          !ctx->getRootRef()->tryDeclareFunctionGlobal(func)) {
        LOG_ERROR("Function " + func->getFunctionNameRef() +
                  " is Already Declared");
      }
      break;
    }
    case BinderKindUtils::BoundNodeKind::VariableDeclaration: {
      auto var = static_cast<BoundVariableDeclaration *>(stat.get());

      if (!ctx->getRootRef()->tryDeclareVariableGlobal(var->getVariableName(),
                                                       var)) {

        LOG_ERROR("Variable " + var->getVariableName() +
                  " is Already Declared");
      }
      break;
    }
    case BinderKindUtils::BoundNodeKind::CustomTypeStatement: {
      auto cusType = static_cast<BoundCustomTypeStatement *>(stat.get());

      if (!ctx->getRootRef()->tryDeclareCustomTypeGlobal(cusType)) {

        LOG_ERROR("Type " + cusType->getTypeNameAsString() +
                  " is Already Declared");
      }
      break;
    }
    case BinderKindUtils::BoundNodeKind::ClassStatement: {
      auto classType = static_cast<BoundClassStatement *>(stat.get());

      PARSER_DEBUG_LOG("CLASS,", classType->getClassName());

      if (!ctx->getRootRef()->tryDeclareClassGlobal(classType)) {

        LOG_ERROR("Type " + classType->getClassName() + " is Already Declared");
      }
      break;
    }
    case BinderKindUtils::BoundNodeKind::BoundModuleStatement: {
      auto moduleStatement = static_cast<BoundModuleStatement *>(stat.get());
      if (!ctx->getRootRef()->tryDeclareModuleGlobal(moduleStatement)) {

        LOG_ERROR("Module " + moduleStatement->getModuleName() +
                  " is Already Declared");
      }

      for (auto &stat : moduleStatement->getStatementsRef()) {
        switch (stat->getKind()) {
        case BinderKindUtils::BoundNodeKind::ClassStatement: {
          auto _mClass = static_cast<BoundClassStatement *>(stat);
          if (!ctx->getRootRef()->tryDeclareClass(_mClass)) {

            LOG_ERROR("Class " + _mClass->getClassName() +
                      " is Already Declared: [" +
                      moduleStatement->getModuleName() + "]");
          }
          break;
        }
        case BinderKindUtils::BoundNodeKind::VariableDeclaration: {
          auto _mVarDec = static_cast<BoundVariableDeclaration *>(stat);
          if (!ctx->getRootRef()->tryDeclareVariableGlobal(
                  _mVarDec->getVariableName(), _mVarDec)) {

            LOG_ERROR("Variable " + _mVarDec->getVariableName() +
                      " is Already Declared : [" +
                      moduleStatement->getModuleName() + "]");
          }
          break;
        }

        case BinderKindUtils::BoundNodeKind::FunctionDeclaration: {
          auto _mFuncDec = static_cast<BoundFunctionDeclaration *>(stat);
          if (_mFuncDec->isOnlyDeclared() &&
              !ctx->getRootRef()->tryDeclareFunctionGlobal(_mFuncDec)) {

            LOG_ERROR("Function " + _mFuncDec->getFunctionNameRef() +
                      " is Already Declared : [" +
                      moduleStatement->getModuleName() + "]");
          }
          break;
        }

        case BinderKindUtils::BoundNodeKind::CustomTypeStatement: {
          auto _mCusType = static_cast<BoundCustomTypeStatement *>(stat);
          if (!ctx->getRootRef()->tryDeclareCustomTypeGlobal(_mCusType)) {

            LOG_ERROR("Type " + _mCusType->getTypeNameAsString() +
                      " is Already Declared : [" +
                      moduleStatement->getModuleName() + "]");
          }
          break;
        }
        default: {
          break;
        }
        }
      }

      break;
    }
    default: {
      break;
    }
    }
  }

  boundBringStatement->setGlobalScope(std::move(globalScope));

  return std::move(boundBringStatement);
}

std::unordered_map<std::string, int> BringStatementBinder::getMemberMap(
    const std::vector<std::unique_ptr<MemberSyntax>> &members,
    CompilationUnitSyntax *nestedCompilationUnit) {
  std::unordered_map<std::string, int> memberMap;

  for (std::unique_ptr<MemberSyntax> &member :
       nestedCompilationUnit->getMembers()) {
    if (member->getKind() ==
        SyntaxKindUtils::SyntaxKind::FunctionDeclarationSyntax) {
      FunctionDeclarationSyntax *functionDeclaration =
          dynamic_cast<FunctionDeclarationSyntax *>(member.get());

      memberMap[functionDeclaration->getIdentifierTokenPtr()->getText()] = 1;
    } else if (member->getKind() ==
               SyntaxKindUtils::SyntaxKind::GlobalStatement) {
      GlobalStatementSyntax *globalStatement =
          dynamic_cast<GlobalStatementSyntax *>(member.get());
      if (globalStatement->getStatementPtr()->getKind() ==
          SyntaxKindUtils::SyntaxKind::VariableDeclaration) {
        VariableDeclarationSyntax *variableDeclaration =
            dynamic_cast<VariableDeclarationSyntax *>(
                globalStatement->getStatementPtr().get());
        memberMap[variableDeclaration->getIdentifierRef()->getText()] = 1;
      } else if (globalStatement->getStatementPtr()->getKind() ==
                 SyntaxKindUtils::SyntaxKind::ClassStatement) {
        ClassStatementSyntax *classStatement =
            dynamic_cast<ClassStatementSyntax *>(
                globalStatement->getStatementPtr().get());
        memberMap[classStatement->getClassNameIdentifierRef()->getText()] = 1;

      } else if (globalStatement->getStatementPtr()->getKind() ==
                 SyntaxKindUtils::SyntaxKind::CustomTypeStatement) {
        CustomTypeStatementSyntax *customTypeStatement =
            dynamic_cast<CustomTypeStatementSyntax *>(
                globalStatement->getStatementPtr().get());
        memberMap[customTypeStatement->getTypeNameRef()
                      ->getTokenPtr()
                      ->getText()
                      .substr(0, customTypeStatement->getTypeNameRef()
                                     ->getTokenPtr()
                                     ->getText()
                                     .find_last_of("."))] = 1;

      } else if (globalStatement->getStatementPtr()->getKind() ==
                 SyntaxKindUtils::SyntaxKind::ModuleStatement) {
        ModuleStatementSyntax *moduleStatement =
            dynamic_cast<ModuleStatementSyntax *>(
                globalStatement->getStatementPtr().get());
        memberMap
            [moduleStatement->getModuleNameRef()->getTokenPtr()->getText()] = 1;

        PARSER_DEBUG_LOG(
            "Module ",
            moduleStatement->getModuleNameRef()->getTokenPtr()->getText());

        for (int i = 0; i < moduleStatement->getStatementsRef().size(); i++) {
          if (moduleStatement->getStatementsRef()[i]->getKind() ==
              SyntaxKindUtils::SyntaxKind::FunctionDeclarationSyntax) {

            FunctionDeclarationSyntax *functionDeclaration =
                dynamic_cast<FunctionDeclarationSyntax *>(
                    moduleStatement->getStatementsRef()[i].get());

            PARSER_DEBUG_LOG(
                "Function Belongs to Module ",
                functionDeclaration->getIdentifierTokenPtr()->getText());

            memberMap[functionDeclaration->getIdentifierTokenPtr()->getText()] =
                1;
          } else if (moduleStatement->getStatementsRef()[i]->getKind() ==
                     SyntaxKindUtils::SyntaxKind::VariableDeclaration) {
            VariableDeclarationSyntax *variableDeclaration =
                dynamic_cast<VariableDeclarationSyntax *>(
                    moduleStatement->getStatementsRef()[i].get());

            PARSER_DEBUG_LOG(
                "Variable Belongs to Module ",
                variableDeclaration->getIdentifierRef()->getText());

            memberMap[variableDeclaration->getIdentifierRef()->getText()] = 1;

          } else if (moduleStatement->getStatementsRef()[i]->getKind() ==
                     SyntaxKindUtils::SyntaxKind::ClassStatement) {
            ClassStatementSyntax *classStatement =
                dynamic_cast<ClassStatementSyntax *>(
                    moduleStatement->getStatementsRef()[i].get());

            PARSER_DEBUG_LOG(
                "Class Belongs to Module ",
                classStatement->getClassNameIdentifierRef()->getText());

            memberMap[classStatement->getClassNameIdentifierRef()->getText()] =
                1;
          } else if (moduleStatement->getStatementsRef()[i]->getKind() ==
                     SyntaxKindUtils::SyntaxKind::CustomTypeStatement) {
            CustomTypeStatementSyntax *customTypeStatement =
                dynamic_cast<CustomTypeStatementSyntax *>(
                    moduleStatement->getStatementsRef()[i].get());

            PARSER_DEBUG_LOG("Type Belongs to Module ",
                             customTypeStatement->getTypeNameRef()
                                 ->getTokenPtr()
                                 ->getText());

            memberMap[customTypeStatement->getTypeNameRef()
                          ->getTokenPtr()
                          ->getText()] = 1;
          }
        }
      }
    }
  }
  return memberMap;
}