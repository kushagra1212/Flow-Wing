
#include "Binder.h"

BoundStatement *Binder::bindStatement(StatementSyntax *syntax) {
  switch (syntax->getKind()) {
  case SyntaxKindUtils::SyntaxKind::ExpressionStatement: {
    ExpressionStatementSyntax *expressionStatement =
        (ExpressionStatementSyntax *)syntax;
    BoundExpression *expression =
        bindExpression(expressionStatement->getExpression());
    return new BoundExpressionStatement(expression);
  }
  case SyntaxKindUtils::SyntaxKind::BlockStatement: {
    BlockStatementSyntax *blockStatement = (BlockStatementSyntax *)syntax;

    this->root = new BoundScope(this->root);

    std::vector<BoundStatement *> statements;
    for (int i = 0; i < blockStatement->getStatements().size(); i++) {

      BoundStatement *statement =
          bindStatement(blockStatement->getStatements()[i]);
      statements.push_back(statement);
    }

    BoundStatement *statement = new BoundBlockStatement(statements, false);

    this->root = this->root->parent;

    return statement;
  }
  case SyntaxKindUtils::SyntaxKind::VariableDeclaration: {
    VariableDeclarationSyntax *variableDeclaration =
        (VariableDeclarationSyntax *)syntax;
    BoundExpression *initializer =
        bindExpression(variableDeclaration->getInitializer());

    std::string variable_str = std::any_cast<std::string>(
        variableDeclaration->getIdentifier()->getValue());
    bool isConst = variableDeclaration->getKeyword()->getKind() ==
                   SyntaxKindUtils::SyntaxKind::ConstKeyword;

    if (!root->tryDeclareVariable(variable_str,
                                  Utils::Variable(nullptr, false))) {
      logs.push_back(Utils::getLineNumberAndPosition(
                         variableDeclaration->getIdentifier()) +
                     "Error: Variable " + variable_str + " already exists");
    }

    return new BoundVariableDeclaration(variable_str, isConst, initializer);
  }
  case SyntaxKindUtils::SyntaxKind::IfStatement: {
    IfStatementSyntax *ifStatement = (IfStatementSyntax *)syntax;
    BoundExpression *condition = bindExpression(ifStatement->getCondition());
    BoundStatement *thenStatement =
        bindStatement((StatementSyntax *)(ifStatement->getStatement()));
    BoundStatement *elseStatement = nullptr;
    if (ifStatement->getElseClause() != nullptr) {
      elseStatement = bindStatement(
          (StatementSyntax *)ifStatement->getElseClause()->getStatement());
    }
    return new BoundIfStatement(condition, thenStatement, elseStatement);
  }
  case SyntaxKindUtils::SyntaxKind::WhileStatement: {
    WhileStatementSyntax *whileStatement = (WhileStatementSyntax *)syntax;
    BoundExpression *condition = bindExpression(whileStatement->getCondition());
    BoundStatement *body =
        bindStatement((StatementSyntax *)whileStatement->getBody());
    return new BoundWhileStatement(condition, body);
  }

  case SyntaxKindUtils::SyntaxKind::ForStatement: {
    ForStatementSyntax *forStatement = (ForStatementSyntax *)syntax;
    BoundStatement *intializer = (BoundStatement *)bindStatement(
        (StatementSyntax *)forStatement->getInitialization());

    BoundExpression *upperBound =
        (BoundLiteralExpression<std::any> *)bindExpression(
            forStatement->getUpperBound());

    BoundStatement *body =
        bindStatement((StatementSyntax *)forStatement->getStatement());

    return new BoundForStatement(intializer, upperBound, (body));
  }
  default:
    throw "Unexpected syntax";
  }
}

