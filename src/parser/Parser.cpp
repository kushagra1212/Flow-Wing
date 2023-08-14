#include "Parser.h"
Parser::Parser(const std::vector<std::string> &text) {

  std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(text);
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
    } else {
      token.reset();
    }

  } while (_kind != SyntaxKindUtils::SyntaxKind::EndOfFileToken);

  for (auto log : lexer->logs) {
    this->logs.push_back(log);
  }
}

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
  std::vector<std::shared_ptr<MemberSyntax>> members = this->parseMemberList();
  std::shared_ptr<SyntaxToken<std::any>> endOfFileToken =
      this->match(SyntaxKindUtils::SyntaxKind::EndOfFileToken);
  return std::make_shared<CompilationUnitSyntax>(members, endOfFileToken);
}

std::vector<std::shared_ptr<MemberSyntax>> Parser::parseMemberList() {
  std::vector<std::shared_ptr<MemberSyntax>> members;
  while (this->getCurrent()->getKind() !=
         SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
    std::shared_ptr<MemberSyntax> member = this->parseMember();
    members.push_back(member);
  }
  return members;
}

std::shared_ptr<MemberSyntax> Parser::parseMember() {
  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::FunctionKeyword) {
    return (std::shared_ptr<MemberSyntax>)this->parseFunctionDeclaration();
  }
  return this->parseGlobalStatement();
}

std::shared_ptr<FunctionDeclarationSyntax> Parser::parseFunctionDeclaration() {
  std::shared_ptr<SyntaxToken<std::any>> functionKeyword =
      this->match(SyntaxKindUtils::SyntaxKind::FunctionKeyword);
  std::shared_ptr<SyntaxToken<std::any>> identifier =
      this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken);
  std::shared_ptr<SyntaxToken<std::any>> openParenthesisToken =
      this->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken);
  std::vector<std::shared_ptr<ParameterSyntax>> parameters;

  while (this->getCurrent()->getKind() !=
             SyntaxKindUtils::SyntaxKind::CloseParenthesisToken &&
         this->getCurrent()->getKind() !=
             SyntaxKindUtils::SyntaxKind::EndOfFileToken) {

    if (parameters.size() > 0) {

      this->match(SyntaxKindUtils::SyntaxKind::CommaToken);
    }

    parameters.push_back(std::make_shared<ParameterSyntax>(
        this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken)));
  }
  std::shared_ptr<SyntaxToken<std::any>> closeParenthesisToken =
      this->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken);
  std::shared_ptr<BlockStatementSyntax> body = this->parseBlockStatement();

  return std::make_shared<FunctionDeclarationSyntax>(
      functionKeyword, identifier, openParenthesisToken, parameters,
      closeParenthesisToken, body);
}

std::shared_ptr<GlobalStatementSyntax> Parser::parseGlobalStatement() {
  std::shared_ptr<StatementSyntax> statement = this->parseStatement();
  return std::make_shared<GlobalStatementSyntax>(statement);
}

std::shared_ptr<BlockStatementSyntax> Parser::parseBlockStatement() {

  std::shared_ptr<SyntaxToken<std::any>> openBraceToken =
      this->match(SyntaxKindUtils::SyntaxKind::OpenBraceToken);

  std::vector<std::shared_ptr<StatementSyntax>> statements;
  while (this->getCurrent()->getKind() !=
             SyntaxKindUtils::SyntaxKind::CloseBraceToken &&

         this->getCurrent()->getKind() !=
             SyntaxKindUtils::SyntaxKind::EndOfLineToken &&
         this->getCurrent()->getKind() !=
             SyntaxKindUtils::SyntaxKind::EndOfFileToken

  ) {
    std::shared_ptr<StatementSyntax> statement = this->parseStatement();
    statements.push_back(statement);
  }

  std::shared_ptr<SyntaxToken<std::any>> closeBraceToken =
      this->match(SyntaxKindUtils::SyntaxKind::CloseBraceToken);

  return std::make_shared<BlockStatementSyntax>(openBraceToken, statements,
                                                closeBraceToken);
}

