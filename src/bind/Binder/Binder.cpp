
#include "Binder.h"

std::shared_ptr<BoundStatement>
Binder::bindStatement(std::shared_ptr<StatementSyntax> syntax) {
  switch (syntax->getKind()) {
  case SyntaxKindUtils::SyntaxKind::ExpressionStatement: {
    std::shared_ptr<ExpressionStatementSyntax> expressionStatement =
        std::static_pointer_cast<ExpressionStatementSyntax>(syntax);
    std::shared_ptr<BoundExpression> expression =
        bindExpression(expressionStatement->getExpression());
    return std::make_shared<BoundExpressionStatement>(
        expressionStatement->getExpression()->getLineNumberAndColumn(),
        expression);
  }
  case SyntaxKindUtils::SyntaxKind::BlockStatement: {
    std::shared_ptr<BlockStatementSyntax> blockStatement =
        std::static_pointer_cast<BlockStatementSyntax>(syntax);

    this->root = std::make_shared<BoundScope>(this->root);

    std::vector<std::shared_ptr<BoundStatement>> statements;
    for (int i = 0; i < blockStatement->getStatements().size(); i++) {

      std::shared_ptr<BoundStatement> statement =
          bindStatement(blockStatement->getStatements()[i]);
      statements.push_back(statement);
    }

    std::shared_ptr<BoundStatement> statement =
        std::make_shared<BoundBlockStatement>(
            blockStatement->getLineNumberAndColumn(), statements, false);

    this->root = this->root->parent;

    return statement;
  }
  case SyntaxKindUtils::SyntaxKind::VariableDeclaration: {
    std::shared_ptr<VariableDeclarationSyntax> variableDeclaration =
        std::static_pointer_cast<VariableDeclarationSyntax>(syntax);
    std::shared_ptr<BoundExpression> initializer =
        bindExpression(variableDeclaration->getInitializer());

    std::string variable_str = std::any_cast<std::string>(
        variableDeclaration->getIdentifier()->getValue());
    bool isConst = variableDeclaration->getKeyword()->getKind() ==
                   SyntaxKindUtils::SyntaxKind::ConstKeyword;

    if (!root->tryDeclareVariable(variable_str,
                                  Utils::Variable(nullptr, isConst))) {
      this->logs.push_back(Utils::getLineNumberAndPosition(
                               variableDeclaration->getIdentifier().get()) +
                           "Error: Variable " + variable_str +
                           " already exists");
    }

    return std::make_shared<BoundVariableDeclaration>(
        variableDeclaration->getLineNumberAndColumn(), variable_str, isConst,
        initializer);
  }
  case SyntaxKindUtils::SyntaxKind::IfStatement: {
    std::shared_ptr<IfStatementSyntax> ifStatement =
        std::static_pointer_cast<IfStatementSyntax>(syntax);
    std::shared_ptr<BoundExpression> condition =
        bindExpression(ifStatement->getCondition());
    std::shared_ptr<BoundStatement> thenStatement = bindStatement(
        (std::shared_ptr<StatementSyntax>)(ifStatement->getStatement()));
    std::shared_ptr<BoundStatement> elseStatement = nullptr;
    if (ifStatement->getElseClause() != nullptr) {
      elseStatement =
          bindStatement(ifStatement->getElseClause()->getStatement());
    }
    return std::make_shared<BoundIfStatement>(
        ifStatement->getLineNumberAndColumn(), condition, thenStatement,
        elseStatement);
  }
  case SyntaxKindUtils::SyntaxKind::WhileStatement: {
    this->root = std::make_shared<BoundScope>(this->root);
    this->root->makeBreakableAndContinuable();

    std::shared_ptr<WhileStatementSyntax> whileStatement =
        std::static_pointer_cast<WhileStatementSyntax>(syntax);

    std::shared_ptr<BoundExpression> condition =
        bindExpression(whileStatement->getCondition());
    std::shared_ptr<BoundStatement> body = bindStatement(
        (std::shared_ptr<StatementSyntax>)whileStatement->getBody());

    this->root = this->root->parent;
    return std::make_shared<BoundWhileStatement>(
        whileStatement->getLineNumberAndColumn(), condition, body);
  }

  case SyntaxKindUtils::SyntaxKind::ForStatement: {
    std::shared_ptr<ForStatementSyntax> forStatement =
        std::static_pointer_cast<ForStatementSyntax>(syntax);
    this->root = std::make_shared<BoundScope>(this->root);
    this->root->makeBreakableAndContinuable();
    std::shared_ptr<BoundStatement> intializer =
        (std::shared_ptr<BoundStatement>)bindStatement(
            (std::shared_ptr<StatementSyntax>)forStatement->getInitialization()
                .get());

    std::shared_ptr<BoundExpression> upperBound =
        bindExpression(forStatement->getUpperBound());

    std::shared_ptr<BoundStatement> body = bindStatement(
        (std::shared_ptr<StatementSyntax>)forStatement->getStatement());

    this->root = this->root->parent;
    return std::make_shared<BoundForStatement>(
        forStatement->getLineNumberAndColumn(), intializer, upperBound, body);
  }
  case SyntaxKindUtils::SyntaxKind::BreakKeyword: {
    std::shared_ptr<BreakStatementSyntax> breakStatement =
        std::static_pointer_cast<BreakStatementSyntax>(syntax);
    if (!this->root->isBreakable()) {
      this->logs.push_back(Utils::getLineNumberAndPosition(
                               breakStatement->getBreakKeyword().get()) +
                           "Error: Break statement outside of loop");
    }
    return std::make_shared<BoundBreakStatement>(
        breakStatement->getLineNumberAndColumn());
  }
  case SyntaxKindUtils::SyntaxKind::ContinueKeyword: {
    std::shared_ptr<ContinueStatementSyntax> continueStatement =
        std::static_pointer_cast<ContinueStatementSyntax>(syntax);
    if (!this->root->isContinuable()) {
      this->logs.push_back(Utils::getLineNumberAndPosition(
                               continueStatement->getContinueKeyword().get()) +
                           "Error: Continue statement outside of loop");
    }
    return std::make_shared<BoundContinueStatement>(
        continueStatement->getLineNumberAndColumn());
  }

  case SyntaxKindUtils::SyntaxKind::ReturnStatement: {

    std::shared_ptr<ReturnStatementSyntax> returnStatement =
        std::static_pointer_cast<ReturnStatementSyntax>(syntax);

    std::shared_ptr<BoundExpression> expression = nullptr;
    if (!this->root->isInFunction()) {
      this->logs.push_back(Utils::getLineNumberAndPosition(
                               returnStatement->getReturnKeyword().get()) +
                           "Error: Return statement outside of function");
    } else {
      std::shared_ptr<ExpressionSyntax> returnExpression =
          returnStatement->getExpression();

      if (returnExpression) {
        expression = bindExpression(returnStatement->getExpression());
      }
    }

    return std::make_shared<BoundReturnStatement>(
        returnStatement->getLineNumberAndColumn(), expression);
  }
  default:
    throw "Unexpected syntax";
  }
}

