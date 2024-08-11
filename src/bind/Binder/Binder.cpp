
#include "Binder.h"

std::unique_ptr<BoundStatement> Binder::bindExpressionStatement(
    ExpressionStatementSyntax *expressionStatement) {
  ExpressionSyntax *exps = expressionStatement->getExpressionPtr().get();

  std::unique_ptr<BoundExpression> boundExpression =
      std::move(bindExpression(exps));

  return std::make_unique<BoundExpressionStatement>(exps->getSourceLocation(),
                                                    std::move(boundExpression));
}

std::unique_ptr<BoundStatement>
Binder::bindBlockStatement(BlockStatementSyntax *blockStatement) {
  this->root = std::make_unique<BoundScope>(std::move(this->root));

  std::unique_ptr<BoundBlockStatement> boundBlockStatement =
      std::make_unique<BoundBlockStatement>(blockStatement->getSourceLocation(),
                                            false);

  for (int i = 0; i < blockStatement->getStatements().size(); i++) {
    std::unique_ptr<BoundStatement> statement =
        std::move(bindStatement(blockStatement->getStatements()[i].get()));

    boundBlockStatement->addStatement(std::move(statement));
  }

  this->root = std::move(this->root->parent);

  return std::move(boundBlockStatement);
}

std::unique_ptr<BoundVariableDeclaration>
Binder::bindVariableDeclaration(VariableDeclarationSyntax *variableDeclaration,
                                std::string className) {
  std::string variable_str = std::any_cast<std::string>(
      variableDeclaration->getIdentifierRef()->getValue());
  bool isConst = false;

  if (variableDeclaration->getKeywordRef()) {
    isConst = variableDeclaration->getKeywordRef()->getKind() ==
              SyntaxKindUtils::SyntaxKind::ConstKeyword;
  }

  std::unique_ptr<BoundVariableDeclaration> variable =
      std::make_unique<BoundVariableDeclaration>(
          variableDeclaration->getSourceLocation(), variable_str, isConst,
          variableDeclaration->isExposed());

  if (variableDeclaration->getInoutKeywordRef()) {
    variable->setHasInOutKeyword(true);
  }

  if (variableDeclaration->getAsKeywordRef()) {
    variable->setHasAsKeyword(true);
  }

  variable->setIdentifier(std::make_unique<BoundLiteralExpression<std::any>>(
      variableDeclaration->getIdentifierRef()->getSourceLocation(),
      variableDeclaration->getIdentifierRef()->getValue(),
      variableDeclaration->getIdentifierRef()->getKind()));

  if (variableDeclaration->getTypeRef()) {
    std::unique_ptr<BoundTypeExpression> boundTypeExpression =
        std::move(bindTypeExpression(variableDeclaration->getTypeRef().get()));

    if (boundTypeExpression->getKind() ==
        BinderKindUtils::BoundObjectTypeExpression) {
      BoundObjectTypeExpression *objectTypeExpression =
          static_cast<BoundObjectTypeExpression *>(boundTypeExpression.get());

      Utils::DEBUG_LOG("TNAME " + objectTypeExpression->getTypeName());

      //! This Handles when the Type is Class Type in that Case Since we are
      //! only receiving class Name not the type along with Module name e.g A
      //! not local::A and we are inside the Module local
      //! then we need to add the module prefix to the class name
      //! ModuleName::ClassName {It is statisfied only When we Defining Class}
      //! For Normal Types We are already receiving the ModuleName::TypeName

      if (_currentModuleName != "" &&
          objectTypeExpression->getTypeName().find(
              FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX) == std::string::npos) {
        objectTypeExpression->getObjectTypeIdentifier()->setValue(
            _currentModuleName + FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX +
            std::any_cast<std::string>(
                objectTypeExpression->getObjectTypeIdentifier()->getValue()));
      }
      BoundClassStatement *boundClassStatement =
          this->root->tryGetClass(objectTypeExpression->getTypeName());
      if (boundClassStatement) {
        className = boundClassStatement->getClassName();
      }
      Utils::DEBUG_LOG("CN " + className);
    }

    variable->setTypeExpression(std::move(boundTypeExpression));
  }
  if (variableDeclaration->getHasNewKeyWord())
    variable->setMemoryKind(BinderKindUtils::MemoryKind::Heap);
  variable->setClassItBelongsTo(className);

  if (variableDeclaration->getInitializerRef()) {
    std::unique_ptr<BoundExpression> boundInitializerExpression = std::move(
        bindExpression(variableDeclaration->getInitializerRef().get()));
    variable->setInitializer(std::move(boundInitializerExpression));
  }

  if (!root->tryDeclareVariable(variable_str, variable.get())) {
    this->_diagnosticHandler->addDiagnostic(
        Diagnostic("Variable " + variable_str + " Already Exists",
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic,
                   Utils::getSourceLocation(
                       variableDeclaration->getIdentifierRef().get())));
  }

  return std::move(variable);
}

std::unique_ptr<BoundOrIfStatement>
Binder::bindOrIfStatement(OrIfStatementSyntax *orIfStatement) {
  std::unique_ptr<BoundExpression> boundCondition =
      std::move(bindExpression(orIfStatement->getConditionPtr().get()));

  std::unique_ptr<BoundStatement> boundThenStatement =
      std::move(bindStatement(orIfStatement->getStatementPtr().get()));

  return std::make_unique<BoundOrIfStatement>(
      orIfStatement->getSourceLocation(), std::move(boundCondition),
      std::move(boundThenStatement));
}

std::unique_ptr<BoundStatement>
Binder::bindIfStatement(IfStatementSyntax *ifStatement) {
  std::unique_ptr<BoundIfStatement> boundIfStatement =
      std::make_unique<BoundIfStatement>(ifStatement->getSourceLocation());

  std::unique_ptr<BoundExpression> boundCondition =
      std::move(bindExpression(ifStatement->getConditionPtr().get()));

  std::unique_ptr<BoundStatement> boundThenStatement =
      std::move(bindStatement(ifStatement->getStatementPtr().get()));

  boundIfStatement->addCondition(std::move(boundCondition));
  boundIfStatement->addThenStatement(std::move(boundThenStatement));

  for (int i = 0; i < ifStatement->getOrIfStatementsPtr().size(); i++) {
    std::unique_ptr<BoundOrIfStatement> boundOrIfStatement = std::move(
        bindOrIfStatement(ifStatement->getOrIfStatementsPtr()[i].get()));
    boundIfStatement->addOrIfStatement(std::move(boundOrIfStatement));
  }

  std::unique_ptr<BoundStatement> boundElseStatement = nullptr;

  if (ifStatement->getElseClausePtr() != nullptr) {
    boundElseStatement = std::move(bindStatement(
        ifStatement->getElseClausePtr()->getStatementPtr().get()));
    boundIfStatement->addElseStatement(std::move(boundElseStatement));
  }

  return std::move(boundIfStatement);
}
std::unique_ptr<BoundStatement>
Binder::bindWhileStatement(WhileStatementSyntax *whileStatement) {
  this->root = std::make_unique<BoundScope>(std::move(this->root));
  this->root->makeBreakableAndContinuable();

  std::unique_ptr<BoundExpression> boundCondition =
      std::move(bindExpression(whileStatement->getConditionPtr().get()));

  std::unique_ptr<BoundStatement> boundBody =
      bindStatement(whileStatement->getBodyPtr().get());

  this->root = std::move(this->root->parent);

  return std::make_unique<BoundWhileStatement>(
      whileStatement->getSourceLocation(), std::move(boundCondition),
      std::move(boundBody));
}

std::unique_ptr<BoundStatement>
Binder::bindForStatement(ForStatementSyntax *forStatement) {
  this->root = std::make_unique<BoundScope>(std::move(this->root));
  this->root->makeBreakableAndContinuable();
  std::unique_ptr<BoundStatement> boundIntializer =
      std::move(bindStatement(forStatement->getInitializationPtr().get()));

  std::unique_ptr<BoundExpression> boundUpperBound =
      std::move(bindExpression(forStatement->getUpperBoundPtr().get()));

  std::unique_ptr<BoundExpression> boundStepExpression = nullptr;

  if (forStatement->getStepExpressionPtr().get())
    boundStepExpression =
        std::move(bindExpression(forStatement->getStepExpressionPtr().get()));

  std::unique_ptr<BoundStatement> boundBody =
      std::move(bindStatement(forStatement->getStatementPtr().get()));

  this->root = std::move(this->root->parent);
  return std::make_unique<BoundForStatement>(
      forStatement->getSourceLocation(), std::move(boundIntializer),
      std::move(boundUpperBound), std::move(boundStepExpression),
      std::move(boundBody));
}

std::unique_ptr<BoundStatement>
Binder::bindBreakStatement(BreakStatementSyntax *breakStatement) {
  if (!this->root->isBreakable()) {
    this->_diagnosticHandler->addDiagnostic(Diagnostic(
        "Break Statement not within Loop or Switch",
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic,
        Utils::getSourceLocation(breakStatement->getBreakKeywordPtr().get())));
  }
  return std::make_unique<BoundBreakStatement>(
      breakStatement->getSourceLocation());
}