std::shared_ptr<ExpressionStatementSyntax> Parser::parseExpressionStatement() {
  std::shared_ptr<ExpressionSyntax> expression = this->parseExpression();
  return std::make_shared<ExpressionStatementSyntax>(expression);
}
std::shared_ptr<StatementSyntax> Parser::parseStatement() {
  switch (this->getCurrent()->getKind()) {
  case SyntaxKindUtils::SyntaxKind::OpenBraceToken:
    return (std::shared_ptr<StatementSyntax>)this->parseBlockStatement();
  case SyntaxKindUtils::SyntaxKind::VarKeyword:
  case SyntaxKindUtils::SyntaxKind::ConstKeyword:
    return (std::shared_ptr<StatementSyntax>)this->parseVariableDeclaration();
  case SyntaxKindUtils::SyntaxKind::IfKeyword:
    return (std::shared_ptr<StatementSyntax>)this->parseIfStatement();
  case SyntaxKindUtils::SyntaxKind::WhileKeyword:
    return (std::shared_ptr<StatementSyntax>)this->parseWhileStatement();

  case SyntaxKindUtils::SyntaxKind::ForKeyword:
    return (std::shared_ptr<StatementSyntax>)this->parseForStatement();
  case SyntaxKindUtils::SyntaxKind::BreakKeyword:
    return (std::shared_ptr<StatementSyntax>)this->parseBreakStatement();
  case SyntaxKindUtils::SyntaxKind::ContinueKeyword:
    return (std::shared_ptr<StatementSyntax>)this->parseContinueStatement();
  case SyntaxKindUtils::SyntaxKind::ReturnKeyword:
    return (std::shared_ptr<StatementSyntax>)this->parseReturnStatement();
  case SyntaxKindUtils::SyntaxKind::EndOfLineToken:
  case SyntaxKindUtils::SyntaxKind::EndOfFileToken:
    return std::dynamic_pointer_cast<StatementSyntax>(this->nextToken());
  default:
    return (std::shared_ptr<StatementSyntax>)this->parseExpressionStatement();
  }
}

std::shared_ptr<ReturnStatementSyntax> Parser::parseReturnStatement() {
  std::shared_ptr<SyntaxToken<std::any>> returnKeyword =
      this->match(SyntaxKindUtils::SyntaxKind::ReturnKeyword);

  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::OpenParenthesisToken) {
    this->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken);

    std::shared_ptr<ExpressionSyntax> expression = this->parseExpression();
    this->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken);
    return std::make_shared<ReturnStatementSyntax>(returnKeyword, expression);
  }

  return std::make_shared<ReturnStatementSyntax>(returnKeyword, nullptr);
}

std::shared_ptr<BreakStatementSyntax> Parser::parseBreakStatement() {
  std::shared_ptr<SyntaxToken<std::any>> breakKeyword =
      this->match(SyntaxKindUtils::SyntaxKind::BreakKeyword);
  return std::make_shared<BreakStatementSyntax>(breakKeyword);
}

std::shared_ptr<ContinueStatementSyntax> Parser::parseContinueStatement() {
  std::shared_ptr<SyntaxToken<std::any>> continueKeyword =
      this->match(SyntaxKindUtils::SyntaxKind::ContinueKeyword);
  return std::make_shared<ContinueStatementSyntax>(continueKeyword);
}

std::shared_ptr<ForStatementSyntax> Parser::parseForStatement() {
  std::shared_ptr<SyntaxToken<std::any>> keyword =
      this->match(SyntaxKindUtils::SyntaxKind::ForKeyword);
  bool hadOpenParenthesis = false;
  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::OpenParenthesisToken) {
    this->nextToken();
    hadOpenParenthesis = true;
  }

  std::shared_ptr<StatementSyntax> statementSyntax = nullptr;

  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::VarKeyword) {
    statementSyntax = this->parseVariableDeclaration();
  } else {
    statementSyntax = this->parseExpressionStatement();
  }

  std::shared_ptr<SyntaxToken<std::any>> toKeyword =
      this->match(SyntaxKindUtils::SyntaxKind::ToKeyword);

  std::shared_ptr<ExpressionSyntax> upperBound = this->parseExpression();

  if (hadOpenParenthesis) {
    this->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken);
  }

  std::shared_ptr<BlockStatementSyntax> statement = this->parseBlockStatement();
  return std::make_shared<ForStatementSyntax>(statementSyntax, upperBound,
                                              statement);
}