std::shared_ptr<BoundExpression>
Binder::bindExpression(std::shared_ptr<ExpressionSyntax> syntax) {
  switch (syntax->getKind()) {
  case SyntaxKindUtils::SyntaxKind::LiteralExpression: {
    std::shared_ptr<LiteralExpressionSyntax<std::any>> literalSyntax =
        std::static_pointer_cast<LiteralExpressionSyntax<std::any>>(syntax);
    std::any value = literalSyntax->getValue();
    return std::make_shared<BoundLiteralExpression<std::any>>(
        literalSyntax->getLineNumberAndColumn(), value);
  }
  case SyntaxKindUtils::SyntaxKind::UnaryExpression: {
    std::shared_ptr<UnaryExpressionSyntax> unaryExpression =
        std::static_pointer_cast<UnaryExpressionSyntax>(syntax);
    std::shared_ptr<BoundExpression> operand =
        bindExpression(unaryExpression->getOperand());
    BinderKindUtils::BoundUnaryOperatorKind op;

    switch (unaryExpression->getOperatorToken()->getKind()) {
    case SyntaxKindUtils::SyntaxKind::PlusToken:
      op = BinderKindUtils::BoundUnaryOperatorKind::Identity;
      break;
    case SyntaxKindUtils::SyntaxKind::MinusToken:
      op = BinderKindUtils::BoundUnaryOperatorKind::Negation;
      break;
    case SyntaxKindUtils::SyntaxKind::BangToken:
      op = BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation;
      break;
    case SyntaxKindUtils::SyntaxKind::TildeToken:
      op = BinderKindUtils::BoundUnaryOperatorKind::BitwiseNegation;
      break;
    default:
      throw "Unexpected unary operator";
    }
    return std::make_shared<BoundUnaryExpression>(
        unaryExpression->getLineNumberAndColumn(), op, operand);
  }
  case SyntaxKindUtils::SyntaxKind::BinaryExpression: {
    std::shared_ptr<BinaryExpressionSyntax> binaryExpression =
        std::static_pointer_cast<BinaryExpressionSyntax>(syntax);
    std::shared_ptr<BoundExpression> left =
        bindExpression(binaryExpression->getLeft());
    std::shared_ptr<BoundExpression> right =
        bindExpression(binaryExpression->getRight());
    BinderKindUtils::BoundBinaryOperatorKind op;

    // if (left->getType() != typeid(int) || right->getType() != typeid(int)) {
    //   this->logs.push_back("Binary operator can only be applied to numbers");
    //   return left;
    // }

    switch (binaryExpression->getOperatorToken()->getKind()) {
    case SyntaxKindUtils::SyntaxKind::PlusToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Addition;
      break;
    case SyntaxKindUtils::SyntaxKind::MinusToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Subtraction;
      break;
    case SyntaxKindUtils::SyntaxKind::StarToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Multiplication;
      break;
    case SyntaxKindUtils::SyntaxKind::SlashToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Division;
      break;
    case SyntaxKindUtils::SyntaxKind::PercentToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Modulus;
      break;
    case SyntaxKindUtils::SyntaxKind::EqualsEqualsToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Equals;
      break;
    case SyntaxKindUtils::SyntaxKind::BangEqualsToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::NotEquals;
      break;
    case SyntaxKindUtils::SyntaxKind::AmpersandAmpersandToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd;
      break;
    case SyntaxKindUtils::SyntaxKind::PipePipeToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::LogicalOr;
      break;
    case SyntaxKindUtils::SyntaxKind::LessToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Less;
      break;
    case SyntaxKindUtils::SyntaxKind::LessOrEqualsToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals;
      break;
    case SyntaxKindUtils::SyntaxKind::GreaterToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Greater;
      break;
    case SyntaxKindUtils::SyntaxKind::GreaterOrEqualsToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals;
      break;
    case SyntaxKindUtils::SyntaxKind::EqualsToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Assignment;
      break;
    case SyntaxKindUtils::SyntaxKind::AmpersandToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd;
      break;
    case SyntaxKindUtils::SyntaxKind::PipeToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr;
      break;
    case SyntaxKindUtils::SyntaxKind::CaretToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor;
      break;
    default:
      throw "Unexpected binary operator";
    }
    return std::make_shared<BoundBinaryExpression>(
        binaryExpression->getLineNumberAndColumn(), left, op, right);
  }

    // Assignment Expression

  case SyntaxKindUtils::SyntaxKind::AssignmentExpression: {
    std::shared_ptr<AssignmentExpressionSyntax> assignmentExpression =
        std::static_pointer_cast<AssignmentExpressionSyntax>(syntax);
    std::shared_ptr<BoundLiteralExpression<std::any>> identifierExpression =
        std::static_pointer_cast<BoundLiteralExpression<std::any>>(
            bindExpression(assignmentExpression->getLeft()));
    std::string variable_str =
        std::any_cast<std::string>(identifierExpression->getValue());
    BinderKindUtils::BoundBinaryOperatorKind op;
    if (!root->tryLookupVariable(variable_str)) {
      this->logs.push_back(Utils::getLineNumberAndPosition(
                               assignmentExpression->getOperatorToken().get()) +
                           "Error: Can not assign to undeclared variable " +
                           variable_str);
      return identifierExpression;
    }
    if (root->variables[variable_str].isConst) {
      this->logs.push_back(Utils::getLineNumberAndPosition(
                               assignmentExpression->getOperatorToken().get()) +
                           "Error: Can not assign to const variable " +
                           variable_str);
      return identifierExpression;
    }

    switch (assignmentExpression->getOperatorToken()->getKind()) {
    case SyntaxKindUtils::SyntaxKind::EqualsToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Assignment;
      break;
    default:
      throw "Unexpected assignment operator";
    }
    std::shared_ptr<BoundExpression> right =
        bindExpression(assignmentExpression->getRight());
    return std::make_shared<BoundAssignmentExpression>(
        assignmentExpression->getLineNumberAndColumn(), identifierExpression,
        op, right);
  }

  case SyntaxKindUtils::SyntaxKind::VariableExpression: {
    std::shared_ptr<VariableExpressionSyntax> variableExpressionSyntax =
        std::static_pointer_cast<VariableExpressionSyntax>(syntax);

    std::shared_ptr<BoundLiteralExpression<std::any>> identifierExpression =
        std::static_pointer_cast<BoundLiteralExpression<std::any>>(
            bindExpression(variableExpressionSyntax->getIdentifier()));
    std::string variable_str =
        std::any_cast<std::string>(identifierExpression->getValue());
    if (!root->tryLookupVariable(variable_str)) {
      this->logs.push_back(
          Utils::getLineNumberAndPosition(
              variableExpressionSyntax->getIdentifier()->getToken().get()) +
          "Error: Variable " + variable_str + " does not exist");
      return identifierExpression;
    }
    return std::make_shared<BoundVariableExpression>(
        variableExpressionSyntax->getLineNumberAndColumn(),
        identifierExpression);
  }
  case SyntaxKindUtils::SyntaxKind::ParenthesizedExpression: {
    std::shared_ptr<ParenthesizedExpressionSyntax> parenthesizedExpression =
        std::static_pointer_cast<ParenthesizedExpressionSyntax>(syntax);
    return bindExpression(parenthesizedExpression->getExpression());
  }
  case SyntaxKindUtils::SyntaxKind::CallExpression: {
    std::shared_ptr<CallExpressionSyntax> callExpression =
        std::static_pointer_cast<CallExpressionSyntax>(syntax);
    std::shared_ptr<BoundLiteralExpression<std::any>> identifier =
        std::static_pointer_cast<BoundLiteralExpression<std::any>>(
            bindExpression(callExpression->getIdentifier()));

    Utils::FunctionSymbol functionSymbol =
        Utils::BuiltInFunctions::getFunctionSymbol(
            std::any_cast<std::string>(identifier->getValue()));

    if (functionSymbol.name == "") {
      std::vector<Utils::FunctionParameterSymbol> parameters;

      for (int i = 0; i < callExpression->getArguments().size(); i++) {
        parameters.push_back(
            Utils::FunctionParameterSymbol(std::to_string(i), false));
      }

      functionSymbol = Utils::FunctionSymbol(
          std::any_cast<std::string>(identifier->getValue()), parameters,
          Utils::type::VOID);
    }

    // if (!this->root->tryLookupFunction(
    //         Utils::convertAnyToString(identifier->getValue()))) {
    //   this->logs.push_back(Utils::getLineNumberAndPosition(
    //                            callExpression->getIdentifier()->getToken()) +
    //                        "Error: Function " +
    //                        std::any_cast<std::string>(identifier->getValue())
    //                        + " does not exist");
    //   return identifier;
    // }

    // if (functionSymbol.kind == Utils::SymbolKind::None) {
    //   this->logs.push_back(Utils::getLineNumberAndPosition(
    //                      callExpression->getIdentifier()->getToken()) +
    //                  "Error: Function " +
    //                  callExpression->getIdentifier()->getToken()->getText()
    //                  + " does not exist");
    //   return identifier;
    // }

    // if (callExpression->getArguments().size() != functionSymbol.arity()) {
    //   this->logs.push_back("Error: Function " +
    //                  std::any_cast<std::string>(identifier->getValue()) +
    //                  " requires " + std::to_string(functionSymbol.arity())
    //                  + " arguments");
    //   return identifier;
    // }

    std::vector<std::shared_ptr<BoundExpression>> arguments;
    for (int i = 0; i < callExpression->getArguments().size(); i++) {
      arguments.push_back(bindExpression(callExpression->getArguments()[i]));
    }

    std::shared_ptr<BoundCallExpression> boundCallExpression =
        std::make_shared<BoundCallExpression>(
            callExpression->getLineNumberAndColumn(), identifier,
            functionSymbol, arguments);
    this->_callExpressions.push_back(boundCallExpression);
    return boundCallExpression;
  }
  default:
    throw "Unexpected syntax";
  }
}
std::shared_ptr<BoundScope>
Binder::CreateParentScope(std::shared_ptr<BoundScopeGlobal> parent) {
  // std::stack<std::shared_ptr<BoundScopeGlobal>> stack =
  // std::stack<std::shared_ptr<BoundScopeGlobal>>();

  // while (parent != nullptr) {
  //   stack.push(parent);
  //   parent = parent->previous;
  // }

  // std::shared_ptr<BoundScope >current = nullptr;

  // while (!stack.empty()) {
  //   parent = stack.top();
  //   stack.pop();
  //   std::shared_ptr<BoundScope >scope = new BoundScope(current);

  //   for (auto &pair : parent->variables) {
  //     scope->variables[pair.first] = pair.second;
  //   }

  //   current = scope;
  // }

  // return current;
  return nullptr;
}

