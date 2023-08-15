
#include "Binder.h"

std::unique_ptr<BoundStatement> Binder::bindExpressionStatement(
    ExpressionStatementSyntax *expressionStatement) {
  ExpressionSyntax *exps = expressionStatement->getExpression().get();

  std::string lineAndColumn = exps->getLineNumberAndColumn();
  std::unique_ptr<BoundExpression> boundExpression =
      std::move(bindExpression(exps));

  return std::make_unique<BoundExpressionStatement>(lineAndColumn,
                                                    std::move(boundExpression));
}

std::unique_ptr<BoundStatement>
Binder::bindBlockStatement(BlockStatementSyntax *blockStatement) {

  this->root = std::make_unique<BoundScope>(std::move(this->root));

  std::unique_ptr<BoundBlockStatement> boundBlockStatement =
      std::make_unique<BoundBlockStatement>(
          blockStatement->getLineNumberAndColumn(), false);

  for (int i = 0; i < blockStatement->getStatements().size(); i++) {

    std::unique_ptr<BoundStatement> statement =
        std::move(bindStatement(blockStatement->getStatements()[i].get()));

    boundBlockStatement->addStatement(std::move(statement));
  }

  this->root = std::move(this->root->parent);

  return std::move(boundBlockStatement);
}

std::unique_ptr<BoundStatement> Binder::bindVariableDeclaration(
    VariableDeclarationSyntax *variableDeclaration) {

  std::unique_ptr<BoundExpression> boundInitializerExpression =
      std::move(bindExpression(variableDeclaration->getInitializer().get()));

  std::string variable_str = std::any_cast<std::string>(
      variableDeclaration->getIdentifier()->getValue());

  bool isConst = variableDeclaration->getKeyword()->getKind() ==
                 SyntaxKindUtils::SyntaxKind::ConstKeyword;

  if (!root->tryDeclareVariable(variable_str,
                                Utils::Variable(nullptr, isConst))) {
    this->logs.push_back(Utils::getLineNumberAndPosition(
                             variableDeclaration->getIdentifier().get()) +
                         "Error: Variable " + variable_str + " already exists");
  }

  return std::make_unique<BoundVariableDeclaration>(
      variableDeclaration->getLineNumberAndColumn(), variable_str, isConst,
      std::move(boundInitializerExpression));
}

std::unique_ptr<BoundStatement>
Binder::bindIfStatement(IfStatementSyntax *ifStatement) {
  std::unique_ptr<BoundExpression> boundCondition =
      std::move(bindExpression(ifStatement->getCondition().get()));

  std::unique_ptr<BoundStatement> boundThenStatement =
      std::move(bindStatement(ifStatement->getStatement().get()));

  std::unique_ptr<BoundStatement> boundElseStatement = nullptr;

  if (ifStatement->getElseClause() != nullptr) {
    boundElseStatement = std::move(
        bindStatement(ifStatement->getElseClause()->getStatement().get()));
  }

  return std::make_unique<BoundIfStatement>(
      ifStatement->getLineNumberAndColumn(), std::move(boundCondition),
      std::move(boundThenStatement), std::move(boundElseStatement));
}

std::unique_ptr<BoundStatement>
Binder::bindWhileStatement(WhileStatementSyntax *whileStatement) {

  this->root = std::make_unique<BoundScope>(std::move(this->root));
  this->root->makeBreakableAndContinuable();

  std::unique_ptr<BoundExpression> boundCondition =
      std::move(bindExpression(whileStatement->getCondition().get()));

  std::unique_ptr<BoundStatement> boundBody =
      bindStatement(whileStatement->getBody().get());

  this->root = std::move(this->root->parent);

  return std::make_unique<BoundWhileStatement>(
      whileStatement->getLineNumberAndColumn(), std::move(boundCondition),
      std::move(boundBody));
}

std::unique_ptr<BoundStatement>
Binder::bindForStatement(ForStatementSyntax *forStatement) {
  this->root = std::make_unique<BoundScope>(std::move(this->root));
  this->root->makeBreakableAndContinuable();
  std::unique_ptr<BoundStatement> boundIntializer =
      std::move(bindStatement(forStatement->getInitialization().get()));

  std::unique_ptr<BoundExpression> boundUpperBound =
      std::move(bindExpression(forStatement->getUpperBound().get()));

  std::unique_ptr<BoundStatement> boundBody =
      std::move(bindStatement(forStatement->getStatement().get()));

  this->root = std::move(this->root->parent);
  return std::make_unique<BoundForStatement>(
      forStatement->getLineNumberAndColumn(), std::move(boundIntializer),
      std::move(boundUpperBound), std::move(boundBody));
}

