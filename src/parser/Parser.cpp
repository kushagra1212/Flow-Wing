#include "Parser.h"
Parser::Parser(const std::vector<std::string> &text) {

  Lexer *lexer = new Lexer(text);
  std::unique_ptr<SyntaxToken<std::any>> token;
  SyntaxKindUtils::SyntaxKind _kind =
      SyntaxKindUtils::SyntaxKind::EndOfFileToken;
  do {

    token = std::move(lexer->nextToken());
    _kind = token->getKind();

    if (_kind == SyntaxKindUtils::SyntaxKind::BadToken) {
      this->logs.push_back(Utils::getLineNumberAndPosition(token.get()) +
                           "ERROR: unexpected character <" + token->getText() +
                           ">");
    }
    if (_kind != SyntaxKindUtils::SyntaxKind::WhitespaceToken &&
        _kind != SyntaxKindUtils::SyntaxKind::EndOfLineToken) {
      this->tokens.push_back(std::move(token));
    }
  } while (_kind != SyntaxKindUtils::SyntaxKind::EndOfFileToken);

  for (auto log : lexer->logs) {
    this->logs.push_back(log);
  }
}

Parser::~Parser() {}

std::shared_ptr<SyntaxToken<std::any>> Parser::peek(int offset) {
  int index = this->position + offset;
  if (index >= this->tokens.size()) {

    return this->tokens[this->tokens.size() - 1];
  }
  return this->tokens[index];
}

std::shared_ptr<SyntaxToken<std::any>> Parser::getCurrent() {
  return this->peek(0);
}

std::shared_ptr<SyntaxToken<std::any>> Parser::nextToken() {
  std::shared_ptr<SyntaxToken<std::any>> current = this->getCurrent();
  this->position++;
  return current;
}

std::shared_ptr<SyntaxToken<std::any>>
Parser::match(SyntaxKindUtils::SyntaxKind kind) {
  if (this->getCurrent()->getKind() == kind) {
    return this->nextToken();
  }
  this->logs.push_back(
      Utils::getLineNumberAndPosition(this->getCurrent().get()) +
      "ERROR: unexpected token <" +
      SyntaxKindUtils::to_string(this->getCurrent()->getKind()) +
      ">, expected <" + SyntaxKindUtils::to_string(kind) + ">");

  return std::make_shared<SyntaxToken<std::any>>(
      this->getCurrent()->getLineNumber(),
      SyntaxKindUtils::SyntaxKind::EndOfLineToken,
      this->getCurrent()->getPosition(), "\0", 0);
}
bool Parser::matchKind(SyntaxKindUtils::SyntaxKind kind) {
  return this->getCurrent()->getKind() == kind;
}
std::shared_ptr<CompilationUnitSyntax> Parser::parseCompilationUnit() {
  std::vector<MemberSyntax *> members = this->parseMemberList();
  std::shared_ptr<SyntaxToken<std::any>> endOfFileToken =
      this->match(SyntaxKindUtils::SyntaxKind::EndOfFileToken);
  return std::make_shared<CompilationUnitSyntax>(members, endOfFileToken.get());
}

std::vector<MemberSyntax *> Parser::parseMemberList() {
  std::vector<MemberSyntax *> members;
  while (this->getCurrent()->getKind() !=
         SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
    MemberSyntax *member = this->parseMember();
    members.push_back(member);
  }
  return members;
}

MemberSyntax *Parser::parseMember() {
  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::FunctionKeyword) {
    return (MemberSyntax *)this->parseFunctionDeclaration();
  }
  return this->parseGlobalStatement();
}

FunctionDeclarationSyntax *Parser::parseFunctionDeclaration() {
  std::shared_ptr<SyntaxToken<std::any>> functionKeyword =
      this->match(SyntaxKindUtils::SyntaxKind::FunctionKeyword);
  std::shared_ptr<SyntaxToken<std::any>> identifier =
      this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken);
  std::shared_ptr<SyntaxToken<std::any>> openParenthesisToken =
      this->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken);
  std::vector<ParameterSyntax *> parameters;

  while (this->getCurrent()->getKind() !=
             SyntaxKindUtils::SyntaxKind::CloseParenthesisToken &&
         this->getCurrent()->getKind() !=
             SyntaxKindUtils::SyntaxKind::EndOfFileToken) {

    if (parameters.size() > 0) {

      this->match(SyntaxKindUtils::SyntaxKind::CommaToken);
    }

    parameters.push_back(new ParameterSyntax(
        this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken).get()));
  }
  std::shared_ptr<SyntaxToken<std::any>> closeParenthesisToken =
      this->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken);
  BlockStatementSyntax *body = this->parseBlockStatement();

  return new FunctionDeclarationSyntax(functionKeyword.get(), identifier.get(),
                                       openParenthesisToken.get(), parameters,
                                       closeParenthesisToken.get(), body);
}