std::shared_ptr<BoundStatement> Binder::bindFunctionDeclaration(
    std::shared_ptr<FunctionDeclarationSyntax> syntax) {
  std::vector<Utils::FunctionParameterSymbol> parameters;

  this->root = std::make_shared<BoundScope>(this->root);

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
  std::shared_ptr<BoundBlockStatement> body =
      std::static_pointer_cast<BoundBlockStatement>(
          bindStatement(syntax->getBody()));
  std::shared_ptr<BoundFunctionDeclaration> fd =
      std::make_shared<BoundFunctionDeclaration>(
          syntax->getLineNumberAndColumn(), functionSymbol, body);

  this->root->decrementFunctionCount();

  if (!this->root->tryDeclareFunction(functionSymbol.name, fd)) {
    this->logs.push_back(
        Utils::getLineNumberAndPosition(syntax->getFunctionKeyword().get()) +
        "Error: Function " + functionSymbol.name + " already declared");
  }
  this->root = this->root->parent;
  return fd;
}

std::shared_ptr<BoundStatement>
Binder::bindGlobalStatement(std::shared_ptr<GlobalStatementSyntax> syntax) {
  return bindStatement(syntax->getStatement());
}

Binder::Binder(std::shared_ptr<BoundScope> parent) {
  this->root = std::make_shared<BoundScope>(parent);
}