std::unique_ptr<BoundStatement>
Binder::bindBreakStatement(BreakStatementSyntax *breakStatement) {
  if (!this->root->isBreakable()) {
    this->logs.push_back(Utils::getLineNumberAndPosition(
                             breakStatement->getBreakKeyword().get()) +
                         "Error: Break statement outside of loop");
  }
  return std::make_unique<BoundBreakStatement>(
      breakStatement->getLineNumberAndColumn());
}

std::unique_ptr<BoundStatement>
Binder::bindContinueStatement(ContinueStatementSyntax *continueStatement) {
  if (!this->root->isContinuable()) {
    this->logs.push_back(Utils::getLineNumberAndPosition(
                             continueStatement->getContinueKeyword().get()) +
                         "Error: Continue statement outside of loop");
  }
  return std::make_unique<BoundContinueStatement>(
      continueStatement->getLineNumberAndColumn());
}

std::unique_ptr<BoundStatement>
Binder::bindReturnStatement(ReturnStatementSyntax *returnStatement) {
  std::unique_ptr<BoundExpression> boundExpression = nullptr;
  if (!this->root->isInFunction()) {
    this->logs.push_back(Utils::getLineNumberAndPosition(
                             returnStatement->getReturnKeyword().get()) +
                         "Error: Return statement outside of function");
  } else {
    ExpressionSyntax *returnExpression = returnStatement->getExpression().get();

    if (returnExpression) {
      boundExpression = std::move(bindExpression(returnExpression));
    }
  }

  return std::make_unique<BoundReturnStatement>(
      returnStatement->getLineNumberAndColumn(), std::move(boundExpression));
}

