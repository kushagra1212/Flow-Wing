#include "../lexer/Lexer.cpp"
#include "../syntax/CompilationUnitSyntax.cpp"
#include "../syntax/expression/BinaryExpressionSyntax.cpp"
#include "../syntax/expression/NumberExpressionSyntax.cpp"
#include "../syntax/expression/ParenthesizedExpressionSyntax.cpp"
class Parser {
private:
  std::vector<SyntaxToken *> tokens;
  int position;

public:
  std::vector<std::string> logs;

public:
  Parser(std::string text) {
    Lexer *lexer = new Lexer(text);
    SyntaxToken *token;
    do {
      token = lexer->nextToken();
      if (token->getKind() != SyntaxKindUtils::WhitespaceToken &&
          token->getKind() != SyntaxKindUtils::BadToken) {
        this->tokens.push_back(token);
      }
    } while (token->getKind() != SyntaxKindUtils::EndOfFileToken);

    if (lexer->logs.size()) {
      this->logs = lexer->logs;
    }
  }

private:
  SyntaxToken *peek(int offset) {
    int index = this->position + offset;
    if (index >= this->tokens.size()) {
      return this->tokens[this->tokens.size() - 1];
    }
    return this->tokens[index];
  }

private:
  SyntaxToken *getCurrent() { return this->peek(0); }

private:
  SyntaxToken *nextToken() {
    SyntaxToken *current = this->getCurrent();
    this->position++;
    return current;
  }

private:
  SyntaxToken *match(SyntaxKindUtils::SyntaxKind kind) {
    if (this->getCurrent()->getKind() == kind) {
      return this->nextToken();
    }
    this->logs.push_back(
        "ERROR: unexpected token <" + this->getCurrent()->getKindText() +
        ">, expected <" +
        SyntaxKindUtils::enum_to_string_map[SyntaxKindUtils::EndOfFileToken] +
        ">");

    return new SyntaxToken(kind, this->getCurrent()->getPosition(), "\0",
                           nullptr);
  }

public:
  CompilationUnitSyntax *parseCompilationUnit() {
    ExpressionSyntax *expression = this->parseExpression();
    SyntaxToken *endOfFileToken = this->match(SyntaxKindUtils::EndOfFileToken);
    return new CompilationUnitSyntax(this->logs, expression, endOfFileToken);
  }

private:
  ExpressionSyntax *parseExpression(int parentPrecedence = 0) {
    ExpressionSyntax *left;
    int unaryOperatorPrecedence =
        this->getCurrent()->getUnaryOperatorPrecedence();
    if (unaryOperatorPrecedence != 0 &&
        unaryOperatorPrecedence >= parentPrecedence) {
      SyntaxToken *operatorToken = this->nextToken();
      ExpressionSyntax *operand =
          this->parseExpression(unaryOperatorPrecedence);
      left = new BinaryExpressionSyntax(
          new NumberExpressionSyntax(operatorToken), operatorToken, operand);
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

private:
  ExpressionSyntax *parsePrimaryExpression() {
    switch (this->getCurrent()->getKind()) {
    case SyntaxKindUtils::OpenParenthesisToken: {
      SyntaxToken *left = this->nextToken();
      ExpressionSyntax *expression = this->parseExpression();
      SyntaxToken *right = this->match(SyntaxKindUtils::CloseParenthesisToken);
      return new ParenthesizedExpressionSyntax(left, expression, right);
    }
    case SyntaxKindUtils::NumberToken: {
      SyntaxToken *numberToken = this->nextToken();
      return new NumberExpressionSyntax(numberToken);
    }
    default:
      return new NumberExpressionSyntax(
          new SyntaxToken(SyntaxKindUtils::NumberToken,
                          this->getCurrent()->getPosition(), "0", nullptr));
    }
  }
};