void Binder::verifyAllCallsAreValid(std::shared_ptr<Binder> binder) {

  std::vector<std::shared_ptr<BoundFunctionDeclaration>> functions =
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

std::shared_ptr<BoundScopeGlobal>
Binder::bindGlobalScope(std::unique_ptr<BoundScopeGlobal> previousGlobalScope,
                        std::shared_ptr<CompilationUnitSyntax> syntax) {

  std::shared_ptr<Binder> binder = std::make_shared<Binder>(nullptr);

  if (previousGlobalScope) {
    binder->root->variables = previousGlobalScope->variables;
    binder->root->functions = previousGlobalScope->functions;
  }

  std::vector<std::shared_ptr<BoundStatement>> statements;

  for (int i = 0; i < syntax->getMembers().size(); i++) {
    if (syntax->getMembers()[i]->getKind() ==
        SyntaxKindUtils::SyntaxKind::FunctionDeclarationSyntax) {
      std::shared_ptr<FunctionDeclarationSyntax> functionDeclarationSyntax =
          std::static_pointer_cast<FunctionDeclarationSyntax>(
              syntax->getMembers()[i]);
      statements.push_back(
          binder->bindFunctionDeclaration(functionDeclarationSyntax));
    } else if (syntax->getMembers()[i]->getKind() ==
               SyntaxKindUtils::SyntaxKind::GlobalStatement) {
      std::shared_ptr<GlobalStatementSyntax> globalStatementSyntax =
          std::static_pointer_cast<GlobalStatementSyntax>(
              syntax->getMembers()[i]);
      std::shared_ptr<BoundStatement> statement =
          binder->bindGlobalStatement(globalStatementSyntax);
      statements.push_back(statement);
    } else {
      throw "Unexpected global member";
    }
  }

  verifyAllCallsAreValid(binder);

  std::shared_ptr<BoundStatement> statement =
      std::make_shared<BoundBlockStatement>("", statements, true);

  std::vector<std::string> _logs;

  for (const std::string &log : binder->logs) {
    _logs.push_back(log);
  }

  if (previousGlobalScope != nullptr) {
    for (const std::string &log : previousGlobalScope->logs) {
      _logs.push_back(log);
    }
  }

  std::map<std::string, Utils::Variable> variables = binder->root->variables;
  std::map<std::string, std::shared_ptr<BoundFunctionDeclaration>> functions =
      binder->root->functions;

  return std::make_shared<BoundScopeGlobal>(std::move(previousGlobalScope),
                                            variables, functions, _logs,
                                            std::move(statement));
}