std::unique_ptr<BoundStatement> Binder::bindStatement(StatementSyntax *syntax) {
  ;

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
  case SyntaxKindUtils::SyntaxKind::BreakKeyword: {
    return std::move(bindBreakStatement((BreakStatementSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::ContinueKeyword: {
    return std::move(bindContinueStatement((ContinueStatementSyntax *)syntax));
  }
  case SyntaxKindUtils::SyntaxKind::ReturnStatement: {
    return std::move(bindReturnStatement((ReturnStatementSyntax *)syntax));
  }
  default:
    throw "Unexpected syntax";
  }
}

std::unique_ptr<BoundExpression> Binder::bindLiteralExpression(
    LiteralExpressionSyntax<std::any> *literalSyntax) {
  std::any value = literalSyntax->getValue();
  return std::make_unique<BoundLiteralExpression<std::any>>(
      literalSyntax->getLineNumberAndColumn(), value);
}

std::unique_ptr<BoundExpression>
Binder::bindunaryExpression(UnaryExpressionSyntax *unaryExpression) {
  std::unique_ptr<BoundExpression> boundOperand =
      std::move(bindExpression(unaryExpression->getOperand().get()));
  BinderKindUtils::BoundUnaryOperatorKind op =
      BinderKindUtils::getUnaryOperatorKind(
          unaryExpression->getOperatorToken()->getKind());

  return std::make_unique<BoundUnaryExpression>(
      unaryExpression->getLineNumberAndColumn(), op, std::move(boundOperand));
}

std::unique_ptr<BoundExpression>
Binder::bindBinaryExpression(BinaryExpressionSyntax *binaryExpression) {
  std::unique_ptr<BoundExpression> boundLeft =
      std::move(bindExpression(binaryExpression->getLeft().get()));
  std::unique_ptr<BoundExpression> boundRight =
      std::move(bindExpression(binaryExpression->getRight().get()));
  BinderKindUtils::BoundBinaryOperatorKind op =
      BinderKindUtils::getBinaryOperatorKind(
          binaryExpression->getOperatorToken()->getKind());

  return std::make_unique<BoundBinaryExpression>(
      binaryExpression->getLineNumberAndColumn(), std::move(boundLeft), op,
      std::move(boundRight));
}

std::unique_ptr<BoundExpression> Binder::bindAssignmentExpression(
    AssignmentExpressionSyntax *assignmentExpression) {
  std::unique_ptr<BoundLiteralExpression<std::any>> boundIdentifierExpression(
      (BoundLiteralExpression<std::any> *)bindExpression(
          assignmentExpression->getLeft().get())
          .release());

  std::string variable_str =
      Utils::convertAnyToString(boundIdentifierExpression->getValue());

  BinderKindUtils::BoundBinaryOperatorKind op =
      BinderKindUtils::getBinaryOperatorKind(
          assignmentExpression->getOperatorToken()->getKind());

  if (!root->tryLookupVariable(variable_str)) {
    this->logs.push_back(Utils::getLineNumberAndPosition(
                             assignmentExpression->getOperatorToken().get()) +
                         "Error: Can not assign to undeclared variable " +
                         variable_str);
    return std::move(boundIdentifierExpression);
  }

  if (root->variables[variable_str].isConst) {
    this->logs.push_back(Utils::getLineNumberAndPosition(
                             assignmentExpression->getOperatorToken().get()) +
                         "Error: Can not assign to const variable " +
                         variable_str);
    return std::move(boundIdentifierExpression);
  }

  std::unique_ptr<BoundExpression> boundRight =
      bindExpression(assignmentExpression->getRight().get());
  return std::make_unique<BoundAssignmentExpression>(
      assignmentExpression->getLineNumberAndColumn(),
      std::move(boundIdentifierExpression), op, std::move(boundRight));
}

std::unique_ptr<BoundExpression>
Binder::bindVariableExpression(VariableExpressionSyntax *variableExpression) {

  std::unique_ptr<BoundLiteralExpression<std::any>> boundIdentifierExpression(
      (BoundLiteralExpression<std::any>
           *)(bindExpression(variableExpression->getIdentifier().get())
                  .release()));

  std::string variable_str =
      Utils::convertAnyToString(boundIdentifierExpression->getValue());

  if (!root->tryLookupVariable(variable_str)) {
    this->logs.push_back(
        Utils::getLineNumberAndPosition(
            variableExpression->getIdentifier()->getToken().get()) +
        "Error: Variable " + variable_str + " does not exist");
    return std::move(boundIdentifierExpression);
  }
  return std::make_unique<BoundVariableExpression>(
      variableExpression->getLineNumberAndColumn(),
      std::move(boundIdentifierExpression));
}

std::unique_ptr<BoundExpression>
Binder::bindCallExpression(CallExpressionSyntax *callExpression) {
  std::unique_ptr<BoundLiteralExpression<std::any>> boundIdentifier(
      (BoundLiteralExpression<std::any> *)bindExpression(
          (callExpression->getIdentifier().get()))
          .release());

  Utils::FunctionSymbol functionSymbol =
      Utils::BuiltInFunctions::getFunctionSymbol(
          Utils::convertAnyToString(boundIdentifier->getValue()));

  if (functionSymbol.name == "") {
    std::vector<Utils::FunctionParameterSymbol> parameters;

    for (int i = 0; i < callExpression->getArguments().size(); i++) {
      parameters.push_back(
          Utils::FunctionParameterSymbol(std::to_string(i), false));
    }

    functionSymbol = Utils::FunctionSymbol(
        Utils::convertAnyToString(boundIdentifier->getValue()), parameters,
        Utils::type::VOID);
  }

  std::unique_ptr<BoundCallExpression> boundCallExpression =
      std::make_unique<BoundCallExpression>(
          callExpression->getLineNumberAndColumn(), std::move(boundIdentifier),
          functionSymbol);

  for (int i = 0; i < callExpression->getArguments().size(); i++) {
    boundCallExpression->addArgument(
        std::move(bindExpression(callExpression->getArguments()[i].get())));
  }

  this->_callExpressions.push_back(boundCallExpression.get());
  return std::move(boundCallExpression);
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
  case SyntaxKindUtils::SyntaxKind::VariableExpression: {
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
  default:
    throw "Unexpected syntax";
  }
  return nullptr;
}

std::unique_ptr<BoundStatement>
Binder::bindFunctionDeclaration(FunctionDeclarationSyntax *syntax) {
  std::vector<Utils::FunctionParameterSymbol> parameters;

  this->root = std::make_unique<BoundScope>(std::move(this->root));

  std::string function_name = syntax->getIdentifierToken()->getText();

  for (int i = 0; i < syntax->getParameters().size(); i++) {
    std::string variable_str =
        syntax->getParameters()[i]->getIdentifierToken()->getText();
    if (!this->root->tryDeclareVariable(variable_str,
                                        Utils::Variable(nullptr, false))) {
      this->logs.push_back(
          Utils::getLineNumberAndPosition(
              syntax->getParameters()[i]->getIdentifierToken().get()) +
          "Error: Parameter " + variable_str + " already declared");
    }

    parameters.push_back(Utils::FunctionParameterSymbol(
        syntax->getParameters()[i]->getIdentifierToken()->getText(), false));
  }

  Utils::FunctionSymbol functionSymbol =
      Utils::FunctionSymbol(function_name, parameters, Utils::type::VOID);

  this->root->incrementFunctionCount();

  std::unique_ptr<BoundBlockStatement> boundBody(
      (BoundBlockStatement *)bindStatement(syntax->getBody().get()).release());
  std::unique_ptr<BoundFunctionDeclaration> fd =
      std::make_unique<BoundFunctionDeclaration>(
          syntax->getLineNumberAndColumn(), functionSymbol,
          std::move(boundBody));

  this->root->decrementFunctionCount();

  if (!this->root->tryDeclareFunction(functionSymbol.name, fd.get())) {
    this->logs.push_back(
        Utils::getLineNumberAndPosition(syntax->getFunctionKeyword().get()) +
        "Error: Function " + functionSymbol.name + " already declared");
  }
  this->root = std::move(this->root->parent);
  return std::move(fd);
}

std::unique_ptr<BoundStatement>
Binder::bindGlobalStatement(GlobalStatementSyntax *syntax) {

  return bindStatement(syntax->getStatement().get());
}

Binder::Binder(std::unique_ptr<BoundScope> parent) {
  this->root = std::make_unique<BoundScope>(std::move(parent));
}

void Binder::verifyAllCallsAreValid(Binder *binder) {

  std::vector<BoundFunctionDeclaration *> functions =
      binder->root->getAllFunctions();

  std::unordered_map<std::string, Utils::FunctionSymbol> functionDefinitionMap;

  for (auto &function : functions) {

    functionDefinitionMap[function->getFunctionSymbol().name] =
        function->getFunctionSymbol();
  }

  std::vector<Utils::FunctionSymbol> builtInFunctions =
      Utils::BuiltInFunctions::getAllFunctions();

  for (auto &function : builtInFunctions) {
    functionDefinitionMap[function.name] = function;
  }

  for (const auto &callExpression : binder->_callExpressions) {
    Utils::FunctionSymbol functionSymbol = callExpression->getFunctionSymbol();

    if (functionDefinitionMap.find(functionSymbol.name) ==
        functionDefinitionMap.end()) {
      binder->logs.push_back(
          callExpression->getCallerIdentifier()->getLineNumberAndColumn() +
          "Error: Function " + functionSymbol.name + " does not exist");
      continue;
    }

    Utils::FunctionSymbol functionDefinition =
        functionDefinitionMap.at(functionSymbol.name);

    if (functionSymbol.parameters.size() !=
        functionDefinition.parameters.size()) {
      binder->logs.push_back(
          callExpression->getCallerIdentifier()->getLineNumberAndColumn() +
          "Error: Function " + functionSymbol.name + " requires " +
          std::to_string(functionDefinition.parameters.size()) + " arguments");
      continue;
    }
  }
}

std::unique_ptr<BoundScopeGlobal>
Binder::bindGlobalScope(std::unique_ptr<BoundScopeGlobal> previousGlobalScope,
                        CompilationUnitSyntax *syntax) {

  std::unique_ptr<Binder> binder = std::make_unique<Binder>(nullptr);

  if (previousGlobalScope) {

    binder->root->variables = previousGlobalScope->variables;
    binder->root->functions = previousGlobalScope->functions;
  }

  std::unique_ptr<BoundBlockStatement> _globalBoundBlockStatement =
      std::make_unique<BoundBlockStatement>("", true);

  std::vector<std::unique_ptr<MemberSyntax>> &members = syntax->getMembers();

  for (int i = 0; i < members.size(); i++) {
    switch (members[i].get()->getKind()) {
    case SyntaxKindUtils::SyntaxKind::FunctionDeclarationSyntax: {

      std::unique_ptr<BoundStatement> _statement =
          std::move(binder->bindFunctionDeclaration(
              (FunctionDeclarationSyntax *)members[i].get()));
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

  verifyAllCallsAreValid(binder.get());

  std::vector<std::string> _logs;

  for (std::string log : binder->logs) {
    _logs.push_back(log);
  }

  if (previousGlobalScope != nullptr) {
    for (std::string log : previousGlobalScope->logs) {
      _logs.push_back(log);
    }
  }

  return std::make_unique<BoundScopeGlobal>(
      std::move(previousGlobalScope), binder->root->variables,
      binder->root->functions, _logs, std::move(_globalBoundBlockStatement));
}