BoundExpression *Binder::bindExpression(ExpressionSyntax *syntax) {
  switch (syntax->getKind()) {
  case SyntaxKindUtils::SyntaxKind::LiteralExpression: {

    std::any value = ((LiteralExpressionSyntax<std::any> *)syntax)->getValue();
    return new BoundLiteralExpression<std::any>(value);
  }
  case SyntaxKindUtils::SyntaxKind::UnaryExpression: {
    UnaryExpressionSyntax *unaryExpression = (UnaryExpressionSyntax *)syntax;
    BoundExpression *operand = bindExpression(unaryExpression->getOperand());
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
    return new BoundUnaryExpression(op, operand);
  }
  case SyntaxKindUtils::SyntaxKind::BinaryExpression: {
    BinaryExpressionSyntax *binaryExpression = (BinaryExpressionSyntax *)syntax;
    BoundExpression *left = bindExpression(binaryExpression->getLeft());
    BoundExpression *right = bindExpression(binaryExpression->getRight());
    BinderKindUtils::BoundBinaryOperatorKind op;

    // if (left->getType() != typeid(int) || right->getType() != typeid(int)) {
    //   logs.push_back("Binary operator can only be applied to numbers");
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
    return new BoundBinaryExpression(left, op, right);
  }

    // Assignment Expression

  case SyntaxKindUtils::SyntaxKind::AssignmentExpression: {
    AssignmentExpressionSyntax *assignmentExpression =
        (AssignmentExpressionSyntax *)syntax;
    BoundLiteralExpression<std::any> *identifierExpression =
        (BoundLiteralExpression<std::any> *)bindExpression(
            assignmentExpression->getLeft());
    std::string variable_str =
        std::any_cast<std::string>(identifierExpression->getValue());
    BinderKindUtils::BoundBinaryOperatorKind op;
    if (!root->tryLookupVariable(variable_str)) {
      logs.push_back(Utils::getLineNumberAndPosition(
                         assignmentExpression->getOperatorToken()) +
                     "Error: Can not assign to undeclared variable " +
                     variable_str);
      return identifierExpression;
    }
    if (root->variables[variable_str].isConst) {
      logs.push_back(Utils::getLineNumberAndPosition(
                         assignmentExpression->getOperatorToken()) +
                     "Error: Can not assign to const variable " + variable_str);
      return identifierExpression;
    }

    switch (assignmentExpression->getOperatorToken()->getKind()) {
    case SyntaxKindUtils::SyntaxKind::EqualsToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Assignment;
      break;
    default:
      throw "Unexpected assignment operator";
    }
    BoundExpression *right = bindExpression(assignmentExpression->getRight());
    return new BoundAssignmentExpression(identifierExpression, op, right);
  }

  case SyntaxKindUtils::SyntaxKind::VariableExpression: {
    VariableExpressionSyntax *variableExpressionSyntax =
        (VariableExpressionSyntax *)syntax;

    BoundLiteralExpression<std::any> *identifierExpression =
        (BoundLiteralExpression<std::any> *)bindExpression(
            variableExpressionSyntax->getIdentifier());
    std::string variable_str =
        std::any_cast<std::string>(identifierExpression->getValue());
    if (!root->tryLookupVariable(variable_str)) {
      logs.push_back(
          Utils::getLineNumberAndPosition(
              variableExpressionSyntax->getIdentifier()->getToken()) +
          "Error: Variable " + variable_str + " does not exist");
      return identifierExpression;
    }
    return new BoundVariableExpression(identifierExpression);
  }
  case SyntaxKindUtils::SyntaxKind::ParenthesizedExpression: {
    ParenthesizedExpressionSyntax *parenthesizedExpression =
        (ParenthesizedExpressionSyntax *)syntax;
    return bindExpression(parenthesizedExpression->getExpression());
  }
  case SyntaxKindUtils::SyntaxKind::CallExpression: {
    CallExpressionSyntax *callExpression = (CallExpressionSyntax *)syntax;
    BoundLiteralExpression<std::any> *identifier =
        (BoundLiteralExpression<std::any> *)bindExpression(
            callExpression->getIdentifier());

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

    // if (functionSymbol.kind == Utils::SymbolKind::None) {
    //   logs.push_back(Utils::getLineNumberAndPosition(
    //                      callExpression->getIdentifier()->getToken()) +
    //                  "Error: Function " +
    //                  callExpression->getIdentifier()->getToken()->getText() +
    //                  " does not exist");
    //   return identifier;
    // }

    // if (callExpression->getArguments().size() != functionSymbol.arity()) {
    //   logs.push_back("Error: Function " +
    //                  std::any_cast<std::string>(identifier->getValue()) +
    //                  " requires " + std::to_string(functionSymbol.arity()) +
    //                  " arguments");
    //   return identifier;
    // }

    std::vector<BoundExpression *> arguments;
    for (int i = 0; i < callExpression->getArguments().size(); i++) {
      arguments.push_back(bindExpression(callExpression->getArguments()[i]));
    }

    return new BoundCallExpression(functionSymbol, arguments);
  }
  default:
    throw "Unexpected syntax";
  }
}
BoundScope *Binder::CreateParentScope(BoundScopeGlobal *parent) {
  std::stack<BoundScopeGlobal *> stack = std::stack<BoundScopeGlobal *>();

  while (parent != nullptr) {
    stack.push(parent);
    parent = parent->previous;
  }

  BoundScope *current = nullptr;

  while (!stack.empty()) {
    parent = stack.top();
    stack.pop();
    BoundScope *scope = new BoundScope(current);

    for (auto &pair : parent->variables) {
      scope->variables[pair.first] = pair.second;
    }

    current = scope;
  }

  return current;
}