std::unique_ptr<BoundStatement>
Binder::bindContinueStatement(ContinueStatementSyntax *continueStatement) {
  if (!this->root->isContinuable()) {
    this->_diagnosticHandler->addDiagnostic(
        Diagnostic("Continue Statement Outside Of Loop",
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic,
                   Utils::getSourceLocation(
                       continueStatement->getContinueKeywordPtr().get())));
  }
  return std::make_unique<BoundContinueStatement>(
      continueStatement->getSourceLocation());
}

std::unique_ptr<BoundStatement>
Binder::bindReturnStatement(ReturnStatementSyntax *returnStatement) {
  std::unique_ptr<BoundReturnStatement> boundRetExpression =
      std::make_unique<BoundReturnStatement>(
          returnStatement->getSourceLocation());

  if (!this->root->isInFunction()) {
    this->_diagnosticHandler->addDiagnostic(
        Diagnostic("Return Statement Outside Of Function",
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic,
                   returnStatement->getSourceLocation()));
  } else {
    // TODO IMPLEMENT all Expression

    for (const auto &expr : returnStatement->getReturnExpressionListRef()) {
      boundRetExpression->addReturnExpression(
          std::move(bindExpression(expr.get())));
    }
  }

  return std::move(boundRetExpression);
}

std::unique_ptr<BoundStatement> Binder::bindStatement(StatementSyntax *syntax) {
  switch (syntax->getKind()) {
  case SyntaxKindUtils::SyntaxKind::ExpressionStatement: {
    return std::move(
        bindExpressionStatement((ExpressionStatementSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::BlockStatement: {
    return std::move(bindBlockStatement((BlockStatementSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::VariableDeclaration: {
    return std::move(
        bindVariableDeclaration((VariableDeclarationSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::IfStatement: {
    return std::move(bindIfStatement((IfStatementSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::WhileStatement: {
    return std::move(bindWhileStatement((WhileStatementSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::ForStatement: {
    return std::move(bindForStatement((ForStatementSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::BreakStatement: {
    return std::move(bindBreakStatement((BreakStatementSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::ContinueStatement: {
    return std::move(bindContinueStatement((ContinueStatementSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::ReturnStatement: {
    return std::move(bindReturnStatement((ReturnStatementSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::BringStatementSyntax: {
    return std::move(bindBringStatement((BringStatementSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::ClassStatement: {
    return std::move(bindClassStatement((ClassStatementSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::CustomTypeStatement: {
    return std::move(
        bindCustomTypeStatement((CustomTypeStatementSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::ModuleStatement: {
    return std::move(bindModuleStatement((ModuleStatementSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::MultipleVariableDeclaration: {
    return std::move(bindMultipleVariableDeclaration(
        (MultipleVariableDeclarationSyntax *)syntax));
  }
  default:
    throw "Unexpected syntax";
  }
}

std::unique_ptr<BoundMultipleVariableDeclaration>
Binder::bindMultipleVariableDeclaration(
    MultipleVariableDeclarationSyntax *multipleVariableDeclaration) {

  std::unique_ptr<BoundMultipleVariableDeclaration>
      boundMultipleVariableDeclaration =
          std::make_unique<BoundMultipleVariableDeclaration>(
              multipleVariableDeclaration->getSourceLocation());

  for (auto &variableDeclaration :
       multipleVariableDeclaration->getVariableDeclarationListRef()) {
    boundMultipleVariableDeclaration->addVariableDeclaration(
        std::move(this->bindVariableDeclaration(variableDeclaration.get())));
  }

  auto firstVariableDeclaration =
      boundMultipleVariableDeclaration->getVariableDeclarationListRef()[0]
          .get();

  for (auto i = 1;
       i <
       boundMultipleVariableDeclaration->getVariableDeclarationListRef().size();
       i++) {

    boundMultipleVariableDeclaration->getVariableDeclarationListRef()[i]
        ->setIsConst(firstVariableDeclaration->isConst());

    boundMultipleVariableDeclaration->getVariableDeclarationListRef()[i]
        ->setHasAsKeyword(firstVariableDeclaration->getHasAsKeyword());

    boundMultipleVariableDeclaration->getVariableDeclarationListRef()[i]
        ->setHasInOutKeyword(firstVariableDeclaration->getHasInOutKeyword());

    boundMultipleVariableDeclaration->getVariableDeclarationListRef()[i]
        ->setMemoryKind(firstVariableDeclaration->getMemoryKind());

    boundMultipleVariableDeclaration->getVariableDeclarationListRef()[i]
        ->setIsExposed(firstVariableDeclaration->isExposed());
  }

  return std::move(boundMultipleVariableDeclaration);
}

std::unique_ptr<BoundStatement>
Binder::bindModuleStatement(ModuleStatementSyntax *moduleStatement) {
  // this->root = std::make_unique<BoundScope>(std::move(this->root));
  std::unique_ptr<BoundModuleStatement> boundModuleStat =
      std::make_unique<BoundModuleStatement>(
          moduleStatement->getSourceLocation());

  boundModuleStat->addModuleNameIdentifier(std::move(
      bindLiteralExpression(moduleStatement->getModuleNameRef().get())));

  for (auto &cusType : moduleStatement->getCustomTypeStatementsRef()) {

    _currentModuleName = boundModuleStat->getModuleName();
    auto boundCustomTypeStatement =
        std::move(this->bindCustomTypeStatement(cusType.get()));

    boundModuleStat->addCustomTypeStatement(
        std::move(boundCustomTypeStatement));
    _currentModuleName = "";
  }

  this->root->tryDeclareModule(boundModuleStat.get());
  for (auto &classStmt : moduleStatement->getClassStatementsRef()) {

    _currentModuleName = boundModuleStat->getModuleName();
    auto boundClassStatement =
        std::move(this->bindClassStatement(classStmt.get()));

    boundModuleStat->addClassStatement(std::move(boundClassStatement));
    _currentModuleName = "";
  }

  //  std::unordered_map<std::string, int> varMemberMap;

  for (auto &var : moduleStatement->getVariableStatementsRef()) {

    _currentModuleName = boundModuleStat->getModuleName();
    auto boundMemberVariable = std::move(this->bindVariableDeclaration(
        var.get(), boundModuleStat->getModuleName()));
    // boundModuleStat->addMemberVariablePtr(boundMemberVariable.get());

    // varMemberMap[boundMemberVariable->getVariableName()] = 1;
    this->root->tryDeclareVariableGlobal(boundMemberVariable->getVariableName(),
                                         boundMemberVariable.get());

    boundModuleStat->addVariableStatement(std::move(boundMemberVariable));
    _currentModuleName = "";
  }

  // this->root = std::make_unique<BoundScope>(std::move(this->root));

  for (const auto &fun : moduleStatement->getFunctionStatementsRef()) {
    if (fun->isOnlyDeclared()) {
      _currentModuleName = boundModuleStat->getModuleName();
      // boundModuleStat->addFunctionStatement(
      //     std::any_cast<std::string>(fun->getIdentifierTokenPtr()->getValue()));

      boundModuleStat->addFunctionStatement(
          std::move(this->bindFunctionDeclaration(fun.get(), "")));
      _currentModuleName = "";
      continue;
    }

    fun->setIsOnlyDeclared(true);
    _currentModuleName = boundModuleStat->getModuleName();
    // boundModuleStat->addFunctionStatement(
    //     std::any_cast<std::string>(fun->getIdentifierTokenPtr()->getValue()));

    boundModuleStat->addFunctionStatement(
        std::move(this->bindFunctionDeclaration(
            fun.get(), boundModuleStat->getModuleName() +
                           FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX)));

    // Define Functions
    fun->setIsOnlyDeclared(false);
    boundModuleStat->addFunctionStatement(
        std::move(this->bindFunctionDeclaration(
            fun.get(), boundModuleStat->getModuleName() +
                           FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX)));
    _currentModuleName = "";
  }
  // this->root = std::move(this->root->parent);

  // this->root = std::move(this->root->parent);
  // this->root->tryDeclareModule(boundModuleStat.get());

  return std::move(boundModuleStat);
}

std::unique_ptr<BoundStatement> Binder::bindCustomTypeStatement(
    CustomTypeStatementSyntax *customTypeStatement) {
  std::unique_ptr<BoundCustomTypeStatement> boundCustomTypeStatement =
      std::make_unique<BoundCustomTypeStatement>(
          customTypeStatement->getSourceLocation(),
          customTypeStatement->isExposed());

  std::unique_ptr<BoundLiteralExpression<std::any>> boundLiteralExpression =
      std::move(
          bindLiteralExpression(customTypeStatement->getTypeNameRef().get()));

  boundCustomTypeStatement->setTypeName(std::move(boundLiteralExpression));

  std::unordered_map<std::string, int8_t> attributes;

  for (int i = 0; i < customTypeStatement->getKeyTypePairsRef().size(); i++) {
    const std::string &key = customTypeStatement->getKeyTypePairsRef()[i]
                                 ->getKey()
                                 ->getTokenPtr()
                                 ->getText();

    if (attributes.find(key) != attributes.end()) {
      this->_diagnosticHandler->addDiagnostic(
          Diagnostic("Duplicate Attribute key " + key + " in Custom Type" +
                         Utils::getActualTypeName(
                             boundCustomTypeStatement->getTypeNameAsString()),
                     DiagnosticUtils::DiagnosticLevel::Error,
                     DiagnosticUtils::DiagnosticType::Semantic,
                     customTypeStatement->getKeyTypePairsRef()[i]
                         ->getKey()
                         ->getSourceLocation()));
      return std::move(boundCustomTypeStatement);
    }
    attributes[key] = 1;

    std::unique_ptr<BoundLiteralExpression<std::any>> boundLiteralExpression =
        std::move(bindLiteralExpression(
            customTypeStatement->getKeyTypePairsRef()[i]->getKey().get()));
    std::unique_ptr<BoundTypeExpression> boundTypeExpression =
        std::move(bindTypeExpression(static_cast<TypeExpressionSyntax *>(
            customTypeStatement->getKeyTypePairsRef()[i]->getValue().get())));

    boundCustomTypeStatement->addKeyTypePair(std::move(boundLiteralExpression),
                                             std::move(boundTypeExpression));
  }

  if (_currentModuleName != "" &&
      !this->root->tryDeclareCustomTypeGlobal(boundCustomTypeStatement.get())) {
    this->_diagnosticHandler->addDiagnostic(
        Diagnostic("Duplicate Custom Type " +
                       Utils::getActualTypeName(
                           boundCustomTypeStatement->getTypeNameAsString()),
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic,
                   customTypeStatement->getTypeNameRef()->getSourceLocation()));
  }
  if (_currentModuleName == "" &&
      !this->root->tryDeclareCustomType(boundCustomTypeStatement.get())) {
    this->_diagnosticHandler->addDiagnostic(
        Diagnostic("Duplicate Custom Type " +
                       Utils::getActualTypeName(
                           boundCustomTypeStatement->getTypeNameAsString()),
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic,
                   customTypeStatement->getTypeNameRef()->getSourceLocation()));
  }

  return std::move(boundCustomTypeStatement);
}

std::unique_ptr<BoundExpression> Binder::bindContainerExpression(
    ContainerExpressionSyntax *containerExpression) {
  std::unique_ptr<BoundContainerExpression> boundContainerExpression =
      std::make_unique<BoundContainerExpression>(
          containerExpression->getSourceLocation());

  for (int i = 0; i < containerExpression->getElementsRef().size(); i++) {
    std::unique_ptr<BoundExpression> boundExpression = nullptr;

    if (containerExpression->getElementsRef()[i]->getKind() ==
        SyntaxKindUtils::SyntaxKind::ContainerExpression) {
      boundExpression = std::move(bindContainerExpression(
          (ContainerExpressionSyntax *)containerExpression->getElementsRef()[i]
              .get()));
    } else {
      boundExpression = std::move(
          bindExpression(containerExpression->getElementsRef()[i].get()));
    }

    boundContainerExpression->setElement(std::move(boundExpression));
  }

  return std::move(boundContainerExpression);
}

std::unique_ptr<BoundExpression> Binder::bindBracketedExpression(
    BracketedExpressionSyntax *bracketedExpression) {
  SyntaxKindUtils::SyntaxKind kind =
      bracketedExpression->getExpressionRef()->getKind();

  std::unique_ptr<BoundBracketedExpression> boundBracketedExpression =
      std::make_unique<BoundBracketedExpression>(
          bracketedExpression->getSourceLocation());

  switch (kind) {
  case SyntaxKindUtils::SyntaxKind::ContainerExpression: {
    boundBracketedExpression->setExpression(std::move(bindContainerExpression(
        (ContainerExpressionSyntax *)bracketedExpression->getExpressionRef()
            .get())));
    break;
  }

  case SyntaxKindUtils::SyntaxKind::FillExpression: {
    boundBracketedExpression->setExpression(std::move(bindFillExpression(
        (FillExpressionSyntax *)bracketedExpression->getExpressionRef()
            .get())));
    break;
  }
  default: {
    this->_diagnosticHandler->addDiagnostic(Diagnostic(
        "Invalid Bracketed Expression", DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic,
        bracketedExpression->getSourceLocation()));
    break;
  }
  }

  return std::move(boundBracketedExpression);
}

std::unique_ptr<BoundStatement>
Binder::bindClassStatement(ClassStatementSyntax *classStatement) {

  const std::string CURRENT_MODULE_NAME = _currentModuleName;
  _currentModuleName = "";
  this->root = std::make_unique<BoundScope>(std::move(this->root));
  std::unique_ptr<BoundClassStatement> boundClassStat =
      std::make_unique<BoundClassStatement>(
          classStatement->getSourceLocation());

  std::string className = std::any_cast<std::string>(
      classStatement->getClassNameIdentifierRef()->getValue());

  this->root->setClassName(className);
  boundClassStat->setClassName(className);

  if (classStatement->getExposeKeywordRef()) {
    boundClassStat->setIsExposed(true);
  }

  // If It Has Parent

  if (classStatement->getParentClassNameIdentifierRef()) {

    std::string parentClassName = std::any_cast<std::string>(
        classStatement->getParentClassNameIdentifierRef()->getValue());
    BoundClassStatement *parentClassStat =
        this->root->tryGetClass(parentClassName);

    if (!parentClassStat) {

      this->_diagnosticHandler->addDiagnostic(
          Diagnostic("Parent Class '" + parentClassName + "' Not Found",
                     DiagnosticUtils::DiagnosticLevel::Error,
                     DiagnosticUtils::DiagnosticType::Semantic,
                     classStatement->getParentClassNameIdentifierRef()
                         ->getSourceLocation()));

      return std::move(boundClassStat);
    }

    boundClassStat->setParentClass(parentClassStat);
    boundClassStat->setParentClassName(parentClassName);

    for (auto &var : parentClassStat->getAllMemberVariablesRef()) {
      boundClassStat->addMemberVariablePtr(var);
    }

    for (auto &func : parentClassStat->getAllFunctionNamesRef()) {
      boundClassStat->addFunctionName(func);
    }
  }

  // Class ItsSelf
  for (auto &cusType : classStatement->getCustomTypeStatementsRef()) {

    //! Mutating The Custom Type typeName to className +
    //! FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX
    // std::string typeName =
    //     std::any_cast<std::string>(cusType->getTypeNameRef()->getValue()) +
    //     FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX +
    //     IDGenerator::CustomTypeIDGenerator::instance()->nextString();

    // cusType->setTypeNameString(typeName);

    auto boundCustomTypeStatement =
        std::move(this->bindCustomTypeStatement(cusType.get()));

    boundClassStat->addCustomType(std::move(boundCustomTypeStatement));
  }

  std::unordered_map<std::string, int> varMemberMap;

  for (auto &var : classStatement->getDataMembersRef()) {
    auto boundMemberVariable = std::move(this->bindVariableDeclaration(
        var.get(), boundClassStat->getClassName()));

    boundClassStat->addMemberVariablePtr(boundMemberVariable.get());

    varMemberMap[boundMemberVariable->getVariableName()] = 1;

    boundClassStat->addMemberVariable(std::move(boundMemberVariable));
  }

  for (auto &var : boundClassStat->getAllMemberVariablesRef()) {

    boundClassStat->addKeyTypePair(var->getIdentifierRef().get(),
                                   (var->getTypeExpression().get()));
    this->root->tryDeclareVariable("self." + var->getVariableName(), var);
    if (!varMemberMap[var->getVariableName()]) {
      this->root->tryDeclareVariable(var->getVariableName(), var);
    }
  }

  this->root = std::make_unique<BoundScope>(std::move(this->root));
  this->root->tryDeclareClass(boundClassStat.get());
  for (const auto &fun : classStatement->getClassMemberFunctionsRef()) {
    fun->setIsOnlyDeclared(true);

    boundClassStat->addFunctionName(
        std::any_cast<std::string>(fun->getIdentifierTokenPtr()->getValue()));

    boundClassStat->addMemberFunction(std::move(this->bindFunctionDeclaration(
        fun.get(), className + FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX)));
  }
  for (const auto &fun : classStatement->getClassMemberFunctionsRef()) {
    fun->setIsOnlyDeclared(false);
    boundClassStat->addMemberFunction(std::move(this->bindFunctionDeclaration(
        fun.get(), className + FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX)));
  }

  this->root = std::move(this->root->parent);

  this->root = std::move(this->root->parent);

  if (CURRENT_MODULE_NAME != "")
    this->root->tryDeclareClassGlobal(boundClassStat.get());
  else
    this->root->tryDeclareClass(boundClassStat.get());
  return std::move(boundClassStat);
}

std::unique_ptr<BoundStatement>
Binder::bindBringStatement(BringStatementSyntax *bringStatement) {

  if (!Utils::Node::isPathExists(bringStatement->getAbsoluteFilePath())) {
    this->_diagnosticHandler->addDiagnostic(Diagnostic(
        "File <" + bringStatement->getRelativeFilePathPtr() + "> not found",
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic,
        Utils::getSourceLocation(bringStatement->getBringKeywordPtr().get())));
    return std::make_unique<BoundBringStatement>(
        bringStatement->getSourceLocation(),
        bringStatement->getDiagnosticHandlerPtr().get());
  }

  if (Utils::Node::isCycleDetected(bringStatement->getAbsoluteFilePath())) {
    this->_diagnosticHandler->addDiagnostic(Diagnostic(
        "Found Circular Dependency <" +
            bringStatement->getRelativeFilePathPtr() + "> ",
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic,
        Utils::getSourceLocation(bringStatement->getBringKeywordPtr().get())));

    return std::make_unique<BoundBringStatement>(
        bringStatement->getSourceLocation(),
        bringStatement->getDiagnosticHandlerPtr().get());
  }

  if (Utils::Node::isPathVisited(bringStatement->getAbsoluteFilePathPtr())) {

    this->_diagnosticHandler->addDiagnostic(Diagnostic(
        "File <" + bringStatement->getRelativeFilePathPtr() +
            "> already included ",
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic,
        Utils::getSourceLocation(bringStatement->getBringKeywordPtr().get())));

    return std::make_unique<BoundBringStatement>(
        bringStatement->getSourceLocation(),
        bringStatement->getDiagnosticHandlerPtr().get());
  }

  Utils::Node::addPath(bringStatement->getAbsoluteFilePathPtr());

  auto boundBringStatement = std::make_unique<BoundBringStatement>(
      bringStatement->getSourceLocation(),
      bringStatement->getDiagnosticHandlerPtr().get());

  boundBringStatement->setIsModuleImport(bringStatement->getIsModuleImport());

  if (bringStatement->getIsChoosyImportPtr()) {
    std::unordered_map<std::string, int> memberMap =
        getMemberMap(bringStatement->getCompilationUnitPtr()->getMembers(),
                     bringStatement->getCompilationUnitPtr().get());

    for (auto &expression : bringStatement->getExpressionsPtr()) {
      if (expression->getKind() !=
          SyntaxKindUtils::SyntaxKind::LiteralExpression) {
        this->_diagnosticHandler->addDiagnostic(
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
          memberMap.find(expression->getTokenPtr()->getText()) ==
          memberMap.end();

      if (notFound) {
        this->_diagnosticHandler->addDiagnostic(
            Diagnostic("Identifier <" + expression->getTokenPtr()->getText() +
                           "> not found in <" +
                           bringStatement->getRelativeFilePathPtr() + ">",
                       DiagnosticUtils::DiagnosticLevel::Error,
                       DiagnosticUtils::DiagnosticType::Semantic,
                       (expression->getSourceLocation())));
        continue;
      }
      boundBringStatement->setExpression(
          expression->getTokenPtr()->getText(),
          std::move(bindLiteralExpression(expression.get())));
    }
  }
  Utils::Node::removePath(bringStatement->getAbsoluteFilePathPtr());

  this->_diagnosticHandler->addParentDiagnostics(
      bringStatement->getDiagnosticHandlerPtr().get());

  std::unique_ptr<BoundScopeGlobal> globalScope =
      std::move(Binder::bindGlobalScope(
          nullptr, bringStatement->getCompilationUnitPtr().get(),
          bringStatement->getDiagnosticHandlerPtr().get()));

  for (auto &function : globalScope->functions) {
    if (!this->root->tryDeclareFunctionGlobal(function.second)) {
      this->_diagnosticHandler->addDiagnostic(
          Diagnostic("Function " + function.first + " Already Declared",
                     DiagnosticUtils::DiagnosticLevel::Error,
                     DiagnosticUtils::DiagnosticType::Semantic,
                     Utils::getSourceLocation(
                         bringStatement->getBringKeywordPtr().get())));
    }
  }
  for (auto &_class : globalScope->classes) {
    if (!this->root->tryDeclareClass(_class.second)) {
      this->_diagnosticHandler->addDiagnostic(
          Diagnostic("Class " + _class.first + " Already Declared",
                     DiagnosticUtils::DiagnosticLevel::Error,
                     DiagnosticUtils::DiagnosticType::Semantic,
                     Utils::getSourceLocation(
                         bringStatement->getBringKeywordPtr().get())));
    }
  }
  for (auto &customType : globalScope->customTypes) {
    if (!this->root->tryDeclareCustomType(customType.second)) {
      this->_diagnosticHandler->addDiagnostic(
          Diagnostic("Type " + customType.first + " Already Declared",
                     DiagnosticUtils::DiagnosticLevel::Error,
                     DiagnosticUtils::DiagnosticType::Semantic,
                     Utils::getSourceLocation(
                         bringStatement->getBringKeywordPtr().get())));
    }
  }

  for (auto &variable : globalScope->variables) {
    if (!this->root->tryDeclareVariable(variable.first, variable.second)) {
      this->_diagnosticHandler->addDiagnostic(
          Diagnostic("Variable " + variable.first + " Already Declared",
                     DiagnosticUtils::DiagnosticLevel::Error,
                     DiagnosticUtils::DiagnosticType::Semantic,
                     Utils::getSourceLocation(
                         bringStatement->getBringKeywordPtr().get())));
    }
  }

  for (auto &module : globalScope->modules) {
    if (!this->root->tryDeclareModule(module.second)) {
      this->_diagnosticHandler->addDiagnostic(
          Diagnostic("Module " + module.first + " Already Declared",
                     DiagnosticUtils::DiagnosticLevel::Error,
                     DiagnosticUtils::DiagnosticType::Semantic,
                     Utils::getSourceLocation(
                         bringStatement->getBringKeywordPtr().get())));
    }

    // for (const auto &variable :
    //      module.second->getVariableDeclarationStatementsRef()) {
    //   if (!this->root->tryDeclareVariable(variable->getVariableName(),
    //                                       variable.get())) {
    //     this->_diagnosticHandler->addDiagnostic(Diagnostic(
    //         "Variable " + variable->getVariableName() + " Already Declared",
    //         DiagnosticUtils::DiagnosticLevel::Error,
    //         DiagnosticUtils::DiagnosticType::Semantic,
    //         Utils::getSourceLocation(
    //             bringStatement->getBringKeywordPtr().get())));
    //   }
    // }
  }

  boundBringStatement->setGlobalScope(std::move(globalScope));

  return std::move(boundBringStatement);
}

std::unique_ptr<BoundLiteralExpression<std::any>>
Binder::bindLiteralExpression(ExpressionSyntax *syntax) {
  LiteralExpressionSyntax<std::any> *literalSyntax =
      static_cast<LiteralExpressionSyntax<std::any> *>(syntax);

  std::any value = literalSyntax->getValue();

  return std::make_unique<BoundLiteralExpression<std::any>>(
      literalSyntax->getSourceLocation(), value,
      literalSyntax->getSyntaxKind());
}

std::unique_ptr<BoundExpression>
Binder::bindIndexExpression(IndexExpressionSyntax *indexExpression) {
  std::string variableName = std::any_cast<std::string>(
      indexExpression->getIndexIdentifierExpressionPtr()->getValue());

  if (!root->tryLookupVariable(variableName)) {
    this->_diagnosticHandler->addDiagnostic(
        Diagnostic("Variable " + variableName + " does not exist",
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic,
                   Utils::getSourceLocation(
                       indexExpression->getIndexIdentifierExpressionPtr()
                           ->getTokenPtr()
                           .get())));

    return std::move(bindExpression(
        indexExpression->getIndexIdentifierExpressionPtr().get()));
  }

  BoundVariableDeclaration *variable = root->tryGetVariable(variableName);

  if (variable->getTypeExpression().get()->getSyntaxType() !=
      SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE) {
    this->_diagnosticHandler->addDiagnostic(
        Diagnostic("Variable " + variableName + " is not a array",
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic,
                   Utils::getSourceLocation(
                       indexExpression->getIndexIdentifierExpressionPtr()
                           ->getTokenPtr()
                           .get())));
  }
  std::unique_ptr<BoundLiteralExpression<std::any>> boundIdentifierExpression(
      (BoundLiteralExpression<std::any> *)bindExpression(
          indexExpression->getIndexIdentifierExpressionPtr().get())
          .release());

  std::unique_ptr<BoundIndexExpression> boundIndexExp =
      std::make_unique<BoundIndexExpression>(
          indexExpression->getSourceLocation(),
          std::move(boundIdentifierExpression));

  for (const auto &indexExp : indexExpression->getIndexExpressionsRef()) {
    boundIndexExp->addBoundIndexExpression(
        std::move(bindExpression(indexExp.get())));
  }

  if (indexExpression->isObject()) {

    VariableExpressionSyntax *variableExpressionSyntax =
        static_cast<VariableExpressionSyntax *>(
            indexExpression->getVariableExpressionRef().get());

    std::unique_ptr<BoundVariableExpression> boundVariableExpression =
        std::make_unique<BoundVariableExpression>(
            indexExpression->getSourceLocation(), nullptr,
            variableExpressionSyntax->isConstant(),
            variable->getTypeExpression().get());

    for (const auto &dotExpression :
         variableExpressionSyntax->getDotExpressionList()) {
      if (dotExpression->getKind() ==
          SyntaxKindUtils::SyntaxKind::IndexExpression) {

        IndexExpressionSyntax *indexExpression =
            static_cast<IndexExpressionSyntax *>(dotExpression.get());
        std::unique_ptr<BoundLiteralExpression<std::any>>
            localBoundIdentifierExpression(
                (BoundLiteralExpression<std::any> *)bindExpression(
                    indexExpression->getIndexIdentifierExpressionPtr().get())
                    .release());

        std::unique_ptr<BoundIndexExpression> localBoundIndexExp =
            std::make_unique<BoundIndexExpression>(
                indexExpression->getSourceLocation(),
                std::move(localBoundIdentifierExpression));

        for (const auto &indexExp : indexExpression->getIndexExpressionsRef()) {
          localBoundIndexExp->addBoundIndexExpression(
              std::move(bindExpression(indexExp.get())));
        }
        boundVariableExpression->addDotExpression(
            std::move(localBoundIndexExp));
      } else {
        boundVariableExpression->addDotExpression(
            std::move(bindExpression(dotExpression.get())));
      }
    }

    boundIndexExp->addVariableExpression(std::move(boundVariableExpression));
  }

  return std::move(boundIndexExp);
}

std::unique_ptr<BoundExpression>
Binder::bindunaryExpression(UnaryExpressionSyntax *unaryExpression) {
  std::unique_ptr<BoundExpression> boundOperand =
      std::move(bindExpression(unaryExpression->getOperandPtr().get()));
  BinderKindUtils::BoundUnaryOperatorKind op =
      BinderKindUtils::getUnaryOperatorKind(
          unaryExpression->getOperatorTokenPtr()->getKind());

  return std::make_unique<BoundUnaryExpression>(
      unaryExpression->getSourceLocation(), op, std::move(boundOperand));
}

std::unique_ptr<BoundExpression>
Binder::bindBinaryExpression(BinaryExpressionSyntax *binaryExpression) {
  std::unique_ptr<BoundExpression> boundLeft =
      std::move(bindExpression(binaryExpression->getLeftPtr().get()));
  std::unique_ptr<BoundExpression> boundRight =
      std::move(bindExpression(binaryExpression->getRightPtr().get()));
  BinderKindUtils::BoundBinaryOperatorKind op =
      BinderKindUtils::getBinaryOperatorKind(
          binaryExpression->getOperatorTokenPtr()->getKind());

  return std::make_unique<BoundBinaryExpression>(
      binaryExpression->getSourceLocation(), std::move(boundLeft), op,
      std::move(boundRight));
}

std::unique_ptr<BoundExpression> Binder::bindAssignmentExpression(
    AssignmentExpressionSyntax *assignmentExpression) {
  std::string variable_str = "";

  if (auto variableExpression = dynamic_cast<VariableExpressionSyntax *>(
          assignmentExpression->getLeftPtr().get())) {
    variable_str = variableExpression->getVariableName();
  } else if (auto indexExpression = dynamic_cast<IndexExpressionSyntax *>(
                 assignmentExpression->getLeftPtr().get())) {
    variable_str = std::any_cast<std::string>(
        indexExpression->getIndexIdentifierExpressionPtr()->getValue());
  } else {
    this->_diagnosticHandler->addDiagnostic(
        Diagnostic("Invalid Assignment Expression",
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic,
                   assignmentExpression->getLeftPtr()->getSourceLocation()));

    return std::move(bindExpression(assignmentExpression->getLeftPtr().get()));
  }

  std::unique_ptr<BoundExpression> boundIdentifierExpression(
      bindExpression(assignmentExpression->getLeftPtr().get()));

  BinderKindUtils::BoundBinaryOperatorKind op =
      BinderKindUtils::getBinaryOperatorKind(
          assignmentExpression->getOperatorTokenKind());

  if (!root->tryLookupVariable(variable_str)) {
    this->_diagnosticHandler->addDiagnostic(
        Diagnostic("Can Not Assign To Undeclared Variable " + variable_str,
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic,
                   assignmentExpression->getLeftPtr()->getSourceLocation()));

    return std::move(boundIdentifierExpression);
  }

  if (root->tryGetVariable(variable_str)->isConst()) {
    this->_diagnosticHandler->addDiagnostic(
        Diagnostic("Can Not Assign To Constant Variable " + variable_str,
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic,
                   assignmentExpression->getLeftPtr()->getSourceLocation()));

    return std::move(boundIdentifierExpression);
  }

  if (assignmentExpression->getRightPtr()) {

    std::unique_ptr<BoundExpression> boundRight =
        std::move(bindExpression(assignmentExpression->getRightPtr().get()));
    return std::make_unique<BoundAssignmentExpression>(
        assignmentExpression->getSourceLocation(),
        root->tryGetVariable(variable_str),
        std::move(boundIdentifierExpression), op, std::move(boundRight),
        assignmentExpression->getNeedDefaulInitilization());
  } else {

    return std::make_unique<BoundAssignmentExpression>(
        assignmentExpression->getSourceLocation(),
        root->tryGetVariable(variable_str),
        std::move(boundIdentifierExpression), op, nullptr,
        assignmentExpression->getNeedDefaulInitilization());
  }
}

std::unique_ptr<BoundExpression>
Binder::bindCallExpression(CallExpressionSyntax *callExpression) {
  std::unique_ptr<BoundLiteralExpression<std::any>> boundIdentifier(
      (BoundLiteralExpression<std::any> *)bindExpression(
          (callExpression->getIdentifierPtr().get()))
          .release());

  const std::string CALLER_NAME =
      std::any_cast<std::string>(boundIdentifier->getValue());

  const bool IS_CALLING_SUPPER_OUT_SIDEOF_INIT_FUNCTION =
      CALLER_NAME == "super" && !this->root->isInsideInitFunction();

  if (IS_CALLING_SUPPER_OUT_SIDEOF_INIT_FUNCTION) {
    this->_diagnosticHandler->addDiagnostic(Diagnostic(
        "Can not call 'super' function directly inside any member function "
        "other than init function",
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic,
        Utils::getSourceLocation(
            callExpression->getIdentifierPtr()->getTokenPtr().get())));

    return std::move(boundIdentifier);
  }

  const bool IS_CALLING_INIT_FUNCTION_OUTSIDE_OR_INSIDE_CLASS =
      CALLER_NAME == "init";

  if (IS_CALLING_INIT_FUNCTION_OUTSIDE_OR_INSIDE_CLASS) {
    this->_diagnosticHandler->addDiagnostic(Diagnostic(
        "Can not call 'init' function directly inside or outside of class",
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic,
        Utils::getSourceLocation(
            callExpression->getIdentifierPtr()->getTokenPtr().get())));

    return std::move(boundIdentifier);
  }

  const bool IS_A_BUILTIN_FUNCTION_CALL =
      BuiltInFunction::isBuiltInFunction(CALLER_NAME);

  if (IS_A_BUILTIN_FUNCTION_CALL) {
    const std::unique_ptr<BoundFunctionDeclaration> &boundBuiltinFunction =
        BuiltInFunction::getBuiltInFunction(CALLER_NAME);

    const bool IS_AGUMENT_MISMATCHED_OF_NON_VARIADIC_BUILTIN_FUNCTION_CALL =
        !boundBuiltinFunction->isVariadicFunction() &&
        callExpression->getArguments().size() !=
            boundBuiltinFunction->getParametersRef().size();

    if (IS_AGUMENT_MISMATCHED_OF_NON_VARIADIC_BUILTIN_FUNCTION_CALL) {
      this->_diagnosticHandler->addDiagnostic(Diagnostic(
          "Function " + boundBuiltinFunction->getFunctionNameRef() +
              " requires " +
              std::to_string(boundBuiltinFunction->getParametersRef().size()) +
              " arguments but " +
              std::to_string(callExpression->getArguments().size()) +
              " arguments were given",
          DiagnosticUtils::DiagnosticLevel::Error,
          DiagnosticUtils::DiagnosticType::Semantic,
          Utils::getSourceLocation(
              callExpression->getIdentifierPtr()->getTokenPtr().get())));
    }
  }

  BoundFunctionDeclaration *declared_fd = nullptr;
  std::string updatedCallerName = CALLER_NAME;

  if (!IS_A_BUILTIN_FUNCTION_CALL) {

    const std::string CLASS_NAME = this->root->getClassName();
    const bool IS_INSIDE_CURRENT_CLASS = CLASS_NAME != "";
    if (IS_INSIDE_CURRENT_CLASS) {
      BoundClassStatement *boundClassStatement =
          this->root->tryGetClass(CLASS_NAME);

      const bool IS_SUPPER_INIT_CALL = CALLER_NAME == "super";
      if (IS_SUPPER_INIT_CALL && !declared_fd) {
        const bool IS_CURRENT_CLASS_HAS_NO_PARENT_CLASS =
            boundClassStatement->getParentClassName() == "";

        if (IS_CURRENT_CLASS_HAS_NO_PARENT_CLASS) {
          this->_diagnosticHandler->addDiagnostic(Diagnostic(
              "Could not find super class of class " + CLASS_NAME +
                  ", "
                  "Add super class to class declaration",
              DiagnosticUtils::DiagnosticLevel::Error,
              DiagnosticUtils::DiagnosticType::Semantic,
              Utils::getSourceLocation(
                  callExpression->getIdentifierPtr()->getTokenPtr().get())));

          return std::move(boundIdentifier);
        }

        updatedCallerName =
            boundClassStatement->getParentClassName() +
            FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX + "init" +
            std::to_string(callExpression->getArguments().size());
        declared_fd = boundClassStatement->getParentClass()->getMemberFunction(
            updatedCallerName);
      }
      if (boundClassStatement) {
        const std::string CLASS_MEMBER_FUNCTION_NAME =
            boundClassStatement->getActualFunctionNameIfExists(CALLER_NAME);

        const auto CURRENT_CLASS_MEMEBER_FUNCTION_CALL =
            boundClassStatement->getMemberFunction(CLASS_MEMBER_FUNCTION_NAME);

        if (CURRENT_CLASS_MEMEBER_FUNCTION_CALL && !declared_fd) {
          updatedCallerName = CLASS_MEMBER_FUNCTION_NAME;
          declared_fd = CURRENT_CLASS_MEMEBER_FUNCTION_CALL;
        }
      }
    }
  }

  //! Is Init function
  auto callStatement = this->root->tryGetClass(CALLER_NAME);

  if (callStatement && !declared_fd) {
    updatedCallerName = CALLER_NAME +
                        FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX + "init" +
                        std::to_string(callExpression->getArguments().size());
    declared_fd = callStatement->getMemberFunction(updatedCallerName);

    if (!declared_fd) {
      _diagnosticHandler->addDiagnostic(Diagnostic(
          "Class " + CALLER_NAME +
              " does not have an initializer, Add Default or "
              "Parameterized Initializer in Class Body ",
          DiagnosticUtils::DiagnosticLevel::Error,
          DiagnosticUtils::DiagnosticType::Semantic,
          Utils::getSourceLocation(
              callExpression->getIdentifierPtr()->getTokenPtr().get())));
      return std::move(boundIdentifier);
    }
  }

  //? calling a class member functon outside of a class e.g "a.callMe()"
  {
    const std::string CLASS_NAME = CALLER_NAME.substr(0, CALLER_NAME.find("."));
    std::string fLastName = CALLER_NAME.substr(CALLER_NAME.find(".") + 1);

    BoundClassStatement *boundClassStatement =
        this->root->tryGetClass(CLASS_NAME);

    if (boundClassStatement) {
      fLastName = boundClassStatement->getActualFunctionNameIfExists(fLastName);
    }

    if (fLastName != "" && boundClassStatement) {
      updatedCallerName = fLastName;
      std::unique_ptr<BoundCallExpression> boundCallExpression =
          std::make_unique<BoundCallExpression>(
              callExpression->getSourceLocation());

      boundIdentifier->setValue(updatedCallerName);
      boundCallExpression->setHasNewKeyword(callExpression->hasNewKeyword());
      boundCallExpression->setCallerIdentifier(std::move(boundIdentifier));

      for (int i = 0; i < callExpression->getArguments().size(); i++) {
        boundCallExpression->addArgument(
            std::move(bindExpression(callExpression->getArguments()[i].get())));
      }

      return std::move(boundCallExpression);
    }
  }

  //? Calling a Moudle Function e.g Test::callMe()

  if (!declared_fd) {
    const std::string MODULE_NAME = CALLER_NAME.substr(
        0, CALLER_NAME.find(FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX));
    std::string mLastName = CALLER_NAME.substr(
        CALLER_NAME.find(FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX) + 1);

    BoundModuleStatement *boundModuleStatement =
        this->root->tryGetModule(MODULE_NAME);

    if (boundModuleStatement) {
      updatedCallerName = CALLER_NAME;
      declared_fd = this->root->tryGetFunction(updatedCallerName);
    }
  }

  // if in class -> b, cf, nf
  // not in class -> b, nf

  if (!declared_fd && !IS_A_BUILTIN_FUNCTION_CALL) {
    updatedCallerName = CALLER_NAME;
    declared_fd = this->root->tryGetFunction(updatedCallerName);
  }

  if (!declared_fd && !IS_A_BUILTIN_FUNCTION_CALL) {

    std::string type = "Function";

    if (!this->root->tryGetClass(CALLER_NAME)) {

      _diagnosticHandler->addDiagnostic(
          Diagnostic(type + " " + CALLER_NAME + " does not exist",
                     DiagnosticUtils::DiagnosticLevel::Error,
                     DiagnosticUtils::DiagnosticType::Semantic,
                     callExpression->getIdentifierPtr()->getSourceLocation()));
    }
  }

  if (declared_fd &&
      callExpression->getArguments().size() !=
          declared_fd->getParametersRef().size() &&
      !IS_A_BUILTIN_FUNCTION_CALL) {
    _diagnosticHandler->addDiagnostic(Diagnostic(
        "Function " + CALLER_NAME + " requires " +
            std::to_string(declared_fd->getParametersRef().size()) +
            " arguments",
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic,
        callExpression->getOpenParenthesisTokenPtr()->getSourceLocation()));
    return std::move(boundIdentifier);
  }

  std::unique_ptr<BoundCallExpression> boundCallExpression =
      std::make_unique<BoundCallExpression>(
          callExpression->getSourceLocation());

  boundIdentifier->setValue(updatedCallerName);
  boundCallExpression->setHasNewKeyword(callExpression->hasNewKeyword());
  boundCallExpression->setCallerIdentifier(std::move(boundIdentifier));

  for (int i = 0; i < callExpression->getArguments().size(); i++) {
    boundCallExpression->addArgument(
        std::move(bindExpression(callExpression->getArguments()[i].get())));
  }

  return std::move(boundCallExpression);
}

std::unique_ptr<BoundExpression>
Binder::bindFillExpression(FillExpressionSyntax *fillExpression) {
  std::unique_ptr<BoundFillExpression> boundFillExpression =
      std::make_unique<BoundFillExpression>(
          fillExpression->getSourceLocation());

  if (fillExpression->getSizeToFillExpressionRef().get()) {
    boundFillExpression->setSizeToFill(std::move(
        bindExpression(fillExpression->getSizeToFillExpressionRef().get())));
  }

  boundFillExpression->setElementToFill(std::move(
      bindExpression(fillExpression->getElementExpressionRef().get())));

  return std::move(boundFillExpression);
}

std::unique_ptr<BoundExpression>
Binder::bindExpression(ExpressionSyntax *syntax) {
  switch (syntax->getKind()) {
  case SyntaxKindUtils::SyntaxKind::LiteralExpression: {
    return std::move(
        bindLiteralExpression((LiteralExpressionSyntax<std::any> *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::UnaryExpression: {
    return std::move(bindunaryExpression((UnaryExpressionSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::BinaryExpression: {
    return std::move(bindBinaryExpression((BinaryExpressionSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::AssignmentExpression: {
    return std::move(
        bindAssignmentExpression((AssignmentExpressionSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::VariableExpressionSyntax: {
    return std::move(
        bindVariableExpression((VariableExpressionSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::ParenthesizedExpression: {
    ParenthesizedExpressionSyntax *parenthesizedExpression =
        (ParenthesizedExpressionSyntax *)syntax;
    return bindExpression(parenthesizedExpression->getExpression().get());
  }
  case SyntaxKindUtils::SyntaxKind::CallExpression: {
    return std::move(bindCallExpression((CallExpressionSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::IndexExpression: {
    return std::move(bindIndexExpression((IndexExpressionSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::BracketedExpression: {
    return std::move(
        bindBracketedExpression((BracketedExpressionSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::ObjectExpression: {
    return std::move(bindObjectExpression((ObjectExpressionSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::NirastExpression: {
    return std::move(bindNirastExpression((NirastExpressionSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::MultipleAssignmentExpression: {
    return std::move(bindMultipleAssignmentExpression(
        (MultipleAssignmentExpressionSyntax *)syntax));
  }

  default:
    throw "Unexpected syntax";
  }
  return nullptr;
}

std::unique_ptr<BoundMultipleAssignmentExpression>
Binder::bindMultipleAssignmentExpression(
    MultipleAssignmentExpressionSyntax *multipleAssignmentExpressionSyntax) {

  std::unique_ptr<BoundMultipleAssignmentExpression>
      boundMultipleAssignmentExpression =
          std::make_unique<BoundMultipleAssignmentExpression>(
              multipleAssignmentExpressionSyntax->getSourceLocation());

  for (const auto &assignment :
       multipleAssignmentExpressionSyntax->getAssignmentExprListRef()) {
    boundMultipleAssignmentExpression->addAssignment(
        std::unique_ptr<BoundAssignmentExpression>(
            (BoundAssignmentExpression *)bindAssignmentExpression(
                assignment.get())
                .release()));
  }

  return std::move(boundMultipleAssignmentExpression);
}

std::unique_ptr<BoundExpression>
Binder::bindObjectExpression(ObjectExpressionSyntax *objectExpressionSyntax) {
  std::unique_ptr<BoundObjectExpression> boundObjectExpression =
      std::make_unique<BoundObjectExpression>(
          objectExpressionSyntax->getSourceLocation());

  for (const auto &attribute : objectExpressionSyntax->getAttributes()) {
    boundObjectExpression->addKeyValuePair(
        std::move(bindLiteralExpression(attribute->getKey().get())),
        std::move(bindExpression(attribute->getValue().get())));
  }

  return std::move(boundObjectExpression);
}

std::unique_ptr<BoundExpression>
Binder::bindNirastExpression(NirastExpressionSyntax *nirastExpressionSyntax) {
  std::unique_ptr<BoundNirastExpression> boundNirastExpression =
      std::make_unique<BoundNirastExpression>(
          nirastExpressionSyntax->getSourceLocation());

  boundNirastExpression->setNirastExpression(std::move(bindLiteralExpression(
      nirastExpressionSyntax->getNirastExpressionRef().get())));

  return std::move(boundNirastExpression);
}

std::unique_ptr<BoundExpression> Binder::bindVariableExpression(
    VariableExpressionSyntax *variableExpressionSyntax) {

  BoundVariableDeclaration *variable =
      this->root->tryGetVariable(variableExpressionSyntax->getVariableName());

  if (variableExpressionSyntax->hasModuleNameorCallExpression()) {
    BoundModuleStatement *module =
        this->root->tryGetModule(variableExpressionSyntax->getVariableName());
    if (!module) {

      this->_diagnosticHandler->addDiagnostic(
          Diagnostic("Module " + variableExpressionSyntax->getVariableName() +
                         " Not Found",
                     DiagnosticUtils::DiagnosticLevel::Error,
                     DiagnosticUtils::DiagnosticType::Semantic,
                     variableExpressionSyntax->getSourceLocation()));
      return nullptr;
    }

    return this->bindExpression(
        variableExpressionSyntax->getModuleNameorCallExpression().get());
  }

  if (!variable) {

    this->_diagnosticHandler->addDiagnostic(
        Diagnostic("Variable " + variableExpressionSyntax->getVariableName() +
                       " Not Found",
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic,
                   variableExpressionSyntax->getSourceLocation()));
    return nullptr;
  }

  if (variable->getTypeExpression().get()->getKind() ==
      BinderKindUtils::BoundObjectExpression) {
    BoundObjectTypeExpression *boundObjTypeExp =
        static_cast<BoundObjectTypeExpression *>(
            variable->getTypeExpression().get());

    BoundCustomTypeStatement *boundCustomType =
        this->root->tryGetCustomType(boundObjTypeExp->getTypeName());

    std::unordered_map<std::string, int8_t> boundAttributes;

    for (const auto &[bLE, bTE] : boundCustomType->getKeyPairs()) {
      boundAttributes[std::any_cast<std::string>(bLE->getValue())] = 1;
    }
  }

  std::unique_ptr<BoundVariableExpression> boundVariableExpression =
      std::make_unique<BoundVariableExpression>(
          variableExpressionSyntax->getSourceLocation(),
          std::move(bindLiteralExpression(
              variableExpressionSyntax->getIdentifierTokenRef().get())),
          variableExpressionSyntax->isConstant(),
          variable->getTypeExpression().get());
  boundVariableExpression->setSelf(variableExpressionSyntax->getIsSelf());
  boundVariableExpression->setHasNewKeyword(
      variableExpressionSyntax->getHasNewKeyword());
  for (const auto &dotExpression :
       variableExpressionSyntax->getDotExpressionList()) {
    if (dotExpression->getKind() ==
        SyntaxKindUtils::SyntaxKind::IndexExpression) {

      IndexExpressionSyntax *indexExpression =
          static_cast<IndexExpressionSyntax *>(dotExpression.get());
      std::unique_ptr<BoundLiteralExpression<std::any>>
          localBoundIdentifierExpression(
              (BoundLiteralExpression<std::any> *)bindExpression(
                  indexExpression->getIndexIdentifierExpressionPtr().get())
                  .release());
      std::unique_ptr<BoundIndexExpression> localBoundIndexExp =
          std::make_unique<BoundIndexExpression>(
              indexExpression->getSourceLocation(),
              std::move(localBoundIdentifierExpression));

      for (const auto &indexExp : indexExpression->getIndexExpressionsRef()) {
        localBoundIndexExp->addBoundIndexExpression(
            std::move(bindExpression(indexExp.get())));
      }
      boundVariableExpression->addDotExpression(std::move(localBoundIndexExp));
    } else {
      if (dotExpression->getKind() ==
          SyntaxKindUtils::SyntaxKind::CallExpression) {
        CallExpressionSyntax *callExpression =
            static_cast<CallExpressionSyntax *>(dotExpression.get());

        if (variable->getClassItBelongsTo() != "") {

          std::any fName = variable->getClassItBelongsTo() +
                           FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX +
                           std::any_cast<std::string>(
                               callExpression->getIdentifierPtr()->getValue());

          callExpression->getIdentifierPtr()->setValue((fName));
        }

        boundVariableExpression->addDotExpression(
            std::move(bindCallExpression(callExpression)));
      } else {
        boundVariableExpression->addDotExpression(
            std::move(bindExpression(dotExpression.get())));
      }
    }
  }

  return std::move(boundVariableExpression);
}

void Binder::handleFunctionDefAndDec(FunctionDeclarationSyntax *syntax,
                                     BoundFunctionDeclaration *fd,
                                     std::string prefix) {
  this->root = std::make_unique<BoundScope>(std::move(this->root));
  std::string function_name =
      prefix != "" ? prefix + syntax->getIdentifierTokenPtr()->getText()
                   : syntax->getIdentifierTokenPtr()->getText();

  Utils::DEBUG_LOG("Binder:: Declaring function: " + function_name);

  if (BuiltInFunction::isBuiltInFunction(function_name)) {
    this->_diagnosticHandler->addDiagnostic(Diagnostic(
        "Function " + function_name + " Already Exists",
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic,
        Utils::getSourceLocation(syntax->getIdentifierTokenPtr().get())));
  }

  fd->setIsMemberFunction(syntax->isMemberFunction());

  if (syntax->getAsKeyword()) {
    fd->setHasAsReturnType(true);
  }

  if (function_name.substr(
          function_name.find(FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX) +
          1) == "init") {
    function_name += std::to_string(syntax->getParametersPtr().size());
    this->root->setInsideInitFunction(true);
  }

  fd->setFunctionName(function_name);
  for (int i = 0; i < syntax->getParametersPtr().size(); i++) {
    const std::string &variable_str =
        syntax->getParametersPtr()[i]->getIdentifierRef()->getText();

    std::unique_ptr<BoundVariableDeclaration> varDeclaration =
        std::move(bindVariableDeclaration(syntax->getParametersPtr()[i].get()));
    fd->addParameter(std::move(varDeclaration));
  }

  for (const auto &expr : syntax->getReturnTypeExpressionListRef()) {
    fd->addReturnExpr(
        std::move(bindTypeExpression((TypeExpressionSyntax *)expr.get())));
  }

  if (syntax->isOnlyDeclared()) {
    fd->setOnlyDeclared(true);
  } else {

    this->root->incrementFunctionCount();
    std::unique_ptr<BoundBlockStatement> boundBody(
        (BoundBlockStatement *)bindStatement(syntax->getBodyPtr().get())
            .release());

    fd->setFunctionBody(std::move(boundBody));

    this->root->decrementFunctionCount();
  }

  this->root->setInsideInitFunction(false);
  this->root = std::move(this->root->parent);
}

std::unique_ptr<BoundStatement>
Binder::bindFunctionDeclaration(FunctionDeclarationSyntax *syntax,
                                std::string prefix) {

  std::unique_ptr<BoundFunctionDeclaration> fd =
      std::make_unique<BoundFunctionDeclaration>(syntax->getSourceLocation(),
                                                 syntax->isExposed());

  handleFunctionDefAndDec(syntax, fd.get(), prefix);

  if (syntax->isOnlyDeclared()) {
    const std::string &function_name =
        syntax->getIdentifierTokenPtr()->getText();
    if (syntax->isMemberFunction() &&
        !this->root->tryDeclareFunctionGlobal(fd.get())) {
      this->_diagnosticHandler->addDiagnostic(Diagnostic(
          "Function " + function_name + " Already Declared",
          DiagnosticUtils::DiagnosticLevel::Error,
          DiagnosticUtils::DiagnosticType::Semantic,
          Utils::getSourceLocation(syntax->getFunctionKeywordPtr().get())));
    } else if (!syntax->isMemberFunction() &&
               !this->root->tryDeclareMemberFunction(fd.get())) {
      this->_diagnosticHandler->addDiagnostic(Diagnostic(
          "Function " + function_name + " Already Declared",
          DiagnosticUtils::DiagnosticLevel::Error,
          DiagnosticUtils::DiagnosticType::Semantic,
          Utils::getSourceLocation(syntax->getFunctionKeywordPtr().get())));
    }
  }
  return std::move(fd);
}

std::unique_ptr<BoundTypeExpression>
Binder::bindTypeExpression(TypeExpressionSyntax *typeExpressionSyntax) {
  switch (typeExpressionSyntax->getKind()) {
  case SyntaxKindUtils::SyntaxKind::ArrayTypeExpression: {
    ArrayTypeExpressionSyntax *arrayTypeExpressionSyntax =
        static_cast<ArrayTypeExpressionSyntax *>(typeExpressionSyntax);

    std::unique_ptr<BoundArrayTypeExpression> boundArrayTypeExpression =
        std::make_unique<BoundArrayTypeExpression>(
            typeExpressionSyntax->getSourceLocation(),
            typeExpressionSyntax->getTypeRef()->getKind());

    if (arrayTypeExpressionSyntax->isTrivial()) {
      boundArrayTypeExpression->setElementType(
          arrayTypeExpressionSyntax->getElementTypeRef()->getKind());
    } else {
      boundArrayTypeExpression->setNonTrivialElementType(
          std::move(bindTypeExpression(
              arrayTypeExpressionSyntax->getNonTrivialElementTypeRef().get())));
    }

    for (const auto &size : arrayTypeExpressionSyntax->getDimensions()) {
      boundArrayTypeExpression->addDimension(
          std::move(bindExpression(size.get())));
    }

    return std::move(boundArrayTypeExpression);
  }
  case SyntaxKindUtils::SyntaxKind::PrimitiveTypeExpression: {
    return std::move(std::make_unique<BoundTypeExpression>(
        typeExpressionSyntax->getSourceLocation(),
        typeExpressionSyntax->getTypeRef()->getKind()));
  }
  case SyntaxKindUtils::SyntaxKind::ObjectTypeExpression: {
    ObjectTypeExpressionSyntax *objectTypeExpressionSyntax =
        static_cast<ObjectTypeExpressionSyntax *>(typeExpressionSyntax);

    std::unique_ptr<BoundObjectTypeExpression> boundObjectTypeExpression =
        std::make_unique<BoundObjectTypeExpression>(
            objectTypeExpressionSyntax->getSourceLocation(),
            objectTypeExpressionSyntax->getTypeRef()->getKind());

    boundObjectTypeExpression->setObjectTypeIdentifier(
        std::move(bindLiteralExpression(
            objectTypeExpressionSyntax->getObjectTypeIdentifierRef().get())));

    std::string name = objectTypeExpressionSyntax->getObjectTypeIdentifierRef()
                           ->getTokenPtr()
                           ->getText();

    //! Verify if this is a class or object type
    boundObjectTypeExpression->setTypeName(name);

    //? name -> class Type or Object Type

    BoundCustomTypeStatement *bCT = this->root->tryGetCustomType(name);

    if (!bCT && !this->root->tryGetClass(name)) {
      this->_diagnosticHandler->addDiagnostic(
          Diagnostic("Type " + name + " Not Found",
                     DiagnosticUtils::DiagnosticLevel::Error,
                     DiagnosticUtils::DiagnosticType::Semantic,
                     objectTypeExpressionSyntax->getObjectTypeIdentifierRef()
                         ->getTokenPtr()
                         ->getSourceLocation()));

      return std::move(boundObjectTypeExpression);
    }

    if (bCT) {
      boundObjectTypeExpression->setObjectTypeIdentifier(
          std::move(bindLiteralExpression(
              objectTypeExpressionSyntax->getObjectTypeIdentifierRef().get())));

      boundObjectTypeExpression->setTypeName(bCT->getTypeNameAsString());
    }

    return std::move(boundObjectTypeExpression);
  }
  default: {
    break;
  }
  }

  this->_diagnosticHandler->addDiagnostic(Diagnostic(
      "Invalid Type Expression", DiagnosticUtils::DiagnosticLevel::Error,
      DiagnosticUtils::DiagnosticType::Semantic,
      typeExpressionSyntax->getSourceLocation()));

  return nullptr;
}

std::unique_ptr<BoundStatement>
Binder::bindGlobalStatement(GlobalStatementSyntax *syntax) {
  return bindStatement(syntax->getStatementPtr().get());
}

Binder::Binder(std::unique_ptr<BoundScope> parent,
               FLowWing::DiagnosticHandler *diagnosticHandler) {
  BuiltInFunction::setupBuiltInFunctions();

  this->root = std::make_unique<BoundScope>(std::move(parent));
  this->_diagnosticHandler = diagnosticHandler;
}

void Binder::verifyAllCallsAreValid(Binder *binder) {
  // std::vector<BoundFunctionDeclaration *> functions =
  //     binder->root->getAllFunctions();

  // std::unordered_map<std::string, BoundFunctionDeclaration *>
  //     functionDefinitionMap;

  // for (const auto &function : functions) {
  //   functionDefinitionMap[function->getFunctionNameRef()] = function;
  // }

  // for (const auto &function : BuiltInFunction::getBuiltInFunctions()) {
  //   functionDefinitionMap[function->getFunctionNameRef()] = function.get();
  // }

  // for (BoundCallExpression *callExpression : binder->_callExpressions) {
  //   if (functionDefinitionMap.find(callExpression->getCallerNameRef()) ==
  //       functionDefinitionMap.end()) {
  //     binder->_diagnosticHandler->addDiagnostic(Diagnostic(
  //         "Function " + callExpression->getCallerNameRef() + " does not
  //         exist", DiagnosticUtils::DiagnosticLevel::Error,
  //         DiagnosticUtils::DiagnosticType::Semantic,
  //         callExpression->getCallerIdentifierPtr()->getLocation()));

  //     continue;
  //   }

  //   BoundFunctionDeclaration *fd =
  //       functionDefinitionMap.at(callExpression->getCallerNameRef());

  //   if (callExpression->getArgumentsRef().size() !=
  //       fd->getParametersRef().size()) {
  //     binder->_diagnosticHandler->addDiagnostic(Diagnostic(
  //         "Function " + callExpression->getCallerNameRef() + " requires " +
  //             std::to_string(fd->getParametersRef().size()) + " arguments",
  //         DiagnosticUtils::DiagnosticLevel::Error,
  //         DiagnosticUtils::DiagnosticType::Semantic,
  //         callExpression->getCallerIdentifierPtr()->getLocation()));

  //     continue;
  //   }
  // }
}

std::unique_ptr<BoundScopeGlobal>
Binder::bindGlobalScope(std::unique_ptr<BoundScopeGlobal> previousGlobalScope,
                        CompilationUnitSyntax *syntax,
                        FLowWing::DiagnosticHandler *diagnosticHandler) {
  std::unique_ptr<Binder> binder =
      std::make_unique<Binder>(nullptr, diagnosticHandler);
  std::unordered_map<std::string, std::any> prevVariablesValues;
  if (previousGlobalScope) {
    binder->root->variables = previousGlobalScope->variables;
    binder->root->functions = previousGlobalScope->functions;
    binder->root->customTypes = previousGlobalScope->customTypes;
    binder->root->classes = previousGlobalScope->classes;
    binder->root->modules = previousGlobalScope->modules;
    prevVariablesValues = previousGlobalScope->variablesValues;
  }
  std::unique_ptr<BoundBlockStatement> _globalBoundBlockStatement =
      std::make_unique<BoundBlockStatement>(DiagnosticUtils::SourceLocation(),
                                            true);

  std::vector<std::unique_ptr<MemberSyntax>> &members = syntax->getMembers();
  std::vector<uint64_t> functionsYetToDefine = {};
  for (int i = 0; i < members.size(); i++) {
    switch (members[i].get()->getKind()) {
    case SyntaxKindUtils::SyntaxKind::FunctionDeclarationSyntax: {
      FunctionDeclarationSyntax *functionDeclarationSyntax =
          (FunctionDeclarationSyntax *)members[i].get();

      if (!functionDeclarationSyntax->isOnlyDeclared()) {
        functionDeclarationSyntax->setIsOnlyDeclared(true);
        functionsYetToDefine.push_back(i);
      }

      std::unique_ptr<BoundStatement> _statement =
          std::move(binder->bindFunctionDeclaration(functionDeclarationSyntax));
      _globalBoundBlockStatement->addStatement(std::move(_statement));
      break;
    }
    case SyntaxKindUtils::SyntaxKind::GlobalStatement: {
      std::unique_ptr<BoundStatement> _statement =
          std::move(binder->bindGlobalStatement(
              (GlobalStatementSyntax *)members[i].get()));

      _globalBoundBlockStatement->addStatement(std::move(_statement));
      break;
    }
    default:
      throw "Unexpected global member";
      break;
    }
  }

  for (int i = 0; i < functionsYetToDefine.size(); i++) {
    FunctionDeclarationSyntax *functionDeclarationSyntax =
        (FunctionDeclarationSyntax *)members[functionsYetToDefine[i]].get();

    functionDeclarationSyntax->setIsOnlyDeclared(false);

    std::unique_ptr<BoundStatement> _statement =
        std::move(binder->bindFunctionDeclaration(functionDeclarationSyntax));
    _globalBoundBlockStatement->addStatement(std::move(_statement));
  }

  verifyAllCallsAreValid(binder.get());

  // if (previousGlobalScope != nullptr) {
  //   diagnosticHandler->addParentDiagnostics(
  //       previousGlobalScope->_diagnosticHandler);
  // }

  return std::make_unique<BoundScopeGlobal>(
      std::move(previousGlobalScope), binder->root->variables,
      prevVariablesValues, binder->root->functions, binder->root->customTypes,
      binder->root->classes, binder->root->modules, diagnosticHandler,
      std::move(_globalBoundBlockStatement));
}

// Utils

auto Binder::getMemberMap(
    const std::vector<std::unique_ptr<MemberSyntax>> &members,
    CompilationUnitSyntax *nestedCompilationUnit)
    -> std::unordered_map<std::string, int> {
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
        memberMap
            [customTypeStatement->getTypeNameRef()->getTokenPtr()->getText()] =
                1;
      }
    }
  }

  return memberMap;
}