std::shared_ptr<IfStatementSyntax> Parser::parseIfStatement() {
  std::shared_ptr<SyntaxToken<std::any>> keyword =
      this->match(SyntaxKindUtils::SyntaxKind::IfKeyword);
  std::shared_ptr<ExpressionSyntax> condition = this->parseExpression();

  std::shared_ptr<BlockStatementSyntax> statement = this->parseBlockStatement();
  std::shared_ptr<ElseClauseSyntax> elseClause = nullptr;
  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::ElseKeyword) {
    std::shared_ptr<SyntaxToken<std::any>> elseKeyword =
        this->match(SyntaxKindUtils::SyntaxKind::ElseKeyword);
    std::shared_ptr<BlockStatementSyntax> elseStatement =
        this->parseBlockStatement();
    elseClause = std::make_shared<ElseClauseSyntax>(elseKeyword, elseStatement);
  }
  return std::make_shared<IfStatementSyntax>(keyword, condition, statement,
                                             elseClause);
}

std::shared_ptr<WhileStatementSyntax> Parser::parseWhileStatement() {
  std::shared_ptr<SyntaxToken<std::any>> keyword =
      this->match(SyntaxKindUtils::SyntaxKind::WhileKeyword);
  std::shared_ptr<ExpressionSyntax> condition = this->parseExpression();
  std::shared_ptr<BlockStatementSyntax> statement = this->parseBlockStatement();
  return std::make_shared<WhileStatementSyntax>(keyword, condition, statement);
}

std::shared_ptr<StatementSyntax> Parser::parseVariableDeclaration() {

  std::shared_ptr<SyntaxToken<std::any>> keyword = this->match(
      SyntaxKindUtils::SyntaxKind::VarKeyword == this->getCurrent()->getKind()
          ? SyntaxKindUtils::SyntaxKind::VarKeyword
          : SyntaxKindUtils::SyntaxKind::ConstKeyword);
  std::shared_ptr<SyntaxToken<std::any>> identifier =
      this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken);
  std::shared_ptr<SyntaxToken<std::any>> equalsToken =
      this->match(SyntaxKindUtils::SyntaxKind::EqualsToken);
  std::shared_ptr<ExpressionSyntax> initializer = this->parseExpression();
  return std::make_shared<VariableDeclarationSyntax>(keyword, identifier,
                                                     equalsToken, initializer);
}

std::shared_ptr<ExpressionSyntax>
Parser::parseExpression(int parentPrecedence) {

  std::shared_ptr<ExpressionSyntax> left;
  int unaryOperatorPrecedence =
      this->getCurrent()->getUnaryOperatorPrecedence();

  if (unaryOperatorPrecedence != 0 &&
      unaryOperatorPrecedence >= parentPrecedence) {
    std::shared_ptr<SyntaxToken<std::any>> operatorToken = this->nextToken();
    std::shared_ptr<ExpressionSyntax> operand =
        this->parseExpression(unaryOperatorPrecedence);
    left = std::make_shared<UnaryExpressionSyntax>(operatorToken, operand);
  } else {
    left = this->parsePrimaryExpression();
  }

  while (true) {
    int precedence = this->getCurrent()->getBinaryOperatorPrecedence();
    if (precedence == 0 || precedence <= parentPrecedence) {
      break;
    }

    std::shared_ptr<SyntaxToken<std::any>> operatorToken = this->nextToken();

    std::shared_ptr<ExpressionSyntax> right = this->parseExpression(precedence);

    left = std::make_shared<BinaryExpressionSyntax>(left, operatorToken, right);
  }

  return left;
}