GlobalStatementSyntax *Parser::parseGlobalStatement() {
  StatementSyntax *statement = this->parseStatement();
  return new GlobalStatementSyntax(statement);
}

BlockStatementSyntax *Parser::parseBlockStatement() {

  std::shared_ptr<SyntaxToken<std::any>> openBraceToken =
      this->match(SyntaxKindUtils::SyntaxKind::OpenBraceToken);

  std::vector<StatementSyntax *> statements;
  while (this->getCurrent()->getKind() !=
             SyntaxKindUtils::SyntaxKind::CloseBraceToken &&

         this->getCurrent()->getKind() !=
             SyntaxKindUtils::SyntaxKind::EndOfLineToken &&
         this->getCurrent()->getKind() !=
             SyntaxKindUtils::SyntaxKind::EndOfFileToken

  ) {
    StatementSyntax *statement = this->parseStatement();
    statements.push_back(statement);
  }

  std::shared_ptr<SyntaxToken<std::any>> closeBraceToken =
      this->match(SyntaxKindUtils::SyntaxKind::CloseBraceToken);

  return new BlockStatementSyntax(openBraceToken.get(), statements,
                                  closeBraceToken.get());
}

ExpressionStatementSyntax *Parser::parseExpressionStatement() {
  ExpressionSyntax *expression = this->parseExpression();
  return new ExpressionStatementSyntax(expression);
}
StatementSyntax *Parser::parseStatement() {
  switch (this->getCurrent()->getKind()) {
  case SyntaxKindUtils::SyntaxKind::OpenBraceToken:
    return (StatementSyntax *)this->parseBlockStatement();
  case SyntaxKindUtils::SyntaxKind::VarKeyword:
  case SyntaxKindUtils::SyntaxKind::ConstKeyword:
    return (StatementSyntax *)this->parseVariableDeclaration();
  case SyntaxKindUtils::SyntaxKind::IfKeyword:
    return (StatementSyntax *)this->parseIfStatement();
  case SyntaxKindUtils::SyntaxKind::WhileKeyword:
    return (StatementSyntax *)this->parseWhileStatement();

  case SyntaxKindUtils::SyntaxKind::ForKeyword:
    return (StatementSyntax *)this->parseForStatement();
  case SyntaxKindUtils::SyntaxKind::BreakKeyword:
    return (StatementSyntax *)this->parseBreakStatement();
  case SyntaxKindUtils::SyntaxKind::ContinueKeyword:
    return (StatementSyntax *)this->parseContinueStatement();
  case SyntaxKindUtils::SyntaxKind::ReturnKeyword:
    return (StatementSyntax *)this->parseReturnStatement();
  case SyntaxKindUtils::SyntaxKind::EndOfLineToken:
  case SyntaxKindUtils::SyntaxKind::EndOfFileToken:
    return (StatementSyntax *)this->nextToken().get();
  default:
    return (StatementSyntax *)this->parseExpressionStatement();
  }
}

ReturnStatementSyntax *Parser::parseReturnStatement() {
  std::shared_ptr<SyntaxToken<std::any>> returnKeyword =
      this->match(SyntaxKindUtils::SyntaxKind::ReturnKeyword);

  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::OpenParenthesisToken) {
    this->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken);

    ExpressionSyntax *expression = this->parseExpression();
    this->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken);
    return new ReturnStatementSyntax(returnKeyword.get(), expression);
  }

  return new ReturnStatementSyntax(returnKeyword.get(), nullptr);
}

BreakStatementSyntax *Parser::parseBreakStatement() {
  std::shared_ptr<SyntaxToken<std::any>> breakKeyword =
      this->match(SyntaxKindUtils::SyntaxKind::BreakKeyword);
  return new BreakStatementSyntax(breakKeyword.get());
}