BoundStatement *
Binder::bindFunctionDeclaration(FunctionDeclarationSyntax *syntax) {
  std::vector<Utils::FunctionParameterSymbol> parameters;

  this->root = new BoundScope(this->root);
  std::string function_name = syntax->getIdentifierToken()->getText();

  for (int i = 0; i < syntax->getParameters().size(); i++) {
    std::string variable_str =
        syntax->getParameters()[i]->getIdentifierToken()->getText();
    if (!this->root->tryDeclareVariable(variable_str,
                                        Utils::Variable(nullptr, false))) {
      this->logs.push_back(
          Utils::getLineNumberAndPosition(
              syntax->getParameters()[i]->getIdentifierToken()) +
          "Error: Parameter " + variable_str + " already declared");
    }

    parameters.push_back(Utils::FunctionParameterSymbol(
        syntax->getParameters()[i]->getIdentifierToken()->getText(), false));
  }

  Utils::FunctionSymbol functionSymbol =
      Utils::FunctionSymbol(function_name, parameters, Utils::type::VOID);

  BoundBlockStatement *body =
      (BoundBlockStatement *)bindStatement(syntax->getBody());
  BoundFunctionDeclaration *fd =
      new BoundFunctionDeclaration(functionSymbol, body);

  if (!this->root->tryDeclareFunction(functionSymbol.name, fd)) {
    this->logs.push_back(
        Utils::getLineNumberAndPosition(syntax->getFunctionKeyword()) +
        "Error: Function " + functionSymbol.name + " already declared");
  }
  this->root = this->root->parent;
  return fd;
}

BoundStatement *Binder::bindGlobalStatement(GlobalStatementSyntax *syntax) {
  return bindStatement(syntax->getStatement());
}

Binder::Binder(BoundScope *parent) { this->root = new BoundScope(parent); }

BoundScopeGlobal *Binder::bindGlobalScope(BoundScopeGlobal *previous,
                                          CompilationUnitSyntax *syntax) {

  Binder *binder = new Binder(nullptr);

  if (previous) {
    binder->root->variables = previous->variables;
    binder->root->functions = previous->functions;
  }

  std::vector<BoundStatement *> statements;

  for (int i = 0; i < syntax->getMembers().size(); i++) {
    if (syntax->getMembers()[i]->getKind() ==
        SyntaxKindUtils::SyntaxKind::FunctionDeclarationSyntax) {
      FunctionDeclarationSyntax *functionDeclarationSyntax =
          (FunctionDeclarationSyntax *)syntax->getMembers()[i];
      statements.push_back(
          binder->bindFunctionDeclaration(functionDeclarationSyntax));
    } else if (syntax->getMembers()[i]->getKind() ==
               SyntaxKindUtils::SyntaxKind::GlobalStatement) {
      GlobalStatementSyntax *globalStatementSyntax =
          (GlobalStatementSyntax *)syntax->getMembers()[i];
      BoundStatement *statement =
          binder->bindGlobalStatement(globalStatementSyntax);
      statements.push_back(statement);
    } else {
      throw "Unexpected global member";
    }
  }

  BoundStatement *statement = new BoundBlockStatement(statements, true);

  std::vector<std::string> logs = binder->logs;
  if (previous != nullptr) {
    logs.insert(logs.end(), previous->logs.begin(), previous->logs.end());
  }

  std::map<std::string, Utils::Variable> variables = binder->root->variables;
  std::map<std::string, BoundFunctionDeclaration *> functions =
      binder->root->functions;

  return new BoundScopeGlobal(previous, variables, functions, logs, statement);
}

Binder::~Binder() { delete this->root; }