std::shared_ptr<ExpressionSyntax> Parser::parsePrimaryExpression() {
  switch (this->getCurrent()->getKind()) {
  case SyntaxKindUtils::OpenParenthesisToken: {
    std::shared_ptr<SyntaxToken<std::any>> left = this->nextToken();
    std::shared_ptr<ExpressionSyntax> expression = this->parseExpression();
    std::shared_ptr<SyntaxToken<std::any>> right =
        this->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken);
    return std::make_shared<ParenthesizedExpressionSyntax>(left, expression,
                                                           right);
  }
  case SyntaxKindUtils::NumberToken: {
    std::shared_ptr<SyntaxToken<std::any>> numberToken = this->nextToken();

    return std::make_shared<LiteralExpressionSyntax<std::any>>(
        numberToken, (numberToken->getValue()));
  }

  case SyntaxKindUtils::StringToken: {
    std::shared_ptr<SyntaxToken<std::any>> stringToken = this->nextToken();
    return std::make_shared<LiteralExpressionSyntax<std::any>>(
        stringToken, stringToken->getValue());
  }
  case SyntaxKindUtils::TrueKeyword:
  case SyntaxKindUtils::FalseKeyword: {
    std::shared_ptr<SyntaxToken<std::any>> keywordToken = this->nextToken();
    bool value =
        keywordToken->getKind() == SyntaxKindUtils::SyntaxKind::TrueKeyword
            ? true
            : false;
    return std::make_shared<LiteralExpressionSyntax<std::any>>(keywordToken,
                                                               value);
  }
  case SyntaxKindUtils::SyntaxKind::CommaToken: {
    return std::make_shared<LiteralExpressionSyntax<std::any>>(
        this->nextToken(), ",");
  }
  case SyntaxKindUtils::SyntaxKind::IdentifierToken: {
    return this->parseNameorCallExpression();
  }
  default:
    this->logs.push_back(
        Utils::getLineNumberAndPosition(this->getCurrent().get()) +
        "ERROR: unexpected token <" +
        SyntaxKindUtils::to_string(this->getCurrent()->getKind()) + ">");
    return std::make_shared<LiteralExpressionSyntax<std::any>>(
        this->getCurrent(), (int)0);
  }
}

std::shared_ptr<ExpressionSyntax> Parser::parseNameorCallExpression() {
  if (this->peek(1)->getKind() == SyntaxKindUtils::SyntaxKind::EqualsToken) {
    std::shared_ptr<SyntaxToken<std::any>> identifierToken = this->nextToken();
    std::shared_ptr<SyntaxToken<std::any>> operatorToken = this->nextToken();
    std::shared_ptr<ExpressionSyntax> right = this->parseExpression();
    return std::make_shared<AssignmentExpressionSyntax>(
        std::make_shared<LiteralExpressionSyntax<std::any>>(
            identifierToken, identifierToken->getValue()),
        operatorToken, right);
  } else if (this->peek(1)->getKind() ==
             SyntaxKindUtils::SyntaxKind::OpenParenthesisToken) {
    std::shared_ptr<SyntaxToken<std::any>> identifierToken =
        this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken);
    std::shared_ptr<SyntaxToken<std::any>> openParenthesisToken =
        this->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken);
    std::vector<std::shared_ptr<ExpressionSyntax>> arguments;
    while (this->getCurrent()->getKind() !=
               SyntaxKindUtils::SyntaxKind::CloseParenthesisToken &&
           this->getCurrent()->getKind() !=
               SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
      std::shared_ptr<ExpressionSyntax> expression = this->parseExpression();
      arguments.push_back(expression);
      if (this->getCurrent()->getKind() !=
          SyntaxKindUtils::SyntaxKind::CloseParenthesisToken) {
        this->match(SyntaxKindUtils::SyntaxKind::CommaToken);
      }
    }

    std::shared_ptr<SyntaxToken<std::any>> closeParenthesisToken =
        this->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken);
    return std::make_shared<CallExpressionSyntax>(
        std::make_shared<LiteralExpressionSyntax<std::any>>(
            identifierToken, identifierToken->getValue()),
        openParenthesisToken, arguments, closeParenthesisToken);
  } else {
    std::shared_ptr<SyntaxToken<std::any>> identifierToken = this->nextToken();
    return std::make_shared<VariableExpressionSyntax>(
        std::make_shared<LiteralExpressionSyntax<std::any>>(
            identifierToken, identifierToken->getValue()));
  }
}