ContinueStatementSyntax *Parser::parseContinueStatement() {
  std::shared_ptr<SyntaxToken<std::any>> continueKeyword =
      this->match(SyntaxKindUtils::SyntaxKind::ContinueKeyword);
  return new ContinueStatementSyntax(continueKeyword.get());
}

ForStatementSyntax *Parser::parseForStatement() {
  std::shared_ptr<SyntaxToken<std::any>> keyword =
      this->match(SyntaxKindUtils::SyntaxKind::ForKeyword);
  bool hadOpenParenthesis = false;
  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::OpenParenthesisToken) {
    this->nextToken();
    hadOpenParenthesis = true;
  }

  StatementSyntax *statementSyntax = nullptr;

  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::VarKeyword) {
    statementSyntax = this->parseVariableDeclaration();
  } else {
    statementSyntax = this->parseExpressionStatement();
  }

  std::shared_ptr<SyntaxToken<std::any>> toKeyword =
      this->match(SyntaxKindUtils::SyntaxKind::ToKeyword);

  ExpressionSyntax *upperBound = this->parseExpression();

  if (hadOpenParenthesis) {
    this->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken);
  }

  BlockStatementSyntax *statement = this->parseBlockStatement();
  return new ForStatementSyntax(statementSyntax, upperBound, statement);
}

IfStatementSyntax *Parser::parseIfStatement() {
  std::shared_ptr<SyntaxToken<std::any>> keyword =
      this->match(SyntaxKindUtils::SyntaxKind::IfKeyword);
  ExpressionSyntax *condition = this->parseExpression();

  BlockStatementSyntax *statement = this->parseBlockStatement();
  ElseClauseSyntax *elseClause = nullptr;
  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::ElseKeyword) {
    std::shared_ptr<SyntaxToken<std::any>> elseKeyword =
        this->match(SyntaxKindUtils::SyntaxKind::ElseKeyword);
    BlockStatementSyntax *elseStatement = this->parseBlockStatement();
    elseClause = new ElseClauseSyntax(elseKeyword.get(), elseStatement);
  }
  return new IfStatementSyntax(keyword.get(), condition, statement, elseClause);
}

WhileStatementSyntax *Parser::parseWhileStatement() {
  std::shared_ptr<SyntaxToken<std::any>> keyword =
      this->match(SyntaxKindUtils::SyntaxKind::WhileKeyword);
  ExpressionSyntax *condition = this->parseExpression();
  BlockStatementSyntax *statement = this->parseBlockStatement();
  return new WhileStatementSyntax(keyword.get(), condition, statement);
}

StatementSyntax *Parser::parseVariableDeclaration() {

  std::shared_ptr<SyntaxToken<std::any>> keyword = this->match(
      SyntaxKindUtils::SyntaxKind::VarKeyword == this->getCurrent()->getKind()
          ? SyntaxKindUtils::SyntaxKind::VarKeyword
          : SyntaxKindUtils::SyntaxKind::ConstKeyword);
  std::shared_ptr<SyntaxToken<std::any>> identifier =
      this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken);
  std::shared_ptr<SyntaxToken<std::any>> equalsToken =
      this->match(SyntaxKindUtils::SyntaxKind::EqualsToken);
  ExpressionSyntax *initializer = this->parseExpression();
  return new VariableDeclarationSyntax(keyword.get(), identifier.get(),
                                       equalsToken.get(), initializer);
}

ExpressionSyntax *Parser::parseExpression(int parentPrecedence) {

  ExpressionSyntax *left;
  int unaryOperatorPrecedence =
      this->getCurrent()->getUnaryOperatorPrecedence();

  if (unaryOperatorPrecedence != 0 &&
      unaryOperatorPrecedence >= parentPrecedence) {
    std::shared_ptr<SyntaxToken<std::any>> operatorToken = this->nextToken();
    ExpressionSyntax *operand = this->parseExpression(unaryOperatorPrecedence);
    left = new UnaryExpressionSyntax(operatorToken.get(), operand);
  } else {
    left = this->parsePrimaryExpression();
  }

  while (true) {
    int precedence = this->getCurrent()->getBinaryOperatorPrecedence();
    if (precedence == 0 || precedence <= parentPrecedence) {
      break;
    }

    std::shared_ptr<SyntaxToken<std::any>> operatorToken = this->nextToken();

    ExpressionSyntax *right = this->parseExpression(precedence);

    left = new BinaryExpressionSyntax(left, operatorToken.get(), right);
  }

  return left;
}

