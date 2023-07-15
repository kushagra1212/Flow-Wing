#include "Parser.h"

Parser::Parser(std::string text) {
  Lexer *lexer = new Lexer(text);
  SyntaxToken *token;
  do {
    token = lexer->nextToken();
    if (token->getKind() != SyntaxKindUtils::SyntaxKind::WhitespaceToken &&
        token->getKind() != SyntaxKindUtils::SyntaxKind::BadToken) {
      this->tokens.push_back(token);
    }
    if (token->getKind() == SyntaxKindUtils::SyntaxKind::BadToken) {
      this->logs.push_back("ERROR: unexpected character <" + token->getText() +
                           ">");
    }
  } while (token->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken);

  if (lexer->logs.size()) {
    this->logs = lexer->logs;
  }
}

SyntaxToken *Parser::peek(int offset) {
  int index = this->position + offset;
  if (index >= this->tokens.size()) {

    return this->tokens[this->tokens.size() - 1];
  }
  return this->tokens[index];
}

SyntaxToken *Parser::getCurrent() { return this->peek(0); }

SyntaxToken *Parser::nextToken() {
  SyntaxToken *current = this->getCurrent();
  this->position++;
  return current;
}

SyntaxToken *Parser::match(SyntaxKindUtils::SyntaxKind kind) {
  if (this->getCurrent()->getKind() == kind) {
    return this->nextToken();
  }
  this->logs.push_back("ERROR: unexpected token <" +
                       this->getCurrent()->getText() + ">, expected <" +
                       SyntaxKindUtils::enum_to_string_map
                           [SyntaxKindUtils::SyntaxKind::EndOfFileToken] +
                       ">");

  return new SyntaxToken(kind, this->getCurrent()->getPosition(), "\0",
                         nullptr);
}

CompilationUnitSyntax *Parser::parseCompilationUnit() {
  ExpressionSyntax *expression = this->parseExpression();
  SyntaxToken *endOfFileToken =
      this->match(SyntaxKindUtils::SyntaxKind::EndOfFileToken);
  return new CompilationUnitSyntax(this->logs, expression, endOfFileToken);
}

ExpressionSyntax *Parser::parseExpression(int parentPrecedence) {

  // parse assignment expression

  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::IdentifierToken) {
    if (this->peek(1)->getKind() == SyntaxKindUtils::SyntaxKind::EqualsToken) {
      SyntaxToken *identifierToken = this->nextToken();
      SyntaxToken *operatorToken = this->nextToken();
      ExpressionSyntax *right = this->parseExpression();
      return new AssignmentExpressionSyntax(
          new LiteralExpressionSyntax<std::string>(
              identifierToken, *(std::static_pointer_cast<std::string>(
                                   identifierToken->getValue()))),
          operatorToken, right);
    } else if (this->peek(0)->getKind() ==
               SyntaxKindUtils::SyntaxKind::IdentifierToken) {
      SyntaxToken *identifierToken = this->nextToken();
      return new VariableExpressionSyntax(
          new LiteralExpressionSyntax<std::string>(
              identifierToken, *(std::static_pointer_cast<std::string>(
                                   identifierToken->getValue()))));
    }
  }

  ExpressionSyntax *left;
  int unaryOperatorPrecedence =
      this->getCurrent()->getUnaryOperatorPrecedence();

  if (unaryOperatorPrecedence != 0 &&
      unaryOperatorPrecedence >= parentPrecedence) {
    SyntaxToken *operatorToken = this->nextToken();
    ExpressionSyntax *operand = this->parseExpression(unaryOperatorPrecedence);
    left = new UnaryExpressionSyntax(operatorToken, operand);
  } else {
    left = this->parsePrimaryExpression();
  }

  while (true) {
    int precedence = this->getCurrent()->getBinaryOperatorPrecedence();
    if (precedence == 0 || precedence <= parentPrecedence) {
      break;
    }
    SyntaxToken *operatorToken = this->nextToken();

    ExpressionSyntax *right = this->parseExpression(precedence);

    left = new BinaryExpressionSyntax(left, operatorToken, right);
  }

  return left;
}

ExpressionSyntax *Parser::parsePrimaryExpression() {
  switch (this->getCurrent()->getKind()) {
  case SyntaxKindUtils::OpenParenthesisToken: {
    SyntaxToken *left = this->nextToken();
    ExpressionSyntax *expression = this->parseExpression();
    SyntaxToken *right =
        this->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken);
    return new ParenthesizedExpressionSyntax(left, expression, right);
  }
  case SyntaxKindUtils::NumberToken: {
    SyntaxToken *numberToken = this->nextToken();
    return new LiteralExpressionSyntax<int>(
        numberToken, *(std::static_pointer_cast<int>(numberToken->getValue())));
  }

  case SyntaxKindUtils::StringToken: {
    SyntaxToken *stringToken = this->nextToken();
    return new LiteralExpressionSyntax<std::string>(
        stringToken,
        *(std::static_pointer_cast<std::string>(stringToken->getValue())));
  }
  case SyntaxKindUtils::TrueKeyword:
  case SyntaxKindUtils::FalseKeyword: {
    SyntaxToken *keywordToken = this->nextToken();
    bool value =
        keywordToken->getKind() == SyntaxKindUtils::SyntaxKind::TrueKeyword
            ? true
            : false;
    return new LiteralExpressionSyntax<bool>(keywordToken, value);
  }

  default:
    this->logs.push_back("ERROR: unexpected token <" +
                         this->getCurrent()->getText() + ">, expected <" +
                         SyntaxKindUtils::enum_to_string_map
                             [SyntaxKindUtils::SyntaxKind::EndOfFileToken] +
                         ">");
    return new LiteralExpressionSyntax<int>(this->getCurrent(), 0);
  }
}