ExpressionSyntax *Parser::parsePrimaryExpression() {
  switch (this->getCurrent()->getKind()) {
  case SyntaxKindUtils::OpenParenthesisToken: {
    std::shared_ptr<SyntaxToken<std::any>> left = this->nextToken();
    ExpressionSyntax *expression = this->parseExpression();
    std::shared_ptr<SyntaxToken<std::any>> right =
        this->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken);
    return new ParenthesizedExpressionSyntax(left.get(), expression,
                                             right.get());
  }
  case SyntaxKindUtils::NumberToken: {
    std::shared_ptr<SyntaxToken<std::any>> numberToken = this->nextToken();

    return new LiteralExpressionSyntax<std::any>(numberToken.get(),
                                                 (numberToken->getValue()));
  }

  case SyntaxKindUtils::StringToken: {
    std::shared_ptr<SyntaxToken<std::any>> stringToken = this->nextToken();
    return new LiteralExpressionSyntax<std::any>(stringToken.get(),
                                                 stringToken->getValue());
  }
  case SyntaxKindUtils::TrueKeyword:
  case SyntaxKindUtils::FalseKeyword: {
    std::shared_ptr<SyntaxToken<std::any>> keywordToken = this->nextToken();
    bool value =
        keywordToken->getKind() == SyntaxKindUtils::SyntaxKind::TrueKeyword
            ? true
            : false;
    return new LiteralExpressionSyntax<std::any>(keywordToken.get(), value);
  }
  case SyntaxKindUtils::SyntaxKind::CommaToken: {
    return new LiteralExpressionSyntax<std::any>(this->nextToken().get(), ",");
  }
  case SyntaxKindUtils::SyntaxKind::IdentifierToken: {
    return this->parseNameorCallExpression();
  }
  default:
    this->logs.push_back(
        Utils::getLineNumberAndPosition(this->getCurrent().get()) +
        "ERROR: unexpected token <" +
        SyntaxKindUtils::to_string(this->getCurrent()->getKind()) + ">");
    return new LiteralExpressionSyntax<std::any>(this->getCurrent().get(),
                                                 (int)0);
  }
}

ExpressionSyntax *Parser::parseNameorCallExpression() {
  if (this->peek(1)->getKind() == SyntaxKindUtils::SyntaxKind::EqualsToken) {
    std::shared_ptr<SyntaxToken<std::any>> identifierToken = this->nextToken();
    std::shared_ptr<SyntaxToken<std::any>> operatorToken = this->nextToken();
    ExpressionSyntax *right = this->parseExpression();
    return new AssignmentExpressionSyntax(
        new LiteralExpressionSyntax<std::any>(identifierToken.get(),
                                              identifierToken->getValue()),
        operatorToken.get(), right);
  } else if (this->peek(1)->getKind() ==
             SyntaxKindUtils::SyntaxKind::OpenParenthesisToken) {
    std::shared_ptr<SyntaxToken<std::any>> identifierToken =
        this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken);
    std::shared_ptr<SyntaxToken<std::any>> openParenthesisToken =
        this->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken);
    std::vector<ExpressionSyntax *> arguments;
    while (this->getCurrent()->getKind() !=
               SyntaxKindUtils::SyntaxKind::CloseParenthesisToken &&
           this->getCurrent()->getKind() !=
               SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
      ExpressionSyntax *expression = this->parseExpression();
      arguments.push_back(expression);
      if (this->getCurrent()->getKind() !=
          SyntaxKindUtils::SyntaxKind::CloseParenthesisToken) {
        this->match(SyntaxKindUtils::SyntaxKind::CommaToken);
      }
    }

    std::shared_ptr<SyntaxToken<std::any>> closeParenthesisToken =
        this->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken);
    return new CallExpressionSyntax(
        new LiteralExpressionSyntax<std::any>(identifierToken.get(),
                                              identifierToken->getValue()),
        openParenthesisToken.get(), arguments, closeParenthesisToken.get());
  } else {
    std::shared_ptr<SyntaxToken<std::any>> identifierToken = this->nextToken();
    return new VariableExpressionSyntax(new LiteralExpressionSyntax<std::any>(
        identifierToken.get(), identifierToken->getValue()));
  }
}
